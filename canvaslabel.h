#ifndef CANVASLABEL_H
#define CANVASLABEL_H

#include <QPainter>
#include <QLabel>
#include <QObject>
#include <QMouseEvent>

/**
 * @brief The CanvasLabel class
 *
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of canvasLabel.h : Shu Chen
 *
 *  Date Modified : November 10, 2024

 *  Header class for canvas Label class
 */
class CanvasLabel : public QLabel
{
    Q_OBJECT
    bool isMousePressed;

public:
    CanvasLabel();
    explicit CanvasLabel(const QString &text, QWidget *parent = nullptr);
    explicit CanvasLabel(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private:
    QPointF convertToLocalPosition(const QPointF &pos);

signals:
    void sendMouseEvent(QPoint pos, bool isMousePressed);
};

#endif // CANVASLABEL_H
