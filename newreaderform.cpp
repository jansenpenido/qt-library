#include "newreaderform.h"
#include "ui_newreaderform.h"

NewReaderForm::NewReaderForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewReaderForm)
{
    ui->setupUi(this);

    this->setWindowTitle( QObject::trUtf8("Novo Leitor") );

    model = new QSqlTableModel(this);
    model->setTable("readers");
    model->select();

    ui->birthdateEdit->setDisplayFormat("dd/MM/yyyy");
    ui->birthdateEdit->setCalendarPopup(true);
    ui->birthdateEdit->setMaximumDate( QDate::currentDate() );
}

NewReaderForm::~NewReaderForm()
{
    delete ui;
}

/// Cadastrar o leitor
void NewReaderForm::on_saveButton_clicked()
{
    int row = model->rowCount();

    model->insertRows( row, 1 );

    model->setData( model->index(row, READER_NAME), ui->nameEdit->text() );
    model->setData( model->index(row, READER_EMAIL), ui->emailEdit->text() );
    model->setData( model->index(row, READER_BIRTHDATE), ui->birthdateEdit->date() );

    if( model->submitAll() )
    {
        QMessageBox::information( this, QObject::trUtf8("Leitor Cadastrado"),
                                  QObject::trUtf8("Leitor cadastrado com sucesso!") );
    }

    this->accept();
}
