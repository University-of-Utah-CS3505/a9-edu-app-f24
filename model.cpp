#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}
{
    isPainting = true;
    canvas = QImage(QSize(256,256), QImage::Format_ARGB32);
    canvas.fill(Qt::transparent);
    characterIndex = 0;
    characterLib = QList<Character>();
    characterLib.push_back(Character(QString("我"),"me"));
}

void Model::receiveIsBrushPainting(bool isPainting){
    this->isPainting = isPainting;
}

void Model::receiveCleanCanvas(){
    canvas.fill(Qt::transparent);
    emit sendOverlayImage(creatOverlayImage());
}

void Model::receiveMouseEvent(QPoint pos, bool isMousePressed) {
    qDebug() << pos;
    if (!isMousePressed) return;

    QPainter painter(&canvas);

    if (isPainting) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::black);
        painter.drawEllipse(pos, 5, 5);
    } else {
        // Use composition mode to clear (erase)
        painter.setCompositionMode(QPainter::CompositionMode_Clear);
        painter.setBrush(Qt::transparent);
        painter.drawEllipse(pos, 5, 5);
    }

    emit sendOverlayImage(creatOverlayImage());
}

QImage Model::creatOverlayImage(){
    QImage result(canvas.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    painter.drawImage(0,0,characterLib[characterIndex].getImage());
    painter.drawImage(0,0,canvas);
    return result;
}



