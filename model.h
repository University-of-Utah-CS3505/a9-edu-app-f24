#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "character.h"
#include "QMouseEvent"
#include "QTimer"
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <sstream>

class Model : public QObject
{
    Q_OBJECT
    bool isPainting;
    bool isMousePressed;
    int characterIndex;
    std::string jsonEX;
    std::string apiKey;
    QList<Character> characterLib;
    QList<std::string> selectedCharactersForCraft;
    QImage canvas;

    QImage creatOverlayImage();

    float checkCorrectness();

    void initiallizeCharacterLib();
public:
    explicit Model(QObject *parent = nullptr);

public slots:
    void receiveIsBrushPainting(bool isPainting);
    void receiveCleanCanvas();
    void receiveMouseEvent(QPoint pos, bool isMousePressed);
    void receiveGetCharacterRequest(int index);


    void receiveCraftCharacterRequest();
    ///
    /// \brief receiveAPIKey receive the api key then store it in model
    /// \param apiKey
    ///
    void receiveAPIKey(std::string apiKey);

    ///
    /// \brief receiveSelectedCharactersIndex receive the index, only for edu app class!
    /// \param index
    ///
    void receiveSelectedCharactersIndex(int index);

    ///
    /// \brief receiveSelectedCharacterIndexForCraft only for craft character class!
    /// \param index
    ///
    void receiveSelectedCharacterIndexForCraft(int index);


signals:
    ///
    /// \brief sendOverlayImage update the canvas. image is user's drawed overlayed on a character image
    /// \param image
    ///
    void sendOverlayImage(QImage image);
    ///
    /// \brief sendNewCharacter this method will send ui a new character to make new button.
    /// \param character
    /// \param index
    ///
    void sendNewCharacter(Character& character, int index);
    ///
    /// \brief sendRequestedCharacter this is the result of the "receiveCraftCharacterRequest", give character ui want (Only for Edu app class)
    /// \param character
    ///
    void sendRequestedCharacter(Character& character);
    ///
    /// \brief sendCraftResult if there is a new character found, then return true, else return false
    /// \param isThereNewCharacter
    ///
    void sendCraftResult(bool isThereNewCharacter);

    void sendCorrectness(int correctness);

    ///
    /// \brief sendCraftSelectedCharacter This is for craft ui.
    /// \param character
    ///
    void sendCraftSelectedCharacter(const Character& character);
};

#endif // MODEL_H
