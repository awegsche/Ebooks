#ifndef FILEMODEL_H
#define FILEMODEL_H

#include "QAbstractItemModel"
#include "directoryparser.h"

class FileModel : public QAbstractItemModel
{
private:
    DirectoryParser* _directory;

public:
    FileModel(DirectoryParser* d);

    enum FileModelRoles{
        CheckRole = Qt::UserRole + 1
    };

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void click_on_file(const QModelIndex &index);
};


#endif // FILEMODEL_H
