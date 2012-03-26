#include "newborrowingform.h"
#include "ui_newborrowingform.h"

NewBorrowingForm::NewBorrowingForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBorrowingForm)
{
    ui->setupUi(this);

    this->setWindowTitle( QObject::trUtf8("Novo Empréstimo") );

    model = new QSqlRelationalTableModel(this);

    // Inicializar modelo da tabela Empréstimos
    model->setTable("borrowings");
    model->setRelation( BORROWING_BOOK, QSqlRelation("books", "id", "title") );
    model->setRelation( BORROWING_READER, QSqlRelation("readers", "id", "name") );
    model->select();

    // Inicializar editor da data de devolução
    ui->returnDateEdit->setDisplayFormat("dd/MM/yyyy");
    ui->returnDateEdit->setCalendarPopup(true);
    ui->returnDateEdit->setDate( QDate::currentDate().addDays(7) );

    this->bookModel = model->relationModel(BORROWING_BOOK);
    this->bookModel->sort( BORROWING_BOOK, Qt::AscendingOrder );
    ui->bookBox->setModel(bookModel);
    ui->bookBox->setModelColumn( bookModel->fieldIndex("title") );

    this->readerModel = model->relationModel(BORROWING_READER);
    this->readerModel->sort( BORROWING_READER,Qt::AscendingOrder );
    ui->readerBox->setModel(readerModel);
    ui->readerBox->setModelColumn( readerModel->fieldIndex("name") );
}

NewBorrowingForm::~NewBorrowingForm()
{
    delete readerModel;
    delete bookModel;
    delete model;
    delete ui;
}

/// Registrar empréstimo
void NewBorrowingForm::on_saveButton_clicked()
{
    int row = model->rowCount();

    QModelIndex idBookModel =  bookModel->index( ui->bookBox->currentIndex(), 0 );
    int bookId = idBookModel.data(Qt::DisplayRole).toInt();

    QModelIndex idReaderModel = readerModel->index( ui->readerBox->currentIndex(), 0 );
    int readerId = idReaderModel.data(Qt::DisplayRole).toInt();

    model->insertRows( row, 1 );

    model->setData( model->index(row, BORROWING_BOOK), bookId );
    model->setData( model->index(row, BORROWING_READER), readerId );
    model->setData( model->index(row, BORROWING_LENDING_DATE), QDate::currentDate() );
    model->setData( model->index(row, BORROWING_LENDING_TIME), QTime::currentTime() );
    model->setData( model->index(row, BORROWING_RETURN_DATE), ui->returnDateEdit->date() );

    if( model->submitAll() )
    {
        QMessageBox::information( this, QObject::trUtf8("Empréstimo registrado"),
                                  QObject::trUtf8("Empréstimo registrado com sucesso!") );
    }

    this->accept();
}
