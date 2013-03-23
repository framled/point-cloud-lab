#ifndef PCL_VISUALIZATION_H
#define PCL_VISUALIZATION_H

#undef HAVE_OPENNI

#include <QThread>
#include <QString>
#include <QTimer>

#ifndef Q_MOC_RUN
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/passthrough.h>
#include <pcl/features/normal_3d.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/common/time.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/pcl_base.h>
#include <pcl/io/vtk_lib_io.h>
#endif // Q_MOC_RUN


class pcl_visualization : public QThread
{
Q_OBJECT

protected:
    bool m_stopFlag;

public:
    pcl_visualization(QObject *parent = 0);
    void cloud_cb (pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
    void run ();
    pcl::visualization::PCLVisualizer viewer;

    // Operations
    void normalize_cloud (pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
    pcl::PointXYZ& mean_point (pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

signals:
    void Completed();
    void ObjectFoundStatus(const QString&);

public slots:
    void StopThread();

};


#endif // PCL_VISUALIZATION_H
