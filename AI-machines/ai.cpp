#include "ai.h"

AI::AI(QObject *parent)
    : QObject{parent}
{

}

void AI::playerDatas(QJsonDocument datas) {
    process(datas);
}

void AI::process(QJsonDocument inputs) {
    QVariantMap outputMap;

    outputMap["uuid"] = "uuid";
    outputMap["angle"] = "90";
    outputMap["power"] = "100";

    QVariantMap buttons;

    buttons["banana"] = false;
    buttons["bomb"] = false;
    buttons["rocket"] = false;

    outputMap["buttons"] = buttons;

    QJsonDocument output = QJsonDocument(QJsonObject::fromVariantMap(outputMap));

    emit controllerInputs(output);
}
