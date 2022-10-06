#ifndef GAMESKETCH_H
#define GAMESKETCH_H

#include "game_map_object.h"

class GameSketch : public GameMapObject
{
public:
    GameSketch();
    GameSketch(QWidget *parent, int x, int y);

    void setXY(int x, int y);
    void set(QPointF point);

    void updateProperties(GameProperties* properties);
};

#endif // GAMESKETCH_H
