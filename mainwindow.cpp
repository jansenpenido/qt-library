#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle( QObject::trUtf8("Sistema Bibliotecário") );
    ui->searchBookEdit->setText("Pesquisar livro...");

    this->initializeComboBox();

    this->initializeBookModel();
    this->initializeBookView();

    this->initializeReadersModel();
    this->initializeReadersView();

    this->initializeBorrowingsModel();
    this->initializeBorrowingsView();
}

MainWindow::~MainWindow()
{
    delete borrowingsModel;
    delete readersModel;
    delete booksModel;
    delete ui;
}

/// Inicializar valores da caixa 'categorias'
void MainWindow::initializeComboBox()
{
    QSqlQuery query;

    ui->categoryBox->addItem("<Todos>");

    if( query.exec("SELECT * FROM Categories ORDER BY id") )
    {
        while ( query.next() ) {
            ui->categoryBox->addItem( query.value(CATEGORY_LABEL).toString() );
        }
    }
}

/// Inicializa o modelo da tabela Livros
void MainWindow::initializeBookModel()
{
    booksModel = new QSqlRelationalTableModel(this);

    booksModel->setTable("books");
    booksModel->setRelation( BOOK_CATEGORY, QSqlRelation("categories","id","label") );

    booksModel->setHeaderData( BOOK_TITLE, Qt::Horizontal, QObject::trUtf8("Título") );
    booksModel->setHeaderData( BOOK_AUTHOR, Qt::Horizontal, QObject::trUtf8("Autor") );
    booksModel->setHeaderData( BOOK_CATEGORY, Qt::Horizontal, QObject::trUtf8("Categoria") );
    booksModel->setHeaderData( BOOK_AVAILABLE, Qt::Horizontal, QObject::trUtf8("Disponibilidade") );

    booksModel->sort( BOOK_TITLE, Qt::AscendingOrder );
    booksModel->select();
}

/// Inicializa a visão da tabela Livros
void MainWindow::initializeBookView()
{
    ui->booksView->setModel( booksModel );

    ui->booksView->setColumnHidden( BOOK_ID, true );
    ui->booksView->setColumnHidden( BOOK_DESCRIPTION, true );
    ui->booksView->resizeColumnsToContents();

    ui->booksView->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->booksView->setEditTriggers( QAbstractItemView::NoEditTriggers );
    ui->booksView->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->booksView->horizontalHeader()->setStretchLastSection(true);             // Estica a última coluna da tabela.

    ui->booksView->setItemDelegate( new QSqlRelationalDelegate(this) );         // Habilita combobox para FK...
    ui->booksView->setItemDelegate( new AvailableDelegate(BOOK_AVAILABLE) );    // e o texto no campo 'disponível'.

    // Ao aplicar um duplo clique em um livro da tabela, abrir o diálogo "Editar Livro".
    connect( ui->booksView, SIGNAL( doubleClicked(QModelIndex) ),
             this, SLOT( on_actionEditBooks_triggered() ) );
}

/// Inicializa o modelo da tabela Leitores
void MainWindow::initializeReadersModel()
{
    readersModel = new QSqlTableModel(this);

    readersModel->setTable("readers");

    readersModel->setHeaderData( READER_NAME, Qt::Horizontal, QObject::trUtf8("Nome") );
    readersModel->setHeaderData( READER_EMAIL, Qt::Horizontal, QObject::trUtf8("E-mail") );
    readersModel->setHeaderData( READER_BIRTHDATE, Qt::Horizontal, QObject::trUtf8("Data de Nascimento") );

    readersModel->sort( READER_NAME, Qt::AscendingOrder );
    readersModel->select();
}

/// Inicializa a visão da tabela Leitores
void MainWindow::initializeReadersView()
{
    ui->readersView->setModel( readersModel );

    ui->readersView->setColumnHidden( READER_ID, true );
    ui->readersView->resizeColumnsToContents();

    ui->readersView->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->readersView->setEditTriggers( QAbstractItemView::NoEditTriggers );
    ui->readersView->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->readersView->horizontalHeader()->setStretchLastSection(true);

    // Ao aplicar um duplo clique em um leitor da tabela, abrir o diálogo "Editar Leitor".
    connect( ui->readersView, SIGNAL( doubleClicked(QModelIndex) ),
             this, SLOT( on_actionEditReaders_triggered() ) );
}

