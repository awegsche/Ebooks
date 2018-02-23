#include "filemodel.h"

FileModel::FileModel(DirectoryParser *d)
    : _directory(d)
{

}

QModelIndex FileModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid())
        return createIndex(row, column, nullptr);
    return QModelIndex();
}

QModelIndex FileModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int FileModel::rowCount(const QModelIndex &parent) const
{
    return _directory->_spine.size();
}

int FileModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        switch(role) {
        case Qt::DisplayRole:
            switch (index.column()) {
            case 0:
                return _directory->_spine[index.row()];
            case 1:
                return _directory->_manifest[_directory->_spine[index.row()]]._filename;
            default:
                break;
            }
        case Qt::CheckStateRole:
            if (index.column() == 0)
                return  _directory->_manifest[_directory->_spine[index.row()]]._checked;
        case CheckRole:
           _directory->toggleSourceFile(index.row());
        }
    }
    return QVariant();
}
