
#include <QDebug>
#include <QPen>
#include <qmath.h>

#include "game_player.h"
#include "game_rectangle.h"
#include "game_circle.h"

QPointF pointFA(double angle);
double scalar(QPointF p1, QPointF p2);

GamePlayer::GamePlayer(QWidget* parent, int x, int y, QString uuid, QString pseudo, QString controller, QString vehicle, int team)
    : GameEntity(parent, x, y), m_uuid(uuid), m_pseudo(pseudo), m_conrtoller(controller), m_vehicle(vehicle), m_team(team)
    , c1(parent, x, y), c2(parent, x, y), c3(parent, x, y), c4(parent, x, y)
{
    this->m_color = "blue"; // TODO : donner une couleur qui dépend du nom du joueur, ou de l'équipe s'il y en a plusieurs
    this->m_steering = 0;
    this->m_angle = 0;
    this->m_power = 0;
    this->m_checkpoint = 0;
    this->m_lap = -1;

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

void GamePlayer::reset(int x, int y) {

    this->m_point.setX(gameCheckpoints[0]->X());
    this->m_point.setY(gameCheckpoints[0]->Y());
    this->m_speed.setX(0);
    this->m_speed.setY(0);
    this->m_checkpoint = 0;
    this->m_lap = -1;

}

QJsonObject GamePlayer::toJson() {

    auto lap = 0;
    if(this->m_lap > 0)
        lap = this->m_lap;

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
    json.insert(QString("currentLap"), QJsonValue(lap));
    json.insert(QString("status"), QJsonValue("driving"));
    json.insert(QString("controller"), QJsonValue(this->m_conrtoller));
    json.insert(QString("lastCheckpoint"), QJsonValue(previousCheckpointId(this->m_checkpoint)) );

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

    auto F = pointFA(this->m_angle) *(this->m_power/100.0) *5.0;
    F = (this->m_speed + F) *0.5;
    auto P = this->m_point +F;

    if(P.x() < 0)
        F.setX(-P.x());
    if(P.x() > 1000)
        F.setX(-(P.x()-1000));
    if(P.y() < 0)
        F.setY(-P.y());
    if(P.y() > 1000)
        F.setY(-(P.y()-1000));

    this->m_speed = F;
    this->m_point = P +this->m_speed;

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

    auto check = qobject_cast<GameCheckpoint*>(object);
    if(check) {

        if(gameCheckpoints[this->m_checkpoint]->id == check->id) {
            this->m_checkpoint = this->m_checkpoint +1;
            qDebug() << "checkpoint passed";
            if(this->m_checkpoint == gameCheckpoints.length()) {
                this->m_checkpoint = 0;
                this->m_lap += 1;
                qDebug() << "lap done";
            }
        }

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

#ifdef COLLISION_MODE_BOUNCE
            QPointF mirror;

            if(abs(xw) >= abs(yh))
                mirror = pointFA(rect->angle() +M_PI*0.5);
            else
                mirror = pointFA(rect->angle());

            double theta = acos(scalar(this->m_speed, mirror));

            theta = -theta*2;
            x = this->m_speed.x()*cos(theta) -this->m_speed.y()*sin(theta);
            y = this->m_speed.x()*sin(theta) +this->m_speed.y()*cos(theta);
            qDebug() << this->m_speed;
            this->m_speed = QPointF(x, y)*2.0;
            this->m_angle -= theta;
            qDebug() << this->m_speed;
#else
            QPointF collisionF;

            if(abs(xw) >= abs(yh))
                if(xw > 0)
                    collisionF = pointFA(rect->angle()) *5.0;
                else
                    collisionF = pointFA(rect->angle() +M_PI) *5.0;
            else
                if(yh > 0)
                    collisionF = pointFA(rect->angle() +M_PI*1.5) *5.0;
                else
                    collisionF = pointFA(rect->angle() +M_PI*0.5) *5.0;

            this->m_speed += collisionF;
            this->m_point += collisionF;

            // Draw

            this->m_item->setX(this->X());
            this->m_item->setY(this->Y());
            this->m_item->setRotation(-this->m_angle *57.2974);

#endif

        }

        return;
    }

    // Collision with circle
    auto circle = qobject_cast<GameCircle*>(object);
    if(circle) {

        auto norme = sqrt(this->m_width*this->m_width +this->m_height*this->m_height) /2.0;
        auto angle = atan2(this->m_width, this->m_height);

        this->c1.set((pointFA(angle +this->m_angle) *norme) +this->m_point);
        this->c2.set((pointFA(M_PI -angle +this->m_angle) *norme) +this->m_point);
        this->c3.set((pointFA(M_PI +angle +this->m_angle) *norme) +this->m_point);
        this->c4.set((pointFA(-angle +this->m_angle) *norme) +this->m_point);

        GameSketch* collidingCorner = nullptr;

        if(circle->getItem()->collidesWithItem(this->c1.getItem())) {
            collidingCorner = &(this->c1);
        }
        else if(circle->getItem()->collidesWithItem(this->c2.getItem())) {
            collidingCorner = &(this->c2);
        }
        else if(circle->getItem()->collidesWithItem(this->c3.getItem())) {
            collidingCorner = &(this->c3);
        }
        else if(circle->getItem()->collidesWithItem(this->c4.getItem())) {
            collidingCorner = &(this->c4);
        }

        if(collidingCorner != nullptr) {

            QPointF dir = collidingCorner->point() -circle->point();
            double dirAngle = atan2(dir.y(), dir.x());
            auto collisionF = pointFA(-dirAngle) *5.0;

            this->m_speed += collisionF;
            this->m_point += collisionF;

            // Draw

            this->m_item->setX(this->X());
            this->m_item->setY(this->Y());
            this->m_item->setRotation(-this->m_angle *57.2974);

        }

    }
}

///
/// \brief pointFA Point From Angle
/// \return A point with a lenght of 1
///
QPointF pointFA(double angle) {
    return QPointF(cos(angle), -sin(angle));
}

double scalar(QPointF p1, QPointF p2) {

    return (p1.x()*p2.x() +p1.y()*p2.y())
            /
           (sqrt(p1.x()*p1.x() +p1.y()*p1.y())*sqrt(p2.x()*p2.x() +p2.y()*p2.y()));

}
