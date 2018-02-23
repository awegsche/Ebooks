#ifndef XHTMLLOADER_H
#define XHTMLLOADER_H

#include <QString>
#include "book.h"
#include <QXmlStreamReader>

class XhtmlLoader
{
public:
    XhtmlLoader();

    static void load(const QString& filename, Book* book);
    static void readBody(QXmlStreamReader *reader, Book* book);
};

#endif // XHTMLLOADER_H
