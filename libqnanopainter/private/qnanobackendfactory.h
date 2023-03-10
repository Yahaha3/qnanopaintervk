#ifndef QNANOBACKENDFACTORY_H
#define QNANOBACKENDFACTORY_H

#ifdef QNANO_BUILD_GL_BACKENDS
#include "private/qnanobackendgl2.h"
#include "private/qnanobackendgl3.h"
#endif
#ifdef QNANO_BUILD_GLES_BACKENDS
#include "private/qnanobackendgles2.h"
#include "private/qnanobackendgles3.h"
#endif

#ifdef BUILD_VULKAN_BACKENDS
#include "private/qnanobackendvk.h"
class QVulkanInstance;
class QVulkanWindow;
#endif

class QNanoBackendFactory
{
public:

    static QNanoBackend *createBackend(int major, int minor, bool isGLES) {

#ifndef QNANO_ENABLE_GLES3
        // OpenGL ES 3.0 is disabled, so force ES 2.0 backend
        if (isGLES) {
            major = 2;
            minor = 0;
        }
#endif

        qDebug("Creating suitable QNanoBackend for %s %d.%d context", (isGLES ? "OpenGL ES" : "OpenGL"), major, minor);

        if (isGLES) {
#if defined(QNANO_BUILD_GLES_BACKENDS)
            if (major >= 3) {
                return new QNanoBackendGLES3();
            } else {
                return new QNanoBackendGLES2();
            }
#endif
        } else {
#if defined(QNANO_BUILD_GL_BACKENDS)
            if (major > 3 || (major == 3 && minor >= 2)) {
                return new QNanoBackendGL3();
            } else {
                return new QNanoBackendGL2();
            }
#endif
        }
        qWarning("Creating QNanoBackend for %s %d.%d failed!", (isGLES ? "OpenGL ES" : "OpenGL"), major, minor);
        return nullptr;
    }
#ifdef BUILD_VULKAN_BACKENDS
    static QNanoBackend *createBackendVk(QVulkanInstance* instance, QVulkanWindow* window){
        return new qnanobackendvk(instance, window);
    }
#endif
};

#endif // QNANOBACKENDFACTORY_H
