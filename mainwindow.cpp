#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.h"
#include "QDebug"
#include "QInputDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // gets a list of inventory listings for the main screen list
    UpdateList("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// grab the list of files and list them
void MainWindow::UpdateList(QString search) {
    ui->InventoryList->clear();
    QStringList listOfItems = UpdateListing(search);
    foreach (QString listing, listOfItems) {
        ui->InventoryList->addItem(listing);
    }
}

// when addlisting is clicked, make a new listing
void MainWindow::on_Button_AddListing_clicked()
{
    OpenNewInventoryListingWindow();
    UpdateList(ui->SearchBar->text());
    ui->SearchBar->clear();
}

// not used, but I'm lazy
// clearly not too lazy to write a comment though
void MainWindow::on_Button_OpenListing_clicked()
{

}

// mark a listing as sold
void MainWindow::on_Button_MarkListing_clicked()
{
    // open a window to get the sold-for amount
    QString text = ui->InventoryList->currentItem()->text();
    bool ok;
    QString soldForAmount = QInputDialog::getText(this, tr("Marking Item As Sold"),
                                                  tr("Sold for:"), QLineEdit::Normal,
                                                  tr(""), &ok);
    // if "ok" is clicked, set the file to sold and record the amount.
    if (ok) { // probably a better way to do this, but I didn't know of one at the time.
        bool hasHitHashtag = false; // gets the listing number by extracting it from the listing
        QString filename = "";
        foreach(QChar character, text) {
            if (hasHitHashtag && character != "_") {
                filename = filename + character;
            } else if (!hasHitHashtag && character == "#") {
                hasHitHashtag = true;
            } else if (hasHitHashtag && character == "_") {
                MarkAsSold(filename, soldForAmount); // marks the file as sold
                UpdateList(ui->SearchBar->text());
                return;
            }
        }
    }

    UpdateList(ui->SearchBar->text());
}

void MainWindow::on_Button_DuplicateListing_clicked()
{
    QString text = ui->InventoryList->currentItem()->text(); // getting the listing number from the list again
    bool hasHitHashtag = false;
    QString filename = "";
    foreach(QChar character, text) {
        if (hasHitHashtag && character != "_") {
            filename = filename + character;
        } else if (!hasHitHashtag && character == "#") {
            hasHitHashtag = true;
        } else if (hasHitHashtag && character == "_") {
            OpenDuplicatedInventoryListingWindow(filename);
            return;
        }
    }
    UpdateList(ui->SearchBar->text());
}

// When the searchbar is typed in, filter the list
void MainWindow::on_SearchBar_textChanged(const QString &arg1)
{
    UpdateList(arg1);
}

// clear the search bar
void MainWindow::on_clearButton_clicked()
{
    ui->SearchBar->clear();
}

// open a file when it's double clicked on
void MainWindow::on_InventoryList_itemDoubleClicked(QListWidgetItem *item)
{
    QString text = item->text();
    bool hasHitHashtag = false;
    QString filename = ""; // aaaaa this seems like bad code in hindsight but it's just *everywhere* and I don't wanna fix it now
    foreach(QChar character, text) {
        if (hasHitHashtag && character != "_") {
            filename = filename + character;
        } else if (!hasHitHashtag && character == "#") {
            hasHitHashtag = true;
        } else if (hasHitHashtag && character == "_") {
            OpenInventoryListingWindow(filename);
            return;
        }
    }
}
