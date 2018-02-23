#ifndef STILFORM_H
#define STILFORM_H

#include <QWidget>

#include "latextemplate.h"

namespace Ui {
class StilForm;
}

class StilForm : public QWidget
{
    Q_OBJECT

private:
    LatexTemplate* _template;

public:
    explicit StilForm(LatexTemplate* tmpl, QWidget *parent = 0);
    ~StilForm();

private:
    Ui::StilForm *ui;
};

#endif // STILFORM_H
