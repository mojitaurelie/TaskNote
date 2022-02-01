QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# remove possible other optimization flags
win32 {
    message("Build for Windows")
    QMAKE_CXXFLAGS_RELEASE -= -O
    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE *= -O2
    equals(QMAKE_TARGET.arch, arm64) {
        message("CPU Architecture : aarch64")
        # Add specific arm stuff here
    }
    equals(QMAKE_TARGET.arch, x86_64) {
        message("CPU Architecture : x64")
        QMAKE_CXXFLAGS_RELEASE += -favor:INTEL64
    }
    RC_ICONS = icon.ico
    VERSION = 1.1.0.0
    QMAKE_TARGET_COMPANY = "Aurelie Delhaie"
    QMAKE_TARGET_PRODUCT = "TaskNote"
    QMAKE_TARGET_DESCRIPTION = "TaskNote"
}

macx {
    message("Build for macOS")
    ICON = icon.icns
    QMAKE_INFO_PLIST = Info.plist
    QMAKE_CXXFLAGS_RELEASE -= -O
    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE *= -O3
    equals(QMAKE_APPLE_DEVICE_ARCHS, arm64) {
        message("CPU Architecture : aarch64")
        QMAKE_CXXFLAGS_RELEASE += -mcpu=apple-a14
    }
    VERSION = 1.1.0
}

linux-g++* {
    message("Build for Linux")
    QMAKE_CXXFLAGS_RELEASE *= -O3
    QMAKE_CXXFLAGS_RELEASE += -march=skylake
    VERSION = 1.1.0
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/frames/aboutdialog.cpp \
    src/main.cpp \
    src/frames/mainwindow.cpp \
    src/models/note.cpp \
    src/services/savemanager.cpp

HEADERS += \
    src/frames/aboutdialog.h \
    src/frames/mainwindow.h \
    src/models/note.h \
    src/services/savemanager.h

FORMS += \
    src/frames/aboutdialog.ui \
    src/frames/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
