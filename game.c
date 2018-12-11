#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "listas.h"

#define MAX_NICKNAME_LENGTH 50

typedef struct Player Player;
struct Player {
	char* nickname;
	int hp;
	List *inventory;
};

Player* initialize_player() {
	Player* player = (Player *)malloc(sizeof(Player));

	player -> hp = 1;
	player -> nickname = (char *)malloc(MAX_NICKNAME_LENGTH * sizeof(char));
	player -> inventory = NULL;

	return player;
}

char* getName() {
	char* name = (char *)malloc(MAX_NICKNAME_LENGTH * sizeof(char));

	printf("Insert your name:\n");
	scanf("%s", name);

	return name;
}

void hello_speech(char* nickname) {
	printf("<insert generic greeting speech here>, %s? ", nickname);
	printf("We goin' in a Quest\n");
}

void player_status(Player* player) {
	printf("%s has %dHP\n", player->nickname, player->hp);
}

void opponent_status(int hp) {
	char *name = "Goblin King";
	printf("%s has %dHP\n", name, hp);

	return;
}

void win() {
	printf("\n--------------------------------\n");
	printf("--  YOU WIN! CONGRATULATIONS! --\n");
	printf("--------------------------------\n");
}

void loss() {
	printf("\n---------------------------\n");
	printf("--  YOU DIED! TRY AGAIN! --\n");
	printf("---------------------------\n");
}

void run_away() {
	printf("\n-------------------------------------\n");
	printf("--  YOU RAN AWAY! UNTIL NEXT TIME! --\n");
	printf("-------------------------------------\n");
}

float getRandom() {
	return (float)rand()/(float)(RAND_MAX);
}

int player_attack(Item* weapon, int opponent_hp) {
	if (getCritChance(weapon) > getRandom()) {
		printf("\nYou did critical damage!\n");
		return opponent_hp - getDamage(weapon) * 2;
	}
	
	printf("\nYou attack...\n");
	return opponent_hp - getDamage(weapon);
}

int player_counter(Item* weapon, int opponent_hp) {
	if (getCritChance(weapon) > getRandom()) {
		printf("\nYou countered the opponent's attack, doing critical damage\n\n");
		return opponent_hp - getDamage(weapon) * 2;
	}

	printf("\nYou countered the opponent's attack\n\n");
	return opponent_hp - getDamage(weapon);
}

int opponent_attack(int player_hp, Item* armor) {
	if (0.25 > getRandom()) {
		printf("You take critical damage...\n\n");
		if (getDefense(armor) - 10 * 2 > 0)
			return player_hp;

		return player_hp + getDefense(armor) - 10 * 2;
	}

	printf("You are attacked...\n\n");
	if (getDefense(armor) - 10 > 0)
			return player_hp;
	return player_hp + getDefense(armor) - 10;
}

int player_defense(int player_hp, Item* armor) {
	if (0.5 > getRandom()) {
		if (0.5 > getRandom()) {
			printf("\nYour opponent breaches your defense, doing critical damage...\n\n");
			return player_hp + getDefense(armor) - 10 * 2;
		} else {
			printf("\nYou tried to defend, but your opponent still hit you...\n\n");
			return player_hp + getDefense(armor) - 10;
		}
	}

	printf("\nYou defended your opponent's attack...\n\n");
	return player_hp;
}

int getChoice() {
	int choice = -1;
	printf("Press 1 to attack, 2 to defend, 3 to run\n");
	scanf("%d", &choice);
	while(choice != 1 && choice != 2 && choice != 3) {
		printf("Please choose one of these options.\n");
		printf("Press 1 to attack, 2 to defend, 3 to run\n");
		scanf("%d", &choice);
	}

	return choice;
}

int main() {
	int 	choice = -1;
	int 	damage, defense;
	float	crit_chance;
	int 	opponent_hp = 100;

	Player* player = initialize_player();
	player -> nickname = getName();

	printf("\nHello, %s\n", player->nickname);

	hello_speech(player -> nickname);

	printf("\nNow lets battle!\n");
	printf("Insert your status!\n");

	printf("HP: ");
	scanf("%d", &(player->hp));

	printf("Weapon damage: ");
	scanf("%d", &damage);
	printf("Weapon critical chance: ");
	scanf("%f", &crit_chance);
	while (crit_chance > 1 || crit_chance < 0) {
		printf("\nThe weapon's critical chance has to be between 0 and 1\n");
		printf("Weapon critical chance: ");
		scanf("%f", &crit_chance);
	}
	Item* weapon = mkWeapon(damage, crit_chance);

	printf("Armor defense: ");
	scanf("%d", &defense);
	Item* armor = mkArmor(defense);

	printf("Your opponent is here. FIGHT!\n\n");

	player_status(player);
	opponent_status(opponent_hp);
	while(1) {
		choice = getChoice();
		switch(choice) {
			case 1:
				opponent_hp = player_attack(weapon, opponent_hp);
				if (opponent_hp <= 0) {
					win();
					return 0;
				}

				player -> hp = opponent_attack(player -> hp, armor);
				if (player -> hp <= 0) {
					loss();
					return 0;
				}
				break;
			case 2:
				if (0.20 > getRandom()) {
					opponent_hp = player_counter(weapon, opponent_hp);
					if (opponent_hp <= 0) {
						win();
						return 0;
					}
				} else {
					player -> hp = player_defense(player -> hp, armor);
					if (player -> hp <= 0) {
						loss();
						return 0;
					}
				}
				break;
			case 3:
				printf("\nYou ran away, living to fight another day\n");
				run_away();
				return 0;
		}

		player_status(player);
		opponent_status(opponent_hp);
	}

	return 0;
}
