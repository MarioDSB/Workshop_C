#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

Item* mkWeapon(int damage, float crit_chance) {
	Item* item = (Item *)malloc(sizeof(Item));
	item -> flag = Weapon;
	item -> Union.Weapon.damage = damage;
	item -> Union.Weapon.crit_chance = crit_chance;
	
	return item;	
}

Item* mkArmor(int defense) {
	Item *item = (Item *)malloc(sizeof(Item));
	item -> flag = Armor;
	item -> Union.Armor.defense = defense;
	
	return item;	
}

int getDamage(Item* weapon) {
	return weapon -> Union.Weapon.damage;
}

float getCritChance(Item* weapon) {
	return weapon -> Union.Weapon.crit_chance;
}

int getDefense(Item* armor) {
	return armor -> Union.Armor.defense;
}