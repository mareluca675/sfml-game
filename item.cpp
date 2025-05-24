#include "item.h"
#include "game.h"

void Item::buyItem(Item &item, Game &game)
{
	game.setScore(game.getScore() - item.getCost());
	item.setCost(item.getCost() * 1.5f);
	item.setCriticalChance(item.getCriticalChance() + 0.5f);
}