#ifndef INVENTORYFILE_H
#define INVENTORYFILE_H

#include "QString"

class InventoryFile
{
public:
    InventoryFile();
    QString title;
    QString itemid;
    int classification;
    int catagory;
    QString brand;
    QString size;
    QString color;
    QString cost;
    QString desc;
    QString location;
    QString sold;
};

#endif // INVENTORYFILE_H
