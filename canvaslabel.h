#ifndef CANVASLABEL_H
#define CANVASLABEL_H

#include <QPainter>
#include <QLabel>
#include <QObject>
#include <QMouseEvent>

/// <summary>
/// The CanvasLabel class extends QLabel to enable custom mouse event handling and drawing functionalities.
/// It supports emitting signals for mouse events, providing the position and mouse state for further processing.
/// Team Members: Bingkun Han, Shu Chen, Rohith Veeramachaneni, Ping-Hsun Hsieh
/// Course: CS3500 - A9 Educational App
/// </summary>
class CanvasLabel : public QLabel
{
    Q_OBJECT
    bool isMousePressed; ///< Tracks whether the mouse button is currently pressed.

public:
    /// <summary>
    /// Default constructor for CanvasLabel.
    /// </summary>
    CanvasLabel();

    /// <summary>
    /// Constructs a CanvasLabel with the specified text and an optional parent widget.
    /// </summary>
    explicit CanvasLabel(const QString &text, QWidget *parent = nullptr);

    /// <summary>
    /// Constructs a CanvasLabel with an optional parent widget.
    /// </summary>
    explicit CanvasLabel(QWidget *parent = nullptr);

protected:
    /// <summary>
    /// Handles mouse press events and updates the isMousePressed state.
    /// </summary>
    void mousePressEvent(QMouseEvent *event) override;

    /// <summary>
    /// Handles mouse move events and emits the current position and press state.
    /// </summary>
    void mouseMoveEvent(QMouseEvent *event) override;

    /// <summary>
    /// Handles mouse release events and updates the isMousePressed state.
    /// </summary>
    void mouseReleaseEvent(QMouseEvent *event) override;

    /// <summary>
    /// Handles custom painting logic for the CanvasLabel.
    /// </summary>
    void paintEvent(QPaintEvent *event) override;

private:
    /// <summary>
    /// Converts a global mouse position to the local widget's coordinate system.
    /// </summary>
    QPointF convertToLocalPosition(const QPointF &pos);

signals:
    /// <summary>
    /// Signal emitted to provide mouse event data, including position and press state.
    /// </summary>
    void sendMouseEvent(QPoint pos, bool isMousePressed);
};

#endif // CANVASLABEL_H
