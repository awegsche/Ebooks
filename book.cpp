#include "book.h"

#include <QColor>

Book::Book()
{

}

void Book::addElement(EpubElement *element)
{
    element->set_index(_elements.size());
    this->_elements.push_back(element);

    bool has_class = false;
    for (QString c : _classes)
        if (c == element->get_class())
            has_class = true;
    if (!has_class)
        _classes << element->get_class();

    has_class = false;
    QString format = element->get_attribute("class");
    for (QString c : _formats)
        if (c == format)
            has_class = true;
    if (!has_class)
        _formats << format;

}

QModelIndex Book::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid()) // top level
        return createIndex(row, column, this->_elements[row]);
    EpubElement* ptr = (EpubElement*)parent.internalPointer();
    return createIndex(row, column, ptr->get_child(row));
}

QModelIndex Book::parent(const QModelIndex &child) const
{
    EpubElement* p = ((EpubElement*)child.internalPointer())->get_parent();

    if (p == nullptr) return QModelIndex();

    return createIndex(p->get_index(), 0, p);
}

int Book::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return ((EpubElement*)parent.internalPointer())->child_count();
    return _elements.size();
}

int Book::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant Book::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    EpubElement* el = (EpubElement*)index.internalPointer();

    switch (index.column()) {
    case 0:
        switch(role) {
        case Qt::DisplayRole:
            return el->get_class();
            break;
        case Qt::ForegroundRole:
            return QColor(1);
            break;
        }
        break;
    case 1:
        switch(role) {
        case Qt::DisplayRole:
            return el->get_text();
            break;

        }
        break;
    default:
        break;
    }

    if (role > Qt::UserRole)  // user defined roles
    {
        switch (role){
        case GiveItemRole:
            return el->toHtml();
        }
    }
    return QVariant();
}
