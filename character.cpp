#include "character.h"

Character::Character(QString character, std::string def, QObject *parent)
    : character(character), definition(def)
{
    // Init the image
    image = QImage(256, 256, QImage::Format_ARGB32);
    image.fill(Qt::white);

    // Set the painter
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // set the font
    QFont font("Arial", 128, QFont::Bold);
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
}



void Character::exportImage(std::string path){
    image.save(QString::fromStdString(path), "PNG");
}

QImage& Character::getImage(){
    return image;
}
