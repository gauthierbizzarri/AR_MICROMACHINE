
#include <QDebug>
#include <QPen>
#include <qmath.h>

#include "game_player.h"
#include "game_rectangle.h"
#include "game_circle.h"

QPointF pointFA(double angle);

GamePlayer::GamePlayer(QWidget* parent, int x, int y, QString uuid, QString pseudo, QString controller, QString vehicle, int team)
    : GameEntity(parent, x, y), m_uuid(uuid), m_pseudo(pseudo), m_conrtoller(controller), m_vehicle(vehicle), m_team(team)
    , c1(parent, x, y), c2(parent, x, y), c3(parent, x, y), c4(parent, x, y)
{
    this->m_color = "blue"; // TODO : donner une couleur qui dépend du nom du joueur, ou de l'équipe s'il y en a plusieurs
    this->m_steering = 0;
    this->m_angle = 0;
    this->m_power = 0;
    this->m_checkpoint = nullptr;

    this->m_width = 12;
    this->m_height = 25;

    QGraphicsRectItem* item = new QGraphicsRectItem(-this->m_height/2, -this->m_width/2, this->m_height, this->m_width);
    QPen pen;
    pen.setWidth(1);
    item->setPen(pen);
    item->setBrush(QBrush(Qt::blue));
    item->moveBy(this->X(), this->Y());
    item->setRotation(0);

    this->m_item = item;

    qDebug() << "player log : " << pseudo;
}

GamePlayer::~GamePlayer() {

}

QString GamePlayer::getUuid() {
    return this->m_uuid;
}

QString GamePlayer::getPseudo() {
    return this->m_pseudo;
}

QString GamePlayer::getColor() {
    return this->m_color;
}

QString GamePlayer::getController() {
    return this->m_conrtoller;
}

QString GamePlayer::getVehicle() {
    return this->m_vehicle;
}

int GamePlayer::getTeam() {
    return this->m_team;
}

void GamePlayer::setSteering(double value) {
    this->m_steering = value;
}

void GamePlayer::setPower(int value) {
    this->m_power = value;
}

void GamePlayer::setCheckpoint(GameCheckpoint *checkpoint) {
    this->m_checkpoint = checkpoint;
}

QJsonObject GamePlayer::toJson() {

    QJsonObject json;

    json.insert(QString("uuid"), QJsonValue(this->m_uuid));
    json.insert(QString("pseudo"), QJsonValue(this->m_pseudo));
    json.insert(QString("color"), QJsonValue(this->m_color));
    json.insert(QString("team"), QJsonValue(this->m_team));
    json.insert(QString("x"), QJsonValue(this->X()));
    json.insert(QString("y"), QJsonValue(this->Y()));
    json.insert(QString("angle"), QJsonValue(this->m_angle));
    json.insert(QString("speed"), QJsonValue(this->m_power));
    json.insert(QString("vehicle"), QJsonValue(this->m_vehicle));
    json.insert(QString("currentLap"), QJsonValue(0));
    json.insert(QString("status"), QJsonValue("driving"));
    json.insert(QString("controller"), QJsonValue(this->m_conrtoller));
    if(this->m_checkpoint != nullptr)
        json.insert(QString("lastCheckpoint"), QJsonValue(this->m_checkpoint->id));

    QJsonObject items;
    items.insert(QString("banana"), QJsonValue(1));
    items.insert(QString("bomb"), QJsonValue(1));
    items.insert(QString("rocket"), QJsonValue(1));

    json.insert(QString("items"), items);

    return json;
}

void GamePlayer::update() {

    // Move

    this->m_angle += this->m_steering;

    auto F = pointFA(this->m_angle) *this->m_power;
    auto P = this->m_point +F;//+this->m_collisionF;

    if(P.x() < 0)
        P.setX(0);
    if(P.x() > 1000)
        P.setX(1000);
    if(P.y() < 0)
        P.setY(0);
    if(P.y() > 1000)
        P.setY(1000);

    this->m_point = P;

    // Attenuate forces

    //this->m_collisionF = this->m_collisionF *0.99;

    // Draw

    this->m_item->setX(this->X());
    this->m_item->setY(this->Y());
    this->m_item->setRotation(-this->m_angle *57.2974);

}

void GamePlayer::checkCollision() {

    for(GameMapObject* object : gameObjects) {
        if(this != object)
            if(this->m_item->collidesWithItem(object->getItem())) {
                this->collideWith(object);
            }
    }
}

void GamePlayer::collideWith(GameMapObject *object) {

    // Collision with checkpoint

    if(this->m_checkpoint->next == object) {
        qDebug() << "Checkpoint passed for " << this->m_pseudo;
        this->m_checkpoint = this->m_checkpoint->next;
        return;
    }

    // Collision with rectangle

    auto rect = qobject_cast<GameRectangle*>(object);
    if(rect) {

        auto norme = sqrt(this->m_width*this->m_width +this->m_height*this->m_height) /2.0;
        auto angle = atan2(this->m_width, this->m_height);

        this->c1.set((pointFA(angle +this->m_angle) *norme) +this->m_point);
        this->c2.set((pointFA(M_PI -angle +this->m_angle) *norme) +this->m_point);
        this->c3.set((pointFA(M_PI +angle +this->m_angle) *norme) +this->m_point);
        this->c4.set((pointFA(-angle +this->m_angle) *norme) +this->m_point);

        GameSketch* collidingCorner = nullptr;

        if(rect->getItem()->collidesWithItem(this->c1.getItem())) {
            collidingCorner = &(this->c1);
        }
        else if(rect->getItem()->collidesWithItem(this->c2.getItem())) {
            collidingCorner = &(this->c2);
        }
        else if(rect->getItem()->collidesWithItem(this->c3.getItem())) {
            collidingCorner = &(this->c3);
        }
        else if(rect->getItem()->collidesWithItem(this->c4.getItem())) {
            collidingCorner = &(this->c4);
        }

        if(collidingCorner != nullptr) {
            auto point = collidingCorner->point() -rect->point();
            auto x = point.x() *cos(rect->angle()) -point.y() *sin(rect->angle());
            auto y = point.x() *sin(rect->angle()) +point.y() *cos(rect->angle());

            auto xw = x /rect->W();
            auto yh = y /rect->H();

            if(abs(xw) > abs(yh))
                if(xw > 0)
                    this->m_collisionF = pointFA(rect->angle()) *10;
                else
                    this->m_collisionF = pointFA(rect->angle() +M_PI) *10;
            else
                if(yh > 0)
                    this->m_collisionF = pointFA(rect->angle() +M_PI*1.5) *10;
                else
            this->m_collisionF = pointFA(rect->angle() +M_PI*0.5) *10;

            qDebug() << "I TOOK A WALL";
        }

        return;
    }

    // Collision with circle
    auto circle = qobject_cast<GameCircle*>(object);
    if(circle) {



    }
}

///
/// \brief pointFA Point From Angle
/// \return A point with a lenght of 1
///
QPointF pointFA(double angle) {
    return QPointF(cos(angle), -sin(angle));
}
