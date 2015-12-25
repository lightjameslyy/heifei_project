#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialog_site.h>
#include <dialog_graphdisplay.h>
#include <QWebFrame>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setGraphPosition(float lon, float lat);
    void draw(QString dataDir);

private slots:
    void on_btn_site_clicked();

    void on_btn_graphDisplay_clicked();

private:
    Ui::MainWindow *ui;
    Dialog_GraphDisplay *dialog_graph;
    Dialog_Site *dialog_site;
};

#endif // MAINWINDOW_H
