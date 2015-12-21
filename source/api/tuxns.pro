#-------------------------------------------------
#
# Project created by QtCreator 2014-12-27T23:48:21
#
#-------------------------------------------------

QT             += core sql network
QT             -= gui
TARGET          = tuxns
CONFIG         += console link_prl
LIBS           += -lGeoIP
CONFIG         -= app_bundle
QMAKE_CXXFLAGS += -std=c++11
DEFINES        += HGI_CONFIG_FILE=\"\\\"$$PWD/application.ini\\\"\"
TEMPLATE        = app
SOURCES        += main.cpp \
	externals/HeimdallGI/CGI.cpp \
	externals/HeimdallGI/Configuration.cpp \
	externals/HeimdallGI/DBI.cpp \
	externals/HeimdallGI/ErrorController.cpp \
	externals/HeimdallGI/HTML.cpp \
	externals/HeimdallGI/Log.cpp \
	externals/HeimdallGI/MaxMind.cpp \
	externals/HeimdallGI/Router.cpp \
	externals/HeimdallGI/Template.cpp \
	externals/HeimdallGI/View.cpp \
	controllers/GeoIP.cpp \
	#controllers/DDNS.cpp

HEADERS        += \
	externals/HeimdallGI/CGI.h \
	externals/HeimdallGI/Configuration.h \
	externals/HeimdallGI/DBI.h \
	externals/HeimdallGI/ErrorController.h \
	externals/HeimdallGI/HTML.h \
	externals/HeimdallGI/Log.h \
	externals/HeimdallGI/MaxMind.h \
	externals/HeimdallGI/Router.h \
	externals/HeimdallGI/Template.h \
	externals/HeimdallGI/View.h \
	controllers/GeoIP.h \
	#controllers/DDNS.h

DISTFILES      += \
	application.ini \
	Readme.md
