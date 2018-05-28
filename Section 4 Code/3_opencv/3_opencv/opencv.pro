QT       += core gui multimedia widgets

TARGET = opencv
TEMPLATE = app

# NOTE: See here for how to compile OpenCV with Qt on windows
# https://wiki.qt.io/How_to_setup_Qt_and_openCV_on_Windows


unix: INCLUDEPATH += /usr/include/opencv2
# Windows users need to add the correct include path! Uncomment below line and fix path!
# win32: INCLUDEPATH += C:\opencv\build\include


unix {
	!contains(QT_CONFIG, no-pkg-config) {
    		CONFIG += link_pkgconfig
    		PKGCONFIG += opencv
	} else {
    		LIBS += -lopencv_core -lopencv_imgproc -lopencv_objdetect
	}
}
win32 {
	# Windows users need to correct the lib path! Uncomment below and fix paths!
	# LIBS+= C:\opencv-build\bin\libopencv_core320.dll
	# LIBS+= C:\opencv-build\bin\libopencv_imgproc320.dll
	# LIBS+= C:\opencv-build\bin\libopencv_objdetect320.dll
}

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    videowidget.cpp \
    videosurface.cpp

HEADERS += \
        mainwindow.h \
    videowidget.h \
    videosurface.h

# Logic from: https://stackoverflow.com/a/39234363/2701402
copydata.commands = $(COPY_FILE) \"$$shell_path($$PWD\\haarcascade_frontalface_default.xml)\" \"$$shell_path($$OUT_PWD)\"
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
