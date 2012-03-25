#include "editbookform.h"
#include "ui_editbookform.h"

EditBookForm::EditBookForm(QWidget *parent, const int id) :
    QDialog(parent),
    ui(new Ui::EditBookForm)
{
    ui->setupUi(this);

    this->initializeModel();

    QSqlTableModel *boxModel = model->relationModel(BOOK_CATEGORY);
    ui->categoryBox->setModel(boxModel);
    ui->categoryBox->setModelColumn( boxModel->fieldIndex("label") );

    this->loadBookInfos( id );

    connect( ui->firstButton, SIGNAL( clicked() ), mapper, SLOT( toFirst() ) );
    connect( ui->nextButton, SIGNAL( clicked() ), mapper, SLOT( toNext() ) );
    connect( ui->previousButton, SIGNAL( clicked() ), mapper, SLOT( toPrevious() ) );
    connect( ui->lastButton, SIGNAL( clicked() ), mapper, SLOT( toLast() ) );

    this->setWindowTitle( QObject::trUtf8("Editar livro") );
}

EditBookForm::~EditBookForm()
{
    delete mapper;
    delete model;
    delete ui;
}

void EditBookForm::done(int result)
{
    mapper->submit();
    QDialog::done(result);
}

 /// Inicializar o modelo do banco de dados usado pelo tableView
void EditBookForm::initializeModel()
{
     model = new QSqlRelationalTableModel(this);

     model->setTable("Books");
     model->setRelation( BOOK_CATEGORY, QSqlRelation("categories","id","label") );

     model->sort( BOOK_TITLE, Qt::AscendingOrder );
     model->select();
}


/// Carregar dados do livro no formulário
void EditBookForm::loadBookInfos( int id )
{
    mapper = new QDataWidgetMapper(this);
    mapper->setModel( model );

    mapper->setSubmitPolicy( QDataWidgetMapper::AutoSubmit );
    mapper->setItemDelegate( new QSqlRelationalDelegate(this) );

    mapper->addMapping( ui->titleEdit, BOOK_TITLE );
    mapper->addMapping( ui->authorEdit, BOOK_AUTHOR );
    mapper->addMapping( ui->categoryBox, BOOK_CATEGORY );
    mapper->addMapping( ui->descriptionEdit, BOOK_DESCRIPTION );

    if ( id != -1 )
    {
        for ( int row = 0; row < model->rowCount(); ++row )
        {
            QSqlRecord record = model->record(row);

            if ( record.value(BOOK_ID).toInt() == id ) {
                mapper->setCurrentIndex(row);
                break;
            }
        }
    } else {
        mapper->toFirst();
    }
}
