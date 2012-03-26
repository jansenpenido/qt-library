#ifndef EDITREADERFORM_H
#define EDITREADERFORM_H

#include "database.h"
#include <QDialog>

namespace Ui {
    class EditReaderForm;
}

class EditReaderForm : public QDialog
{
    Q_OBJECT

public:
    explicit EditReaderForm(QWidget *parent = 0, const int id = -1);
    ~EditReaderForm();

protected:
    void done(int result);

    void initializeModel();
    void loadReaderInfos(int id);

private:
    Ui::EditReaderForm *ui;

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;
};

#endif // EDITREADERFORM_H
