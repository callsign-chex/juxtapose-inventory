#ifndef MAIN_H
#define MAIN_H

#include <QApplication>
#include <inventoryfile.h>

bool SaveInventoryListing(InventoryFile, QString);
void OpenInventoryListingWindow(QString);
InventoryFile GetInventoryListing(QString);
void OpenNewInventoryListingWindow();
void OpenDuplicatedInventoryListingWindow(QString);
void MarkAsSold(QString, QString);

#endif // MAIN_H
