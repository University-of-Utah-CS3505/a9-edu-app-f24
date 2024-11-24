#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "character.h"
#include "QMouseEvent"

class Model : public QObject
{
    Q_OBJECT
    QList<Character> frameSequence;
    QImage canvas;
public:
    explicit Model(QObject *parent = nullptr);

public slots:
    void receiveIsBrushPainting(bool isPainting);
    void receiveCleanCanvas();
    void receiveMouseEvent(QMouseEvent *event);

signals:
};

#endif // MODEL_H
