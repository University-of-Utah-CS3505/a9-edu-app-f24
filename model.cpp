#include "model.h"

/*
 * Class: Model
 * Purpose: Handles the core logic for an educational application. It manages the painting canvas,
 *          character crafting, API interactions, and communication with the view through signals.
 * Team Members: Bingkun Han, Shu Chen, Rohith Veeramachaneni, Ping-Hsun Hsieh
 * Course: CS3500 - A9 Educational App
 */
Model::Model(QObject *parent)
    : QObject{parent}
{
    isPainting = true;
    canvas = QImage(QSize(256,256), QImage::Format_ARGB32);
    canvas.fill(Qt::transparent);
    characterIndex = 0;
    characterLib = QList<Character>();
    selectedCharactersForCraft = QList<std::string>();
    initiallizeCharacterLib();

    QTimer::singleShot(1000,[=]{
        for(int i = 0; i < characterLib.size(); i++)
        emit sendNewCharacter(characterLib[i], i);
    });
    jsonEX = R"({\"exists\": true, \"character\": \"炎", \"spell\": \"ya2n" , \"english\": \"really hot, since there are two fire in same place\"})";

}

/*
 * Method: receiveIsBrushPainting
 * Purpose: Updates the painting state (painting or erasing).
 */
void Model::receiveIsBrushPainting(bool isPainting){
    this->isPainting = isPainting;
}

/*
 * Method: receiveCleanCanvas
 * Purpose: Clears the painting canvas and emits an updated overlay image.
 */
void Model::receiveCleanCanvas(){
    canvas.fill(Qt::transparent);
    emit sendOverlayImage(creatOverlayImage());
}

/*
 * Method: receiveMouseEvent
 * Purpose: Handles mouse events to either paint or erase on the canvas.
 * Parameters: pos - Mouse position, isMousePressed - Whether the mouse is pressed.
 */
void Model::receiveMouseEvent(QPoint pos, bool isMousePressed) {
    if (!isMousePressed) return;

    QPainter painter(&canvas);

    if (isPainting) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::black);
        painter.drawEllipse(pos, 7, 7);
    } else {
        // Use composition mode to clear (erase)
        painter.setCompositionMode(QPainter::CompositionMode_Clear);
        painter.setBrush(Qt::transparent);
        painter.drawEllipse(pos, 7, 7);
    }

    emit sendOverlayImage(creatOverlayImage());
    emit sendCorrectness(int(checkCorrectness() * 100));
}

/*
 * Method: creatOverlayImage
 * Purpose: Creates and returns a composite image of the character and the canvas.
 */
QImage Model::creatOverlayImage(){
    QImage result(canvas.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    painter.drawImage(0,0,characterLib[characterIndex].getImage());
    painter.drawImage(0,0,canvas);
    return result;
}

/*
 * Method: checkCorrectness
 * Purpose: Compares the canvas with the target character image to calculate correctness.
 * Returns: Float value representing the correctness percentage.
 */
float Model::checkCorrectness(){
    float correctness = 0;
    float point = 1.0 / characterLib[characterIndex].getBlackPixelCount() * 1.1;

    //QImage img = QImage(256,256, QImage::Format_ARGB32);
    for(int i = 0; i < canvas.width(); i++){
        for(int j = 0; j < canvas.height(); j++){
            int inputVal = canvas.pixelColor(i,j).alpha() == 0 ? 255 : 0; // if it is transprant, set it to white, else black
            int targetVal = characterLib[characterIndex].getImage().pixelColor(i,j).red() < 200 ? 0 : 255;
            if(inputVal == 0){
                if(targetVal == 0){
                    correctness += point;
                }else{
                    correctness -= point / 2.0;
                }
            }
        }
    }
    return correctness;
}

/*
 * Method: receiveGetCharacterRequest
 * Purpose: Emits the requested character from the library.
 * Parameters: index - Index of the requested character.
 */
void Model::receiveGetCharacterRequest(int index){
    emit sendRequestedCharacter(characterLib[index]);
}

/*
 * Method: receiveCraftCharacterRequest
 * Purpose: Handles character crafting using the OpenAI API.
 */
void Model::receiveCraftCharacterRequest(){
    std::ostringstream oss;

    for (std::string& character : selectedCharactersForCraft) {
        oss << character << ",";
    }

    std::string prompt = oss.str();

    selectedCharactersForCraft.clear();

    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    QUrl url("https://api.openai.com/v1/chat/completions");
    QNetworkRequest request(url);

    // Set Http header
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    std::string key = "Bearer "+ apiKey;
    request.setRawHeader("Authorization", QByteArray(key));

    // Set JSON request body
    QJsonObject systemMessage {{"role", "system"}, {"content", QString::fromStdString("你是一个汉字专家, 会尝试把用户提供的独体字或偏旁合并成合体字,一定要用上用户提供的所有偏旁, 如日月合体成明, 一二合成三, 但不能是二. 三个火必须合成焱, 而不是炎. 如果有对应的字, 则在json中输出true, 并给出对应的汉字和解释,先理解用户输入了几个字, 想想汉字偏旁自己的意思和文字的意思,解释一定要是英文,如果没有的话,输出false" + jsonEX)}};
    QJsonObject userMessage {{"role", "user"}, {"content", QString::fromStdString("用户提供的偏旁/独体字是:" + prompt)}};
    QJsonArray messages {systemMessage, userMessage};

    QJsonObject postData;
    postData["model"] = "gpt-4o";
    postData["messages"] = messages;

    QJsonDocument postDataDoc(postData);
    QByteArray postDataBytes = postDataDoc.toJson();

    // send POST Request
    QNetworkReply* reply = networkManager->post(request, postDataBytes);

    // connect method
    connect(reply, &QNetworkReply::finished, this, [this, reply]{
        QString content;
        bool gotJson = false;
        // check error
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseBytes = reply->readAll();
            QJsonParseError jsonError;
            QJsonDocument responseDoc = QJsonDocument::fromJson(responseBytes, &jsonError);

            if (jsonError.error == QJsonParseError::NoError && responseDoc.isObject()) {
                QJsonObject responseObject = responseDoc.object();
                if (responseObject.contains("choices")) {
                    QJsonArray choices = responseObject["choices"].toArray();
                    if (!choices.isEmpty()) {
                        QJsonObject choice = choices.at(0).toObject();
                        if (choice.contains("message")) {
                            QJsonObject message = choice["message"].toObject();
                            if (message.contains("content")) {
                                content = message["content"].toString();
                                gotJson = true;
                            }
                        }
                    }
                }
            } else {
                qDebug() << "JSON parse error:" << jsonError.errorString();
            }
        } else {
            // 显示错误信息
            qDebug() << "Network Error:" << reply->errorString();
        }

        if(gotJson){
            // try to get info from JSON
            QJsonDocument dataDoc = QJsonDocument::fromJson(content.toUtf8());
            QString outputChar;
            QString english;
            QString spell;
            bool found = false;
            if (!dataDoc.isNull() && dataDoc.isObject()) {
                QJsonObject data = dataDoc.object();

                if (data.contains("exists") && data["exists"].toBool()) {
                    outputChar = data["character"].toString();
                    english = data["english"].toString();
                    spell = data["spell"].toString();
                    found = true;
                }
            }

            // if character already exist, return false
            if(found){
                for(Character& c : characterLib){
                    if(c.getCharacter() == outputChar){
                        found = false;
                    }
                }
            }

            emit sendCraftResult(found);
            if(found){
                Character newCharacter(outputChar, spell, english);
                characterLib.push_back(newCharacter);
                emit sendNewCharacter(newCharacter, characterLib.size() - 1);
            }


        }
        reply->deleteLater();
    });

}

