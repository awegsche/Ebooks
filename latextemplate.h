#ifndef LATEXTEMPLATE_H
#define LATEXTEMPLATE_H

#include <QString>
#include <QDir>

class LatexTemplate
{
public:
    QDir templates;

public:
    LatexTemplate();

    QString get_preamble();
};

#endif // LATEXTEMPLATE_H
