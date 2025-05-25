#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Item {
private:
    std::string name;
    sf::Texture texture;
    sf::Sprite sprite;  // Changed from sf::Sprite& to sf::Sprite
    float cost;
    float mousePower;
    float criticalChance;
public:
    // Constructors
    Item() = default;
    Item(float cost, const std::string name, sf::Texture&& texture, float mousePower, float criticalChance);

    // Getters
    const std::string& getName() const { return name; }
    float getCost() const { return cost; }
    float getMousePower() const { return mousePower; }
    float getCriticalChance() const { return criticalChance; }
    sf::Sprite& getSprite() { return sprite; }
	sf::Texture getTexture() const { return texture; }

    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setCost(float newCost) { cost = newCost; }
    void setMousePower(float power) { mousePower = power; }
    void setCriticalChance(float chance) { criticalChance = chance; }
	void setSprite(const sf::Sprite& newSprite) { sprite = newSprite; }
	void setTexture(const sf::Texture& newTexture) { texture = newTexture; sprite.setTexture(texture); }
};

#endif