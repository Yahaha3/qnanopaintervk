TEMPLATE = app

QT += widgets core

DEFINES += NOMINMAX

DEFINES += BUILD_VULKAN_BACKENDS

equals(QT_MAJOR_VERSION, 6) { ## for Qt6 need openglwidgets module to define QOpenGLWidget
    QT += openglwidgets       ## see https://doc-snapshots.qt.io/qt6-dev/sourcebreaks.html#changes-to-qt-ope
}                             ## NB: "QOpenGLWidget has been moved to its own openglwidgets module. Applications relying on QOpenGLWidget should add QT += openglwidgets to their project file."

SOURCES += main.cpp

HEADERS += \
    VkWidget.h \
    hellowidget.h \
    normalwidget.h

# Include QNanoPainter
include(../../libqnanopainter/include.pri)

# Include shared examples content
include(../shared/sharedinclude.pri)

# Default rules for deployment.
include(deployment.pri)

win32 {
#    DEFINES *= VK_USE_PLATFORM_WIN32_KHR
    CONFIG(debug, debug|release) {
        LIBS *= -L$$(VULKAN_SDK)/Lib -lvulkan-1 #-lGenericCodeGend -lMachineIndependentd -lOGLCompilerd -lOSDependentd -lglslangd -lspirv-cross-cd -lspirv-cross-cored -lspirv-cross-cppd -lspirv-cross-glsld -lspirv-cross-reflectd -lspirv-cross-utild -lSPIRVd -lSPIRV-Tools-optd -lSPIRV-Toolsd
    } else {
        LIBS *= -L$$(VULKAN_SDK)/Lib -lvulkan-1 #-lGenericCodeGen -lMachineIndependent -lOGLCompiler -lOSDependent -lglslang -lspirv-cross-c -lspirv-cross-core -lspirv-cross-cpp -lspirv-cross-glsl -lspirv-cross-reflect -lspirv-cross-util -lSPIRV -lSPIRV-Tools-opt -lSPIRV-Tools
    }

    #QT_BIN_DIR = $$dirname(QMAKE_QMAKE)
    #DEPLOY_TARGET = $$shell_quote($${DESTDIR}/$${TARGET}.exe)
    #QMAKE_POST_LINK += $$QT_BIN_DIR\\windeployqt --no-compiler-runtime --dir $${DESTDIR} --plugindir $${DESTDIR}/plugins $${DEPLOY_ARGS} $${DEPLOY_TARGET} $$escape_expand(\\n\\t)
}

