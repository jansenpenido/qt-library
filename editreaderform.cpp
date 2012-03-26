#include "editreaderform.h"
#include "ui_editreaderform.h"

EditReaderForm::EditReaderForm(QWidget *parent, const int id) :
    QDialog(parent),
    ui(new Ui::EditReaderForm)
{
    ui->setupUi(this);

    this->setWindowTitle( QObject::trUtf8("Editar dados do leitor") );

    this->initializeModel();
    this->loadReaderInfos(id);

    // Inicializar botões de navegação
    connect( ui->firstButton, SIGNAL( clicked() ), mapper, SLOT( toFirst() ) );
    connect( ui->nextButton, SIGNAL( clicked() ), mapper, SLOT( toNext() ) );
    connect( ui->previousButton, SIGNAL( clicked() ), mapper, SLOT( toPrevious() ) );
    connect( ui->lastButton, SIGNAL( clicked() ), mapper, SLOT( toLast() ) );
}

EditReaderForm::~EditReaderForm()
{
    delete mapper;
    delete model;
    delete ui;
}

void EditReaderForm::done(int result)
{
    mapper->submit();
    QDialog::done(result);
}

/// Inicializar modelo
void EditReaderForm::initializeModel()
{
    model = new QSqlTableModel(this);

    model->setTable("readers");
    model->sort( READER_NAME, Qt::AscendingOrder );
    model->select();
}

/// Carregar os dados dos leitores para o aplicativo
void EditReaderForm::loadReaderInfos(int id)
{
    mapper = new QDataWidgetMapper(this);

    mapper->setModel( model );
    mapper->setSubmitPolicy( QDataWidgetMapper::AutoSubmit );

    mapper->addMapping( ui->nameEdit, READER_NAME );
    mapper->addMapping( ui->emailEdit, READER_EMAIL );
    mapper->addMapping( ui->birthdateEdit, READER_BIRTHDATE );

    if ( id != -1 )
    {
        for ( int row = 0; row < model->rowCount(); ++row )
        {
            QSqlRecord record = model->record(row);

            if ( record.value(READER_ID).toInt() == id ) {
                mapper->setCurrentIndex(row);
                break;
            }
        }
    } else {
        mapper->toFirst();
    }
}
