#ifndef QNANOWIDGETVK_H
#define QNANOWIDGETVK_H

#include <QWidget>
#include <QVulkanWindow>

class VulkanWindow;
class QNanoPainter;
class QVulkanDeviceFunctions;

class QNanoWidgetVk: public QWidget
{
    Q_OBJECT
public:
    explicit QNanoWidgetVk(VulkanWindow *w, QWidget* parent = nullptr);
    QNanoPainter *painter() const;
    void debug();

protected:
    virtual void paint(QNanoPainter* painter);
    bool event(QEvent *event) override;

signals:
    void sig_vk_widget_event(QEvent *);

private slots:
    void slot_readypaint(QNanoPainter* painter);
private:
    void prepaint(QNanoPainter* painter);
    void postpaint(QNanoPainter* painter);

private:
    VulkanWindow *m_window;
};

class QNanoVulkanRenderer : public QVulkanWindowRenderer
{
public:
    QNanoVulkanRenderer(VulkanWindow *w);

    void initResources() override;
    void startNextFrame() override;

protected:

    VulkanWindow *m_window;
    QNanoPainter* m_painter;
    QVulkanDeviceFunctions* m_dev_func;

private:
    bool inited_ = false;
};


class VulkanWindow : public QVulkanWindow
{
    Q_OBJECT

public:
    QVulkanWindowRenderer *createRenderer() override;
    bool event(QEvent *) override;

signals:
    void sig_readypaint(QNanoPainter* painter);
    void sig_window_event(QEvent *);

private:

    friend class QNanoVulkanRenderer;
    friend class QNanoWidgetVk;
};

#endif // QNANOWIDGETVK_H
