#pragma once
#ifndef ITEM_H
#define ITEM_H


#include <iostream>
#include "game.h"
#include <SFML/Graphics.hpp>

class Item
{
private:
	std::string name;
	float cost;
	float mousePower;
	float criticalChance;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	//Constructer()
	Item(std::string name, sf::Texture Texture, sf::Sprite Sprite, float cost = 0, float mousePower = 1, float criticalChance = 0)
		: name(name), cost(cost), mousePower(mousePower), criticalChance(criticalChance), texture(Texture), sprite(Sprite) {
		sprite.setTexture(texture);
	}
	//Getters
	std::string getName() const { return name; }
	float getCost() const { return cost; }
	float getMousePower() const { return mousePower; }
	float getCriticalChance() const { return criticalChance; }
	// setters
	void setName(std::string name) { this->name = name; }
	void setCost(float cost) { this->cost = cost; }
	void setMousePower(float mousePower) { this->mousePower = mousePower; }
	void setCriticalChance(float criticalChance) { this->criticalChance = criticalChance; }

	void buyItem(Item& item, Game &game);
};
#endif