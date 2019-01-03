#include "mainwindow.h"
#include "inventoryfileeditor.h"
#include <QApplication>
#include "QDir"
#include "QDebug"
#include "QXmlStreamReader"
#include "QXmlStreamWriter"
#include "inventoryfile.h"
#include "inventoryfileeditor.h"
#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

// this function gets the current counter from the counter file, so it can make a new item ID that's not been used before.
// Then it increments it so that the next time a new number is needed, it has a new one.
int GetAndIncrementItemCounter() {
    int itemNumber = -1; // sets a default of -1, just to make sure no files are overwritten if something goes wrong.
                         // There's probably a better way to do this.

    QFile counterFile("counter");

    if (!counterFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read counter file";
    } else {
        QXmlStreamReader reader;
        reader.setDevice(&counterFile);

        if (reader.readNextStartElement()) {
            if (reader.name() == "inventorycounter") {
                while (reader.readNextStartElement()) {
                    if (reader.name() == "counter") {
                        itemNumber = reader.readElementText().toInt();
                    }
                }
            }
        }
        counterFile.close();
    }

    if (!counterFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Cannot write the file" << counterFile.errorString();
    } else {
        QXmlStreamWriter writer;
        writer.setDevice(&counterFile);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("inventorycounter");
        writer.writeStartElement("counter");
        if (itemNumber != -1)
            writer.writeCharacters(QString::number(itemNumber + 1));
        else
            qDebug() << "failed to read counter file!";
        writer.writeEndElement();
        writer.writeEndElement(); // inventorycounter
        writer.writeEndDocument();
        counterFile.close();
    }

    return  itemNumber;
}

// Gets the InventoryFile from a .xml file
InventoryFile GetInventoryListing(QString listingFileName) {
    QFile listingFile(listingFileName);

    InventoryFile inventoryFile;
    if(!listingFile.open(QFile::ReadOnly | QFile::Text)) { // if it can't open the file
        qDebug() << "Cannot read the file" << listingFile.errorString(); // throw an error
    } else {
        QXmlStreamReader reader; // create an xml reader
        reader.setDevice(&listingFile); // open the file with the xml reader

        if (reader.readNextStartElement()) { // start reading the file
            if (reader.name() == "inventorylisting") { // when it finds the inventorylisting root attribute
                while(reader.readNextStartElement()) { // read all of the attributes beneath it
                    if (reader.name() == "title") {
                        inventoryFile.title = reader.readElementText();
                    } else if (reader.name() == "itemid") {
                        inventoryFile.itemid = reader.readElementText();
                    } else if (reader.name() == "classification") {
                        inventoryFile.classification = reader.readElementText().toInt();
                    } else if (reader.name() == "catagory") {
                        inventoryFile.catagory = reader.readElementText().toInt();
                    } else if (reader.name() == "brand") {
                        inventoryFile.brand = reader.readElementText();
                    } else if (reader.name() == "size") {
                        inventoryFile.size = reader.readElementText();
                    } else if (reader.name() == "color") {
                        inventoryFile.color = reader.readElementText();
                    } else if (reader.name() == "cost") {
                        inventoryFile.cost = reader.readElementText();
                    } else if (reader.name() == "desc") {
                        inventoryFile.desc = reader.readElementText();
                    } else if (reader.name() == "location") {
                        inventoryFile.location = reader.readElementText();
                    } else if (reader.name() == "sold") {
                        inventoryFile.sold = reader.readElementText();
                    } else
                        reader.skipCurrentElement();
                }
            } else {
                reader.raiseError(QObject::tr("Incorrect file"));
            }
        }
    }

    return inventoryFile;
}

