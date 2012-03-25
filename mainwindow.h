#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"
#include "availabledelegate.h"
#include "newbookform.h"
#include "editbookform.h"
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initializeComboBox();

    void initializeBookModel();
    void initializeBookView();

private slots:
    void on_availableOnlyBox_clicked();

    void on_searchButton_clicked();

    void on_categoryBox_activated(int index);

    void on_actionEditBooks_triggered();

    void on_actionNewBook_triggered();

private:
    Ui::MainWindow *ui;

    QSqlRelationalTableModel *booksModel;
};

#endif // MAINWINDOW_H
