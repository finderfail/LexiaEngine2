#include "../include/Player.h"
#include "../include/Map.h" // Включаем Map.h
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

void Player::move(float distance, const Map& map) {
    // Временно сохраняем старую позицию
    float oldX = position_.x;
    float oldY = position_.y;

    float newX = position_.x + direction_.x * distance;
    float newY = position_.y + direction_.y * distance;

    // Проверка коллизии
    if (!checkCollision(newX, newY, map)) {
        position_.x = newX;
        position_.y = newY;
    } else {
        // Попробуем двигаться только по оси X
        newX = position_.x + direction_.x * distance;
        if (!checkCollision(newX, position_.y, map)) {
            position_.x = newX;
        }

        // Попробуем двигаться только по оси Y
        newY = position_.y + direction_.y * distance;
        if (!checkCollision(position_.x, newY, map)) {
            position_.y = newY;
        }
    }
}

void Player::rotate(float angle) {
    float oldDirX = direction_.x;
    direction_.x = direction_.x * std::cos(angle) - direction_.y * std::sin(angle);
    direction_.y = oldDirX * std::sin(angle) + direction_.y * std::cos(angle);
}

// Метод проверки коллизии (остается)
bool Player::checkCollision(float x, float y, const Map& map) const {
    int mapX = static_cast<int>(x);
    int mapY = static_cast<int>(y);

    if (mapX < 0 || mapX >= map.getWidth() || mapY < 0 || mapY >= map.getHeight() || map.getTile(mapX, mapY) != ' ')
    {
        return true; // Столкновение
    }

    return false; // Нет столкновения
}