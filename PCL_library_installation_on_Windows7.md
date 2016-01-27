This page present the long way to getting a working copy of PCL library (and its 3rd party libraries) on a windows PC.

# Introduction #
The installation process contains the following steps:

1. Downloading PCL 1.6.0 library pre-built binaries.

2. Installation of QT creator and QT-sdk 5.0.1

3. Installation of Visual-Studio 2010 express (VC++ is sufficient).

4. Getting the basic working program in QT.


# Details #

## Download PCL 1.6.0 ##
Use the following link: http://sourceforge.net/projects/pointclouds/files/1.6.0/PCL-1.6.0-AllInOne-msvc2010-win32.exe/download to download the latest PCL library binaries for 32-bit machine. I strongly suggest using the 32-bit as the 64-bit binaries don't work for the current version (1.6.0) in QT.
Install the binaries in "C:\Program Files\PCL 1.6.0 ...". Take a little tour to the installation path. Notice the 3rd-party folder contains BOOST, Eigen, FLANN, OPENNI, QHULL, VTK libraries.
Not all of those libraries are needed to build a working basic PCL application. For example, if you won't need any visualization ability in your application, the VTK library won't be linked.

The PCL installation should modify the environmental variable "path" in your windows system. The path modification is needed to register the folders containing DLLs needed for your application to run.
Check the variable "path" and verify its contents (it should contain all bin and some lib libraries - all of whom contain DLLs and EXEs under the PCL installation path).

## QT 5.0.1 Installation ##
QT development environment is widely used as the preferred cross platform development tool (for Windows, Linux, Mac-OsX, etc..). The coding is done in C++ language. You can make really nice and neat UI cross platform applications with QT. So lets download it: Go to http://qt-project.org/downloads and get the latest "Qt X.X.X for Windows 32-bit (VS 2010, 481 MB)". It important to download the version with the Visual-Studio XXXX toolchain for our purposes.

## Visual Studio (C++) Download ##
By the time I wrote this page, the latest version of VC was 2012. After downloading the 2012 express edition, I noticed QT stopped working properly with the PCL libraries. The reason was the installation of the .NET framework 4.5 (apparently). I strongly suggest downloading the 2010 edition from http://www.microsoft.com/visualstudio/eng/downloads#d-2010-express. You don't really need the whole Visual Studio, but just the Visual C++ 2010 Express (there's a separate download for that one).

## Getting a Basic QT + PCL + VTK Program ##
Now if you have all of the above stuff, just clone the PCLab program from my SVN repository and open it using QT. The building process is very long unfortunately. I'm still looking for a method to shorten the building and linking time with BOOST, PCL and so on.

# QT Makefile #
QT environment projects contain a .pro file which defines the project and how to build it. From a single glance its easy to notice the similarity to a regular Makefile. We need to define variables like "LIBS", "INCLUDEPATH" and so on.
In our .pro file, among others I defined the include and library paths. The file starts with :

```
PCL_INSTALLATION_PATH = "C:/Program Files (x86)/PCL 1.6.0"
VTK_VERSION = "5.8"
BOOST_LIB_FILE = "boost_thread-vc100-mt-1_49"
```

So you can define the prefixes of your installations.


Thats it. Enjoy...
David Michaeli