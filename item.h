#pragma once
#ifndef ITEM_H
#define ITEM_H


#include <iostream>
#include "game.h"
#include <SFML/Graphics.hpp>

class Item {
private:
	// Item properties
    std::string name;
    sf::Texture texture; 
    sf::Sprite sprite;
    float cost;
public:
	// Constructor
    Item(float cost, const std::string, const std::string);

    // Getters
    std::string getName() { return name; }
    float getCost() { return cost; }
    sf::Sprite& getSprite() { return sprite; }

	// Setters
	void setName(const std::string& newName) { name = newName; }
	void setCost(float newCost) { cost = newCost; }
	void setTexture(const std::string& texturePath) {
		if (!texture.loadFromFile(texturePath)) {
			std::cerr << "ERROR: Could not load texture for item: " << name << std::endl;
		}

		sprite.setTexture(texture);
	}

	// Function to buy an item
    void buyItem(Item&, Game&);
};

class Book : public Item {
private:
    float criticalChance;
public:
	// Constructor
	Book(float cost, const std::string name, const std::string texturePath, float criticalChance)
		: Item(cost, name, texturePath), criticalChance(criticalChance) {}

    // Getters and setters
	float getCriticalChance() const { return criticalChance; }
	void setCriticalChance(float chance) { criticalChance = chance; }
};

#endif