/*
 * Method: receiveAPIKey
 * Purpose: Sets the API key for external API requests.
 * Parameters: apiKey - The API key as a string.
 */
void Model::receiveAPIKey(std::string apiKey){
    this->apiKey = apiKey;
}

/*
 * Method: receiveSelectedCharactersIndex
 * Purpose: Updates the current character index and resets the canvas.
 */
void Model::receiveSelectedCharactersIndex(int index){
    if(this->characterIndex != index){
        this->characterIndex = index;
        this->canvas.fill(Qt::transparent);
    }
}

/*
 * Method: receiveSelectedCharacterIndexForCraft
 * Purpose: Adds the selected character to the crafting list.
 * Parameters: index - Index of the character to add.
 */
void Model::receiveSelectedCharacterIndexForCraft(int index){
    selectedCharactersForCraft.append(characterLib[index].getCharacter().toStdString());
    emit sendCraftSelectedCharacter(characterLib[index]);
}

/*
 * Method: initiallizeCharacterLib
 * Purpose: Populates the character library with predefined characters.
 */
void Model::initiallizeCharacterLib(){
    characterLib.clear();
    characterLib.push_back(Character(QString("火"), QString("huo3"), QString("flame, fire")));
    characterLib.push_back(Character(QString("一"), QString("yi1"), QString("number one")));
    characterLib.push_back(Character(QString("子"), QString("zi3"), QString("son, offspring")));
    characterLib.push_back(Character(QString("日"), QString("ri4"), QString("sun")));
    characterLib.push_back(Character(QString("月"), QString("yue4"), QString("moon")));
    characterLib.push_back(Character(QString("木"), QString("mu4"), QString("wood, tree")));
    characterLib.push_back(Character(QString("山"), QString("shan1"), QString("mountain")));
    characterLib.push_back(Character(QString("川"), QString("chuan1"), QString("river")));
    characterLib.push_back(Character(QString("田"), QString("tian2"), QString("field")));
    characterLib.push_back(Character(QString("力"), QString("li4"), QString("strength")));
    characterLib.push_back(Character(QString("口"), QString("kou3"), QString("mouth")));
    characterLib.push_back(Character(QString("大"), QString("da4"), QString("big")));
    characterLib.push_back(Character(QString("天"), QString("tian1"), QString("sky, heaven")));
    characterLib.push_back(Character(QString("水"), QString("shui3"), QString("water")));
    characterLib.push_back(Character(QString("冰"), QString("bing1"), QString("ice")));
    characterLib.push_back(Character(QString("人"), QString("ren2"), QString("person, human")));
    characterLib.push_back(Character(QString("女"), QString("nv3"), QString("woman, female")));
    characterLib.push_back(Character(QString("土"), QString("tu3"), QString("earth, soil")));
    characterLib.push_back(Character(QString("石"), QString("shi2"), QString("stone")));
    characterLib.push_back(Character(QString("金"), QString("jin1"), QString("metal, gold")));
    characterLib.push_back(Character(QString("雨"), QString("yu3"), QString("rain")));
    characterLib.push_back(Character(QString("禾"), QString("he2"), QString("grain, crop")));
    characterLib.push_back(Character(QString("竹"), QString("zhu2"), QString("bamboo")));
}
