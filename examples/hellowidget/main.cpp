/**********************************************************
** Copyright (c) 2018 QUIt Coding <info@quitcoding.com>
**
** This software is provided 'as-is', without any express or implied
** warranty.  In no event will the authors be held liable for any damages
** arising from the use of this software.
**
** Permission is granted to anyone to use this software for any purpose,
** including commercial applications, and to alter it and redistribute it
** freely, subject to the following restrictions:
**
** 1. The origin of this software must not be misrepresented; you must not
**    claim that you wrote the original software. If you use this software
**    in a product, an acknowledgment in the product documentation would be
**    appreciated but is not required.
** 2. Altered source versions must be plainly marked as such, and must not be
**    misrepresented as being the original software.
** 3. This notice may not be removed or altered from any source distribution.
**
**********************************************************/

#include <QApplication>
#include "hellowidget.h"
#include "normalwidget.h"
#include "VkWidget.h"
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    // Select between OpenGL and OpenGL ES (Angle)
    //QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
#endif
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

    QApplication app(argc, argv);
#ifdef BUILD_VULKAN_BACKENDS
    QVulkanInstance inst;

    inst.setLayers(QByteArrayList() << "VK_LAYER_LUNARG_standard_validation");

    if (!inst.create())
        qFatal("Failed to create Vulkan instance: %d", inst.errorCode());

    VulkanWindow *vulkanWindow = new VulkanWindow();
    vulkanWindow->setVulkanInstance(&inst);
//    vulkanWindow->show();

    VkWidget mainWindow(vulkanWindow);
    mainWindow.resize(1200, 800);
    mainWindow.show();

#else
    //    NormalWidget widget;
        HelloWidget widget;
        widget.resize(1200, 800);
        widget.show();
#endif


    return app.exec();
}
