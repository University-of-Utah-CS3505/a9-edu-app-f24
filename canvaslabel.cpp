#include "canvaslabel.h"


/// <summary>
/// The CanvasLabel class extends QLabel to enable custom mouse event handling and drawing functionalities.
/// It supports emitting signals for mouse events, providing the position and mouse state for further processing.
/// Team Members: Bingkun Han, Shu Chen, Rohith Veeramachaneni, Ping-Hsun Hsieh
/// Course: CS3500 - A9 Educational App
/// </summary>


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
    painter.drawPixmap(this->rect(), this->pixmap());
}

/**
 * @brief CanvasLabel::mousePressEvent
 * @param event Mouse event received
 *
 *  Emits sendMouseEvent signal on the appropriate mouse button when mouse is moved
 */
void CanvasLabel::mousePressEvent(QMouseEvent *event)
{
    isMousePressed = true;
    QPoint pos = event->pos();
    pos = QPoint(pos.x() * 256 / this->width(), pos.y() * 256 / this->height());
    emit sendMouseEvent(pos, true);
    // QLabel::mousePressEvent(event); // 保持原始事件行为
}

/**
 * @brief CanvasLabel::mouseMoveEvent
 * @param event Pointer to mouse event received
 *
 *  Emits mouseMove signal when mouse is moved
 */
void CanvasLabel::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    pos = QPoint(pos.x() * 256 / this->width(), pos.y() * 256 / this->height());
    emit sendMouseEvent(pos, isMousePressed);
}

/**
 * @brief CanvasLabel::mouseMoveEvent
 * @param event Pointer to mouse event received
 *
 *  Emits mouseRelease signal when mouse is moved
 */
void CanvasLabel::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    pos = QPoint(pos.x() * 256 / this->width(), pos.y() * 256 / this->height());
    isMousePressed = false;
    emit sendMouseEvent(pos, false);
}


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
