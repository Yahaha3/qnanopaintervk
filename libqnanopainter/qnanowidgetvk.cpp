#include "qnanowidgetvk.h"

#include "qnanopainter.h"
#include "vulkan/vulkan.h"
#include <QVBoxLayout>
#include <QVulkanInstance>
#include <QVulkanWindow>
#include <QVulkanDeviceFunctions>
#include <QCoreApplication>
#include <sstream>
#include <iostream>

QNanoWidgetVk::QNanoWidgetVk(VulkanWindow *w, QWidget *parent)
    : QWidget(parent)
    , m_window(w)
{
    QWidget *wrapper = QWidget::createWindowContainer(w);
    connect(w, &VulkanWindow::sig_readypaint, this, &QNanoWidgetVk::slot_readypaint);
    connect(w, &VulkanWindow::sig_window_event, this, &QNanoWidgetVk::sig_vk_widget_event);
    auto *layout = new QHBoxLayout;
    layout->addWidget(wrapper);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

void QNanoWidgetVk::debug()
{
}

void QNanoWidgetVk::paint(QNanoPainter *painter)
{
    Q_UNUSED(painter);
}

bool QNanoWidgetVk::event(QEvent *event)
{
//    std::cout << "[vulkan] widget render event " << event->type() << std::endl;
    return QWidget::event(event);
}

void QNanoWidgetVk::slot_readypaint(QNanoPainter *painter)
{
    paint(painter);
}

void QNanoWidgetVk::prepaint(QNanoPainter *painter)
{
//    nvgBeginFrame(painter->nvgCtx(),
//                  m_window->width(), m_window->height(),
//                  devicePixelRatio());
}

void QNanoWidgetVk::postpaint(QNanoPainter *painter)
{
//    nvgEndFrame(painter->nvgCtx());
}


QNanoVulkanRenderer::QNanoVulkanRenderer(VulkanWindow *w)
    : m_window(w)
{
}

void QNanoVulkanRenderer::initResources()
{
    auto device = m_window->device();
    m_dev_func = m_window->vulkanInstance()->deviceFunctions(device);
}

void QNanoVulkanRenderer::startNextFrame()
{
    auto cb = m_window->currentCommandBuffer();
    if(inited_){
        auto param = m_painter->m_backend->internalParams(m_painter->nvgCtx());
        m_painter->m_backend->updateparam(param->userPtr/*, cb*/);

    }
#ifdef BUILD_VULKAN_BACKENDS
    if(!inited_){
        m_painter = QNanoPainter::getInstance();
        m_painter->vulkan_init_create(m_window->vulkanInstance(), m_window);
        inited_ = true;
    }
#endif

    const QSize sz = m_window->swapChainImageSize();

    VkClearColorValue clearColor = {{ 0.67f, 0.67f, 0.67f, 1.0f }};
    VkClearDepthStencilValue clearDS = { 1, 0 };
    VkClearValue clearValues[3];
    memset(clearValues, 0, sizeof(clearValues));
    clearValues[0].color = clearValues[2].color = clearColor;
//    clearValues[0].color = clearColor;
    clearValues[1].depthStencil = clearDS;

    VkRenderPassBeginInfo rpBeginInfo;
    memset(&rpBeginInfo, 0, sizeof(rpBeginInfo));
    rpBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpBeginInfo.renderPass = m_window->defaultRenderPass();
    rpBeginInfo.framebuffer = m_window->currentFramebuffer();
    rpBeginInfo.renderArea.extent.width = sz.width();
    rpBeginInfo.renderArea.extent.height = sz.height();
    rpBeginInfo.clearValueCount = m_window->sampleCountFlagBits() > VK_SAMPLE_COUNT_1_BIT ? 3 : 2;
    rpBeginInfo.pClearValues = clearValues;

    auto buf = m_window->currentCommandBuffer();
    m_dev_func->vkCmdBeginRenderPass(buf, &rpBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    VkViewport viewport;
    viewport.x = viewport.y = 0;
    viewport.width = sz.width();
    viewport.height = sz.height();
    viewport.minDepth = 0;
    viewport.maxDepth = 1;
    m_dev_func->vkCmdSetViewport(cb, 0, 1, &viewport);

    VkRect2D scissor;
    scissor.offset.x = scissor.offset.y = 0;
    scissor.extent.width = viewport.width;
    scissor.extent.height = viewport.height;
    m_dev_func->vkCmdSetScissor(cb, 0, 1, &scissor);

    nvgBeginFrame(m_painter->nvgCtx(),
                  m_window->width(), m_window->height(),
                  m_window->devicePixelRatio());

//    if(!m_window->frozen)
    {
        emit static_cast<VulkanWindow *>(m_window)->sig_readypaint(m_painter);
    }

    nvgEndFrame(m_painter->nvgCtx());
    m_dev_func->vkCmdEndRenderPass(buf);

    m_window->frameReady();
    m_window->requestUpdate();
}

QVulkanWindowRenderer *VulkanWindow::createRenderer()
{
    std::cout << "[vulkan] window render create " << std::endl;
    return new QNanoVulkanRenderer(this);
}

bool VulkanWindow::event(QEvent *e)
{
//    std::cout << "[vulkan] window render event " << e->type() << std::endl;
    auto res = QVulkanWindow::event(e);
    emit sig_window_event(e);
    return res;
}
