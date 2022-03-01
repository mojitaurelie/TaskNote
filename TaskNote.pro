QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

win32:VERSION = 1.1.1.0 # major.minor.patch.build
else:VERSION = 1.1.1    # major.minor.patch

DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\"
DEFINES += APP_NAME=\"\\\"TaskNote\\\"\"

# remove possible other optimization flags
win32 {
    message("Build for Windows")
    QMAKE_CXXFLAGS_RELEASE -= -O
    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE *= -O2
    DEFINES += APP_OS=\"\\\"Windows\\\"\"
    DEFINES += APP_OS_VERSION=\"\\\"$$system(wmic os get version /value)\\\"\"
    equals(QMAKE_TARGET.arch, arm64) {
        message("CPU Architecture : aarch64")
        DEFINES += APP_ARCH=\"\\\"arm64\\\"\"
    }
    equals(QMAKE_TARGET.arch, x86_64) {
        message("CPU Architecture : x64")
        QMAKE_CXXFLAGS_RELEASE += -favor:INTEL64
        DEFINES += APP_ARCH=\"\\\"x64\\\"\"
    }
    RC_ICONS = icon.ico
    QMAKE_TARGET_COMPANY = "Aurelie Delhaie"
    QMAKE_TARGET_PRODUCT = "TaskNote"
    QMAKE_TARGET_DESCRIPTION = "Simple note-taking workbook"
}

macx {
    message("Build for macOS")
    ICON = icon.icns
    QMAKE_INFO_PLIST = Info.plist
    QMAKE_CXXFLAGS_RELEASE -= -O
    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE *= -O3
    DEFINES += APP_OS=\"\\\"macOS\\\"\"
    DEFINES += APP_OS_VERSION=\"\\\"$$system(uname -r)\\\"\"
    equals(QMAKE_APPLE_DEVICE_ARCHS, arm64) {
        message("CPU Architecture : aarch64")
        DEFINES += APP_ARCH=\"\\\"aarch64\\\"\"
        QMAKE_CXXFLAGS_RELEASE += -mcpu=apple-a14
    }
}

linux-g++* {
    message("Build for Linux")

    #LIBS += -L/usr/lib/crypto++ -lcrypto++
    #INCS += -I/usr/include/crypto++

    #DEFINES += __SECURED=1
    DEFINES += APP_OS=\"\\\"$$system(cat /etc/issue | cut -d\' \' -f1)\\\"\"
    DEFINES += APP_OS_VERSION=\"\\\"$$system(uname -r)\\\"\"
    DEFINES += APP_ARCH=\"\\\"amd64\\\"\"
    QMAKE_CXXFLAGS_RELEASE *= -O3
    QMAKE_CXXFLAGS_RELEASE += -march=skylake
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
