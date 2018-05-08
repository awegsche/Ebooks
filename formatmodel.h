#ifndef FORMATMODEL_H
#define FORMATMODEL_H

#include <QAbstractItemModel>
#include "latexbook.h"

class FormatModel : public QAbstractItemModel
{
private:
    LatexBook* _book;


public:
    FormatModel(LatexBook* book);

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    FormatVorlage get_format(const QString &key) const;

    enum Roles {
        GetKeyRole = Qt::UserRole + 1
    };
};

#endif // FORMATMODEL_H
