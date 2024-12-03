#include "character.h"

Character::Character(QString character, QString spell, QString def, QObject *parent)
    : character(character), spell(spell), definition(def)
{

    // Init the image
    image = QImage(256, 256, QImage::Format_ARGB32);
    image.fill(Qt::white);

    // Set the painter
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // set the font
    QFont font("悠哉字体 Medium", 128, QFont::Bold);
    painter.setFont(font);
    painter.setPen(QColor(128,128,128));

    // cal the size of the font
    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(character);
    int textHeight = metrics.height();

    // cal the center
    int x = (image.width() - textWidth) / 2;
    int y = (image.height() + textHeight) / 2 - metrics.descent();

    // draw on center
    painter.drawText(x, y, character);

    // end printing
    painter.end();

    blackPixelCount = 0;
    //calculate black pixel count
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 256; j++){
            if(image.pixelColor(i,j).red() == 128){
                blackPixelCount ++;
            }
        }
    }
}

int Character::getBlackPixelCount(){
    return blackPixelCount;
}

void Character::exportImage(std::string path){
    image.save(QString::fromStdString(path), "PNG");
}

QImage& Character::getImage(){
    return image;
}

QString& Character::getCharacter(){
    return character;
}

QString& Character::getDef(){
    return definition;
}

QString& Character::getSpell(){
    return spell;
}
