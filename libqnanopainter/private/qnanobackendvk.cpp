#include "qnanobackendvk.h"

#ifdef BUILD_VULKAN_BACKENDS
#include "nanovg/nanovg.h"
#define NANOVG_VULKAN_IMPLEMENTATION
#include "nanovg/nanovg_vk.h"

#include <QVulkanInstance>
#include <QVulkanWindow>
#include <QVulkanDeviceFunctions>

qnanobackendvk::qnanobackendvk(QVulkanInstance *instance, QVulkanWindow *window)
    : m_instance(instance), m_window(window)
{

}

const QString qnanobackendvk::backendName()
{
    return "Vulkan";
}

NVGcontext *qnanobackendvk::nvgCreate(int flags)
{
    auto device = m_window->device();
    auto renderpass = m_window->defaultRenderPass();
    auto gpu = m_window->physicalDevice();
    auto queue = m_window->graphicsQueue();
    auto buf = m_window->currentCommandBuffer();
    m_devFuncs = m_window->vulkanInstance()->deviceFunctions(device);

    VKNVGCreateInfo create_info = {0};
    create_info.device =device;
    create_info.gpu = gpu;
    create_info.renderpass = renderpass;
    create_info.cmdBuffer = buf;

//    return  NULL;
    return nvgCreateVk(create_info, flags, queue);
}

void qnanobackendvk::nvgDelete(NVGcontext *nvgCtx)
{
//    nvgCtx->params.userPtr;
    nvgDeleteVk(nvgCtx);
}

int qnanobackendvk::nvglCreateImageFromHandle(NVGcontext *ctx, GLuint textureId, int w, int h, int imageFlags)
{
    return 1;
//    return nvglCreateImageFromHandle()
}

NVGparams *qnanobackendvk::internalParams(NVGcontext *nvgCtx)
{
    return nvgInternalParams(nvgCtx);
}

void qnanobackendvk::setFlag(NVGcontext *nvgCtx, int flag, bool enable)
{
    QNANOBACKEND_SETFLAG_VK(nvgCtx, flag, enable)
}

