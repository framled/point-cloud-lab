#pragma warning(disable: 4996)

#include "pcl_visualization.h"
#include <QDebug>

//==================================================================
pcl_visualization::pcl_visualization(QObject *parent)
    : QThread(parent), m_stopFlag(false), viewer("Point-Cloud View")
{

}

//==================================================================
void pcl_visualization::StopThread()
{
    qDebug() << "StopThread:";
    m_stopFlag = true;
}

//==================================================================
void pcl_visualization::run ()
{
    qDebug() << "PCL visualization thread is running.";
    m_stopFlag = false;

    while (!viewer.wasStopped() && !m_stopFlag)
        this->msleep(100);
}

//==================================================================
pcl::PointXYZ& pcl_visualization::mean_point (pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
    unsigned int i;
    unsigned int size = cloud->points.size();
    double mean_x=0.0, mean_y=0.0, mean_z=0.0;
    pcl::PointXYZ point;

    qDebug() << "Calculating mean point.";

    // find mean
    for (i=0; i<size; i++)
    {
        mean_x += cloud->points[i].x;
        mean_y += cloud->points[i].y;
        mean_z += cloud->points[i].z;
    }
    mean_x /= (double)size;
    mean_y /= (double)size;
    mean_z /= (double)size;

    point.x = mean_x;
    point.y = mean_y;
    point.z = mean_z;

    return point;
}

//==================================================================
void pcl_visualization::normalize_cloud (pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
    unsigned int i;
    unsigned int size = cloud->points.size();
    pcl::PointXYZ mean_p;
    double std_x=0.0, std_y=0.0, std_z=0.0;
    double std_max = 0.0;

    qDebug() << "Point cloud normalization:";

    // find the mean point
    mean_p = mean_point(cloud);

    qDebug() << "Finding standard-deviation";
    // find sigma^2
    for (i=0; i<size; i++)
    {
        std_x += cloud->points[i].x - mean_p.x;
        std_y += cloud->points[i].y - mean_p.y;
        std_z += cloud->points[i].z - mean_p.z;
    }
    std_x /= (double)size;
    std_y /= (double)size;
    std_z /= (double)size;

    // which one is the biggest? we want to normalize with respect
    // to the biggest component
    std_max = (std_x>std_y)?std_x:std_y;
    std_max = (std_z>std_max)?std_z:std_max;

    qDebug() << "Scaling point cloud.";

    // normalize
    for (i=0; i<size; i++)
    {
        cloud->points[i].x /= std_max;
        cloud->points[i].y /= std_max;
        cloud->points[i].z /= std_max;
    }
}

//==================================================================
void pcl_visualization::cloud_cb (pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
    if (viewer.wasStopped() || m_stopFlag)
        return;

    // normalize
    normalize_cloud (cloud);

    // Viewer
    qDebug() << "cloud_cb_: cloud->width" << cloud->width;
    viewer.addPointCloud<pcl::PointXYZ> (cloud, "cloud");
    viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "cloud");

    // All the objects needed
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());

    qDebug() << "Estimating point normals.";
    // Estimate point normals
    ne.setSearchMethod (tree);
    ne.setInputCloud (cloud);
    ne.setKSearch (50);
    ne.compute (*cloud_normals);

    qDebug() << "Adding visualizations to viewer.";
    viewer.setBackgroundColor (0, 0, 0);
    viewer.addPointCloudNormals<pcl::PointXYZ, pcl::Normal> (cloud, cloud_normals, 1, 0.1, "normals");
    viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_COLOR, 1.0, 0.0, 0.0, "normals");
    viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_LINE_WIDTH, 2, "normals");

    viewer.addCoordinateSystem(1.0);
    viewer.initCameraParameters();
}

