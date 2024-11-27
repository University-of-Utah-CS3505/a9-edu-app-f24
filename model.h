#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "character.h"
#include "QMouseEvent"
#include "QTimer"

class Model : public QObject
{
    Q_OBJECT
    bool isPainting;
    bool isMousePressed;
    int characterIndex;
    QList<Character> characterLib;
    QImage canvas;

    QImage creatOverlayImage();

    float checkCorrectness();
public:
    explicit Model(QObject *parent = nullptr);

public slots:
    void receiveIsBrushPainting(bool isPainting);
    void receiveCleanCanvas();
    void receiveMouseEvent(QPoint pos, bool isMousePressed);
    void receiveGetCharacterRequest(int index);

signals:
    void sendOverlayImage(QImage image);
    void sendNewCharacter(Character& character, int index);
    void sendRequestedCharacter(Character& character);
};

#endif // MODEL_H
