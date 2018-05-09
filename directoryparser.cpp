#include "directoryparser.h"

#include "xhtmlloader.h"

#include <QDir>
#include <QDebug>



DirectoryParser::DirectoryParser()
{

}

void DirectoryParser::readFDirectory(const QString &dir)
{
    // please delete soon
    QXmlStreamReader xml;
    QDir directory(dir);
    auto list = directory.entryInfoList(QDir::AllDirs | QDir::NoDotDot);
    emit log(QString("Start reading source directory %1").arg(dir), this);


    for (QFileInfo fn : list) {
        emit log(fn.fileName(), this);
        QFile content(fn.absoluteFilePath() + "/content.opf");

        if (!content.open(QIODevice::ReadOnly)) {

            continue;
        }
        _directory = fn.absoluteFilePath();

        xml.setDevice(&content);

        while(!xml.atEnd()) {
            auto ttype = xml.readNext();

            if (ttype == QXmlStreamReader::StartElement)
            {
                QString name = xml.name().toString();
                if (name == "metadata")
                    readMetadata(xml);
                else if (name == "manifest")
                    readManifest(xml);
                else if (name == "spine")
                    readSpine(xml);

            }
        }
    }

}

// Loads the files into memory
void DirectoryParser::loadFiles(Book *book)
{
    emit log("Loading files into memory", this);
    for (QString idref : _spine) {
        XhtmlLoader::load(_directory + "/" + _manifest[idref]._filename, book);
    }
}


void DirectoryParser::readMetadata(QXmlStreamReader &xml)
{

}

void DirectoryParser::readManifest(QXmlStreamReader &xml)
{
    while(!(xml.isEndElement() && xml.name() == "manifest"))
    {
        xml.readNext();

        if (xml.isStartElement() && xml.name() == "item")
            this->_manifest.insert(xml.attributes().value("id").toString(),
                                   SourceFile(xml.attributes().value("href").toString(), true));
    }
    emit log(QString("got manifest. %1 entries")
             .arg(QString::number(this->_manifest.size())), this);
}

void DirectoryParser::readSpine(QXmlStreamReader &xml)
{
    while(!(xml.isEndElement() && xml.name() == "spine"))
    {
        xml.readNext();

        if (xml.isStartElement() && xml.name() == "itemref")
            this->_spine << xml.attributes().value("idref").toString();
    }
    emit log(QString("got spine. %1 entries")
             .arg(QString::number(this->_spine.size())), this);
}

QString DirectoryParser::toString()
{
   return "Directory Parser";
}

SourceFile::SourceFile()
    : _checked(false), _filename("")
{

}

SourceFile::SourceFile(const QString &filename, bool checked)
    :_checked(checked), _filename(filename)
{
    qDebug()<<filename;
}
