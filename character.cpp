#include "character.h"

/**
 * @brief Constructs a Character object with the provided data and initializes its image.
 * @param character The character to represent.
 * @param spell The spelling of the character.
 * @param def The definition of the character.
 * @param parent Optional QObject parent (default is nullptr).
 */
Character::Character(QString character, QString spell, QString def, QObject *parent)
    : character(character), spell(spell), definition(def)
{
    // Initialize a blank 256x256 white image
    image = QImage(256, 256, QImage::Format_ARGB32);
    image.fill(Qt::white);

    // Set up a QPainter to render text onto the image
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // Configure the font for drawing the character
    QFont font("悠哉字体 Medium", 128, QFont::Bold);
    painter.setFont(font);
    painter.setPen(QColor(128, 128, 128)); // Gray color for the text

    // Calculate the size and position to center the character text
    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(character);
    int textHeight = metrics.height();
    int x = (image.width() - textWidth) / 2;
    int y = (image.height() + textHeight) / 2 - metrics.descent();

    // Draw the character text at the calculated position
    painter.drawText(x, y, character);

    // Finalize painting
    painter.end();

    blackPixelCount = 0;

    // Count the number of gray pixels (red = 128) in the image
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            if (image.pixelColor(i, j).red() == 128) {
                blackPixelCount++;
            }
        }
    }
}

/**
 * @brief Retrieves the count of black (gray) pixels in the character's image.
 * @return The number of black pixels.
 */
int Character::getBlackPixelCount() {
    return blackPixelCount;
}

/**
 * @brief Exports the character's image to a file in PNG format.
 * @param path The file path where the image will be saved.
 */
void Character::exportImage(std::string path) {
    image.save(QString::fromStdString(path), "PNG");
}

/**
 * @brief Provides access to the character's image.
 * @return A reference to the QImage of the character.
 */
QImage& Character::getImage() {
    return image;
}

/**
 * @brief Provides access to the character string.
 * @return A reference to the QString of the character.
 */
QString& Character::getCharacter() {
    return character;
}

/**
 * @brief Provides access to the definition of the character.
 * @return A reference to the QString containing the character's definition.
 */
QString& Character::getDef() {
    return definition;
}

/**
 * @brief Provides access to the spelling of the character.
 * @return A reference to the QString containing the character's spelling.
 */
QString& Character::getSpell() {
    return spell;
}