/// Inicializar modelo da tabela Empréstimos
void MainWindow::initializeBorrowingsModel()
{
    borrowingsModel = new QSqlRelationalTableModel(this);

    borrowingsModel->setTable("borrowings");
    borrowingsModel->setRelation( BORROWING_BOOK, QSqlRelation("books", "id", "title") );
    borrowingsModel->setRelation( BORROWING_READER, QSqlRelation("readers", "id", "name") );

    borrowingsModel->setHeaderData( BORROWING_BOOK, Qt::Horizontal, QObject::trUtf8("Livro") );
    borrowingsModel->setHeaderData( BORROWING_READER, Qt::Horizontal, QObject::trUtf8("Leitor") );
    borrowingsModel->setHeaderData( BORROWING_LENDING_DATE, Qt::Horizontal, QObject::trUtf8("Data de Empréstimo") );
    borrowingsModel->setHeaderData( BORROWING_LENDING_TIME, Qt::Horizontal, QObject::trUtf8("Hora do Empréstimo") );
    borrowingsModel->setHeaderData( BORROWING_RETURN_DATE, Qt::Horizontal, QObject::trUtf8("Data de Entrega") );

    borrowingsModel->sort( BORROWING_LENDING_DATE, Qt::DescendingOrder );
    borrowingsModel->select();
}

/// Inicializar visão da tabela Empréstimos
void MainWindow::initializeBorrowingsView()
{
    ui->borrowingsView->setModel( borrowingsModel );

    ui->borrowingsView->resizeColumnsToContents();

    ui->borrowingsView->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->borrowingsView->setEditTriggers( QAbstractItemView::NoEditTriggers );
    ui->borrowingsView->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->borrowingsView->horizontalHeader()->setStretchLastSection(true);
}

/// Exibir somente livros disponíveis
void MainWindow::on_availableOnlyBox_clicked()
{
    if ( ui->availableOnlyBox->isChecked() ) {
        booksModel->setFilter("available = 't'");
        booksModel->select();
    } else {
        booksModel->setFilter("");
        booksModel->select();
    }
}

/// Pesquisar livro
void MainWindow::on_searchButton_clicked()
{
    QString str = ui->searchBookEdit->text();         // Guarda a string do campo de busca.

    if( str.isEmpty() ) {                       // Se o campo está vazio:
        booksModel->setFilter("");              // deixar o filtro vazio,
        booksModel->select();                   // exibindo, assim, todos os livros
    } else {
        QString condition = "title ILIKE '%" + str + "%'";          // 'ILIKE' faz uma busca case insensitive

        booksModel->setFilter(condition);       // filtrar...
        booksModel->select();                   // e exibir as linhas na tabela.
    }
}

/// Selecionar categoria
void MainWindow::on_categoryBox_activated(int index)
{
    if ( index == 0 ) {
        booksModel->setFilter("");
        booksModel->select();
    } else {
        booksModel->setFilter("id_category = '" + QString::number(index) + "'");
        booksModel->select();
    }
}

/// Novo livro
void MainWindow::on_actionNewBook_triggered()
{
    NewBookForm f(this);
    f.exec();

    booksModel->select();
}

/// Editar livro
void MainWindow::on_actionEditBooks_triggered()
{
    int bookId = -1;
    QModelIndex index = ui->booksView->currentIndex();

    if( index.isValid() )
    {
        QSqlRecord record = booksModel->record( index.row() );
        bookId = record.value(BOOK_ID).toInt();
    }

    EditBookForm f( this, bookId );
    f.exec();

    booksModel->select();
}

/// Novo leitor
void MainWindow::on_actionNewReader_triggered()
{
    NewReaderForm f(this);
    f.exec();

    readersModel->select();
}

/// Editar leitor
void MainWindow::on_actionEditReaders_triggered()
{
    int readerId = -1;
    QModelIndex index = ui->readersView->currentIndex();

    if( index.isValid() )
    {
        QSqlRecord record = readersModel->record( index.row() );
        readerId = record.value(READER_ID).toInt();
    }

    EditReaderForm f(this, readerId);
    f.exec();

    readersModel->select();
}
