#ifndef NEWBOOKFORM_H
#define NEWBOOKFORM_H

#include "database.h"
#include <QDialog>

namespace Ui {
    class NewBookForm;
}

class NewBookForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewBookForm(QWidget *parent = 0);
    ~NewBookForm();

private slots:
    void on_saveButton_clicked();

private:
    Ui::NewBookForm *ui;

    QSqlRelationalTableModel *model;
};

#endif // NEWBOOKFORM_H
