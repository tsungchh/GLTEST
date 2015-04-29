HEADERS  = \
    patch.h \
    solarsystem.h \
    textest.h \
    multitex.h \
    texmatrix.h \
    widget.hpp \
    mesh.h \
    shadertest.h \
    technique.h \
    picktechnique.h \
    pickingfbo.h \
    rendertechnique.h \
    MYMACRO.h \
    texture.h \
    glwidget.h \
    mathbase.h \
    observer.h


SOURCES  = main.cpp\
           widget.cpp \
    patch.cpp \
    solarsystem.cpp \
    textest.cpp \
    multitex.cpp \
    texmatrix.cpp \
    mesh.cpp \
    shadertest.cpp \
    technique.cpp \
    picktechnique.cpp \
    pickingfbo.cpp \
    rendertechnique.cpp \
    texture.cpp \
    glwidget.cpp \
    mathbase.cpp \
    observer.cpp


RESOURCES     = textest.qrc

QT       +=  widgets opengl

OTHER_FILES += \
    models/phoenix_ugv.md2 \
    ToDo.txt \
    vertex.vs \
    fragment.fs \
    meshV.vert \
    meshF.frag \
    textestF.frag \
    textestV.vert

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lassimp.3.1.1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lassimp.3.1.1
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lassimp.3.1.1

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include
