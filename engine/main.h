#ifndef MAIN_H
#define MAIN_H

#define MQTT_HOST "gerald.imerir.org"
#define MQTT_PORT 1883
#define MQTT_USER "username"
#define MQTT_PASS "Test"
#define MQTT_TOPIC_MAP "map"
#define MQTT_TOPIC_PLAYER_CONTROL "player/control"
#define MQTT_TOPIC_PLAYER_REGISTER "player/register"
#define MQTT_TOPIC_GAME "game"
#define MQTT_TOPIC_GAME_PROPERTIES "game/properties"

#define IHM_WIDTH 1000
#define IHM_HEIGHT 1000

//#define IA_TRAINING
//#define ENGINE_SEND_MAP
//#define GAMEPAD_ONLY
#define NO_GAMEPAD

#define GAME_TICK 50
#define GAME_PROPERTY_TICK 1000
#define PLAYER_TTL 10000


#endif // MAIN_H
