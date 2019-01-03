#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

QStringList UpdateListing(QString search);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void UpdateList(QString);

private slots:
    void on_Button_AddListing_clicked();

    void on_Button_OpenListing_clicked();

    void on_Button_MarkListing_clicked();

    void on_Button_DuplicateListing_clicked();

    void on_SearchBar_textChanged(const QString &arg1);

    void on_clearButton_clicked();

    void on_InventoryList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
