
#include <QDebug>
#include <QPen>
#include <qmath.h>

#include "game_player.h"
#include "game_rectangle.h"
#include "game_circle.h"
#include "main.h"

const QString teamNames[] = {
    "white",
    "cyan",
    "yellow",
    "magenta",
    "orange",
    "brown",
    "purple"
};

QPointF pointFA(double angle);
double scalar(QPointF p1, QPointF p2);

GamePlayer::GamePlayer(QWidget* parent, int x, int y, QString uuid, QString pseudo, QString controller, QString vehicle, int team, GameProperties* properties)
    : GameEntity(parent, x, y), m_uuid(uuid), m_pseudo(pseudo), m_conrtoller(controller), m_vehicle(vehicle), m_team(team)
    , c1(parent, x, y, true), c2(parent, x, y, false), c3(parent, x, y, false), c4(parent, x, y, true)
{
    this->m_color = teamNames[team]; // TODO : donner une couleur qui dépend du nom du joueur, ou de l'équipe s'il y en a plusieurs
    this->m_steering = 0;
    this->m_angle = 0;
    this->m_power = 0;
    this->m_checkpoint = 0;
    this->m_lap = -1;
    this->m_stunnedAge = false;
    this->m_bananaCd = 0;
    this->m_bombCd = 0;
    this->m_rocketCd = 0;
    this->m_bananaCdMax = properties->bananaCd *1000;
    this->m_bombCdMax = properties->bombCd *1000;
    this->m_rocketCdMax = properties->rocketCd *1000;
    this->m_ttl = PLAYER_TTL;

    QGraphicsRectItem* item = new QGraphicsRectItem(-1, -1, 2, 2);
    QPen pen;
    pen.setWidth(1);
    item->setPen(pen);
    item->setBrush(QBrush(QColor(teamNames[team])));
    item->moveBy(this->X(), this->Y());
    item->setRotation(0);

    this->m_item = item;

    this->updateProperties(properties);

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

int GamePlayer::getCheckpoint() {
    return this->m_checkpoint;
}

int GamePlayer::getLap() {
    return this->m_lap;
}

bool GamePlayer::isStun() {
    return this->m_stunnedAge > 0;
}

void GamePlayer::setSteering(double value) {

    this->m_ttl = PLAYER_TTL;

    if(abs(value) > this->m_maxSteering)
        if(value > 0)
            this->m_steering = this->m_maxSteering;
        else
            this->m_steering = -this->m_maxSteering;
    else
        this->m_steering = value;
}

void GamePlayer::setPower(int value) {

    this->m_ttl = PLAYER_TTL;

    this->m_power = value;
}

bool GamePlayer::canPlaceBanana() {
    return this->m_bananaCd <= 0;
}

void GamePlayer::placeBanana(GameBanana* banana) {

    auto point = this->point() +pointFA(this->m_angle) *-this->m_height *1.1;
    banana->set(point.x(), point.y());
    this->m_bananaCd = this->m_bananaCdMax;

}

bool GamePlayer::canPlaceBomb() {
    return this->m_bombCd <= 0;
}

void GamePlayer::placeBomb(GameBomb* bomb) {

    auto point = this->point() +pointFA(this->m_angle) *-this->m_height *1.1;
    bomb->set(point.x(), point.y());
    this->m_bombCd = this->m_bombCdMax;

}

bool GamePlayer::canFireRocket() {
    return this->m_rocketCd <= 0;
}

void GamePlayer::fireRocket(GameRocket* rocket) {

    auto point = this->point() +pointFA(this->m_angle) *this->m_height *1.1;
    rocket->set(point.x(), point.y(), this->m_angle +this->m_steering);
    this->m_rocketCd = this->m_rocketCdMax;

}

void GamePlayer::reset(int x, int y) {

    this->m_point.setX(gameCheckpoints[0]->X());
    this->m_point.setY(gameCheckpoints[0]->Y());
    this->m_speed.setX(0);
    this->m_speed.setY(0);
    this->m_angle = 0;
    this->m_checkpoint = 0;
    this->m_lap = -1;

}

void GamePlayer::updateProperties(GameProperties* properties) {

    this->m_bananaCdMax = properties->bananaCd *1000;
    this->m_bombCdMax = properties->bombCd *1000;
    this->m_rocketCdMax = properties->rocketCd *1000;

    if(this->m_vehicle == "bike") {
        this->m_maxSpeed = properties->bike.maxSpeed;
        this->m_acceleration = properties->bike.acceleration;
        this->m_weight = properties->bike.weight;
        this->m_maxSteering = properties->bike.steeringAngle;
        this->m_width = properties->bike.width;
        this->m_height = properties->bike.height;
    }
    else if(this->m_vehicle == "car") {
        this->m_maxSpeed = properties->car.maxSpeed;
        this->m_acceleration = properties->car.acceleration;
        this->m_weight = properties->car.weight;
        this->m_maxSteering = properties->car.steeringAngle;
        this->m_width = properties->car.width;
        this->m_height = properties->car.height;
    }
    else if(this->m_vehicle == "truck") {
        this->m_maxSpeed = properties->truck.maxSpeed;
        this->m_acceleration = properties->truck.acceleration;
        this->m_weight = properties->truck.weight;
        this->m_maxSteering = properties->truck.steeringAngle;
        this->m_width = properties->truck.width;
        this->m_height = properties->truck.height;
    }
    else {
        this->m_maxSpeed = properties->car.maxSpeed;
        this->m_acceleration = properties->car.acceleration;
        this->m_weight = properties->car.weight;
        this->m_maxSteering = properties->car.steeringAngle;
        this->m_width = properties->car.width;
        this->m_height = properties->car.height;
    }

    auto item = (QGraphicsRectItem*) this->m_item;
    item->setRect(-this->m_height/2, -this->m_width/2, this->m_height, this->m_width);
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
    json.insert(QString("status"), QJsonValue(this->m_stunnedAge <= 0 ? "driving" : "accident"));
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
    this->m_ttl -= GAME_TICK;
    if(this->m_ttl <= 0) {
        emit this->endOfLife(this);
        return;
    }

    // Cooldowns

    if(this->m_bananaCd > 0)
        this->m_bananaCd -= GAME_TICK;
    if(this->m_bombCd > 0)
        this->m_bombCd -= GAME_TICK;
    if(this->m_rocketCd > 0)
        this->m_rocketCd -= GAME_TICK;

    // Angle

    auto percent = sqrt(this->m_speed.x()*this->m_speed.x() +this->m_speed.y()*this->m_speed.y()) /this->m_maxSpeed;
    if(percent < 0.001)
        percent = 0;
    auto steering = this->m_steering *percent;

    // Speed

    auto F = pointFA(this->m_angle) *(this->m_power/10000.0) *this->m_maxSpeed;
    if(this->m_stunnedAge > 0) {
        F = F*0.0;
        steering = 1;
        this->m_stunnedAge -= GAME_TICK;
    }

    F = (this->m_speed + F) *0.95;
    auto P = this->m_point +F;

    if(P.x() < 0)
        F.setX(-P.x());
    if(P.x() > 1000)
        F.setX(-(P.x()-1000));
    if(P.y() < 0)
        F.setY(-P.y());
    if(P.y() > 1000)
        F.setY(-(P.y()-1000));

    // Updates

    if(this->m_power < 0)
        this->m_angle -= steering;
    else
        this->m_angle += steering;

    this->m_speed = F;
    this->m_point = P +this->m_speed;

    // Draw

    this->m_item->setX(this->X());
    this->m_item->setY(this->Y());
    this->m_item->setRotation(-this->m_angle *57.2974);

    this->checkCollision();

}

void GamePlayer::getHit() {

    this->m_stunnedAge = 1000;

}

void GamePlayer::checkCollision() {

    for(GameMapObject* object : gameObjects) {
        if(this != object)
            if(this->m_item->collidesWithItem(object->getItem())) { // TODO : CRASH HERE
                this->collideWith(object);
            }
    }
}

void GamePlayer::collideWith(GameMapObject *object) {

    auto norme = sqrt(this->m_width*this->m_width +this->m_height*this->m_height) /2.0;
    auto angle = atan2(this->m_width, this->m_height);

    this->c1.set((pointFA(angle +this->m_angle) *norme) +this->m_point);
    this->c2.set((pointFA(M_PI -angle +this->m_angle) *norme) +this->m_point);
    this->c3.set((pointFA(M_PI +angle +this->m_angle) *norme) +this->m_point);
    this->c4.set((pointFA(-angle +this->m_angle) *norme) +this->m_point);

    // Collision with checkpoint

    auto check = qobject_cast<GameCheckpoint*>(object);
    if(check) {

        if(gameCheckpoints[this->m_checkpoint]->id == check->id) {
            this->m_checkpoint = this->m_checkpoint +1;
            qDebug() << "checkpoint passed";
            if(this->m_checkpoint == gameCheckpoints.length()) {
                this->m_checkpoint = 0;
            }
            if(this->m_checkpoint == 1) {
                this->m_lap += 1;
                qDebug() << "lap done";
            }

            emit this->statsChanged(this);
        }

        return;
    }

    // Collision with rectangle

    auto rect = qobject_cast<GameRectangle*>(object);
    if(rect) {

//        auto norme = sqrt(this->m_width*this->m_width +this->m_height*this->m_height) /2.0;
//        auto angle = atan2(this->m_width, this->m_height);

//        this->c1.set((pointFA(angle +this->m_angle) *norme) +this->m_point);
//        this->c2.set((pointFA(M_PI -angle +this->m_angle) *norme) +this->m_point);
//        this->c3.set((pointFA(M_PI +angle +this->m_angle) *norme) +this->m_point);
//        this->c4.set((pointFA(-angle +this->m_angle) *norme) +this->m_point);

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

//        auto norme = sqrt(this->m_width*this->m_width +this->m_height*this->m_height) /2.0;
//        auto angle = atan2(this->m_width, this->m_height);

//        this->c1.set((pointFA(angle +this->m_angle) *norme) +this->m_point);
//        this->c2.set((pointFA(M_PI -angle +this->m_angle) *norme) +this->m_point);
//        this->c3.set((pointFA(M_PI +angle +this->m_angle) *norme) +this->m_point);
//        this->c4.set((pointFA(-angle +this->m_angle) *norme) +this->m_point);

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

        return;
    }

    // Collision with banana

    auto banana = qobject_cast<GameBanana*>(object);
    if(banana) {
        banana->getHit();
        this->m_stunnedAge = 1000;
        return;
    }

    // Collision with banana

    auto bomb = qobject_cast<GameBomb*>(object);
    if(bomb) {
        bomb->getHit();
        this->m_stunnedAge = 1000;
        return;
    }


}

///
/// \brief pointFA : Point From Angle
/// \param angle
/// \return
///
QPointF pointFA(double angle) {
    return QPointF(cos(angle), -sin(angle));
}

double scalar(QPointF p1, QPointF p2) {

    return (p1.x()*p2.x() +p1.y()*p2.y())
            /
           (sqrt(p1.x()*p1.x() +p1.y()*p1.y())*sqrt(p2.x()*p2.x() +p2.y()*p2.y()));

}
