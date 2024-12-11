#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QImage>
#include <QPainter>

/**
 * @class Character
 * @brief Represents a character with its associated spelling, definition, and image.
 *
 * This class provides functionality to manage a character's data and export its image.
 *
 * Team Members: Bingkun Han, Shu Chen, Rohith Veeramachaneni, Ping-Hsun Hsieh
 * Course: CS3500 - A9 Educational App
 */
class Character
{
    QString character; ///< The character represented as a QString.
    QString spell; ///< The spelling of the character.
    QString definition; ///< The definition of the character.
    QImage image; ///< The image associated with the character.
    int blackPixelCount; ///< The count of black pixels in the image.

public:
    /**
     * @brief Constructs a Character object.
     * @param character The character.
     * @param spell The spelling of the character.
     * @param def The definition of the character.
     * @param parent Optional QObject parent (default is nullptr).
     */
    explicit Character(QString character, QString spell, QString def, QObject *parent = nullptr);

    /**
     * @brief Exports the character's image to the specified path.
     * @param path The file path where the image will be saved.
     */
    void exportImage(std::string path);

    /**
     * @brief Retrieves the count of black pixels in the character's image.
     * @return The number of black pixels.
     */
    int getBlackPixelCount();

    /**
     * @brief Provides access to the character's image.
     * @return A reference to the character's QImage.
     */
    QImage& getImage();

    /**
     * @brief Provides access to the character's QString representation.
     * @return A reference to the character QString.
     */
    QString& getCharacter();

    /**
     * @brief Provides access to the character's definition.
     * @return A reference to the definition QString.
     */
    QString& getDef();

    /**
     * @brief Provides access to the character's spelling.
     * @return A reference to the spelling QString.
     */
    QString& getSpell();

signals:
};

#endif // CHARACTER_H
