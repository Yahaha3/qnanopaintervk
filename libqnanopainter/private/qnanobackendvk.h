#ifndef QNANOBACKENDVK_H
#define QNANOBACKENDVK_H

#include "qnanobackend.h"
#ifdef BUILD_VULKAN_BACKENDS
class QVulkanInstance;
class QVulkanWindow;
class QVulkanDeviceFunctions;
class qnanobackendvk : public QNanoBackend
{
public:
    qnanobackendvk(QVulkanInstance* instance, QVulkanWindow* window);
    const QString backendName() Q_DECL_OVERRIDE;
    NVGcontext* nvgCreate(int flags) Q_DECL_OVERRIDE;
    void nvgDelete(NVGcontext* nvgCtx) Q_DECL_OVERRIDE;
    int nvglCreateImageFromHandle(NVGcontext* ctx, GLuint textureId, int w, int h, int imageFlags) Q_DECL_OVERRIDE;
    NVGparams *internalParams(NVGcontext* nvgCtx) Q_DECL_OVERRIDE;
    void setFlag(NVGcontext* nvgCtx, int flag, bool enable) Q_DECL_OVERRIDE;

    void prepareframe() override;
    void postframe() override;
    void submitframe() override;

    void updateparam(void *uptr/*, VkCommandBuffer buf*/) override;
private:

private:
    VkPhysicalDevice init_vk_gpu(VkInstance instance, VkSurfaceKHR *surface);
    VkCommandBuffer createCmdBuffer(VkDevice device, VkCommandPool cmd_pool);
    VkCommandPool createCmdPool(VkDevice *device, VkPhysicalDevice gpu);
    uint32_t get_graphics_queue_family_index(VkDevice *device, VkPhysicalDevice gpu);

private:
    QVulkanInstance* m_instance;
    QVulkanDeviceFunctions *m_devFuncs;
    QVulkanWindow* m_window;
};
#endif

#endif // QNANOBACKENDVK_H
