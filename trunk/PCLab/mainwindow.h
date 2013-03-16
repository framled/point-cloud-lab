#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pcl_visualization.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    pcl_visualization *pclVisualization;
    bool pclVisualizationThreadExists;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void DeletePCLVisualizationThread();
    void PCLVisualizationThreadFinished();
    void on_importButton_clicked();

private:
    Ui::MainWindow *ui;

    void processCurrentPointCloud();
    void exitCurrentProcessing();
};

#endif // MAINWINDOW_H
