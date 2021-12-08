#include "properties_widget.h"

#include <QDebug>
#include <QFile>

PropertiesWidget::PropertiesWidget(QWidget* parent) : QTreeView(parent) {
    QStandardItemModel* model = new QStandardItemModel(0, 1);

    for (const auto& property: kPropertyConfigFileNames) {
        property_to_item_[property.first] = new PropertiesItem(property.second);
        model->appendRow(property_to_item_[property.first]);
    }

    model->setHorizontalHeaderItem(0, new QStandardItem("Параметр"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Значение"));

    setModel(model);
    resizeColumnToContents(0);
}

void PropertiesWidget::SaveToFile(const QString& file_name) {
    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "error opening file: " << file.error();
        return;
    }
    QTextStream file_stream(&file);

    for (const auto& property : property_to_item_.keys()) {
        file_stream << property << '\n';
        property_to_item_[property]->SaveToFile(file_stream);
    }

    file.close();
}