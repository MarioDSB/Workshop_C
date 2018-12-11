#ifndef __item_h__
#define __item_h__

typedef struct Item Item;
struct Item {
	enum {Weapon, Armor} flag;
	union {
		struct {
			int damage;
			float crit_chance;
		} Weapon;
		struct {
			int defense;
		} Armor;
	} Union;
};

Item* mkWeapon(int damage, float crit_chance);
Item* mkArmor(int defense);
int getDamage(Item* weapon);
float getCritChance(Item* weapon);
int getDefense(Item* armor);

#endif