#include "dialog_graphdisplay.h"
#include "ui_dialog_graphdisplay.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

Dialog_GraphDisplay::Dialog_GraphDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_GraphDisplay)
{
    ui->setupUi(this);
}

Dialog_GraphDisplay::~Dialog_GraphDisplay()
{
    delete ui;
}

void Dialog_GraphDisplay::on_buttonBox_accepted()
{
    if (ui->checkBox->isChecked() == true)
    {
        MainWindow *ptr = (MainWindow*)parentWidget();
//        ptr->draw("C:/lightjames/HPC_group/hefei_client/data_fomat&software_illustration/data/mmpldata/20150624_1_tunnel");

        ptr->draw("/Users/lightjames/HPC_group/hefei_client/data_fomat&software_illustration/data/mmpldata/20150624_1_tunnel");
    }

//    MapWindow* mw = new MapWindow();
//    mw->plot();
//    mw->show();
}

void Dialog_GraphDisplay::on_buttonBox_rejected()
{
    this->close();
}
