#include "stilform.h"
#include "ui_stilform.h"
#include <QFile>

StilForm::StilForm(LatexTemplate *tmpl, QWidget *parent) :
    QWidget(parent), _template(tmpl),
    ui(new Ui::StilForm)
{
    ui->setupUi(this);

    auto elist = _template->templates.entryList(QDir::Files);

    ui->lineEdit->setText(elist[0]);

    QFile F(_template->templates.absoluteFilePath(elist[0]));
    F.open(QFile::ReadOnly);

    auto arr = F.readAll();

    ui->textBrowser->setText(QString(arr));
    F.close();
}

StilForm::~StilForm()
{
    delete ui;
}
