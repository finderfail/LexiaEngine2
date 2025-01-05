#ifndef PLAYER_H
#define PLAYER_H

struct Point2D {
    float x;
    float y;
};

struct Vector2D {
    float x;
    float y;
};

class Map;
class Player {
public:
    Player(float x, float y, float direction);
    Point2D getPosition() const;
    Vector2D getDirection() const;
    void setPosition(float x, float y);
    void setDirection(float direction);
    void move(float distance, const Map& map);
    void rotate(float angle);

private:
    Point2D position_;
    Vector2D direction_;
    bool checkCollision(float x, float y, const Map& map) const;
};

#endif