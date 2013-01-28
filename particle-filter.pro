TEMPLATE = app
CONFIG += console debug
CONFIG -= qt release

SOURCES += main.cpp
QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    mcmc.h \
    slice-sampler.h

# Custom target 'doc'
dox.target = doc
dox.commands = doxygen Doxyfile; \
    test -d doxydoc/html/images || mkdir doxydoc/html/images; \
    cp documentation/images/* doxydoc/html/images
dox.depends =

QMAKE_EXTRA_TARGETS += dox
