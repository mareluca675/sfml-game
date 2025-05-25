#include "item.h"
#include "game.h"

Item::Item(float _cost, const std::string _name, sf::Texture&& _texture, float _mousePower, float _criticalChance)
    : cost(_cost),
    name(_name),
    texture(std::move(_texture)),  // Move the texture into the member
    mousePower(_mousePower),
    criticalChance(_criticalChance),
    sprite()  // Default-construct sprite
{
    sprite.setTexture(texture);       // Set the sprite's texture to the member's texture
    sprite.setPosition(sf::Vector2f(0, 0));  // Set initial position
}