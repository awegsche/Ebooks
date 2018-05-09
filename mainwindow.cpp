#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <QByteArray>
//#include <QtZlib/zlib.h>
#include <QXmlStreamReader>

#include "directoryparser.h"
#include "formatmodel.h"
#include "filemodel.h"
#include "stilform.h"
#include "latextemplate.h"
#include "QVBoxLayout"
#include <QTime>

#define LOAD_LAPTOP true

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LatexTemplate *templ = new LatexTemplate();

    ui->tabStil->setLayout(new QVBoxLayout());
    ui->tabStil->layout()->addWidget(new StilForm(templ, this));

    ui->textBrowser->document()->setDefaultStyleSheet(
                QString(".p-display { padding-left=12pt; }\n"));

    if (LOAD_LAPTOP) {
        DirectoryParser *p = new DirectoryParser();
#ifdef WINHOME
        QString filename = "G:/Data/Ebooks/Simmons, Dan - [Hyperion-Cantos 1] - Hyperion (3-453-13304-8)";
#else
        QString filename = "/home/awegsche/Documents/Ebooks/Brooks, Terry - Das Schwert Von Shannara (2000, Goldmann, 3442238285).epub_FILES";
#endif

        QObject::connect(
                    p, SIGNAL(log(QString,const LoggerInterface*,int)),
                    this, SLOT(ListenToLog(QString,const LoggerInterface*,int)));

        //QString filename = "F:/Ebooks/Schaetzing, Frank/Breaking News";
        p->readFDirectory(filename);
        _openBook = new Book();
        p->loadFiles(_openBook);

        _latex_book = new LatexBook(_openBook);
        _latex_book->setup_formate();

        ui->toolBox->setItemText(
                    ui->toolBox->indexOf(ui->toolParagraphs),
                    QString("Paragraphs (%1)").arg(_openBook->element_count())
                    );
        ui->toolBox->setItemText(
                    ui->toolBox->indexOf(ui->toolFormats),
                    QString("Formats (%1)").arg(_openBook->get_formats()->size())
                    );

        ui->treeView->setModel(_openBook);
        ui->tableFormats->setModel(new FormatModel(_latex_book));
        ui->tableFiles->setModel(new FileModel(p));


    }

    //xml.setDevice(new QFile(filename));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionPreamble_triggered()
{
   ui->tabWidget->setCurrentWidget(ui->tabStil);
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
   ui->textBrowser->setHtml(_openBook->data(index, Book::GiveItemRole).value<QString>());
}

void MainWindow::on_tableFiles_doubleClicked(const QModelIndex &index)
{
    auto filename = ui->tableFiles->model()->data(index, Book::GiveItemRole);
    ui->textBrowser->setHtml("file selected");

}

void MainWindow::on_tableFormats_clicked(const QModelIndex &index)
{
}

void MainWindow::on_tableFiles_clicked(const QModelIndex &index)
{
    ((FileModel*)ui->tableFiles->model())->click_on_file(index);


}

void MainWindow::ListenToLog(const QString &message, const LoggerInterface *sender, int level)
{
    ui->textLog->append(message);
}

void MainWindow::on_tableFormats_doubleClicked(const QModelIndex &index)
{
    QString key = ui->tableFormats->model()->data(index, FormatModel::GetKeyRole);
    auto format = ((FormatModel*)ui->tableFormats->model())->get_format(key);

    ui->plainEditBefore->document()->setHtml(format.get_before());
}
