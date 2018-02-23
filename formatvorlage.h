#ifndef FORMATVORLAGE_H
#define FORMATVORLAGE_H
#include <qstring.h>

class FormatVorlage
{
public:
    enum FormatType {
        FORMAT,
        CLASS
    };

private:
    FormatType _type;
    QString _before;
    QString _after;

public:
    FormatVorlage(FormatType t = FORMAT);
    FormatVorlage(QString &before, QString &after, FormatType t = FORMAT);
    FormatVorlage(const char *before, const char *after, FormatType t = FORMAT);

    QString get_before(){
        return _before;
    }

    QString get_after(){
        return _after;
    }
};

namespace Formats {
const FormatVorlage Chapter("\\chapter{", "}");
const FormatVorlage Section("\\section{", "}");
const FormatVorlage Emph("\\emph{", "}");
const FormatVorlage Empty("", "");
}
#endif // FORMATVORLAGE_H
