#include "database.h"

/// Conecta ao banco de dados Postgres
bool connectToDatabase ()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");   // QPSQL é o driver padrão para Postgres

    // Definir os parâmetros do banco de dados
    db.setDatabaseName("library");          // nome do banco
    db.setUserName("jansen");               // nome do usuário
    db.setPassword("jansen");               // senha
    db.setHostName("localhost");            // servidor
    db.setPort(5432);                       // porta

    if ( !db.open() )                   // Abrir o banco de dados
    {
        // Se ocorrer algum problema, informar ao usuário e retornar 'false'.
        QMessageBox::critical( 0, QObject::trUtf8("Erro ao abrir o Banco de Dados"),
                               db.lastError().text() );
        return false;
    }

    if ( db.tables().count() == 0 )
        createDatabaseTables();

    return true;
}


/// Cria as tabelas do banco de dados
void createDatabaseTables ()
{
    // lista de servidores de email
    QHash<int, QString> emailServers;
    emailServers.insert( 1, "@yahoo.com" );
    emailServers.insert( 2, "@aol.com" );
    emailServers.insert( 3, "@ig.com.br" );
    emailServers.insert( 4, "@uol.com.br" );

    // lista de nomes de leitores
    QStringList readerNames;
    readerNames << "Maria Pereira" << "João da Silva" << "Nelson Gomes" << "Luana Reis"
                << "Nicolau Cavalcante" << "Aline Martins" << "Juliana de Assis";

    // lista de categorias
    QStringList categoryLabels;
    categoryLabels << "teatro" << "poesia" << "mitologia" << "filosofia"
                   << "romance" << "ficção científica";

    // Criar a barra de progresso
    QProgressDialog progress;

    progress.setWindowModality( Qt::WindowModal );
    progress.setWindowTitle( QObject::trUtf8("Sistema Bibliotecário") );

    unsigned int max = readerNames.count() + categoryLabels.count() + 15;
    unsigned int loader = 1;

    // Definir valores mínimo e máximo para a barra de progresso
    progress.setMinimum( 0 );
    progress.setMaximum( max );

    progress.setLabelText( QObject::trUtf8("Criando o banco de dados...") );

    QSqlQuery query;

    // Limpar o banco de dados
    query.exec("DROP TABLE Readers");
    query.exec("DROP TABLE Categories CASCADE");
    query.exec("DROP TABLE Books");
    query.exec("DROP TABLE Borrowings");

    progress.setValue( loader++ );
    qApp->processEvents();


    // Criar tabelas
    query.exec( "CREATE TABLE Readers ("
                "id SERIAL PRIMARY KEY,"
                "name VARCHAR(50) NOT NULL,"
                "birthdate DATE NOT NULL,"
                "email VARCHAR(100) )" );
    progress.setValue( loader++ );
    qApp->processEvents();

    query.exec( "CREATE TABLE Categories ("
                "id SERIAL PRIMARY KEY,"
                "label VARCHAR(100) NOT NULL )" );
    progress.setValue( loader++ );
    qApp->processEvents();

    query.exec( "CREATE TABLE Books ("
                "id SERIAL PRIMARY KEY,"
                "title VARCHAR(100) NOT NULL,"
                "description VARCHAR(700),"
                "author VARCHAR(150) NOT NULL,"
                "id_category INTEGER,"
                "FOREIGN KEY (id_category) REFERENCES Categories(id) ON DELETE SET NULL )" );
    progress.setValue( loader++ );
    qApp->processEvents();

    query.exec( "CREATE TABLE Borrowings ("
                "id_book INTEGER,"
                "id_reader INTEGER,"
                "date DATE NOT NULL,"
                "FOREIGN KEY (id_book) REFERENCES Books(id) ONDELETE CASCADE,"
                "FOREIGN KEY (id_reader) REFERENCES Categories(id) ONDELETE CASCADE )" );
    progress.setValue( loader++ );
    qApp->processEvents();


    progress.setLabelText( QObject::trUtf8("Inserindo os dados...") );

    // Inserir leitores
    query.prepare( "INSERT INTO Readers(name, birthdate, email) VALUES (:name, :birthdate, :email)" );

    qDebug() << "Leitores:";
    foreach( QString name, readerNames )
    {
        query.bindValue( ":name", name );

        QDate date;
        date.setDate( 1970 + qrand() % 25, qrand() % 12 + 1, qrand() % 30 + 1 );
        query.bindValue( ":birthdate", date );

        QString email = name.toLower().replace(" ", ".") + emailServers[ qrand() % 4 + 1 ] ;
        query.bindValue( ":email", email );

        query.exec();

        qDebug() << name << " - " << date.toString("dd.MM.yyyy") << " - " << email;
        progress.setValue( loader++ );
    }


    // Inserir categorias
    query.prepare( "INSERT INTO Categories(label) VALUES (:label)" );

    qDebug() << endl << "Categorias:";
    foreach( QString label, categoryLabels )
    {
        query.bindValue( ":name", label );
        query.exec();

        qDebug() << label;
        progress.setValue( loader++ );
    }

    // Inserir livros
    query.exec("INSERT INTO Books(title, author, id_category) VALUES ('Ecce Homo', 'Friedrich Nietzsche', 4)");
    progress.setValue( loader++ );

    query.exec("INSERT INTO Books(title, author, id_category) VALUES ('Orgulho e Preconceito', 'Jane Austen', 6)");
    progress.setValue( loader++ );

    query.exec("INSERT INTO Books(title, author, id_category) VALUES ('A República', 'Platão', 4)");
    progress.setValue( loader++ );

    query.exec("INSERT INTO Books(title, author, id_category) VALUES ('Dom Casmurro', 'Machado de Assis', 6)");
    progress.setValue( loader++ );

    query.exec("INSERT INTO Books(title, author, id_category) VALUES ('Memórias Póstumas de Brás Cubas', 'Machado de Assis', 6)");
    progress.setValue( loader++ );

    query.exec("INSERT INTO Books(title, author, id_category) VALUES ('Romeu e Julieta', 'William Shakespeare', 6)");
    progress.setValue( loader++ );

    query.exec("INSERT INTO Books(title, author, id_category) VALUES ('Hamlet', 'William Shakespeare', 1)");
    progress.setValue( loader++ );

    query.exec("INSERT INTO Books(title, author, id_category) VALUES ('O Mercador de Veneza', 'William Shakespeare', 1)");
    progress.setValue( loader++ );

    query.exec("INSERT INTO Books(title, author, id_category) VALUES ('Frankenstein', 'Mary Shelley', 7)");
    progress.setValue( loader++ );

    query.exec("INSERT INTO Books(title, author, id_category) VALUES ('O Manifesto Comunista', 'Karl Marx; Friedrick Engels', 4)");

    // Concluir
    progress.setValue( progress.maximum() );
    qApp->processEvents();
}
