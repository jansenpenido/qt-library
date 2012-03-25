#include "newbookform.h"
#include "ui_newbookform.h"

NewBookForm::NewBookForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBookForm)
{
    ui->setupUi(this);

    this->setWindowTitle( QObject::trUtf8("Novo livro") );

    // Inicializar modelo
    model = new QSqlRelationalTableModel(this);
    model->setTable("books");
    model->setRelation( BOOK_CATEGORY, QSqlRelation("categories","id","label") );
    model->sort( BOOK_CATEGORY, Qt::AscendingOrder );
    model->select();

    // Inicializar box de categorias
    QSqlQuery query;
    if( query.exec("SELECT * FROM Categories ORDER BY id") )
    {
        while ( query.next() ) {
            ui->categoryBox->addItem( query.value(CATEGORY_LABEL).toString() );
        }
    }

//    QSqlTableModel *boxModel = model->relationModel(BOOK_CATEGORY);
//    boxModel->sort(BOOK_CATEGORY, Qt::AscendingOrder);
//    ui->categoryBox->setModel(boxModel);
//    ui->categoryBox->setModelColumn( boxModel->fieldIndex("label") );
}

NewBookForm::~NewBookForm()
{
    delete model;
    delete ui;
}

/// Salvar livro
void NewBookForm::on_saveButton_clicked()
{
    int row = model->rowCount();

    model->insertRows( row, 1 );

    model->setData( model->index(row, BOOK_TITLE), ui->titleEdit->text() );
    model->setData( model->index(row, BOOK_DESCRIPTION), ui->descriptionEdit->toPlainText() );
    model->setData( model->index(row, BOOK_AUTHOR), ui->authorEdit->text() );
    model->setData( model->index(row, BOOK_CATEGORY), ui->categoryBox->currentIndex() + 1 );
    model->setData( model->index(row, BOOK_AVAILABLE), true );

    if( model->submitAll() )
    {
        QMessageBox::information( this, QObject::trUtf8("Livro Cadastrado"),
                                  QObject::trUtf8("Livro cadastrado com sucesso!") );
    }

    this->accept();
}
