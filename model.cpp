#include "model.h"


Model::Model(QObject *parent)
    : QObject{parent}
{
    isPainting = true;
    canvas = QImage(QSize(256,256), QImage::Format_ARGB32);
    canvas.fill(Qt::transparent);
    characterIndex = 0;
    characterLib = QList<Character>();
    characterLib.push_back(Character(QString("我"), QString("wo2"), QString("me")));
    QTimer::singleShot(1000,[=]{emit sendNewCharacter(characterLib[0], 0);});
    jsonEX = R"({\"exists\": true, \"character\": \"炎", \"spell\": \"ya2n" , \"english\": \"really hot, since there are two fire in same place\"})";

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

void Model::receiveGetCharacterRequest(int index){
    emit sendRequestedCharacter(characterLib[index]);
}

void Model::receiveCraftCharacterRequest(QList<std::string>& selectedCharacters){
    std::ostringstream oss;

    for (std::string& character : selectedCharacters) {
        oss << character << ",";
    }

    std::string prompt = oss.str();

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

            emit sendCraftResult(true);
            if(found){
                Character newCharacter(outputChar, spell, english);
                characterLib.push_back(newCharacter);
                emit sendNewCharacter(newCharacter, characterLib.size() - 1);
            }


        }
        reply->deleteLater();
    });

}

void Model::receiveAPIKey(std::string apiKey){
    this->apiKey = apiKey;
}
