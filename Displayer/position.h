#ifndef POSITION_H
#define POSITION_H


class Position
{
private:
    int x;
    int y;
public:
    Position(int x, int y);
    int getX();
    int getY();

    Position* translate(int x = 0, int y = 0);
};

#endif // POSITION_H
