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
    qDebug() << "correctness" << checkCorrectness();
}

QImage Model::creatOverlayImage(){
    QImage result(canvas.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    painter.drawImage(0,0,characterLib[characterIndex].getImage());
    painter.drawImage(0,0,canvas);
    return result;
}

float Model::checkCorrectness(){
    float correctness = 0;
    float point = 1.0 / 65536.0;
    //QImage img = QImage(256,256, QImage::Format_ARGB32);
    for(int i = 0; i < canvas.width(); i++){
        for(int j = 0; j < canvas.height(); j++){
            int inputVal = canvas.pixelColor(i,j).alpha() == 0 ? 255 : 0; // if it is transprant, set it to white, else black
            int targetVal = characterLib[characterIndex].getImage().pixelColor(i,j).red() < 200 ? 0 : 255;
            //img.setPixelColor(i,j,QColor(inputVal,0,targetVal));
            if(inputVal == targetVal){
                correctness += point;
            }
        }
    }
    //emit sendOverlayImage(img);
    return correctness;
}


