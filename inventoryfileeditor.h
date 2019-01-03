#ifndef INVENTORYFILEEDITOR_H
#define INVENTORYFILEEDITOR_H

#include <QDialog>
#include "inventoryfile.h"
#include "main.h"

namespace Ui {
class InventoryFileEditor;
}

class InventoryFileEditor : public QDialog
{
    Q_OBJECT

public:
    explicit InventoryFileEditor(QWidget *parent = nullptr);
    ~InventoryFileEditor();
    void PopulateInventoryFile(InventoryFile inventoryFile);

private slots:
    void on_cancelButton_clicked();

    void on_saveAndCloseButton_clicked();

private:
    Ui::InventoryFileEditor *ui;
};


#endif // INVENTORYFILEEDITOR_H
