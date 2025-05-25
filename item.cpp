#include "item.h"
#include "game.h"

Item::Item(float _cost, const std::string _name, const std::string texturePath) {
	cost = _cost;
	name = _name;

	if (!texture.loadFromFile(texturePath)) {
		std::cerr << "ERROR: Could not load texture for item: " << name << std::endl;
	}

	sprite.setTexture(texture);
}

void Item::buyItem(Item &item, Game &game) {
	game.setScore(game.getScore() - item.getCost());
}