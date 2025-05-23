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
	Item() = default;

	//Getters

	std::string getName() const { return name; }
	float getCost() const { return cost; }
	float getMousePower() const { return mousePower; }
	float getCriticalChance() const { return criticalChance; }
	sf::Texture getTexture() const { return texture; }
	sf::Sprite getSprite() const { return sprite; }

	// Setters

	void setName(std::string name) { this->name = name; }
	void setCost(float cost) { this->cost = cost; }
	void setMousePower(float mousePower) { this->mousePower = mousePower; }
	void setCriticalChance(float criticalChance) { this->criticalChance = criticalChance; }
	void setTexture(sf::Texture texture) { this->texture = texture; }
	void setSprite(sf::Sprite sprite) { this->sprite = sprite; }
	void buyItem(Item& item, Game &game);
};
#endif