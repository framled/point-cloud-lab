#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>

//================================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pclVisualizationThreadExists(false)
{
    ui->setupUi(this);
}

//================================================================
MainWindow::~MainWindow()
{
    DeletePCLVisualizationThread();
    delete ui;
}

//================================================================
void MainWindow::DeletePCLVisualizationThread()
{
    qDebug() << "DeletePCLVisualizationThread: pclVisualizationThreadExists" << pclVisualizationThreadExists;

    if (pclVisualizationThreadExists)
        PCLVisualizationThreadFinished();
}

//================================================================
void MainWindow::exitCurrentProcessing()
{
    qDebug() << "on_Stop_pushButton_clicked:";
    DeletePCLVisualizationThread();
}

//================================================================
void MainWindow::processCurrentPointCloud()
{
    DeletePCLVisualizationThread();
    qDebug() << "on_Go_pushButton_clicked: Deleted pcl-visualization thread";

    // try creating a new pcl_cisualization thread
    try
    {
        pclVisualization = new pcl_visualization(this);
    }
    catch (std::bad_alloc &a)
    {
        qDebug() << "on_Go_pushButton_clicked: allocation of pcl_visualization thread failed.";
    }
    qDebug() << "on_Go_pushButton_clicked: Created a new visualization";

    connect(pclVisualization, SIGNAL(ObjectFoundStatus(const QString&)),
            ui->statusbar, SLOT(showMessage(const QString&)));

    connect(pclVisualization, SIGNAL(finished()), this, SLOT(PCLVisualizationThreadFinished()));
    pclVisualization->start();
    pclVisualizationThreadExists = true;
    qDebug() << "on_Go_pushButton_clicked: finished calling";
}

//================================================================
void MainWindow::PCLVisualizationThreadFinished()
{
    qDebug() << "PCLVisualizationFinished:";

    pclVisualizationThreadExists = false;

    qDebug() << "PCLVisualizationFinished: StopThread" ;
    pclVisualization->StopThread();

    qDebug() << "PCLVisualizationFinished: wait(500)";
    pclVisualization->wait(500);

    qDebug() << "PCLVisualizationFinished: isRunning" << pclVisualization->isRunning();
    if (pclVisualization->isRunning())
    {
        qDebug() << "PCLVisualizationFinished: deleteLater";
        pclVisualization->quit();
        qDebug() << "PCLVisualizationFinished: deleted";
    }

    qDebug() << "PCLVisualizationThreadFinished: end";
}

//================================================================
void MainWindow::on_importButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Point Cloud"), "",
                                                    tr("OBJ File (*.obj)"));
    if (filename.isNull()==false)
    {
        qDebug() << "on_importButton_clicked: Selected filename " << filename;

        QByteArray ba = filename.toLocal8Bit();

        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
        pcl::PolygonMesh mesh;

        pcl::io::loadPolygonFileOBJ(ba.data(), mesh);
        pcl::fromROSMsg(mesh.cloud, *cloud);

        ui->numOfPoints->setText(QString("%1").arg(cloud->size()));

        processCurrentPointCloud();

        if (pclVisualization) pclVisualization->cloud_cb(cloud);
    }
}
