#include "epubelement.h"

EpubElement::EpubElement()
{

}

EpubElement::EpubElement(QString text, EpubElement *parent)
    : _text(new QString(text)), _parent(parent)
{


}

EpubElement::EpubElement(QXmlStreamReader *reader, EpubElement* parent)
    :  _parent(parent), _element_class( reader->name().toString()), _text(nullptr)
{
    for (QXmlStreamAttribute a : reader->attributes())
        this->_attributes.insert(a.qualifiedName().toString(), a.value().toString());
    while(!(reader->isEndElement() && reader->name() == _element_class)) {
        reader->readNext();
        if (reader->isStartElement())
            _children.push_back(new EpubElement(reader, this));
        else if (reader->isCharacters())
            _children.push_back(new EpubElement(reader->text().toString(), this));

    }

}

QString EpubElement::toHtml()
{
    if (_text) {
        return QString("<font color=%2>Chars:</font> %1")
                .arg(*_text)
                .arg(EpubDisplay::TypeColor);
    }
    QString attstr = "";
    if (_attributes.count() > 0) {
        attstr += QString("[");
        auto iter = _attributes.constBegin();
        while(iter != _attributes.constEnd()){
            attstr += QString("%1: %2 ")
                    .arg(iter.key())
                    .arg(iter.value());
            iter++;
        }
        attstr += QString("]");

    }

    QString retstr = QString("<b>%1</b>%3<br/>%2")
            .arg(get_class())
            .arg(get_text())
            .arg(attstr);
    if (child_count() > 0){
        retstr += QString("<br/>Children [%1]:<table>")
                .arg(child_count());
        for (EpubElement* el : _children) {
            retstr += QString("<tr><td class=\"p-child\">%1</td></tr>")
                    .arg(el->toHtml());
        }
        retstr += "</table></br>";
    }

    return retstr;
}
