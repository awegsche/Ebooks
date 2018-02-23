#ifndef EPUBELEMENT_H
#define EPUBELEMENT_H

#include <vector>
#include <QMap>
#include <QString>
#include <QXmlStreamReader>

namespace EpubDisplay {
const QString TypeColor = "#606060";
}

// EpubElement is a primitive (hierarchical) data structure
// that mirrors the XML-structure of the original files.
// Latex/Paragraph uses the content of the element to generate the actual paragraph
// in the LaTeX source file
class EpubElement
{
private:
    std::vector<EpubElement*> _children;
    QMap<QString, QString> _attributes;
    QString _element_class;
    QString* _text;
    EpubElement* _parent;
    int _index;

public:
    EpubElement();
    EpubElement(QString text, EpubElement *parent);
    EpubElement(QXmlStreamReader* reader, EpubElement *parent = nullptr);

    void set_index(const int index) {
        _index = index;
    }
    int get_index() const {
        return _index;
    }

    QString get_class() const {
        return _element_class;
    }
    QString get_text() const {
        if (_text)
            return *_text;
        QString rettext = "";
        for (EpubElement* el : _children)
            rettext += el->get_text();
        return rettext;
    }
    QString get_attribute(const QString &key) const {
        return _attributes[key];
    }
    EpubElement* get_child(const int index) const {
        return _children[index];
    }
    EpubElement* get_parent() const {
        return _parent;
    }
    int child_count() const {
        return _children.size();
    }
    QString toHtml();
};

#endif // EPUBELEMENT_H
