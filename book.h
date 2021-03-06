#ifndef BOOK_H
#define BOOK_H

#include "epubelement.h"

#include <vector>
#include <QAbstractItemModel>

class Book : public QAbstractItemModel
{
private:
    std::vector<EpubElement*> _elements;
    QStringList _classes;
    QStringList _formats;

public:
    Book();

    void addElement(EpubElement* element);

    enum BookRoles{
        GiveItemRole = Qt::UserRole + 1
    };

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    const QStringList* get_formats() const {
        return &_formats;
    }
    const QStringList* get_classes() const {
        return &_classes;
    }
    int element_count() const {
        return _elements.size();
    }
    EpubElement *get_element_by_format(const QString &key, const int start = 0) {
        for(int i = start; i < _elements.size(); i++)
            if (_elements[i]->get_class() == key)
                return _elements[i];
        return nullptr;
    }
};

#endif // BOOK_H