// Saves a .xml file of an InventoryFile
bool SaveInventoryListing(InventoryFile inventoryFile, QString filename) {
    QFile outputFile(filename);
    if (!outputFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Cannot write the file" << outputFile.errorString();
        return false;
    } else {
        QXmlStreamWriter writer(&outputFile);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("inventorylisting");
        writer.writeStartElement("title");
        writer.writeCharacters(inventoryFile.title);
        writer.writeEndElement();
        writer.writeStartElement("itemid");
        writer.writeCharacters(inventoryFile.itemid);
        writer.writeEndElement();
        writer.writeStartElement("classification");
        writer.writeCharacters(QString::number(inventoryFile.classification));
        writer.writeEndElement();
        writer.writeStartElement("catagory");
        writer.writeCharacters(QString::number(inventoryFile.catagory));
        writer.writeEndElement();
        writer.writeStartElement("brand");
        writer.writeCharacters(inventoryFile.brand);
        writer.writeEndElement();
        writer.writeStartElement("size");
        writer.writeCharacters(inventoryFile.size);
        writer.writeEndElement();
        writer.writeStartElement("color");
        writer.writeCharacters(inventoryFile.color);
        writer.writeEndElement();
        writer.writeStartElement("cost");
        writer.writeCharacters(inventoryFile.cost);
        writer.writeEndElement();
        writer.writeStartElement("desc");
        writer.writeCharacters(inventoryFile.desc);
        writer.writeEndElement();
        writer.writeStartElement("location");
        writer.writeCharacters(inventoryFile.location);
        writer.writeEndElement();
        writer.writeStartElement("sold");
        writer.writeCharacters(inventoryFile.sold);
        writer.writeEndElement();
        writer.writeEndElement(); // inventorylisting
        writer.writeEndDocument();
        outputFile.close();
        return true;
    }
}

// opens the editor for a listing
void OpenInventoryListingWindow(QString listingNumber) {
    InventoryFileEditor editor;

    editor.PopulateInventoryFile(GetInventoryListing("listings/" + listingNumber + ".xml"));
    editor.exec();
}

// opens the editor for a new listing
void OpenNewInventoryListingWindow() {
    InventoryFile inventoryFile;
    inventoryFile.itemid = QString::number(GetAndIncrementItemCounter());

    InventoryFileEditor editor;

    editor.PopulateInventoryFile(inventoryFile);
    editor.exec();
}

// opens the editor for a duplicated listing
void OpenDuplicatedInventoryListingWindow(QString filename) {
    InventoryFileEditor editor;

    InventoryFile inventoryFile = GetInventoryListing("listings/" + filename + ".xml");
    inventoryFile.itemid = QString::number(GetAndIncrementItemCounter());
    inventoryFile.sold = "nil";
    editor.PopulateInventoryFile(inventoryFile);
    editor.exec();
}

// sets the sold price attribute in the listing file
void MarkAsSold(QString filename, QString soldForPrice) {
    InventoryFile inventoryFile = GetInventoryListing("listings/" + filename + ".xml");
    inventoryFile.sold = soldForPrice;
    SaveInventoryListing(inventoryFile, "listings/" + filename + ".xml");
}

// updates the list of files for the main screen
QStringList UpdateListing(QString search) {
    QStringList itemList; // stores a list of items found

    QString directoryString = "listings"; // sets the directory to a relative dir
    QDir directory(directoryString); // gets the QDir object for the directory
    QStringList list = directory.entryList(QStringList(), QDir::Files); //gets a list of files in the directory
    foreach(QString filename, list) { // sorts through the filenames
        QFile listingFile(directoryString + "/" + filename); // open the current file

        if(!listingFile.open(QFile::ReadOnly | QFile::Text)) { // if it can't open the file
            qDebug() << "Cannot read the file" << listingFile.errorString(); // throw an error
        } else { // otherwise
            InventoryFile inventoryFile = GetInventoryListing(listingFile.fileName());

            QString itemlistingFull = "#" + inventoryFile.itemid + "_" + inventoryFile.title;

            if (inventoryFile.sold != "nil") {
                itemlistingFull = itemlistingFull + " [Sold for " + inventoryFile.sold + "]";
            }

            if (itemlistingFull.toLower().contains(search)) {
                itemList << itemlistingFull;
            }
        }
    }

    return itemList;
}
