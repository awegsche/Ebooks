#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionPreamble_triggered();

    void on_treeView_clicked(const QModelIndex &index);

    void on_tableFiles_doubleClicked(const QModelIndex &index);

    void on_tableFormats_clicked(const QModelIndex &index);

    void on_tableFiles_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
