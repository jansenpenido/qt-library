#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle( QObject::trUtf8("Sistema Bibliotecário") );

    this->initializeComboBox();

    this->initializeBookModel();
    this->initializeBookView();

    ui->searchBookEdit->setText("Pesquisar livro...");

    ui->booksView->setModel(booksModel);
}

MainWindow::~MainWindow()
{
    delete booksModel;
    delete ui;
}

/// Inicializar o modelo do banco de dados usado pelo tableView
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

/// Inicializar o tableView
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

///
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

///
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

///
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
