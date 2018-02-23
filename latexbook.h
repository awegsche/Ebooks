#ifndef LATEXBOOK_H
#define LATEXBOOK_H

#include "book.h"
#include "formatvorlage.h"
#include "latextemplate.h"
#include <QMap>
#include <QString>

class LatexBook
{
private:
    Book *_book;

public:
    QMap<QString, FormatVorlage> _formate;

public:
    LatexBook(Book* book);

    void setup_formate();

    void convert_latex(const LatexTemplate* t, const QString &filename);
};

#endif // LATEXBOOK_H
