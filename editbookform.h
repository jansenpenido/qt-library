#ifndef EDITBOOKFORM_H
#define EDITBOOKFORM_H

#include "database.h"
#include <QDialog>

namespace Ui {
    class EditBookForm;
}

class EditBookForm : public QDialog
{
    Q_OBJECT

public:
    explicit EditBookForm(QWidget *parent = 0, const int id = -1);
    ~EditBookForm();

protected:
    void done(int result);

    void initializeModel();
    void loadBookInfos(int id);

private slots:

private:
    Ui::EditBookForm *ui;

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
};

#endif // EDITBOOKFORM_H
