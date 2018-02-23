#include "latexbook.h"

#include <QFile>

LatexBook::LatexBook(Book *book)
    : _book(book)
{

}

void LatexBook::setup_formate()
{
    for (QString f : *_book->get_formats())
        _formate.insert(f, FormatVorlage());
    for (QString f : *_book->get_classes())
        _formate.insert(f, FormatVorlage(FormatVorlage::CLASS));
}

void LatexBook::convert_latex(const LatexTemplate *t, const QString &filename)
{
    QFile F(filename);

    F.open(QFile::WriteOnly);




}
