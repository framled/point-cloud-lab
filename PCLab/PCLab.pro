##
##  PCLab - PCL Laboratory
##  David Michaeli, March 2013
##


## GENERAL INSTALLATION INFORMATION
###################################
PCL_INSTALLATION_PATH = "C:/Program Files (x86)/PCL 1.6.0"
VTK_VERSION = "5.8"
BOOST_LIB_FILE = "boost_thread-vc100-mt-1_49"



# includes
INCLUDEPATH +=  "$${PCL_INSTALLATION_PATH}/3rdParty/Boost/include" \
                "$${PCL_INSTALLATION_PATH}/3rdParty/Eigen/include" \
                "$${PCL_INSTALLATION_PATH}/3rdParty/FLANN/include" \
                "$${PCL_INSTALLATION_PATH}/3rdParty/Qhull/include" \
                "$${PCL_INSTALLATION_PATH}/3rdParty/VTK/include/vtk-5.8" \
                "$${PCL_INSTALLATION_PATH}/include/pcl-1.6"

# libs
win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_apps_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_apps_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_common_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_common_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_features_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_features_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_filters_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_filters_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_io_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_io_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_io_ply_debug
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_io_ply_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_kdtree_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_kdtree_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_keypoints_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_keypoints_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_octree_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_octree_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_registration_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_registration_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_sample_consensus_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_sample_consensus_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_search_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_search_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_segmentation_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_segmentation_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_surface_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_surface_debug

win32:CONFIG(release, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_tracking_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"$${PCL_INSTALLATION_PATH}/lib/" -lpcl_tracking_debug

win32:CONFIG(release, debug|release): LIBS += -L"/$${PCL_INSTALLATION_PATH}/lib/" -lpcl_visualization_release
else:win32:CONFIG(debug, debug|release): LIBS += -L"/$${PCL_INSTALLATION_PATH}/lib/" -lpcl_visualization_debug

LIBS += -L"$${PCL_INSTALLATION_PATH}/3rdParty/Flann/lib" -lflann
LIBS += -L"$${PCL_INSTALLATION_PATH}/3rdParty/VTK/lib/vtk-$${VTK_VERSION}" \
        -lMapReduceMPI-gd -lmpistubs-gd -lQVTK-gd -lvtkalglib-gd -lvtkCharts-gd -lvtkCommon-gd \
        -lvtkDICOMParser-gd -lvtkexoIIc-gd -lvtkexpat-gd -lvtkFiltering-gd -lvtkfreetype-gd \
        -lvtkftgl-gd -lvtkGenericFiltering-gd -lvtkGeovis-gd -lvtkGraphics-gd -lvtkhdf5-gd \
        -lvtkHybrid-gd -lvtkImaging-gd -lvtkInfovis-gd -lvtkIO-gd -lvtkjpeg-gd -lvtkmetaio-gd \
        -lvtkNetCDF-gd -lvtkNetCDF_cxx-gd -lvtkpng-gd -lvtkproj4-gd -lvtkRendering-gd \
        -lvtksqlite-gd -lvtksys-gd -lvtktiff-gd -lvtkverdict-gd -lvtkViews-gd -lvtkVolumeRendering-gd \
        -lvtkWidgets-gd -lvtkzlib-gd
LIBS += -L"$${PCL_INSTALLATION_PATH}/3rdParty/Boost/lib" -l$${BOOST_LIB_FILE}
LIBS += -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 \
        -loleaut32 -luuid
LIBS += -lopengl32

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    mainwindow.cpp \
    pcl_visualization.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    pcl_visualization.h


