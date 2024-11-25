#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "character.h"
#include "QMouseEvent"

class Model : public QObject
{
    Q_OBJECT
    bool isPainting;
    bool isMousePressed;
    int characterIndex;
    QList<Character> characterLib;
    QImage canvas;

    QImage creatOverlayImage();
public:
    explicit Model(QObject *parent = nullptr);

public slots:
    void receiveIsBrushPainting(bool isPainting);
    void receiveCleanCanvas();
    void receiveMouseEvent(QPoint pos, bool isMousePressed);

signals:
    void sendOverlayImage(QImage image);
};

#endif // MODEL_H
