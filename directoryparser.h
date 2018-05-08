#ifndef DIRECTORYPARSER_H
#define DIRECTORYPARSER_H

#include "logger.h"
#include "book.h"

#include <QString>
#include <QXmlStreamReader>
#include <QMap>

struct SourceFile
{
    SourceFile();
    SourceFile(const QString &filename, bool checked);
    bool _checked;
    QString _filename;
};

class DirectoryParser : public LoggerInterface
{
public:
    QMap<QString, SourceFile> _manifest;
    QStringList _spine;
    QString _directory;

public:
    DirectoryParser();

    void readFDirectory(const QString &dir);

    void loadFiles(Book* book);
    void toggleSourceFile(int index) {
        auto f = &_manifest[_spine[index]];
        f->_checked = !f->_checked;
    }

private:
    void readMetadata(QXmlStreamReader &xml);
    void readManifest(QXmlStreamReader &xml);
    void readSpine(QXmlStreamReader &xml);


    // LoggerInterface interface
public:
    QString toString() Q_DECL_OVERRIDE;
};

#endif // DIRECTORYPARSER_H
