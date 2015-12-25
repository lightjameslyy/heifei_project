#include "mapwindow.h"
#include "ui_mapwindow.h"

MapWindow::MapWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint );
}

MapWindow::~MapWindow()
{
    delete ui;
}

void MapWindow::plot(QString dataDir)
{


    QDir dir(dataDir);

    QFileInfoList infoList = dir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot);


    // configure axis rect:
    ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->customPlot->axisRect()->setupFullAxesBox(true);
    ui->customPlot->xAxis->setLabel("时间");
    ui->customPlot->yAxis->setLabel("高度（km）");

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(colorMap);
    int nx = infoList.size();
    int ny = 270;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(0, 24), QCPRange(0, 8.1)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
        QFile file(infoList[xIndex].absoluteFilePath());

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
        QTextStream in(&file);
        in.readLine();
        in.readLine();
//        in.readLine();
        for (int yIndex=1; yIndex<=270; yIndex++)
        {
            int i;
            double d;
            in >>i >>d;

            colorMap->data()->setCell(xIndex, yIndex, d/75000);
            in.readLine();
        }
        file.close();
    }



    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
    ui->customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
//    colorScale->axis()->setLabel("Magnetic Field Strength");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->customPlot);
    ui->customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}
