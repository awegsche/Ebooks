#include "formatvorlage.h"

FormatVorlage::FormatVorlage(FormatType t)
    : _type(t)
{

}

FormatVorlage::FormatVorlage(QString &before, QString &after, FormatVorlage::FormatType t)
    : _before(before), _after(after), _type(t)
{

}

FormatVorlage::FormatVorlage(const char *before, const char *after, FormatVorlage::FormatType t)
    : _before(QString(before)), _after(QString(after)), _type(t)
{

}
