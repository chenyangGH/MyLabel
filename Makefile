#############################################################################
# Makefile for building: targetFile
# Generated by qmake (2.01a) (Qt 4.8.1) on: Fri Dec 26 01:19:31 2014
# Project:  main.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile main.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = mainwindow.cpp \
		mainview.cpp \
		uicircle.cpp \
		picview.cpp \
		uirectangle.cpp \
		uielement.cpp \
		main.cpp \
		uicoordinate.cpp \
		uicurve.cpp moc_mainwindow.cpp \
		moc_mainview.cpp \
		moc_uicircle.cpp \
		moc_picview.cpp \
		moc_uirectangle.cpp \
		moc_uielement.cpp \
		moc_uicoordinate.cpp \
		moc_uicurve.cpp
OBJECTS       = mainwindow.o \
		mainview.o \
		uicircle.o \
		picview.o \
		uirectangle.o \
		uielement.o \
		main.o \
		uicoordinate.o \
		uicurve.o \
		moc_mainwindow.o \
		moc_mainview.o \
		moc_uicircle.o \
		moc_picview.o \
		moc_uirectangle.o \
		moc_uielement.o \
		moc_uicoordinate.o \
		moc_uicurve.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		main.pro
QMAKE_TARGET  = targetFile
DESTDIR       = 
TARGET        = targetFile

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: main.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile main.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile main.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/targetFile1.0.0 || $(MKDIR) .tmp/targetFile1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/targetFile1.0.0/ && $(COPY_FILE) --parents mainwindow.h mainview.h uicircle.h picview.h uirectangle.h uielement.h uicoordinate.h uicurve.h .tmp/targetFile1.0.0/ && $(COPY_FILE) --parents mainwindow.cpp mainview.cpp uicircle.cpp picview.cpp uirectangle.cpp uielement.cpp main.cpp uicoordinate.cpp uicurve.cpp .tmp/targetFile1.0.0/ && (cd `dirname .tmp/targetFile1.0.0` && $(TAR) targetFile1.0.0.tar targetFile1.0.0 && $(COMPRESS) targetFile1.0.0.tar) && $(MOVE) `dirname .tmp/targetFile1.0.0`/targetFile1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/targetFile1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_mainview.cpp moc_uicircle.cpp moc_picview.cpp moc_uirectangle.cpp moc_uielement.cpp moc_uicoordinate.cpp moc_uicurve.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_mainview.cpp moc_uicircle.cpp moc_picview.cpp moc_uirectangle.cpp moc_uielement.cpp moc_uicoordinate.cpp moc_uicurve.cpp
moc_mainwindow.cpp: mainwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_mainview.cpp: mainview.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainview.h -o moc_mainview.cpp

moc_uicircle.cpp: uielement.h \
		uicircle.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) uicircle.h -o moc_uicircle.cpp

moc_picview.cpp: picview.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) picview.h -o moc_picview.cpp

moc_uirectangle.cpp: uielement.h \
		uirectangle.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) uirectangle.h -o moc_uirectangle.cpp

moc_uielement.cpp: uielement.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) uielement.h -o moc_uielement.cpp

moc_uicoordinate.cpp: uielement.h \
		uicoordinate.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) uicoordinate.h -o moc_uicoordinate.cpp

moc_uicurve.cpp: uielement.h \
		uicurve.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) uicurve.h -o moc_uicurve.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

mainwindow.o: mainwindow.cpp mainwindow.h \
		picview.h \
		mainview.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

mainview.o: mainview.cpp picview.h \
		mainview.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainview.o mainview.cpp

uicircle.o: uicircle.cpp uicircle.h \
		uielement.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o uicircle.o uicircle.cpp

picview.o: picview.cpp picview.h \
		uirectangle.h \
		uielement.h \
		uicoordinate.h \
		uicurve.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o picview.o picview.cpp

uirectangle.o: uirectangle.cpp uirectangle.h \
		uielement.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o uirectangle.o uirectangle.cpp

uielement.o: uielement.cpp uielement.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o uielement.o uielement.cpp

main.o: main.cpp mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

uicoordinate.o: uicoordinate.cpp uicoordinate.h \
		uielement.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o uicoordinate.o uicoordinate.cpp

uicurve.o: uicurve.cpp uicurve.h \
		uielement.h \
		uirectangle.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o uicurve.o uicurve.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_mainview.o: moc_mainview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainview.o moc_mainview.cpp

moc_uicircle.o: moc_uicircle.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_uicircle.o moc_uicircle.cpp

moc_picview.o: moc_picview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_picview.o moc_picview.cpp

moc_uirectangle.o: moc_uirectangle.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_uirectangle.o moc_uirectangle.cpp

moc_uielement.o: moc_uielement.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_uielement.o moc_uielement.cpp

moc_uicoordinate.o: moc_uicoordinate.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_uicoordinate.o moc_uicoordinate.cpp

moc_uicurve.o: moc_uicurve.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_uicurve.o moc_uicurve.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

