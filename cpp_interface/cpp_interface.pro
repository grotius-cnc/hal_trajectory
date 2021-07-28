QT -= gui

TEMPLATE = lib
DEFINES += CPP_INTERFACE_LIBRARY
# Name of the library:
TARGET = trajectory_6DoFs

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpp_interface.cpp

HEADERS += \
    cpp_interface_global.h \
    cpp_interface.h

INCLUDEPATH+=   /home/user/Desktop/Linux-Embedded/linux-hal/halcompile-trajectory-ruckig/cpp_interface/ruckig/include/ruckig
LIBS+= -L/home/user/Desktop/Linux-Embedded/linux-hal/halcompile-trajectory-ruckig/cpp_interface/ruckig/build -lruckig

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
