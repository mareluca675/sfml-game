#pragma once
#ifndef ITEM_H
#define ITEM_H


#include <iostream>
#include "game.h"
#include <SFML/Graphics.hpp>

class Item {
private:
    std::string name;
    float cost;
    float mousePower;
    float criticalChance;
    sf::Texture texture; 
    sf::Sprite sprite;
public:
    Item() = default;

    void setName(const std::string& n) { name = n; }
    void setCost(float c) { cost = c; }
    void setCriticalChance(float cc) { criticalChance = cc; }

    void setTexture(const std::string& path) {
        if (!texture.loadFromFile(path)) {
            throw std::runtime_error("Could not load texture from " + path);
        }
        sprite.setTexture(texture); // important: set sprite's texture
    }

    void setSpritePosition(float x, float y) {
        sprite.setPosition(x, y);
    }
	//Getters
	
	std::string getName() const { return name; }
	float getCost() const { return cost; }
	float getMousePower() const { return mousePower; }
	float getCriticalChance() const { return criticalChance; }
    const sf::Sprite& getSprite() const { return sprite; }

    void buyItem(Item& item, Game& game);

};
#endif