void qnanobackendvk::prepareframe()
{
    // vulkan prepare frame
//    const QSize sz = m_window->swapChainImageSize();

//    VkClearColorValue clearColor = {{ 0, 0, 0, 1 }};
//    VkClearDepthStencilValue clearDS = { 1, 0 };
//    VkClearValue clearValues[3];
//    memset(clearValues, 0, sizeof(clearValues));
//    clearValues[0].color = clearValues[2].color = clearColor;
//    clearValues[1].depthStencil = clearDS;

//    VkRenderPassBeginInfo rpBeginInfo;
//    memset(&rpBeginInfo, 0, sizeof(rpBeginInfo));
//    rpBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
//    rpBeginInfo.renderPass = m_window->defaultRenderPass();
//    rpBeginInfo.framebuffer = m_window->currentFramebuffer();
//    rpBeginInfo.renderArea.extent.width = sz.width();
//    rpBeginInfo.renderArea.extent.height = sz.height();
//    rpBeginInfo.clearValueCount = m_window->sampleCountFlagBits() > VK_SAMPLE_COUNT_1_BIT ? 3 : 2;
//    rpBeginInfo.pClearValues = clearValues;
//    VkCommandBuffer cmdBuf = m_window->currentCommandBuffer();
//    m_devFuncs->vkCmdBeginRenderPass(cmdBuf, &rpBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void qnanobackendvk::postframe()
{
//    const QSize sz = m_window->swapChainImageSize();
//    VkViewport viewport;
//    viewport.x = viewport.y = 0;
//    viewport.width = sz.width();
//    viewport.height = sz.height();
//    viewport.minDepth = 0;
//    viewport.maxDepth = 1;
//    m_devFuncs->vkCmdSetViewport(cmd_buf_, 0, 1, &viewport);

//    VkRect2D scissor;
//    scissor.offset.x = scissor.offset.y = 0;
//    scissor.extent.width = viewport.width;
//    scissor.extent.height = viewport.height;
//    m_devFuncs->vkCmdSetScissor(cmd_buf_, 0, 1, &scissor);
}

void qnanobackendvk::submitframe()
{
//    m_devFuncs->vkCmdEndRenderPass(cmd_buf_);
//    m_window->frameReady();
    //    m_window->requestUpdate();
}

void qnanobackendvk::updateparam(void *uptr/*, VkCommandBuffer cmd_buf*/)
{
    VKNVGcontext *vk = (VKNVGcontext *)uptr;
    vk->createInfo.cmdBuffer = m_window->currentCommandBuffer();
}

VkPhysicalDevice qnanobackendvk::init_vk_gpu(VkInstance instance, VkSurfaceKHR *surface)
{  VkResult res;
    uint32_t gpu_count = 0;

    res = vkEnumeratePhysicalDevices(instance, &gpu_count, NULL);
    if (VK_SUCCESS != res && res != VK_INCOMPLETE) {
      printf("vkEnumeratePhysicalDevices failed %d \n", res);
      exit(-1);
    }
    if (gpu_count < 1){
      printf("No Vulkan device found.\n");
      exit(-1);
    }

    VkPhysicalDevice gpu[32];
    res = vkEnumeratePhysicalDevices(instance, &gpu_count, gpu);
    if (res != VK_SUCCESS && res != VK_INCOMPLETE) {
      printf("vkEnumeratePhysicalDevices failed %d \n", res);
      exit(-1);
    }

    uint32_t idx = 0;
    bool use_idx = false;
    bool discrete_idx = false;
    for (uint32_t i = 0; i < gpu_count && (!discrete_idx); i++)
    {
      uint32_t qfc = 0;
      vkGetPhysicalDeviceQueueFamilyProperties(gpu[i], &qfc, NULL);
      if (qfc < 1)continue;

      VkQueueFamilyProperties *queue_family_properties;
      queue_family_properties = (VkQueueFamilyProperties*)malloc(qfc * sizeof(VkQueueFamilyProperties));

      vkGetPhysicalDeviceQueueFamilyProperties(gpu[i], &qfc, queue_family_properties);

      for (uint32_t j = 0; j < qfc; j++)
      {
        VkBool32 supports_present;
        vkGetPhysicalDeviceSurfaceSupportKHR(gpu[i], j, *surface, &supports_present);

        if ((queue_family_properties[j].queueFlags & VK_QUEUE_GRAPHICS_BIT) && supports_present)
        {

          VkPhysicalDeviceProperties pr;
          vkGetPhysicalDeviceProperties(gpu[i], &pr);
          idx = i;
          use_idx = true;
          if(pr.deviceType==VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
            discrete_idx = true;
          }
          break;
        }
      }
      free(queue_family_properties);
    }
    if (!use_idx){
        printf("Not found suitable queue which supports graphics.\n");
        exit(-1);
    }

    printf("Using GPU device %lu\n", (unsigned long) idx);
    return gpu[idx];
}

VkCommandBuffer qnanobackendvk::createCmdBuffer(VkDevice device, VkCommandPool cmd_pool)
{
    VkResult res;
    VkCommandBufferAllocateInfo cmd = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
    cmd.commandPool = cmd_pool;
    cmd.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmd.commandBufferCount = 1;

    VkCommandBuffer cmd_buffer;
    res = vkAllocateCommandBuffers(device, &cmd, &cmd_buffer);
    assert(res == VK_SUCCESS);
    return cmd_buffer;
}

VkCommandPool qnanobackendvk::createCmdPool(VkDevice *device, VkPhysicalDevice gpu)
{
    VkResult res;
    uint32_t queue_family_index = get_graphics_queue_family_index(device, gpu);
    /* Create a command pool to allocate our command buffer from */
    VkCommandPoolCreateInfo cmd_pool_info = {VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
    cmd_pool_info.queueFamilyIndex = queue_family_index;
    cmd_pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    VkCommandPool cmd_pool;
    res = vkCreateCommandPool(*device, &cmd_pool_info, NULL, &cmd_pool);
    assert(res == VK_SUCCESS);
    return cmd_pool;
}

uint32_t qnanobackendvk::get_graphics_queue_family_index(VkDevice *device, VkPhysicalDevice gpu)
{
    uint32_t family_properties_count;
    vkGetPhysicalDeviceQueueFamilyProperties(gpu, &family_properties_count, NULL);
    assert(family_properties_count >= 1);

    auto queueFamilyProperties = (VkQueueFamilyProperties *)malloc(family_properties_count * sizeof(VkQueueFamilyProperties));

    vkGetPhysicalDeviceQueueFamilyProperties(gpu, &family_properties_count, queueFamilyProperties);
    assert(family_properties_count >= 1);

    uint32_t graphics_queue_family_index = UINT32_MAX;
    for (uint32_t i = 0; i < family_properties_count; ++i) {
        if ((queueFamilyProperties->queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
            graphics_queue_family_index = i;
        }
    }
    return graphics_queue_family_index;
}
#endif
