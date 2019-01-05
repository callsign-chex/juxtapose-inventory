#include "inventoryfileeditor.h"
#include "ui_inventoryfileeditor.h"
#include "qdebug.h"

InventoryFileEditor::InventoryFileEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InventoryFileEditor)
{
    ui->setupUi(this);
}

InventoryFileEditor::~InventoryFileEditor()
{
    delete ui;
}

void InventoryFileEditor::PopulateInventoryFile(InventoryFile inventoryFile) {
    this->setWindowTitle("Inventory Listing Editor - #" + inventoryFile.itemid);

    // gets information from the InventoryFile, pushes it to the UI
    ui->titleLineEdit->setText(inventoryFile.title);
    ui->itemNumberLabel->setText("#" + inventoryFile.itemid);
    ui->brandLineEdit->setText(inventoryFile.brand);
    ui->sizeLineEdit->setText(inventoryFile.size);
    ui->colorLineEdit->setText(inventoryFile.color);
    ui->costLineEdit->setText(inventoryFile.cost);
    ui->descriptionLineEdit->setText(inventoryFile.desc);
    ui->locationLineEdit->setText(inventoryFile.location);
    if (inventoryFile.sold != "nil") {
        ui->soldForLabel->setText("Sold for " + inventoryFile.sold);
    }
    qDebug() << "catagory:" << inventoryFile.catagory << " class:" << inventoryFile.classification;
    switch (inventoryFile.classification) {
    case 0:
        ui->mensRadioButton->setChecked(true);
        break;
    case 1:
        ui->womenRadioButtons->setChecked(true);
        break;
    case 2:
        ui->kidsRadioButton->setChecked(true);
        break;
    default:
        break;
    }

    switch (inventoryFile.catagory) {
    case 0:
        ui->pantsRadioButton->setChecked(true);
        break;
    case 1:
        ui->shortsRadioButton->setChecked(true);
        break;
    case 2:
        ui->skirtsRadioButton->setChecked(true);
        break;
    case 3:
        ui->dressesRadioButton->setChecked(true);
        break;
    case 4:
        ui->topRadioButton->setChecked(true);
        break;
    case 5:
        ui->outerwearRadioButton->setChecked(true);
        break;
    case 6:
        ui->underwearRadioButton->setChecked(true);
        break;
    case 7:
        ui->accessoriesRadioButton->setChecked(true);
        break;
    case 8:
        ui->bagsRadioButton->setChecked(true);
        break;
    case 9:
        ui->shoesRadioButton->setChecked(true);
        break;
    case 10:
        ui->makeupRadioButton->setChecked(true);
    case 11:
        ui->swimwearRadioButton->setChecked(true);
    default:
        break;
    }
}

void InventoryFileEditor::on_cancelButton_clicked()
{
    this->close(); // closes the window without saving
}

void InventoryFileEditor::on_saveAndCloseButton_clicked()
{
    // creates an InventoryFile from the UI elements.
    // There's probably a much better way to do this, but I did it this way.
    InventoryFile inventoryFile;
    inventoryFile.title = ui->titleLineEdit->text();
    inventoryFile.itemid = ui->itemNumberLabel->text().remove(0, 1);
    inventoryFile.brand = ui->brandLineEdit->text();
    inventoryFile.size = ui->sizeLineEdit->text();
    inventoryFile.color = ui->colorLineEdit->text();
    inventoryFile.cost = ui->costLineEdit->text();
    inventoryFile.desc = ui->descriptionLineEdit->text();
    inventoryFile.location = ui->locationLineEdit->text();
    if (ui->soldForLabel->text() != "")
        inventoryFile.sold = ui->soldForLabel->text().remove(0, 9);
    else
        inventoryFile.sold = "nil";
    if (ui->mensRadioButton->isChecked()) {
        inventoryFile.classification = 0;
    } else if (ui->womenRadioButtons->isChecked()) {
        inventoryFile.classification = 1;
    } else if (ui->kidsRadioButton->isChecked()) {
        inventoryFile.classification = 2;
    }

    if (ui->pantsRadioButton->isChecked()) {
        inventoryFile.catagory = 0;
    } else if (ui->shortsRadioButton->isChecked()) {
        inventoryFile.catagory = 1;
    } else if (ui->skirtsRadioButton->isChecked()) {
        inventoryFile.catagory = 2;
    } else if (ui->dressesRadioButton->isChecked()) {
        inventoryFile.catagory = 3;
    } else if (ui->topRadioButton->isChecked()) {
        inventoryFile.catagory = 4;
    } else if (ui->outerwearRadioButton->isChecked()) {
        inventoryFile.catagory = 5;
    } else if (ui->underwearRadioButton->isChecked()) {
        inventoryFile.catagory = 6;
    } else if (ui->accessoriesRadioButton->isChecked()) {
        inventoryFile.catagory = 7;
    } else if (ui->bagsRadioButton->isChecked()) {
        inventoryFile.catagory = 8;
    } else if (ui->shoesRadioButton->isChecked()) {
        inventoryFile.catagory = 9;
    } else if (ui->makeupRadioButton->isChecked()) {
        inventoryFile.catagory = 10;
    } else if (ui->swimwearRadioButton->isChecked()) {
        inventoryFile.catagory = 11;
    }

    // saves the listing as the appropriately named .xml file, and closes if it succeeds.
    // TODO: Make it do something when it doesn't succeed.
    bool success = SaveInventoryListing(inventoryFile, "listings/" + inventoryFile.itemid + ".xml");
    if (success) {
        this->close();
    }
}
