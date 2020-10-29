QT += core gui svg widgets

TARGET = menu
TEMPLATE = app

REV_MAJOR_CODE = 0
REV_MINOR_CODE = 8
REV_PATCH_CODE = 0
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

# message($$DEFINES)
# message($$CONFIG)
# message($$QT)
# message($$TARGET)
# message($$HEADERS)
