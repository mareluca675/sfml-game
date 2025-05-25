#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Item {
private:
	// Item properties
    std::string name;
    sf::Texture texture; 
    sf::Sprite sprite;
    float cost;
	float mousePower;
	float criticalChance;
public:
	// Constructor
	Item() = default;
    Item(float cost, const std::string, const std::string);

    // Getters
    std::string getName() { return name; }
    float getCost() { return cost; }
	float getMousePower() const { return mousePower; }
	float getCriticalChance() const { return criticalChance; }
    sf::Sprite& getSprite() { return sprite; }
	sf::Texture getTexture() const { return texture; }

	// Setters
	void setName(const std::string& newName) { name = newName; }
	void setCost(float newCost) { cost = newCost; }
	void setTexture(const std::string& texturePath) {
		if (!texture.loadFromFile(texturePath)) {
			std::cerr << "ERROR: Could not load texture for item: " << name << std::endl;
		}

		sprite.setTexture(texture);
	}
	void setMousePower(float power) { mousePower = power; }
	void setCriticalChance(float chance) { criticalChance = chance; }
};

#endif