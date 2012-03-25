#ifndef NEWREADERFORM_H
#define NEWREADERFORM_H

#include "database.h"
#include <QDialog>

namespace Ui {
    class NewReaderForm;
}

class NewReaderForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewReaderForm(QWidget *parent = 0);
    ~NewReaderForm();

private slots:
    void on_saveButton_clicked();

private:
    Ui::NewReaderForm *ui;
    QSqlTableModel *model;
};

#endif // NEWREADERFORM_H
