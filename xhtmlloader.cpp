#include "xhtmlloader.h"
#include "epubelement.h"
#include <QFile>

XhtmlLoader::XhtmlLoader()
{

}

void XhtmlLoader::load(const QString &filename, Book *book)
{
    QXmlStreamReader r;

    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    r.setDevice(&file);

    while(!r.atEnd()) {
        r.readNext();
        QString name = r.name().toString();
        if (r.isStartElement() && r.name() == "body")
            XhtmlLoader::readBody(&r, book);
    }
}

void XhtmlLoader::readBody(QXmlStreamReader *reader, Book *book)
{
    while(!reader->atEnd()) {
        reader->readNext();

        if (reader->isStartElement())
            book->addElement(new EpubElement(reader));
    }
}
