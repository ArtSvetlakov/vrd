/*
    VRD - Very random dungeon. A text-based rogue-like with RPG elements about a novice knight, an endless dungeon and defeating a dragon.
	Copyright (C) 2023  ArtSvetlakov (Artemiy Svetlakov)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#if _MSC_VER && !__INTEL_COMPILER
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#if (defined(__unix__) || defined(__APPLE__)) && !defined(__MSDOS__)
	#define CLEARSCREEN system("clear")
	#define PAUSE printf("Press Enter to continue...\n");getchar();getchar() //I don't know how to do this properly on mac/linux, so this is my "solution"
#else
	#define CLEARSCREEN system("cls")
	#define PAUSE system("pause")
#endif

void gamePlay();
void startScreen();
void gameInit();
_Bool isEquipped(int YourItemLVL, int ItemLVL);
float randomRangef(float min, float max);
void trading();

//localization
int langSelect; //1 - English, 2 - Russian, 3 - Spanish
char startTitle[1050], 
introTitle[1500], 
traderGreeting[2100],
isEquippedTitle[150],
noCoinsTitle[270],
victoryTitle[360],
youDiedTitle[600],
drinkHPTitle[120],
notNeedHPTitle[210],
drinkSPTitle[120],
equipLATitle[120],
equipLHTitle[120],
equipDaggerTitle[105],
equipCATitle[120],
equipCHTitle[120],
equipSSwordTitle[105],
equipHATitle[120],
equipHHTitle[120],
equipLSwordTitle[105],
chooseListTitle[120],
chestTitle[100],
helmetTitle[75],
weaponTitle[75];

//game assets array for random generator
char gameAssets[12][75];

struct Enemy {
	int health, 
	strength;
} dragon, goblin, wolf, rat, bat, bear, skeleton;

//structures of game assets
struct Player {
	int health, 
	strength,
	maxHealth, 
	armor,
	chestArmor,
	helmetArmor,
	damage,
	weaponDamage,
	level,
	weaponEquipLevel,
	armorEquipLevel,
	helmetEquipLevel,
	EXP,
	maxEXP,
	coins;
	char left[75],
	up[75],
	right[75],
	choise[75];
} player;


struct Equipment {
	int strength,
	equipLevel;
	char name[75];
} dagger, shortSword, longSword, leatherArmor, leatherHelmet, chainArmor, chainHelmet, heavyArmor, heavyHelmet;

void gameInit()
{
	//enemies
	goblin.strength = 4;
	goblin.health = 8;

	wolf.strength = 3;
	wolf.health = 4;
	
	rat.strength = 2;
	rat.health = 3;
	
	bat.strength = 2;
	bat.health = 4;
	
	bear.strength = 10;
	bear.health = 10;
	
	skeleton.strength = 5;
	skeleton.health = 10;
	
	dragon.strength = 20;
	dragon.health = 50;
	
	//weapon and armor
	dagger.equipLevel = 1;
	dagger.strength = 2;
	
	shortSword.equipLevel = 2;
	shortSword.strength = 4;
	
	longSword.equipLevel = 3;
	longSword.strength = 6;
	
	leatherArmor.equipLevel = 1;
	leatherArmor.strength = 1;
	
	chainArmor.equipLevel = 2;
	chainArmor.strength = 4;
	
	heavyArmor.equipLevel = 3;
    heavyArmor.strength = 6;
	
	leatherHelmet.equipLevel = 1;
	leatherHelmet.strength = 1;
	
	chainHelmet.equipLevel = 2;
    chainHelmet.strength = 2;
	
	heavyHelmet.equipLevel = 3;
	heavyHelmet.strength = 4;
	
	//player
	player.strength = 2;
	player.health = 10;
	player.maxHealth = 10;
	player.level = 1;
	player.EXP = 0;
	player.maxEXP = 6;
	player.weaponDamage = 0;
	player.weaponEquipLevel = 0;
	player.armorEquipLevel = 0;
	player.helmetEquipLevel = 0;
	player.chestArmor = 0;
	player.helmetArmor = 0;
	player.coins = 0;
	
	//localize
	switch(langSelect)
	{
		case 1: 
		{
			snprintf(gameAssets[0], sizeof(gameAssets[0]), "Dragon");
			snprintf(gameAssets[1], sizeof(gameAssets[1]), "Goblin");
			snprintf(gameAssets[2], sizeof(gameAssets[2]), "Bear");
			snprintf(gameAssets[3], sizeof(gameAssets[3]), "Skeleton");
			snprintf(gameAssets[4], sizeof(gameAssets[4]), "Wolf");
			snprintf(gameAssets[5], sizeof(gameAssets[5]), "Rat");
			snprintf(gameAssets[6], sizeof(gameAssets[6]), "Bat");
			snprintf(gameAssets[7], sizeof(gameAssets[7]), "Poison trap");
			snprintf(gameAssets[8], sizeof(gameAssets[8]), "Spiked trap");
			snprintf(gameAssets[9], sizeof(gameAssets[9]), "Coins");
			snprintf(gameAssets[10], sizeof(gameAssets[10]), "Bonfire");
			snprintf(gameAssets[11], sizeof(gameAssets[11]), "Goblin-merchant");
			snprintf(dagger.name, sizeof(dagger.name), "Dagger");
			snprintf(shortSword.name, sizeof(shortSword.name), "Short sword");
			snprintf(longSword.name, sizeof(longSword.name), "Long sword");
			snprintf(leatherArmor.name, sizeof(leatherArmor.name), "Leather armor");
			snprintf(chainArmor.name, sizeof(chainArmor.name), "Chain armor");
			snprintf(heavyArmor.name, sizeof(heavyArmor.name), "Heavy armor");
			snprintf(leatherHelmet.name, sizeof(leatherHelmet.name), "Leather helmet");
			snprintf(chainHelmet.name, sizeof(chainHelmet.name), "Chain helmet");
			snprintf(heavyHelmet.name, sizeof(heavyHelmet.name), "Heavy helmet");
			snprintf(startTitle, sizeof(startTitle), "\nxXxXxXxXxXxXxXxxxXxx\nXxXxx ________ xxXxx\nxXx //        \\\\ xXx\nXxx ||        || Xxx\nxXX ||  ____  || xXx\nxXx || /    \\ || xXx\nXXx ||/      \\|| XxX\n^^^^^^^^^^^^^^^^^^^^\n\nVery random dungeon\nN) New game\nQ) Quit (this command can be used at any moment during the game, except battle)\n\0");
			snprintf(introTitle, sizeof(introTitle), "You live in a land filled with evil dragons.\nLarge and small beasts are equally aggressive.\nThe big ones live on the tops of the mountains, while the small ones can hide in dungeons...\nYou are a beginner who dreams of becoming a knight!\nTo complete the initiation, you must kill at least one small dragon....\nOr die trying.\nYou descend into the dungeon. It's dark all around and you'll have to go almost at random.\n\0");
			snprintf(traderGreeting, sizeof(traderGreeting), "Hi big guy! I have something for you if you have something to pay.\n1) Health Potion (restores 5 health points) - 50 coins\n2) Potion of Strength (adds 1 point of strength) - 75 coins\n3) Leather armor (gives 1 armor points) - 25 coins\n4) Leather helmet (gives 1 armor points) - 25 coins\n5) Dagger (gives 2 power points) - 25 coins\n6) Chain armor (gives 4 armor points) - 100 coins\n7) Chain helmet (gives 2 armor points) - 75 coins\n8) Short sword (gives 4 power points) - 100 coins\n9) Heavy armor (gives 6 armor points) - 200 coins\n10) Heavy helmet (gives 4 armor points) - 150 coins\n11) Long sword (gives 6 power points) - 200 coins\nQ) Step away from the stall\n\0");
			snprintf(isEquippedTitle, sizeof(isEquippedTitle), "You already have this or better item.\n\0");
			snprintf(noCoinsTitle, sizeof(noCoinsTitle), "Not enough coins! Choose another item... or go earn coins!!!\n\0");
			snprintf(victoryTitle, sizeof(victoryTitle), "\n\nYou have survived! And you have defeated the Dragon!!!\nYou have been knighted!\nYour mission here was completed!\n\0");
			snprintf(youDiedTitle, sizeof(youDiedTitle), "      _______\n    //VVVVVVV\\\\ \n  _//--     --\\\\_\n / /( x ) ( x )\\ \\\n( (     /_\\     ) )\n \\_\\   _____   /_/\n    \\ /WWWWW\\ /\n     \\ (___) /\n      \\MMMMM/\nYOU DIED!\n\0");
			snprintf(drinkHPTitle, sizeof(drinkHPTitle), "You drank a health potion\n\0");
			snprintf(notNeedHPTitle, sizeof(notNeedHPTitle), "You don't need a health potion. You are completely healthy.\n\0");
			snprintf(drinkSPTitle, sizeof(drinkSPTitle), "You drank a potion of strength\n\0");
			snprintf(equipLATitle, sizeof(equipLATitle), "You have put on a leather armor\n\0");
			snprintf(equipLHTitle, sizeof(equipLHTitle), "You have put on a leather helmet\n\0");
			snprintf(equipDaggerTitle, sizeof(equipDaggerTitle), "You have equipped a dagger\n\0");
			snprintf(equipCATitle, sizeof(equipCATitle), "You have put on a chain armor\n\0");
			snprintf(equipCHTitle, sizeof(equipCHTitle), "You have put on a chain helmet\n\0");
			snprintf(equipSSwordTitle, sizeof(equipSSwordTitle), "You have equipped a short sword\n\0");
			snprintf(equipHATitle, sizeof(equipHATitle), "You have put on a heavy armor\n\0");
			snprintf(equipHHTitle, sizeof(equipHHTitle), "You have put on a heavy helmet\n\0");
			snprintf(equipLSwordTitle, sizeof(equipLSwordTitle), "You have equipped a long sword\n\0");
			snprintf(chooseListTitle, sizeof(chooseListTitle), "Choose from the list above!\n\0");
			snprintf(chestTitle, sizeof(chestTitle), "without chest armor");
			snprintf(helmetTitle, sizeof(helmetTitle), "without helmet");
			snprintf(weaponTitle, sizeof(weaponTitle), "without weapon");
			break;	
		}
		case 2: 
		{
			snprintf(gameAssets[0], sizeof(gameAssets[0]), "Дракон");
			snprintf(gameAssets[1], sizeof(gameAssets[1]), "Гоблин");
			snprintf(gameAssets[2], sizeof(gameAssets[2]), "Медведь");
			snprintf(gameAssets[3], sizeof(gameAssets[3]), "Скелет");
			snprintf(gameAssets[4], sizeof(gameAssets[4]), "Волк");
			snprintf(gameAssets[5], sizeof(gameAssets[5]), "Крыса");
			snprintf(gameAssets[6], sizeof(gameAssets[6]), "Летучая мышь");
			snprintf(gameAssets[7], sizeof(gameAssets[7]), "Ядовитая ловушка");
			snprintf(gameAssets[8], sizeof(gameAssets[8]), "Шипастая ловушка");
			snprintf(gameAssets[9], sizeof(gameAssets[9]), "Монеты");
			snprintf(gameAssets[10], sizeof(gameAssets[10]), "Костёр");
			snprintf(gameAssets[11], sizeof(gameAssets[11]), "Гоблин-торговец");
			snprintf(dagger.name, sizeof(dagger.name), "Кинжал");
			snprintf(shortSword.name, sizeof(shortSword.name), "Короткий меч");
			snprintf(longSword.name, sizeof(longSword.name), "Длинный меч");
			snprintf(leatherArmor.name, sizeof(leatherArmor.name), "Кожаная броня");
			snprintf(chainArmor.name, sizeof(chainArmor.name), "Кольчужная броня");
			snprintf(heavyArmor.name, sizeof(heavyArmor.name), "Тяжелая броня");
			snprintf(leatherHelmet.name, sizeof(leatherHelmet.name), "Кожаный шлем");
			snprintf(chainHelmet.name, sizeof(chainHelmet.name), "Кольчужный шлем");
			snprintf(heavyHelmet.name, sizeof(heavyHelmet.name), "Тяжелый шлем");
			snprintf(startTitle, sizeof(startTitle), "\nxXxXxXxXxXxXxXxxxXxx\nXxXxx ________ xxXxx\nxXx //        \\\\ xXx\nXxx ||        || Xxx\nxXX ||  ____  || xXx\nxXx || /    \\ || xXx\nXXx ||/      \\|| XxX\n^^^^^^^^^^^^^^^^^^^^\n\nВесьма случайное подземелье\nN) Новая игра\nQ) Выход (данная команда может быть использована в любой момент во время игры, кроме боя)\n\0");
			snprintf(introTitle, sizeof(introTitle), "Вы живёте на земле, которую заполонили злые драконы.\nБольшие и малые особи одинаково агрессивны.\nБольшие живут на вершинах гор, а малые могут прятаться в подземельях...\nВы новичок, который мечтает стать рыцарем!\nЧтобы пройти посвящение, вам надо убить хотя бы одного малого дракона...\nИли умереть, пытаясь.\nВы спускаетесь в подземелье. Кругом темно и идти придётся почти наугад.\n\0");
			snprintf(traderGreeting, sizeof(traderGreeting), "Привет, здоровяк! У меня есть кое-что для тебя, если тебе есть чем заплатить.\n1) Зелье здоровья (восстанавливает 5 очков здоровья) - 50 монет\n2) Зелье силы (добавляет 1 очко силы) - 75 монет\n3) Кожаная броня (даёт 1 очки брони) - 25 монет\n4) Кожаный шлем (даёт 1 очко брони) - 25 монет\n5) Кинжал (даёт 2 очка силы) - 25 монет\n6) Кольчужная броня (даёт 4 очка брони) - 100 монет\n7) Кольчужный шлем (даёт 2 очка брони) — 75 монет\n8) Короткий меч (даёт 4 очка силы) — 100 монет\n9) Тяжелый доспех (даёт 6 очков брони) — 200 монет\n10) Тяжелый шлем (даёт 4 очка брони) - 150 монет\n11) Длинный меч (даёт 6 очков силы) - 200 монет\nQ) Отойти от прилавка\n\0");
			snprintf(isEquippedTitle, sizeof(isEquippedTitle), "У вас уже есть этот предмет или лучше.\n\0");
			snprintf(noCoinsTitle, sizeof(noCoinsTitle), "Недостаточно монет! Выбери другой предмет... или иди и зарабатывай монеты!!!\n\0");
			snprintf(victoryTitle, sizeof(victoryTitle), "\n\nВы выжили! И вы победили Дракона!!!\nВы посвящены в рыцари!\nВаша миссия здесь выполнена!\n\0");
			snprintf(youDiedTitle, sizeof(youDiedTitle), "      _______\n    //VVVVVVV\\\\ \n  _//--     --\\\\_\n / /( x ) ( x )\\ \\\n( (     /_\\     ) )\n \\_\\   _____   /_/\n    \\ /WWWWW\\ /\n     \\ (___) /\n      \\MMMMM/\nВЫ УМЕРЛИ!\n\0");
			snprintf(drinkHPTitle, sizeof(drinkHPTitle), "Вы выпили зелье здоровья\n\0");
			snprintf(notNeedHPTitle, sizeof(notNeedHPTitle), "Вам не нужно зелье здоровья. Вы полностью здоровы.\n\0");
			snprintf(drinkSPTitle, sizeof(drinkSPTitle), "Вы выпили зелье силы\n\0");
			snprintf(equipLATitle, sizeof(equipLATitle), "Вы надели кожаную броню\n\0");
			snprintf(equipLHTitle, sizeof(equipLHTitle), "Вы надели кожаный шлем\n\0");
			snprintf(equipDaggerTitle, sizeof(equipDaggerTitle), "Вы взяли кинжал\n\0");
			snprintf(equipCATitle, sizeof(equipCATitle), "Вы надели кольчужную броню\n\0");
			snprintf(equipCHTitle, sizeof(equipCHTitle), "Вы надели кольчужный шлем\n\0");
			snprintf(equipSSwordTitle, sizeof(equipSSwordTitle), "Вы взяли короткий меч\n\0");
			snprintf(equipHATitle, sizeof(equipHATitle), "Вы надели тяжелый доспех\n\0");
			snprintf(equipHHTitle, sizeof(equipHHTitle), "Вы надели тяжелый шлем\n\0");
			snprintf(equipLSwordTitle, sizeof(equipLSwordTitle), "Вы взяли длинный меч\n\0");
			snprintf(chooseListTitle, sizeof(chooseListTitle), "Выберите из списка выше!\n\0");
			snprintf(chestTitle, sizeof(chestTitle), "без нагрудника");
			snprintf(helmetTitle, sizeof(helmetTitle), "без шлема");
			snprintf(weaponTitle, sizeof(weaponTitle), "без оружия");
			break;
		}
		case 3: 
		{
			snprintf(gameAssets[0], sizeof(gameAssets[0]), "el Dragon");
			snprintf(gameAssets[1], sizeof(gameAssets[1]), "Duende");
			snprintf(gameAssets[2], sizeof(gameAssets[2]), "Oso");
			snprintf(gameAssets[3], sizeof(gameAssets[3]), "Esqueleto");
			snprintf(gameAssets[4], sizeof(gameAssets[4]), "Lobo");
			snprintf(gameAssets[5], sizeof(gameAssets[5]), "Rato");
			snprintf(gameAssets[6], sizeof(gameAssets[6]), "Bate");
			snprintf(gameAssets[7], sizeof(gameAssets[7]), "Trampa de veneno");
			snprintf(gameAssets[8], sizeof(gameAssets[8]), "Trampa con púas");
			snprintf(gameAssets[9], sizeof(gameAssets[9]), "Monedas");
			snprintf(gameAssets[10], sizeof(gameAssets[10]), "Hoguera");
			snprintf(gameAssets[11], sizeof(gameAssets[11]), "el Duende-comerciante");			
			snprintf(dagger.name, sizeof(dagger.name), "Daga");
			snprintf(shortSword.name, sizeof(shortSword.name), "Espada corta");
			snprintf(longSword.name, sizeof(longSword.name), "Espada larga");
			snprintf(leatherArmor.name, sizeof(leatherArmor.name), "Armadura de cuero");
			snprintf(chainArmor.name, sizeof(chainArmor.name), "Armadura de cadena");
			snprintf(heavyArmor.name, sizeof(heavyArmor.name), "Armadura pesada");
			snprintf(leatherHelmet.name, sizeof(leatherHelmet.name), "Casco de cuero");
			snprintf(chainHelmet.name, sizeof(chainHelmet.name), "Casco de cadena");
			snprintf(heavyHelmet.name, sizeof(heavyHelmet.name), "Casco pesado");
			snprintf(startTitle, sizeof(startTitle), "\nxXxXxXxXxXxXxXxxxXxx\nXxXxx ________ xxXxx\nxXx //        \\\\ xXx\nXxx ||        || Xxx\nxXX ||  ____  || xXx\nxXx || /    \\ || xXx\nXXx ||/      \\|| XxX\n^^^^^^^^^^^^^^^^^^^^\n\nVery random dungeon\nN) Nuevo juego\nQ) Salir (este comando se puede utilizar en cualquier momento del juego, excepto en combate)\n\0");
			snprintf(introTitle, sizeof(introTitle), "Vives en una tierra invadida por dragones malvados.\nLos individuos grandes y pequeños son igualmente agresivos.\nLos grandes viven en las cimas de las montañas, y los pequeños pueden esconderse en las mazmorras... \n¡Eres un principiante que sueña con convertirse en caballero!\nPara completar la iniciación, deberás matar al menos a un dragón menor...\no morir en el intento.\nBajas al calabozo.\nEstá oscuro por todas partes y tendrás que caminar casi al azar.\n\0");
			snprintf(traderGreeting, sizeof(traderGreeting), "¡Hola grandullón! Tengo algo para ti si tienes algo que pagar.\n1) Poción de salud (restaura 5 puntos de salud) - 50 monedas\n2) Poción de fuerza (agrega 1 punto de fuerza) - 75 monedas\n3) Armadura de cuero (da 1 punto de armadura) ) - 25 monedas\n4) Casco de cuero (da 1 punto de armadura) - 25 monedas\n5) Daga (da 2 puntos de fuerza) - 25 monedas\n6) Armadura de cadena (da 4 puntos de armadura) - 100 monedas\n7) Casco de cadena (da 2 puntos de armadura) - 75 monedas\n8) Espada corta (da 4 puntos de fuerza) - 100 monedas\n9) Armadura pesada (da 6 puntos de armadura) - 200 monedas\n10) Casco pesado (da 4 puntos de armadura) - 150 monedas\n11) Espada larga (da 6 puntos de fuerza) - 200 monedas\nQ) Aléjate del mostrador\n\0");
			snprintf(isEquippedTitle, sizeof(isEquippedTitle), "Ya tienes este o mejor artículo.\n\0");
			snprintf(noCoinsTitle, sizeof(noCoinsTitle), "¡No hay suficientes monedas! Elige otro artículo... ¡¡¡o gana monedas!!!\n\0");
			snprintf(victoryTitle, sizeof(victoryTitle), "\n\n¡Has sobrevivido! ¡¡¡Y has derrotado al Dragón!!!\n¡Te han nombrado caballero!\n¡Tu misión aquí fue completada!\n\0");
			snprintf(youDiedTitle, sizeof(youDiedTitle), "      _______\n    //VVVVVVV\\\\ \n  _//--     --\\\\_\n / /( x ) ( x )\\ \\\n( (     /_\\     ) )\n \\_\\   _____   /_/\n    \\ /WWWWW\\ /\n     \\ (___) /\n      \\MMMMM/\n¡Has muerto!\n\0");
			snprintf(drinkHPTitle, sizeof(drinkHPTitle), "Bebiste una poción de salud\n\0");
			snprintf(notNeedHPTitle, sizeof(notNeedHPTitle), "No necesitas una poción de salud. Estás completamente sano.\n\0");
			snprintf(drinkSPTitle, sizeof(drinkSPTitle), "Bebiste una poción de fuerza\n\0");
			snprintf(equipLATitle, sizeof(equipLATitle), "Te has puesto una armadura de cuero\n\0");
			snprintf(equipLHTitle, sizeof(equipLHTitle), "Te has puesto un casco de cuero\n\0");
			snprintf(equipDaggerTitle, sizeof(equipDaggerTitle), "Has equipado una daga\n\0");
			snprintf(equipCATitle, sizeof(equipCATitle), "Te has puesto una armadura de cadena\n\0");
			snprintf(equipCHTitle, sizeof(equipCHTitle), "Te has puesto un casco de cadena\n\0");
			snprintf(equipSSwordTitle, sizeof(equipSSwordTitle), "Has equipado una espada corta\n\0");
			snprintf(equipHATitle, sizeof(equipHATitle), "Te has puesto una armadura pesada\n\0");
			snprintf(equipHHTitle, sizeof(equipHHTitle), "Te has puesto un casco pesado\n\0");
			snprintf(equipLSwordTitle, sizeof(equipLSwordTitle), "Has equipado una espada larga\n\0");
			snprintf(chooseListTitle, sizeof(chooseListTitle), "¡Seleccione de la lista anterior!\n\0");
			snprintf(chestTitle, sizeof(chestTitle), "sin armadura de pecho");
			snprintf(helmetTitle, sizeof(helmetTitle), "sin casco");
			snprintf(weaponTitle, sizeof(weaponTitle), "ningún arma");
			break;
		}
	}
}

float randomRangef(float min, float max)
{
    return ((max - min) * ((float)rand() / (float)RAND_MAX) + min);
}

void startScreen()
{
	CLEARSCREEN;
	gameInit();
	printf(startTitle);
	scanf("%s", player.choise);
	if(strcmp(player.choise, "n") == 0 || strcmp(player.choise, "N") == 0)
	{
		CLEARSCREEN;
		printf(introTitle);
		PAUSE;
		gamePlay();
	}
	else if(strcmp(player.choise, "q") == 0 || strcmp(player.choise, "Q") == 0)
	{
		CLEARSCREEN;
		exit(0);
	}
	else startScreen();
}

_Bool isEquipped(int YourItemLVL, int ItemLVL)
{
  if(YourItemLVL >= ItemLVL)
  {
      printf(isEquippedTitle);
      return 1;
  }
  else return 0;
}

void trading()
{
	CLEARSCREEN;
	printf(traderGreeting);
    
	while(1)
	{
		printf("%s: %d\n", gameAssets[9], player.coins);
		scanf("%s", player.choise);
		if(strcmp(player.choise, "1") == 0)
		{
			if(player.coins >= 50)
			{
                if(player.health < (player.maxHealth))
				{
					player.coins = player.coins - 50;
                    player.health = player.health + 5;
					if(player.health > player.maxHealth) player.health = player.maxHealth;
                    printf(drinkHPTitle);
				}
                else printf(notNeedHPTitle);
			}
            else printf(noCoinsTitle);
		}
		
		else if(strcmp(player.choise, "2") == 0)
		{
			if(player.coins >= 75)
			{
				player.coins = player.coins - 75;
				player.strength = player.strength + 1;
				printf(drinkSPTitle);
			}
			else printf(noCoinsTitle);
		}
		
		else if(strcmp(player.choise, "3") == 0)
		{
			if(player.coins >= 25)
			{
               if(isEquipped(player.armorEquipLevel, leatherArmor.equipLevel) == 0)
			   {
                   player.chestArmor = leatherArmor.strength;
                   player.armorEquipLevel = leatherArmor.equipLevel;
                   player.coins = player.coins - 25;
				   snprintf(chestTitle, sizeof(chestTitle), leatherArmor.name);
                   printf(equipLATitle);
			   };
			}
           else printf(noCoinsTitle);
		}
		
		else if(strcmp(player.choise, "4") == 0)
		{
			if (player.coins >= 25)
			{
               if(isEquipped(player.helmetEquipLevel, leatherHelmet.equipLevel) == 0)
			   {
                   player.helmetArmor = leatherHelmet.strength;
                   player.helmetEquipLevel = leatherHelmet.equipLevel;
                   player.coins = player.coins - 25;
				   snprintf(helmetTitle, sizeof(helmetTitle), leatherHelmet.name);
                   printf(equipLHTitle);
			   }
			}
           else printf(noCoinsTitle);
		}
		
		else if(strcmp(player.choise, "5") == 0)
		{
			if (player.coins >= 25)
			{
               if(isEquipped(player.weaponEquipLevel, dagger.equipLevel) == 0)
			   {
				   player.weaponDamage = dagger.strength;
                   player.weaponEquipLevel = dagger.equipLevel;
                   player.coins = player.coins - 25;
				   snprintf(weaponTitle, sizeof(weaponTitle), dagger.name);
                   printf(equipDaggerTitle);
			   }
			}
			else printf(noCoinsTitle);
		}
		
		else if(strcmp(player.choise, "6") == 0)
		{
			if(player.coins >= 100)
			{
                if(isEquipped(player.armorEquipLevel, chainArmor.equipLevel) == 0)
				{
					player.chestArmor = chainArmor.strength;
                    player.armorEquipLevel = chainArmor.equipLevel;
                    player.coins = player.coins - 100;
					snprintf(chestTitle, sizeof(chestTitle), chainArmor.name);
                    printf(equipCATitle);
				}
			}
            else printf(noCoinsTitle);
		}
		
		else if(strcmp(player.choise, "7") == 0)
		{
			if(player.coins >= 75)
			{
				if(isEquipped(player.helmetEquipLevel, chainHelmet.equipLevel) == 0)
				{
					player.helmetArmor = chainHelmet.strength;
					player.helmetEquipLevel = chainHelmet.equipLevel;
					player.coins = player.coins - 75;
					snprintf(helmetTitle, sizeof(helmetTitle), chainHelmet.name);
					printf(equipCHTitle);
				}
			}
			else printf(noCoinsTitle);
		}
		
		else if(strcmp(player.choise, "8") == 0)
		{
			if(player.coins >= 100)
			{
				if(isEquipped(player.weaponEquipLevel, shortSword.equipLevel) == 0)
				{
					player.weaponDamage = shortSword.strength;
					player.weaponEquipLevel = shortSword.equipLevel;
					player.coins = player.coins - 100;
					snprintf(weaponTitle, sizeof(weaponTitle), shortSword.name);
					printf(equipSSwordTitle);
				}
			}
			else printf(noCoinsTitle);
		}
		
		else if(strcmp(player.choise, "9") == 0)
		{
			if(player.coins >= 200)
			{
				if(isEquipped(player.armorEquipLevel, heavyArmor.equipLevel) == 0)
				{
					player.chestArmor = heavyArmor.strength;
					player.armorEquipLevel = heavyArmor.equipLevel;
					player.coins = player.coins - 200;
					snprintf(chestTitle, sizeof(chestTitle), heavyArmor.name);
					printf(equipHATitle);
				}
			}
            else printf(noCoinsTitle);
		}
		
		else if(strcmp(player.choise, "10") == 0)
		{
			if (player.coins >= 150)
			{
				if (isEquipped(player.helmetEquipLevel, heavyHelmet.equipLevel) == 0)
				{
					player.helmetArmor = heavyHelmet.strength;
					player.helmetEquipLevel = heavyHelmet.equipLevel;
					player.coins = player.coins - 150;
					snprintf(helmetTitle, sizeof(helmetTitle), heavyHelmet.name);
					printf(equipHHTitle);
				}
			}
			else printf(noCoinsTitle);
		}
		
		else if(strcmp(player.choise, "11") == 0)
		{
			if(player.coins >= 200)
			{
				if(isEquipped(player.weaponEquipLevel, longSword.equipLevel) == 0)
				{
					player.weaponDamage = longSword.strength;
					player.weaponEquipLevel = longSword.equipLevel;
					player.coins = player.coins - 200;
					snprintf(weaponTitle, sizeof(weaponTitle), longSword.name);
					printf(equipLSwordTitle);
				}
			}
            else printf(noCoinsTitle);
		}
		else if((strcmp(player.choise, "Q") == 0) || (strcmp(player.choise, "q") == 0)) gamePlay();
		else printf(chooseListTitle);
	} 
}

void battle(int enemyStrength, int enemyHealth)
{
	int hit, armorInBattle;
	CLEARSCREEN;
	switch(langSelect)
	{
		case 1:
		{
			do
			{
				printf("Your health %d/%d Armor %d\n\0", player.health ,player.maxHealth, player.armor);
				printf("%s: Health %d Strength %d\n\0", player.choise, enemyHealth, enemyStrength);
				hit = rand() % enemyStrength;
				armorInBattle = randomRangef((player.armor / 2), player.armor);
				if(armorInBattle <= hit)
				{
					hit = hit - armorInBattle;
					player.health = player.health - hit;
					printf("%s hit %d damage.\nArmor reflected %d damage.\n\0", player.choise, hit, armorInBattle);
				}
				else printf("Enemy %s did not break the armor.\n\0", player.choise);
				hit = rand() % player.damage;
				enemyHealth = enemyHealth - hit;
				printf("You hit %d damage.\n\0", hit);
			} while ((player.health > 0) && (enemyHealth > 0));
			if(enemyHealth <= 0)
			{
				printf("Enemy %s was defeated!\n\0", player.choise);
				if (strcmp(player.choise, gameAssets[0]) == 0) //Dragon
				{
					printf(victoryTitle);
					PAUSE;
					startScreen();
				}
				//add EXP
				if(strcmp(player.choise, gameAssets[1]) == 0) player.EXP = player.EXP + 4; //Goblin
				if(strcmp(player.choise, gameAssets[2]) == 0) player.EXP = player.EXP + 6; //Bear
				if(strcmp(player.choise, gameAssets[3]) == 0) player.EXP = player.EXP + 5; //Skeleton
				if(strcmp(player.choise, gameAssets[4]) == 0) player.EXP = player.EXP + 3; //Wolf
				if(strcmp(player.choise, gameAssets[5]) == 0) player.EXP = player.EXP + 1; //Rat
				if(strcmp(player.choise, gameAssets[6]) == 0) player.EXP = player.EXP + 2; //Bat
					
				//LVL UP
				if (player.EXP >= player.maxEXP)
				{
					player.maxHealth = player.maxHealth + 2;
					player.strength = player.strength + 1;
					player.health = player.maxHealth;
					player.level = player.level +1;
					player.EXP = 0;
					player.maxEXP = player.maxEXP + 2;
					printf("You have reached level %d\n\0", player.level);
				}
			}
			break;
		}
		case 2:
		{
			do
			{
				printf("Ваше Здоровье %d/%d Броня %d\n\0", player.health ,player.maxHealth, player.armor);
				printf("%s: Здоровье %d Сила %d\n\0", player.choise, enemyHealth, enemyStrength);
				hit = rand() % enemyStrength;
				armorInBattle = randomRangef((player.armor / 2), player.armor);
				if(armorInBattle <= hit)
				{
					hit = hit - armorInBattle;
					player.health = player.health - hit;
					printf("%s наносит %d урона.\nБроня отразила %d урона.\n\0", player.choise, hit, armorInBattle);
				}
				else printf("Враг %s не пробил броню.\n\0", player.choise);
				hit = rand() % player.damage;
				enemyHealth = enemyHealth - hit;
				printf("Вы наносите %d урона.\n\0", hit);
			} while ((player.health > 0) && (enemyHealth > 0));
			if(enemyHealth <= 0)
			{
				printf("Враг %s повержен!\n\0", player.choise);
				if (strcmp(player.choise, gameAssets[0]) == 0) //Dragon
				{
					printf(victoryTitle);
					PAUSE;
					startScreen();
				}
				//add EXP
				if(strcmp(player.choise, gameAssets[1]) == 0) player.EXP = player.EXP + 4; //Goblin
				if(strcmp(player.choise, gameAssets[2]) == 0) player.EXP = player.EXP + 6; //Bear
				if(strcmp(player.choise, gameAssets[3]) == 0) player.EXP = player.EXP + 5; //Skeleton
				if(strcmp(player.choise, gameAssets[4]) == 0) player.EXP = player.EXP + 3; //Wolf
				if(strcmp(player.choise, gameAssets[5]) == 0) player.EXP = player.EXP + 1; //Rat
				if(strcmp(player.choise, gameAssets[6]) == 0) player.EXP = player.EXP + 2; //Bat
					
				//LVL UP
				if (player.EXP >= player.maxEXP)
				{
					player.maxHealth = player.maxHealth + 2;
					player.strength = player.strength + 1;
					player.health = player.maxHealth;
					player.level = player.level +1;
					player.EXP = 0;
					player.maxEXP = player.maxEXP + 2;
					printf("Вы достигли уровня %d\n\0", player.level);
				}
			}
			break;
		}
		case 3:
		{
			do
			{
				printf("Tu salud %d/%d Armadura %d\n\0", player.health ,player.maxHealth, player.armor);
				printf("%s: Salud %d Fuerza %d\n\0", player.choise, enemyHealth, enemyStrength);
				hit = rand() % enemyStrength;
				armorInBattle = randomRangef((player.armor / 2), player.armor);
				if(armorInBattle <= hit)
				{
					hit = hit - armorInBattle;
					player.health = player.health - hit;
					printf("%s causó %d daño.\n%d daño reflejado por armadura.\n\0", player.choise, hit, armorInBattle);
				}
				else printf("El enemigo %s no penetró la armadura.\n\0", player.choise);
				hit = rand() % player.damage;
				enemyHealth = enemyHealth - hit;
				printf("has hecho %d daño.\n\0", hit);
			} while ((player.health > 0) && (enemyHealth > 0));
			if(enemyHealth <= 0)
			{
				printf("El enemigo %s está derrotado!\n\0", player.choise);
				if (strcmp(player.choise, gameAssets[0]) == 0) //Dragon
				{
					printf(victoryTitle);
					PAUSE;
					startScreen();
				}
				//add EXP
				if(strcmp(player.choise, gameAssets[1]) == 0) player.EXP = player.EXP + 4; //Goblin
				if(strcmp(player.choise, gameAssets[2]) == 0) player.EXP = player.EXP + 6; //Bear
				if(strcmp(player.choise, gameAssets[3]) == 0) player.EXP = player.EXP + 5; //Skeleton
				if(strcmp(player.choise, gameAssets[4]) == 0) player.EXP = player.EXP + 3; //Wolf
				if(strcmp(player.choise, gameAssets[5]) == 0) player.EXP = player.EXP + 1; //Rat
				if(strcmp(player.choise, gameAssets[6]) == 0) player.EXP = player.EXP + 2; //Bat
					
				//LVL UP
				if (player.EXP >= player.maxEXP)
				{
					player.maxHealth = player.maxHealth + 2;
					player.strength = player.strength + 1;
					player.health = player.maxHealth;
					player.level = player.level +1;
					player.EXP = 0;
					player.maxEXP = player.maxEXP + 2;
					printf("Has alcanzado el nivel %d\n\0", player.level);
				}
			}
			break;
		}
	}
	PAUSE;
	gamePlay();
}

void action()
{
	//Dragon
	if(strcmp(player.choise, gameAssets[0]) == 0) battle(dragon.strength, dragon.health);
	//Goblin
	if(strcmp(player.choise, gameAssets[1]) == 0) battle(goblin.strength, goblin.health);
	//Bear
	if(strcmp(player.choise, gameAssets[2]) == 0) battle(bear.strength, bear.health);
	//Skeleton
	if(strcmp(player.choise, gameAssets[3]) == 0) battle(skeleton.strength, skeleton.health);
	//Wolf
	if(strcmp(player.choise, gameAssets[4]) == 0) battle(wolf.strength, wolf.health);
	//Rat
	if(strcmp(player.choise, gameAssets[5]) == 0) battle(rat.strength, rat.health);
	//Bat
	if(strcmp(player.choise, gameAssets[6]) == 0) battle(bat.strength, bat.health);
	//Poison trap
	if(strcmp(player.choise, gameAssets[7]) == 0)
	{
		if(player.strength > 0)
		{
			player.strength = player.strength - 1;
			gamePlay();
		}
	}
	//Spiked trap
	if(strcmp(player.choise, gameAssets[8]) == 0)
	{
		player.health = player.health - 2;
		gamePlay();
	}
	//Coins
	if(strcmp(player.choise, gameAssets[9]) == 0)
	{
		player.coins = player.coins + randomRangef(10, 50);
		gamePlay();
	}
	//Bonfire
	if(strcmp(player.choise, gameAssets[10]) == 0)
	{
		player.health = player.maxHealth;
		gamePlay();
	}
	//Goblin-merchant
	if(strcmp(player.choise, gameAssets[11]) == 0) trading();
}

void gamePlay()
{
	CLEARSCREEN;
	if (player.health <= 0)
	{
		CLEARSCREEN;
		printf(youDiedTitle);
		PAUSE;
		startScreen();
	}
	player.damage = player.strength + player.weaponDamage;
	player.armor = player.chestArmor + player.helmetArmor;
	
	switch(langSelect)
	{
		case 1: 
		{
			printf("Health: %d/%d Armor: %d (%s - %d, %s - %d) Damage: %d (strength - %d, %s - %d)\n%s: %d Level: %d EXP: %d/%d\n\n       W\n       ^\nA <--  |  --> D\n      \\|/\n       |\n\n\0", player.health, player.maxHealth, player.armor, chestTitle, player.chestArmor, helmetTitle, player.helmetArmor, player.damage, player.strength, weaponTitle, player.weaponDamage, gameAssets[9], player.coins, player.level, player.EXP, player.maxEXP);
			break;
		}
		case 2: 
		{
			printf("Здоровье: %d/%d Броня: %d (%s - %d, %s - %d) Урон: %d (сила - %d, %s - %d)\n%s: %d Уровень: %d EXP: %d/%d\n\n       W\n       ^\nA <--  |  --> D\n      \\|/\n       |\n\n\0", player.health, player.maxHealth, player.armor, chestTitle, player.chestArmor, helmetTitle, player.helmetArmor, player.damage, player.strength, weaponTitle, player.weaponDamage, gameAssets[9], player.coins, player.level, player.EXP, player.maxEXP);
			break;
		}	
		case 3: 
		{
			printf("Salud: %d/%d Armadura: %d (%s - %d, %s - %d) Daño: %d (fuerza - %d, %s - %d)\n%s: %d Nivel: %d EXP: %d/%d\n\n       W\n       ^\nA <--  |  --> D\n      \\|/\n       |\n\n\0", player.health, player.maxHealth, player.armor, chestTitle, player.chestArmor, helmetTitle, player.helmetArmor, player.damage, player.strength, weaponTitle, player.weaponDamage, gameAssets[9], player.coins, player.level, player.EXP, player.maxEXP);
			break;
		}		
	}
	
	do
	{
	snprintf(player.left, sizeof(player.left), "%s", gameAssets[rand() % 12]);
	snprintf(player.up, sizeof(player.up), "%s", gameAssets[rand() % 12]);
	snprintf(player.right, sizeof(player.up), "%s", gameAssets[rand() % 12]);
	} while ((strcmp(player.left, player.right) == 0 || strcmp(player.up, player.left) == 0 || strcmp(player.up, player.right) == 0)); // 0 = equal
	
	switch(langSelect)
	{
		case 1: 
		{
			printf("Left: %s\nForward: %s\nRight: %s\n\na) Left\nw) Forward\nd) Right\nPress the button from the list above (or 'q' to close game) and then press Enter\n\0", player.left, player.up, player.right);
			break;
		}
		case 2: 
		{
			printf("Слева: %s\nВпереди: %s\nСправа: %s\n\na) Налево\nw) Вперёд\nd) Направо\nНажмите клавишу из списка выше (или 'q', чтобы закрыть игру), затем нажмите Enter\n\0", player.left, player.up, player.right);
			break;
		}	
		case 3: 
		{
			printf("Izquierda: %s\nAdelante: %s\nA la derecha: %s\n\na) Izquierda\nw) Adelante\nd) A la derecha\nPresiona el botón de la lista anterior (o 'q' para cerrar el juego) y luego presiona Enter\n\0", player.left, player.up, player.right);
			break;
		}		
	}	
	
	while(1)
	{
		scanf("%s", player.choise);
		if(strcmp(player.choise, "a") == 0 || strcmp(player.choise, "A") == 0)
		{
			snprintf(player.choise, sizeof(player.choise), "%s", player.left);
			action();
		}
		else if(strcmp(player.choise, "w") == 0 || strcmp(player.choise, "W") == 0)
		{
			snprintf(player.choise, sizeof(player.choise), "%s", player.up);
			action();				
		}
		else if(strcmp(player.choise, "d") == 0 || strcmp(player.choise, "D") == 0)
		{
			snprintf(player.choise, sizeof(player.choise), "%s", player.right);
			action();				
		}
		else if(strcmp(player.choise, "q") == 0 || strcmp(player.choise, "Q") == 0)
		{
			CLEARSCREEN;
			exit(0);
		}
		else if(strcmp(player.choise, "G") == 0) //GOD-Mode cheat
		{
			player.weaponDamage = 100;
			player.chestArmor = 100;
			player.coins = player.coins + 1000;
			gamePlay();
		}
		else printf("\n");
	}
}

int main()
{
	srand(time(NULL));
	#if !defined(__APPLE__) && !defined(__unix__)
		system("chcp 65001"); //enable Unicode (UTF-8) in command prompt
	#endif
	//choose language
	#if !defined(__MSDOS__)
	while(1)
	{
		CLEARSCREEN;
		printf("VRD - Very random dungeon. A text-based rogue-like with RPG elements about a novice knight, an endless dungeon and defeating a dragon.\nCopyright (C) 2023  ArtSvetlakov (Artemiy Svetlakov)\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it under certain conditions.\nFor details please read the LICENSE file.\n\n\nChoose the language:\n1) English\n2) Русский\n3) Español\n\0");
		scanf("%s", player.choise);
		if(strcmp(player.choise, "1") == 0 )
		{
			langSelect = 1;
			break;
		}
		else if(strcmp(player.choise, "2") == 0)
		{
			langSelect = 2;
			break;				
		}
		else if(strcmp(player.choise, "3") == 0)
		{
			langSelect = 3;
			break;				
		}
		else printf("\n");
	}
	#else
	langSelect = 1;
	CLEARSCREEN;
	printf("VRD - Very random dungeon. A text-based rogue-like with RPG elements about a novice knight, an endless dungeon and defeating a dragon.\nCopyright (C) 2023  ArtSvetlakov (Artemiy Svetlakov)\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it under certain conditions.\nFor details please read the LICENSE file.\n\0");
	PAUSE;
	#endif
	startScreen();
	return 0;
}
