#ifndef NEWBORROWINGFORM_H
#define NEWBORROWINGFORM_H

#include "database.h"
#include <QDialog>

namespace Ui {
    class NewBorrowingForm;
}

class NewBorrowingForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewBorrowingForm(QWidget *parent = 0);
    ~NewBorrowingForm();

private slots:
    void on_saveButton_clicked();

private:
    Ui::NewBorrowingForm *ui;

    QSqlTableModel *bookModel;
    QSqlTableModel *readerModel;
    QSqlRelationalTableModel *model;
};

#endif // NEWBORROWINGFORM_H
