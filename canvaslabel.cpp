#include "canvaslabel.h"


/**
 * @brief CanvasLabel::CanvasLabel
 *
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of canvasLabel.cpp : Shu Chen
 *
 *  Date Modified : November 10, 2024
 *
 *  CanvasLabel class contains methods such as paintEvent,setOffset, mousePressEvent,
 *  mouseMove, mouseRelease, wheelEvent to simulate a canvas object

 */


///
/// \brief CanvasLabel::CanvasLabel
///
///  Default constructor
///
CanvasLabel::CanvasLabel() {}

///
/// \brief CanvasLabel::CanvasLabel
/// \param text
/// \param parent
///
CanvasLabel::CanvasLabel(const QString &text, QWidget *parent) : QLabel(text, parent)
{
}

CanvasLabel::CanvasLabel(QWidget *parent) : QLabel("", parent)
{
}

/**
 * @brief CanvasLabel::paintEvent
 * @param event
 */
void CanvasLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(offset, this->pixmap());
}

/**
 * @brief CanvasLabel::setOffset
 * @param offset new offset in Floating point type
 *
 *  Sets offset of current canvas to be the new offsey
 */
void CanvasLabel::setOffset(const QPointF &offset)
{
    this->offset = offset;
}

/**
 * @brief CanvasLabel::mousePressEvent
 * @param event Mouse event received
 *
 *  Emits sendMouseEvent signal on the appropriate mouse button when mouse is moved
 */
void CanvasLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit sendMouseEvent(MouseButton(leftButtonDown, convertToLocalPosition(event->pos()), 1));
    }
    else if (event->button() == Qt::RightButton)
    {
        emit sendMouseEvent(MouseButton(rightButtonDown, convertToLocalPosition(event->pos()), 1));
    }
    QLabel::mousePressEvent(event); // 保持原始事件行为
}

/**
 * @brief CanvasLabel::mouseMoveEvent
 * @param event Pointer to mouse event received
 *
 *  Emits mouseMove signal when mouse is moved
 */
void CanvasLabel::mouseMoveEvent(QMouseEvent *event)
{
    emit sendMouseEvent(MouseButton(mouseMove, convertToLocalPosition(event->pos()), 1));
}

/**
 * @brief CanvasLabel::mouseMoveEvent
 * @param event Pointer to mouse event received
 *
 *  Emits mouseRelease signal when mouse is moved
 */
void CanvasLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit sendMouseEvent(MouseButton(leftButtonUp, convertToLocalPosition(event->pos()), 1));
    }
    else if (event->button() == Qt::RightButton)
    {
        emit sendMouseEvent(MouseButton(rightButtonUp, convertToLocalPosition(event->pos()), 1));
    }
}

/**
 * @brief CanvasLabel::wheelEvent
 * @param event Pointer to mouse event received
 *
 *  Emits mouse event signal with middleButtonScroll button
 */
void CanvasLabel::wheelEvent(QWheelEvent *event)
{
    // 获取滚动的角度
    QPointF delta = event->angleDelta();
    emit sendMouseEvent(MouseButton(middleButtonScroll, convertToLocalPosition(event->position()), delta.y()));
};

/**
 * @brief CanvasLabel::convertToLocalPosition
 * @param pos Reference to the position of type Floating point that should be converted
 *            to local position relative to canvas
 *
 *
 * @return Local position of the position given in argument
 */
QPointF CanvasLabel::convertToLocalPosition(const QPointF &pos)
{
    QPixmap pixmap = this->pixmap();
    if (pixmap.isNull())
        return QPointF(-10000, -10000);
    // 获取 QLabel 的尺寸和 QPixmap 的实际尺寸
    QSize labelSize = this->size();
    QSize pixmapSize = pixmap.size();
    QPointF picTopLeftRelToLableTopLeft = QPointF(labelSize.width() - pixmapSize.width(),
                                                  labelSize.height() - pixmapSize.height()) /
                                          2.0;

    return (pos - picTopLeftRelToLableTopLeft);
}
