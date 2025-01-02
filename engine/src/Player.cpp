#include "../include/Player.h"
#include <cmath>

Player::Player(float x, float y, float direction) {
    position_.x = x;
    position_.y = y;
    direction_.x = std::cos(direction);
    direction_.y = std::sin(direction);
}

Point2D Player::getPosition() const {
    return position_;
}
Vector2D Player::getDirection() const {
    return direction_;
}

void Player::setPosition(float x, float y) {
    position_.x = x;
    position_.y = y;
}

void Player::setDirection(float direction) {
    direction_.x = std::cos(direction);
    direction_.y = std::sin(direction);
}

void Player::move(float distance) {
    position_.x += direction_.x * distance;
    position_.y += direction_.y * distance;
}

void Player::rotate(float angle)
{
    float oldDirX = direction_.x;
    direction_.x = direction_.x * std::cos(angle) - direction_.y * std::sin(angle);
    direction_.y = oldDirX * std::sin(angle) + direction_.y * std::cos(angle);
}