#include "inventoryfile.h"
#include "QString"

InventoryFile::InventoryFile(){
    title = "";
    itemid = "";
    classification = 1;
    catagory = 0;
    brand = "";
    size = "";
    color = "";
    cost = "";
    desc = "";
    location = "";
    sold = "nil";
}

static QString title;
static QString itemid;
static int classification;
static int catagory;
static QString brand;
static QString size;
static QString color;
static QString cost;
static QString desc;
static QString location;
static QString sold;
