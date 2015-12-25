#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QFile"
#include "QFileInfo"
#include "QScrollArea"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->dialog_site = NULL;
    this->dialog_graph = NULL;

    QUrl url("file:///Users/lightjames/workspace/Qt/Project/mymap.html");
//    QUrl url("file:///C:\\workspace\\qt\\Project\\mymap.html");
    ui->webView_map->setUrl(url);

    ui->listWidget->setAutoScroll(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_site_clicked()
{
    if(!this->dialog_site)
    {
        dialog_site = new Dialog_Site;
    }
    //dialog_site->show();
    dialog_site->exec();
    //qDebug() << this->dialog_site->latitude;
    //qDebug()<<this->dialog_site->longitude;
    if(this->dialog_site->result() == 1)
    {
        float lat = this->dialog_site->getLatitude().toFloat();
        float lon = this->dialog_site->getLontitude().toFloat();
        this->ui->lineEdit_lon->setText(this->dialog_site->getLontitude());
        this->ui->lineEdit_lat->setText(this->dialog_site->getLatitude());
        this->setGraphPosition(lon, lat);
    }
}

void MainWindow::on_btn_graphDisplay_clicked()
{
    if(!this->dialog_graph)
        dialog_graph = new Dialog_GraphDisplay(this);
    dialog_graph->show();
}

void MainWindow::setGraphPosition(float lon, float lat)
{
    qDebug()<<lon<<lat;
    QWebFrame *frame = ui->webView_map->page()->mainFrame();
        QString method = QString("SetPosition(%1,%2)").arg(lon).arg(lat);
        frame->evaluateJavaScript(method);
}

void MainWindow::draw(QString dataDir)
{

    MapWindow *mp = new MapWindow();

    mp->plot(dataDir);
    mp->setFixedSize(mp->width(),mp->height());

    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(item->sizeHint().width(),mp->height()));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, mp);

}
