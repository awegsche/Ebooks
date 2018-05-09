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
                return  _directory->_manifest[_directory->_spine[index.row()]]._checked ? Qt::Checked : Qt::Unchecked;
            else
                return QVariant();
        case Book::GiveItemRole:
            return _directory->_manifest[_directory->_spine[index.row()]]._filename;
        }
    }
    return QVariant();
}

void FileModel::click_on_file(const QModelIndex &index)
{

    //_directory->toggleSourceFile(index.row());
    emit dataChanged(index, index);
}

Qt::ItemFlags FileModel::flags(const QModelIndex &index) const
{
   if (index.isValid())
       return Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
   return Qt::ItemIsEnabled;
}

bool FileModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
   if (index.isValid() && role == Qt::CheckStateRole)
       _directory->toggleSourceFile(index.row());
    emit dataChanged(index, index);
   return true;
}
