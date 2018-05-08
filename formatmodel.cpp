#include "formatmodel.h"

FormatModel::FormatModel(LatexBook *book)
    : _book(book)
{

}

QModelIndex FormatModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid())
        return createIndex(row, column, nullptr);

}

QModelIndex FormatModel::parent(const QModelIndex &child) const
{
    return QModelIndex(); // no hierarchy so far
}

int FormatModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return _book->_formate.size();
    return 0;
}

int FormatModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}


QVariant FormatModel::data(const QModelIndex &index, int role) const
{
    switch(role) {
    case Qt::DisplayRole:
        switch(index.column()) {
        case 0:
            return _book->_formate.keys().at(index.row());
        }
        break;
    case GetKeyRole:
        return _book->_formate.keys().at(index.row());
    }
    return QVariant();
}

FormatVorlage FormatModel::get_format(const QString &key) const
{
   return _book->_formate[key];
}
