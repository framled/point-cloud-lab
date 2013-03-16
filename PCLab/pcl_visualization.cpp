#pragma warning(disable: 4996)

#include "pcl_visualization.h"
#include <QDebug>


pcl_visualization::pcl_visualization(QObject *parent)
    : QThread(parent), m_stopFlag(false), viewer("Point-Cloud View")
{

}

void
pcl_visualization::StopThread()
{
    qDebug() << "StopThread:";
    m_stopFlag = true;
}

void
pcl_visualization::run ()
{
    qDebug() << "run :";
    m_stopFlag = false;

    while (!viewer.wasStopped() && !m_stopFlag)
        this->msleep(100);
}


void
pcl_visualization::cloud_cb (pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
    if (viewer.wasStopped() || m_stopFlag)
        return;

    // Viewer
    qDebug() << "cloud_cb_: cloud->width" << cloud->width;
    viewer.addPointCloud<pcl::PointXYZ> (cloud, "cloud");
    viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cloud");

    // All the objects needed
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);

    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());

    // Estimate point normals
    ne.setSearchMethod (tree);
    ne.setInputCloud (cloud);
    ne.setKSearch (50);
    ne.compute (*cloud_normals);

    viewer.setBackgroundColor (0, 0, 0);
    viewer.addPointCloudNormals<pcl::PointXYZ, pcl::Normal> (cloud, cloud_normals, 10, 0.05, "normals");
    viewer.addCoordinateSystem(1.0);
    viewer.initCameraParameters();
}

