#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <logger.h>
#include <QMainWindow>
#include <book.h>
#include "latexbook.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Book *_openBook;
    LatexBook *_latex_book;

    int _formatindex = 0;
    QString _selected_format_key;
    QMap<QString, FormatVorlage> _predefined_formats;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionPreamble_triggered();

    void on_treeView_clicked(const QModelIndex &index);

    void on_tableFiles_doubleClicked(const QModelIndex &index);

    void on_tableFormats_clicked(const QModelIndex &index);

    void on_tableFiles_clicked(const QModelIndex &index);

    void ListenToLog(const QString &message, const LoggerInterface *sender, int level);

    void on_tableFormats_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_listPredefinedFormats_itemDoubleClicked(QListWidgetItem *item);

    void on_buttonUpdateFormat_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
