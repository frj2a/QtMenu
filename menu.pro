QT += core gui svg widgets

TARGET = menu
TEMPLATE = app

VER_MAJ = 0
VER_MIN = 8
VER_PAT = 0
PROJECT_DIR=$$PWD
include (../QtBaseGeral/base_geral.pri)

win32:QMAKE_CXXFLAGS -= -Zm200

SOURCES += main.cpp\
        CGMenu.cpp \
        CTelaConfirmacao.cpp \
        CQuickMenu.cpp \
        CQuickMenuLineEdit.cpp

HEADERS  += CGMenu.h \
        CTelaConfirmacao.h \
        CQuickMenu.h \
        CQuickMenuLineEdit.h

FORMS    += CGMenu.ui \
        CTelaConfirmacao.ui \
        CQuickMenu.ui

RESOURCES += \
        CGMenu.qrc \
        CGMenuJPEG.qrc

win32:RC_FILE = menu.rc

unix {
    INCLUDEPATH += /usr/include/opencv4
    # LIBS += -L/usr/lib -lopencv_core -lopencv_features2d -lopencv_highgui
    LIBS += -L/usr/lib/x86_64-linux-gnu \
            # -lopencv_aruco            \
            # -lopencv_bgsegm           \
            # -lopencv_bioinspired      \
            # -lopencv_calib3d          \
            # -lopencv_ccalib           \
            -lopencv_core             \
            # -lopencv_datasets         \
            # -lopencv_dnn              \
            # -lopencv_dpm              \
            # -lopencv_face             \
            # -lopencv_features2d       \
            # -lopencv_flann            \
            # -lopencv_fuzzy            \
            # -lopencv_hdf              \
            # -lopencv_highgui          \
            -lopencv_imgcodecs        \
            -lopencv_imgproc          \
            # -lopencv_line_descriptor  \
            # -lopencv_ml               \
            # -lopencv_objdetect        \
            # -lopencv_optflow          \
            # -lopencv_photo            \
            # -lopencv_plot             \
            # -lopencv_reg              \
            # -lopencv_rgbd             \
            # -lopencv_saliency         \
            # -lopencv_shape            \
            # -lopencv_stereo           \
            # -lopencv_stitching        \
            # -lopencv_structured_light \
            # -lopencv_superres         \
            # -lopencv_surface_matching \
            # -lopencv_text             \
            # -lopencv_tracking         \
            # -lopencv_video            \
            # -lopencv_videoio          \
            # -lopencv_videostab        \
            # -lopencv_xfeatures2d      \
            # -lopencv_ximgproc         \
            # -lopencv_xobjdetect       \
            # -lopencv_xphoto           \

}


# message($$DEFINES)
# message($$CONFIG)
# message($$QT)
# message($$TARGET)
# message($$HEADERS)
