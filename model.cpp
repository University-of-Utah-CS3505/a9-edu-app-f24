#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}
{
    isPainting = true;
    canvas = QImage(QSize(256,256), QImage::Format_ARGB32);
    characterIndex = 0;
    characterLib = QList<Character>();
    characterLib.push_back(Character(QString("我"),"me"));
}

void Model::receiveIsBrushPainting(bool isPainting){
    this->isPainting = isPainting;
}

void Model::receiveCleanCanvas(){
    canvas.fill(Qt::transparent);
}

void Model::receiveMouseEvent(QPoint pos, bool isMousePressed){
    qDebug() << pos;
    if(!isMousePressed) return;

    QPainter painter(&canvas);
    painter.setPen(Qt::NoPen);     // no border
    if(isPainting){
        painter.setBrush(Qt::black); // inside color
    }else{
        painter.setBrush(Qt::transparent);
    }
    painter.drawEllipse(pos, 5, 5);

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



