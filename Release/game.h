#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "windows.h"
#include "audiere.h"
int ochki = 0;
int ochki1 = 0;
int musicnomer = 5;
bool musicplay = false;
int schet[4];
int schet1[4];
int dv[20];
int poloshenie = 0;
int poloshenie1 = 0;
float peredachatimer = 0;
bool peredacha = false;
bool death1=false;
bool death2=false;
bool bonusplay = false;
bool drowtext1 = false;
bool drowtext2 = false;
bool drowtext3 = false;
bool drowtext = false;
bool interval[2];
bool svoboda = false;
bool timer = false;
bool armor[2];
bool shtab = false;
bool poiavlenie = true;
bool igra = false;
bool perezapusk = false;
bool paus = false;
bool pause = false;
bool mag = false;
bool magazine = false;
bool vnis = false;
bool vverx = false;
bool enter = false;
bool magazine1 = false;
bool vnis1 = false;
bool vverx1 = false;
bool enter1 = false;
bool vvod = true;
float poloshenietimer1 = 0;
float vnistimer1 = 0;
float vverxtimer1 = 0;
float magazinetimer1 = 0;
float poloshenietimer = 0;
float vnistimer = 0;
float vverxtimer = 0;
float magazinetimer = 0;
float pausetimer = 0;
float perezapusktime = 0;
float vistreltimer[2];
float shtabtimer = 0;
float CurrentFrame[2];
float CurrentFrame1[20];
float spaunertimer = 0;
float bonustimer = 0;
float bonustimer1 = 0;
float bonustimer2 = 0;
float logictimer = 0;
float timertimer = 0;
float armortimer[2];
float lvltimer = 0;
int colvo = 20;
int lvl = 1;
int closhnost = 2;
bool nytr = false;
int Rand, nomer;
using namespace sf;
using namespace audiere;

class bonus {
public:
	float x, y, w1, h1, w2, h2, dx, dy, speed = 0;
	int j;
	float vrem = 0;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	int New(String F, float X, float Y, float W1, float H1, float W2, float H2) {
		File = F;// имя файла + расширение

		w1 = W1; h1 = H1; w2 = W2; h2 = H2;
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(w1, h1, w2, h2));
		sprite.setPosition(x, y);
		return 0;
	}
}q[3];

class bots {
public:
	float x, y, w1, h1, w2, h2, dx, dy, speed = 0;
	int hp = 4;
	bool death = true;
	int lvl = 0;
	int dir;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	void New(String F, float X, float Y, float W1, float H1, float W2, float H2) {
		File = F;// имя файла + расширение

		w1 = W1; h1 = H1; w2 = W2; h2 = H2;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(w1, h1, w2, h2));
	}
	void update(float time) {
		switch (dir) {
		case 0: dx = speed-(0.005*(closhnost-2)); dy = 0; break;
		case 1: dx = -speed+ (0.005*(closhnost - 2)); dy = 0; break;
		case 2: dx = 0; dy = speed- (0.005*(closhnost - 2)); break;
		case 3: dx = 0; dy = -speed+ (0.005*(closhnost - 2)); break;
		}
		x += dx * time;
		y += dy * time;
		speed = 0;
		sprite.setPosition(x, y);
		interactionWithMap();
	}
	void interactionWithMap()//ф-ция взаимодействия с картой
	{
		if ((x < 580) && (x > 0) && (y < 580) && (y > 0)) {
			for (int i = y / 20; i < (y + h2) / 20; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
				for (int j = x / 20; j < (x + w2) / 20; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
				{
					if (TileMap[i][j] == 'l')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
					{
						if (dy > 0)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dy < 0)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dx > 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dx < 0)
						{
							x = j * 20 + 20;//аналогично идем влево
						}
					}
					if (TileMap[i][j] == 'k') { //если символ равен 's' (камень)
						if (dy > 0)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dy < 0)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dx > 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dx < 0)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					if (TileMap[i][j] == 'q') { //если символ равен 's' (камень)
						if (dy > 0)//если мы шли вниз,
						{
							y = i * 20 - 30;
						}
						if ((b[0].y - 20 <= i * 20) && (b[0].y + 20 >= i * 20)) {
							if (dx > 0)
							{
								x = j * 20 - w2;
							}
							if (dx < 0)
							{
								x = j * 20 + 20;
							}
							if (dy < 0)
							{
								y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
							}
						}
						else if (dx > 0)
						{
							y = y - 10;
						}
						else if (dx < 0)
						{
							y = y - 10;
						}
					}
					if (TileMap[i][j] == 'w') { //если символ равен 's' (камень)
						if (dy < 0)
						{
							y = i * 20 + 11;
						}
						if ((b[0].y - 10 <= i * 20) && (b[0].y + 40 >= i * 20)) {
							if (dx > 0)
							{
								x = j * 20 - w2;
							}
							if (dx < 0)
							{
								x = j * 20 + 20;
							}
							if (dy > 0)
							{
								y = i * 20 - h2;
							}
						}

					}
					if (TileMap[i][j] == 'e') { //если символ равен 's' (камень)
						if (dx > 0)
						{
							x = j * 20 - 31;
						}
						if ((b[0].x - 20 <= j * 20) && (b[0].x + 20 >= j * 20)) {
							if (dy > 0)
							{
								y = i * 20 - h2;
							}
							if (dy < 0)
							{
								y = i * 20 + 20;
							}
							if (dx < 0)
							{
								x = j * 20 + 20;
							}
						}
					}
					if (TileMap[i][j] == 'r') { //если символ равен 's' (камень)
						if (dx < 0)
						{
							x = j * 20 + 11;
						}
						if ((b[0].x - 10 <= j * 20) && (b[0].x + 40 >= j * 20)) {
							if (dy > 0)
							{
								y = i * 20 - h2;
							}
							if (dy < 0)
							{
								y = i * 20 + 20;
							}
							if (dx > 0)
							{
								x = j * 20 - w2;
							}
						}
					}
					if (TileMap[i][j] == 'a') { //если символ равен 's' (камень)

						if ((b[0].y + 25 <= i * 20) && (b[0].y + 33 >= i * 20)) {
							if (dy > 0)
							{
								y = i * 20 - 33;
							}
						}
						if ((b[0].x - 5 <= j * 20) && (b[0].x >= j * 20)) {
							if (dx < 0)
							{
								x = j * 20 + 14;
							}
						}
						if ((b[0].x + 25 <= j * 20) && (b[0].x + 35 >= j * 20)) {
							if (dx > 0)
							{
								x = j * 20 - 40;
							}
						}
						if ((b[0].y - 25 <= i * 20) && (b[0].y - 15 >= i * 20)) {
							if (dy < 0)
							{
								y = i * 20 + 20;
							}
						}
					}
					if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
						if ((b[0].y - 35 <= i * 20) && (b[0].y - 5 >= i * 20)) {
							if (dy < 0)
							{
								y = i * 20 + 15;
							}
						}
						if ((b[0].x - 15 <= j * 20) && (b[0].x - 5 >= j * 20)) {
							if (dx < 0)
							{
								x = j * 20 + 13;
							}
						}
						if ((b[0].x + 25 <= j * 20) && (b[0].x + 35 >= j * 20)) {
							if (dx > 0)
							{
								x = j * 20 - 40;
							}
						}
						if ((b[0].y + 25 <= i * 20) && (b[0].y + 35 >= i * 20)) {
							if (dy > 0)
							{
								y = i * 20 - h2 - 2;
							}
						}

					}
					if (TileMap[i][j] == 'd') { //если символ равен 's' (камень)
						if ((b[0].x + 25 <= j * 20) && (b[0].x + 35 >= j * 20)) {
							if (dx > 0)
							{
								x = j * 20 - 31;
							}
						}
						if ((b[0].y - 35 <= i * 20) && (b[0].y - 5 >= i * 20)) {
							if (dy < 0)
							{
								y = i * 20 + 15;
							}
						}
						if ((b[0].x - 15 <= j * 20) && (b[0].x - 5 >= j * 20)) {
							if (dx < 0)
							{
								x = j * 20 + 20;
							}
						}
						if ((b[0].y + 30 <= i * 20) && (b[0].y + 40 >= i * 20)) {
							if (dy > 0)
							{
								y = i * 20 - h2 - 2;
							}
						}
					}
					if (TileMap[i][j] == 'f') { //если символ равен 's' (камень)
						if ((b[0].x + 25 <= j * 20) && (b[0].x + 35 >= j * 20)) {
							if (dx > 0)
							{
								x = j * 20 - 31;
							}
						}
						if ((b[0].y + 25 <= i * 20) && (b[0].y + 33 >= i * 20)) {
							if (dy > 0)
							{
								y = i * 20 - 33;
							}
						}
						if ((b[0].y - 25 <= i * 20) && (b[0].y - 15 >= i * 20)) {
							if (dy < 0)
							{
								y = i * 20 + 20;
							}
						}
						if ((b[0].x - 15 <= j * 20) && (b[0].x - 5 >= j * 20)) {
							if (dx < 0)
							{
								x = j * 20 + 20;
							}
						}
					}
					if (TileMap[i][j] == 'm') { //если символ равен 's' (камень)
						if (dy > 0)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dy < 0)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dx > 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dx < 0)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					if (TileMap[i][j] == 'v') { //если символ равен 's' (камень)
						if (dy > 0)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dy < 0)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dx > 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dx < 0)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					if (TileMap[i][j] == 'g') { //если символ равен 's' (камень)
						if (dy > 0)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dy < 0)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dx > 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dx < 0)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					if (TileMap[i][j] == 'h') { //если символ равен 's' (камень)
						if (dy > 0)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dy < 0)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dx > 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dx < 0)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					if (TileMap[i][j] == 'b') { //если символ равен 's' (камень)
						if (dy > 0)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dy < 0)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dx > 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dx < 0)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					if (TileMap[i][j] == 'n') { //если символ равен 's' (камень)
						if (dy > 0)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dy < 0)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dx > 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dx < 0)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
				}
		}
	}
}b[20];


class Player {
public:
	bool zamiranie = false;
	int zvezda = 0;
	int skolshenie = 4;
	bool obnovlenie = false;
	float zamiranietimer = 0;
	float x, y, w1, h1, w2, h2, dx, dy, speed = 0;
	int dir = 3, life = 3;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	void New(String F, float X, float Y, float W1, float H1, float W2, float H2) {
		File = F;// имя файла + расширение

		w1 = W2; h1 = H2; w2 = W2; h2 = H2;
		image.loadFromFile("images/" + File);
		for (int i = 240;i < 256;i++) {
			for (int j = 240;j < 256;j++) {
				for (int k = 240;k < 256;k++) {
					image.createMaskFromColor(Color(i, j, k));
				}
			}
		}
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(w1, h1, w2, h2));
	}
	void update(float time) {
		switch (dir) {
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}
		x += dx * time;
		y += dy * time;
		speed = 0;
		sprite.setPosition(x, y);
		interactionWithMap();
	}
	void interactionWithMap()//ф-ция взаимодействия с картой
	{
		if ((x < 580) && (x > 0) && (y < 580) && (y > 0)) {
			if (dy > 0)//если мы шли вниз,
			{
				skolshenie = 2;
			}
			if (dy < 0)
			{
				skolshenie = 3;
			}
			if (dx > 0)
			{
				skolshenie = 0;
			}
			if (dx < 0)
			{
				skolshenie = 1;
			}
			for (int i = y / 20; i < (y + h2) / 20; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
				for (int j = x / 20; j < (x + w2) / 20; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
				{
					if (TileMap[i][j] == 'j') { //если символ равен 's' (камень)
						if ((dx == 0) && (dy == 0)) {
							if (skolshenie == 0)
								x = j * 20 + 20;
							if (skolshenie == 1)
								x = j * 20 - 20;
							if (skolshenie == 2)
								y = i * 20 + 20;
							if (skolshenie == 3)
								y = i * 20 - 20;
							skolshenie = 4;
						}
					}
					if (TileMap[i][j] == 'l')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
					{
						if (dir == 2)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dir == 3)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dir == 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dir == 1)
						{
							x = j * 20 + 20;//аналогично идем влево
						}
					}
					if (TileMap[i][j] == 'k') { //если символ равен 's' (камень)
						if (dir == 2)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dir == 3)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dir == 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dir == 1)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					if (TileMap[i][j] == 'q') { //если символ равен 's' (камень)
						if (dir == 2)//если мы шли вниз,
						{
							y = i * 20 - 30;
						}
						if ((s[0].y - 20 <= i * 20) && (s[0].y + 20 >= i * 20)) {
							if (dir == 0)
							{
								x = j * 20 - w2;
							}
							if (dir == 1)
							{
								x = j * 20 + 20;
							}
							if (dir == 3)
							{
								y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
							}
						}
						else if (dx > 0)
						{
							y = y - 10;
						}
						else if (dx < 0)
						{
							y = y - 10;
						}
					}
					if (TileMap[i][j] == 'w') { //если символ равен 's' (камень)
						if (dir == 3)
						{
							y = i * 20 + 11;
						}
						if ((s[0].y - 10 <= i * 20) && (s[0].y + 40 >= i * 20)) {
							if (dir == 0)
							{
								x = j * 20 - w2;
							}
							if (dir == 1)
							{
								x = j * 20 + 20;
							}
							if (dir == 2)
							{
								y = i * 20 - h2;
							}
						}

					}
					if (TileMap[i][j] == 'e') { //если символ равен 's' (камень)
						if (dir == 0)
						{
							x = j * 20 - 31;
						}
						if ((s[0].x - 20 <= j * 20) && (s[0].x + 20 >= j * 20)) {
							if (dir == 2)
							{
								y = i * 20 - h2;
							}
							if (dir == 3)
							{
								y = i * 20 + 20;
							}
							if (dir == 1)
							{
								x = j * 20 + 20;
							}
						}
					}
					if (TileMap[i][j] == 'r') { //если символ равен 's' (камень)
						if (dir == 1)
						{
							x = j * 20 + 11;
						}
						if ((s[0].x - 10 <= j * 20) && (s[0].x + 40 >= j * 20)) {
							if (dir == 2)
							{
								y = i * 20 - h2;
							}
							if (dir == 3)
							{
								y = i * 20 + 20;
							}
							if (dir == 0)
							{
								x = j * 20 - w2;
							}
						}
					}
					if (TileMap[i][j] == 'a') { //если символ равен 's' (камень)

						if ((s[0].y + 25 <= i * 20) && (s[0].y + 33 >= i * 20)) {
							if (dir == 2)
							{
								y = i * 20 - 33;
							}
						}
						if ((s[0].x - 5 <= j * 20) && (s[0].x >= j * 20)) {
							if (dir == 1)
							{
								x = j * 20 + 14;
							}
						}
						if ((s[0].x + 25 <= j * 20) && (s[0].x + 35 >= j * 20)) {
							if (dir == 0)
							{
								x = j * 20 - 40;
							}
						}
						if ((s[0].y - 25 <= i * 20) && (s[0].y - 15 >= i * 20)) {
							if (dir == 3)
							{
								y = i * 20 + 20;
							}
						}
					}
					if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
						if ((s[0].y - 35 <= i * 20) && (s[0].y - 5 >= i * 20)) {
							if (dir == 3)
							{
								y = i * 20 + 15;
							}
						}
						if ((s[0].x - 15 <= j * 20) && (s[0].x - 5 >= j * 20)) {
							if (dir == 1)
							{
								x = j * 20 + 13;
							}
						}
						if ((s[0].x + 25 <= j * 20) && (s[0].x + 35 >= j * 20)) {
							if (dir == 0)
							{
								x = j * 20 - 40;
							}
						}
						if ((s[0].y + 25 <= i * 20) && (s[0].y + 35 >= i * 20)) {
							if (dir == 2)
							{
								y = i * 20 - h2 - 2;
							}
						}

					}
					if (TileMap[i][j] == 'd') { //если символ равен 's' (камень)
						if ((s[0].x + 25 <= j * 20) && (s[0].x + 35 >= j * 20)) {
							if (dir == 0)
							{
								x = j * 20 - 31;
							}
						}
						if ((s[0].y - 35 <= i * 20) && (s[0].y - 5 >= i * 20)) {
							if (dir == 3)
							{
								y = i * 20 + 15;
							}
						}
						if ((s[0].x - 15 <= j * 20) && (s[0].x - 5 >= j * 20)) {
							if (dir == 1)
							{
								x = j * 20 + 20;
							}
						}
						if ((s[0].y + 30 <= i * 20) && (s[0].y + 40 >= i * 20)) {
							if (dir == 2)
							{
								y = i * 20 - h2 - 2;
							}
						}
					}
					if (TileMap[i][j] == 'f') { //если символ равен 's' (камень)
						if ((s[0].x + 25 <= j * 20) && (s[0].x + 35 >= j * 20)) {
							if (dir == 0)
							{
								x = j * 20 - 31;
							}
						}
						if ((s[0].y + 25 <= i * 20) && (s[0].y + 33 >= i * 20)) {
							if (dir == 2)
							{
								y = i * 20 - 33;
							}
						}
						if ((s[0].y - 25 <= i * 20) && (s[0].y - 15 >= i * 20)) {
							if (dir == 3)
							{
								y = i * 20 + 20;
							}
						}
						if ((s[0].x - 15 <= j * 20) && (s[0].x - 5 >= j * 20)) {
							if (dir == 1)
							{
								x = j * 20 + 20;
							}
						}
					}
					if (TileMap[i][j] == 'm') { //если символ равен 's' (камень)
						if (dir == 2)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dir == 3)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dir == 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dir == 1)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					if (TileMap[i][j] == 'v') { //если символ равен 's' (камень)
						if (dir == 2)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dir == 3)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dir == 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dir == 1)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					if (TileMap[i][j] == 'g') { //если символ равен 's' (камень)
						if (dir == 2)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dir == 3)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dir == 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dir == 1)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					if (TileMap[i][j] == 'h') { //если символ равен 's' (камень)
						if (dir == 2)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dir == 3)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dir == 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dir == 1)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					if (TileMap[i][j] == 'b') { //если символ равен 's' (камень)
						if (dir == 2)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dir == 3)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dir == 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dir == 1)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					if (TileMap[i][j] == 'n') { //если символ равен 's' (камень)
						if (dir == 2)//если мы шли вниз,
						{
							y = i * 20 - h2;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dir == 3)
						{
							y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dir == 0)
						{
							x = j * 20 - w2;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dir == 1)
						{
							x = j * 20 + 20;//аналогично идем влево
						}//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}

				}
		}
	}
	void proverka_na_stolknovenie(float time, int i) {
		bool stolk = false;
		if (dir == 3) {
			for (int j = 0;j < 20;j++) {
				if ((x + 30 >= b[j].x) && (x - 30 <= b[j].x) && (y >= b[j].y) && (y - 40 <= b[j].y)) {
					stolk = true;
				}
			}
			if ((x + 30 >= s[i].x) && (x - 30 <= s[i].x) && (y >= s[i].y) && (y - 40 <= s[i].y)) {
				stolk = true;
			}
			
				
			
		}
		if (dir == 2) {
			for (int j = 0;j < 20;j++) {
				if ((x + 30 >= b[j].x) && (x - 30 <= b[j].x) && (y + 40 >= b[j].y) && (y <= b[j].y)) {
					stolk = true;
				}
			}
			if ((x + 30 >= s[i].x) && (x - 30 <= s[i].x) && (y + 40 >= s[i].y) && (y <= s[i].y)) {
				stolk = true;
			}
			
		}
		if (dir == 1) {
			for (int j = 0;j < 20;j++) {
				if ((x >= b[j].x) && (x - 35 <= b[j].x) && (y + 30 >= b[j].y) && (y - 30 <= b[j].y)) {
					stolk = true;
				}
			}
			if ((x >= s[i].x) && (x - 35 <= s[i].x) && (y + 30 >= s[i].y) && (y - 30 <= s[i].y)) {
				stolk = true;
			}
			
		}
		if (dir == 0) {
			for (int j = 0;j < 20;j++) {
				if ((x + 35 >= b[j].x) && (x <= b[j].x) && (y + 30 >= b[j].y) && (y - 30 <= b[j].y)) {
					stolk = true;
				}
			}
			if ((x + 35 >= s[i].x) && (x <= s[i].x) && (y + 30 >= s[i].y) && (y - 30 <= s[i].y)) {
				stolk = true;
			}
			
		}
		if (stolk == false)
			update(time);
	}
}s[2];


class puli {
public:
	float  x, y, w1, h1, w2, h2, dx, dy, speed = 0;
	int dir, x1, y1, dir1;
	int f;
	bool anim = false;
	float anim_float = 0;
	bool vistrel = false;
	bool vistreldrow = false;
	bool vistreldvish = false;
	bool vistrelzakonchen = true;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Sprite sprite1;
	void New(String F, float X, float Y, float W1, float H1, float W2, float H2) {
		File = F;// имя файла + расширение

		w1 = W1; h1 = H1; w2 = W2; h2 = H2;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setPosition(x, y);
		sprite.setTextureRect(IntRect(w1, h1, w2, h2));
		sprite1.setTexture(texture);
	}
	void interactionWithMap1(int a)//ф-ция взаимодействия с картой
	{
		if ((x < 580) && (x > 0) && (y < 580) && (y > 0)) {
			int m = a;
			for (int i = y / 20; i < (y + h2) / 20; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
				for (int j = x / 20; j < (x + w2) / 20; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
				{
					if (TileMap[i][j] == 'k') { //если символ равен 's' (камень)
						if (F[m].f == 2)//если мы шли вниз,
						{
							TileMap[i][j] = 'q';//вниз
							F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
						}
						else if (F[m].f == 3)
						{
							TileMap[i][j] = 'w';//вверх
							F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
						}
						else if (F[m].f == 0)
						{
							TileMap[i][j] = 'e';//вправо
							F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
						}
						else if (F[m].f == 1)
						{
							TileMap[i][j] = 'r';//влево
							F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
						}
						if (m < 3) {
							if (s[0].zvezda > 2)
								TileMap[i][j] = 'o';
						}
						else if (m < 6) {
							if (s[1].zvezda > 2)
								TileMap[i][j] = 'o';
						}
						x1 = x;
						y1 = y;
						dir1 = f;
						F[m].anim = true;
					}
					else if (TileMap[i][j] == 'q') { //если символ равен 's' (камень)
						if (F[m].f == 2)//если мы шли вниз,
						{
							TileMap[i][j] = 'o';//вниз
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
							F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
						}
						else if (F[m].f == 3)
						{
							TileMap[i][j] = 'o';//вверх
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
							F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
						}
						else if (F[m].f == 0)
						{
							if ((F[m].y - 5 <= i * 20) && (F[m].y + 5 >= i * 20)) {
								TileMap[i][j] = 'f';//вправо
								if (m < 3) {
									if (s[0].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								else if (m < 6) {
									if (s[1].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								x1 = x;
								y1 = y;
								dir1 = f;
								F[m].anim = true;
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
						}
						else if (F[m].f == 1)
						{
							if ((F[m].y - 5 <= i * 20) && (F[m].y + 5 >= i * 20)) {
								TileMap[i][j] = 'a';//влево
								if (m < 3) {
									if (s[0].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								else if (m < 6) {
									if (s[1].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								x1 = x;
								y1 = y;
								dir1 = f;
								F[m].anim = true;
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
						}
						
					}
					else if (TileMap[i][j] == 'w') { //если символ равен 's' (камень)
						if (F[m].f == 2)//если мы шли вниз,
						{
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
							TileMap[i][j] = 'o';//вниз
							F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
						}
						else if (F[m].f == 3)
						{
							TileMap[i][j] = 'o';//вверх
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
							F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
						}
						else if (F[m].f == 0)
						{
							if ((F[m].y + 10 <= i * 20) && (F[m].y + 20 >= i * 20)) {
								TileMap[i][j] = 'd';//вправо
								if (m < 3) {
									if (s[0].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								else if (m < 6) {
									if (s[1].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								x1 = x;
								y1 = y;
								dir1 = f;
								F[m].anim = true;
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
						}
						else if (F[m].f == 1)
						{
							if ((F[m].y + 10 <= i * 20) && (F[m].y + 20 >= i * 20)) {
								TileMap[i][j] = 's';//влево
								if (m < 3) {
									if (s[0].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								else if (m < 6) {
									if (s[1].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								x1 = x;
								y1 = y;
								dir1 = f;
								F[m].anim = true;
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
						}
						
					}
					else if (TileMap[i][j] == 'e') { //если символ равен 's' (камень)

						if ((F[m].x - 10 <= j * 20) && (F[m].x >= j * 20)) {
							if (F[m].f == 2)//если мы шли вниз,
							{
								TileMap[i][j] = 'f';//вниз
								if (m < 3) {
									if (s[0].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								else if (m < 6) {
									if (s[1].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								x1 = x;
								y1 = y;
								dir1 = f;
								F[m].anim = true;
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							else if (F[m].f == 3)
							{
								TileMap[i][j] = 'd';//вверх
								if (m < 3) {
									if (s[0].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								else if (m < 6) {
									if (s[1].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								x1 = x;
								y1 = y;
								dir1 = f;
								F[m].anim = true;
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
						}

						else if (F[m].f == 0)
						{
							TileMap[i][j] = 'o';//вправо
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
							F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
						}
						else if (F[m].f == 1)
						{
							TileMap[i][j] = 'o';//влево
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
							F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
						}
						
					}
					else if (TileMap[i][j] == 'r') { //если символ равен 's' (камень)

						if ((F[m].x <= j * 20) && (F[m].x + 20 >= j * 20)) {
							if (F[m].f == 2)//если мы шли вниз,
							{
								TileMap[i][j] = 'a';//вниз
								if (m < 3) {
									if (s[0].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								else if (m < 6) {
									if (s[1].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							else if (F[m].f == 3)
							{
								TileMap[i][j] = 's';//вверх
								if (m < 3) {
									if (s[0].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								else if (m < 6) {
									if (s[1].zvezda > 2)
										TileMap[i][j] = 'o';
								}
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
						}
						else if (F[m].f == 0)
						{
							TileMap[i][j] = 'o';//вправо
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
							F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
						}
						else if (F[m].f == 1)
						{
							TileMap[i][j] = 'o';//влево
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
							F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
						}
						

					}
					else if (TileMap[i][j] == 'a') { //если символ равен 's' (камень)
						if ((F[m].y - 5 <= i * 20) && (F[m].y + 5 >= i * 20)) {
							if (F[m].f == 0)
							{
								TileMap[i][j] = 'o';//вправо
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							else if (F[m].f == 1)
							{
								TileMap[i][j] = 'o';//влево
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
						}
						if ((F[m].x <= j * 20) && (F[m].x + 20 >= j * 20)) {
							if (F[m].f == 2)//если мы шли вниз,
							{
								TileMap[i][j] = 'o';//вниз
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							else if (F[m].f == 3)
							{
								TileMap[i][j] = 'o';//вверх
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
						}
						

					}
					else if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
						if ((F[m].y + 10 <= i * 20) && (F[m].y + 20 >= i * 20)) {
							if (F[m].f == 0)
							{
								TileMap[i][j] = 'o';//вправо
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							else if (F[m].f == 1)
							{
								TileMap[i][j] = 'o';//влево
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
						}
						if ((F[m].x <= j * 20) && (F[m].x + 20 >= j * 20)) {
							if (F[m].f == 2)//если мы шли вниз,
							{
								TileMap[i][j] = 'o';//вниз
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							else if (F[m].f == 3)
							{
								TileMap[i][j] = 'o';//вверх
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
						}
						
					}
					else if (TileMap[i][j] == 'd') { //если символ равен 's' (камень)
						if ((F[m].y + 10 <= i * 20) && (F[m].y + 20 >= i * 20)) {
							if (F[m].f == 0)
							{
								TileMap[i][j] = 'o';//вправо
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							else if (F[m].f == 1)
							{
								TileMap[i][j] = 'o';//влево
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
						}
						else if ((F[m].x - 10 <= j * 20) && (F[m].x >= j * 20)) {
							if (F[m].f == 2)//если мы шли вниз,
							{
								TileMap[i][j] = 'o';//вниз
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							else if (F[m].f == 3)
							{
								TileMap[i][j] = 'o';//вверх
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
						}
						

					}
					else if (TileMap[i][j] == 'f') { //если символ равен 's' (камень)
						if ((F[m].y - 5 <= i * 20) && (F[m].y + 5 >= i * 20)) {
							if (F[m].f == 0)
							{
								TileMap[i][j] = 'o';//вправо
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							else if (F[m].f == 1)
							{
								TileMap[i][j] = 'o';//влево
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
						}
						else if ((F[m].x - 10 <= j * 20) && (F[m].x >= j * 20)) {
							if (F[m].f == 2)//если мы шли вниз,
							{
								TileMap[i][j] = 'o';//вниз
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							else if (F[m].f == 3)
							{
								TileMap[i][j] = 'o';//вверх
								F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
							}
							x1 = x;
							y1 = y;
							dir1 = f;
							F[m].anim = true;
						}
						

					}
					else if (TileMap[i][j] == 'm') {
						x1 = x;
						y1 = y;
						dir1 = f;
						F[m].anim = true;
						if (m < 3) {
							if (s[0].zvezda > 2)
								TileMap[i][j] = 'o';
						}
						else if (m < 6) {
							if (s[1].zvezda > 2)
								TileMap[i][j] = 'o';
						}
						F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
					}
					else if (TileMap[i][j] == 'u') {

						if (m < 3) {
							if (s[0].zvezda > 2) {
								TileMap[i][j] = 'o';
								x1 = x;
								y1 = y;
								dir1 = f;
								F[m].anim = true;
							}
						}
						else if (m < 6) {
							if (s[1].zvezda > 2) {
								TileMap[i][j] = 'o';
								x1 = x;
								y1 = y;
								dir1 = f;
								F[m].anim = true;
							}
						}

					}
					else if (TileMap[i][j] == 'l') {
						x1 = x;
						y1 = y;
						dir1 = f;
						F[m].anim = true;
						F[m].vistreldvish = false; F[m].vistrelzakonchen = true; F[m].vistrel = false;
					}
					else if (TileMap[i][j] == 'g') {
						s[0].life = 0;
						s[1].life = 0;
					}
					else if (TileMap[i][j] == 'h') {
						s[0].life = 0;
						s[1].life = 0;
					}
					else if (TileMap[i][j] == 'b') {
						s[0].life = 0;
						s[1].life = 0;
					}
					else if (TileMap[i][j] == 'n') {
						s[0].life = 0;
						s[1].life = 0;
					}
				}
		}
	}
	void animation(int i, float x, float y, int dir) {
		int m = i;
		if (dir == 0) {
			if (F[m].anim_float < 11) {
				F[m].sprite1.setTextureRect(IntRect(3 + 15 * int(F[m].anim_float), 121, 14, 15));
				F[m].sprite1.setScale(3.f, 3.f);
				F[m].sprite1.setPosition(x + 10, y);
				F[m].anim_float += 0.04;
			}
			else {
				F[m].anim = false;
				F[m].anim_float = 0;
			}
		}
		if (dir == 1) {
			if (F[m].anim_float < 11) {
				F[m].sprite1.setTextureRect(IntRect(3 + 15 * int(F[m].anim_float), 121, 14, 15));
				F[m].sprite1.setScale(3.f, 3.f);
				F[m].sprite1.setPosition(x - 10, y);
				F[m].anim_float += 0.04;
			}
			else {
				F[m].anim = false;
				F[m].anim_float = 0;
			}
		}
		if (dir == 2) {
			if (F[m].anim_float < 11) {
				F[m].sprite1.setTextureRect(IntRect(3 + 15 * int(F[m].anim_float), 121, 14, 15));
				F[m].sprite1.setScale(3.f, 3.f);
				F[m].sprite1.setPosition(x + 4, y + 10);
				F[m].anim_float += 0.04;
			}
			else {
				F[m].anim = false;
				F[m].anim_float = 0;
			}
		}
		if (dir == 3) {
			if (F[m].anim_float < 11) {
				F[m].sprite1.setTextureRect(IntRect(3 + 15 * int(F[m].anim_float), 121, 14, 15));
				F[m].sprite1.setScale(3.f, 3.f);
				F[m].sprite1.setPosition(x + 4, y - 10);
				F[m].anim_float += 0.04;
			}
			else {
				F[m].anim = false;
				F[m].anim_float = 0;
			}
		}

	}
}F[26];



void Tick() {
	//выстрелы
	if (pause == false) {
		for (int i = 0; i < 26; i++) {
			if (F[i].vistreldvish == false) {
				if (i < 3)
					F[i].f = s[0].dir;
				else if (i < 6)
					F[i].f = s[1].dir;
				else {
					F[i].f = b[i - 6].dir;
				}
			}
			if (i < 3) {
				if (F[i].vistreldvish == true) {
					if ((F[i].x < 580) && (F[i].x > 0) && (F[i].y < 580) && (F[i].y > 0)) {
						if (F[i].f == 2) {
							F[i].sprite.setTextureRect(IntRect(77, 0, 30, 30));
							if (s[0].zvezda == 0)
								F[i].y += 0.5;
							else F[i].y += 0.8;


							F[i].sprite.setPosition(F[i].x + 2, F[i].y);
						}
						if (F[i].f == 1) {
							F[i].sprite.setTextureRect(IntRect(5, 12, 26, 12));

							if (s[0].zvezda == 0)
								F[i].x -= 0.5;
							else F[i].x -= 0.8;

							F[i].sprite.setPosition(F[i].x, F[i].y + 15);
						}
						if (F[i].f == 0) {
							F[i].sprite.setTextureRect(IntRect(120, 3, 34, 34));

							if (s[0].zvezda == 0)
								F[i].x += 0.5;
							else F[i].x += 0.8;


							F[i].sprite.setPosition(F[i].x, F[i].y);
						}
						if (F[i].f == 3) {
							F[i].sprite.setTextureRect(IntRect(50, 5, 12, 26));

							if (s[0].zvezda == 0)
								F[i].y -= 0.5;
							else F[i].y -= 0.8;
							F[i].sprite.setPosition(F[i].x + 13, F[i].y);
						}
					}
					else {
						F[i].vistreldvish = false; F[i].vistrelzakonchen = true; F[i].vistrel = false;
					}
				}
			}
			else if (i < 6) {
				if (player1 == false) {
					if (F[i].vistreldvish == true) {
						if ((F[i].x < 580) && (F[i].x > 0) && (F[i].y < 580) && (F[i].y > 0)) {
							if (F[i].f == 2) {
								F[i].sprite.setTextureRect(IntRect(77, 0, 30, 30));
								if (s[1].zvezda == 0)
									F[i].y += 0.5;
								else F[i].y += 0.8;


								F[i].sprite.setPosition(F[i].x + 2, F[i].y);
							}
							if (F[i].f == 1) {
								F[i].sprite.setTextureRect(IntRect(5, 12, 26, 12));

								if (s[1].zvezda == 0)
									F[i].x -= 0.5;
								else F[i].x -= 0.8;

								F[i].sprite.setPosition(F[i].x, F[i].y + 15);
							}
							if (F[i].f == 0) {
								F[i].sprite.setTextureRect(IntRect(120, 3, 34, 34));

								if (s[1].zvezda == 0)
									F[i].x += 0.5;
								else F[i].x += 0.8;


								F[i].sprite.setPosition(F[i].x, F[i].y);
							}
							if (F[i].f == 3) {
								F[i].sprite.setTextureRect(IntRect(50, 5, 12, 26));

								if (s[1].zvezda == 0)
									F[i].y -= 0.5;
								else F[i].y -= 0.8;
								F[i].sprite.setPosition(F[i].x + 13, F[i].y);
							}
						}
					}
					else {
						F[i].vistreldvish = false; F[i].vistrelzakonchen = true; F[i].vistrel = false;
					}
				}
			}
			else {
				if (F[i].vistreldvish == true) {
					if ((F[i].x < 580) && (F[i].x > 0) && (F[i].y < 580) && (F[i].y > 0)) {
						if (F[i].f == 2) {
							F[i].sprite.setTextureRect(IntRect(77, 0, 30, 30));
							if (b[i - 6].lvl == 2) {
								F[i].y += 0.8-(0.05*(closhnost-2));
							}
							else
								F[i].y += 0.5- (0.05*(closhnost - 2));
							F[i].sprite.setPosition(F[i].x + 2, F[i].y);
						}
						if (F[i].f == 1) {
							F[i].sprite.setTextureRect(IntRect(5, 12, 26, 12));
							if (b[i - 6].lvl == 2) {
								F[i].x -= 0.8+ (0.05*(closhnost - 2));
							}
							else
								F[i].x -= 0.5+ (0.05*(closhnost - 2));
							F[i].sprite.setPosition(F[i].x, F[i].y + 15);
						}
						if (F[i].f == 0) {
							F[i].sprite.setTextureRect(IntRect(120, 3, 34, 34));
							if (b[i - 6].lvl == 2) {
								F[i].x += 0.8- (0.05*(closhnost - 2));
							}
							else
								F[i].x += 0.5- (0.05*(closhnost - 2));
							F[i].sprite.setPosition(F[i].x, F[i].y);
						}
						if (F[i].f == 3) {
							F[i].sprite.setTextureRect(IntRect(50, 5, 12, 26));
							if (b[i - 6].lvl == 2) {
								F[i].y -= 0.8+ (0.05*(closhnost - 2));
							}
							else
								F[i].y -= 0.5+ (0.05*(closhnost - 2));
							F[i].sprite.setPosition(F[i].x + 13, F[i].y);
						}
					}
					else {
						F[i].vistreldvish = false; F[i].vistrelzakonchen = true; F[i].vistrel = false;
					}
				}
			}
		}
	}

	//регулировка движений
	for (int i = 0; i < 2;i++) {
		if ((s[i].dir == 0) || (s[i].dir == 1)) {
			int j = s[i].y;
			j = j % 20;
			if (j >= 10) {
				j = 20 - j;
				s[i].y += j;
			}
			else {
				s[i].y -= j;
			}
		}
		if ((s[i].dir == 3) || (s[i].dir == 2)) {
			int j = s[i].x;
			j = j % 20;
			if (j >= 10) {
				j = 20 - j;
				s[i].x += j;
			}
			else {
				s[i].x -= j;
			}
		}
		s[i].sprite.setPosition(s[i].x, s[i].y);
	}
	for (int i = 0;i < 20;i++) {
		if ((b[i].dir == 0) || (b[i].dir == 1)) {
			int j = b[i].y;
			j = j % 20;
			if (j >= 10) {
				j = 20 - j;
				b[i].y += j;
			}
			else {
				b[i].y -= j;
			}
		}
		if ((b[i].dir == 3) || (b[i].dir == 2)) {
			int j = b[i].x;
			j = j % 20;
			if (j >= 10) {
				j = 20 - j;
				b[i].x += j;
			}
			else {
				b[i].x -= j;
			}
		}
		b[i].sprite.setPosition(b[i].x, b[i].y);
	}


	//движение в пределах карты
	if ((s[0].x < 580) && (s[0].x > 0) && (s[0].y < 580) && (s[0].y > 0)) {
	}
	else {
		if ((s[0].x != 350) && (s[0].y != 600)) {
			s[0].x = 200;
			s[0].y = 520;
		}
	}
	if (player1 == false) {
		if ((s[1].x < 580) && (s[1].x > 0) && (s[1].y < 580) && (s[1].y > 0)) {
		}
		else {
			if ((s[1].x != 350) && (s[1].y != 600)) {
				s[1].x = 360;
				s[1].y = 520;
			}
		}
	}
	for (int i = 0; i < 20;i++) {
		if ((b[i].x < 580) && (b[i].x > 0) && (b[i].y < 580) && (b[i].y > 0)) {
		}
		else {
			if ((b[i].x != 600) && (b[i].y != 600)) {
				b[i].x = 280;
				b[i].y = 40;
			}
		}
	}

	// уничтожение танков
	if (player1 == false)
	{
		for (int j = 3; j < 6;j++) {
			for (int i = 0; i < 20;i++) {
				if ((F[j].x - 20 < b[i].x) && (F[j].x + 20 > b[i].x) && (F[j].y - 20 < b[i].y) && (F[j].y + 20 > b[i].y)) {
					F[j].vistreldvish = false; F[j].vistrelzakonchen = true; F[j].vistrel = false;
					if (b[i].lvl == 3) {
						b[i].hp -= 1;
						F[j].x1 = F[j].x;
						F[j].y1 = F[j].y;
						F[j].dir1 = F[j].f;
						F[j].anim = true;
						
						if (b[i].hp <= 0) {
							b[i].x = 600;
							b[i].y = 600;
							b[i].sprite.setPosition(b[i].x, b[i].y);
							colvo -= 1;
							b[i].death = true;
							schet1[3] += 1;
							ochki1 += 800;
						}
					}
					else {
						if (b[i].lvl == 2) {
							schet1[2] += 1;
							ochki1 += 600;
						}
						if (b[i].lvl == 1) {
							schet1[1] += 1;
							ochki1 += 400;
						}
						if (b[i].lvl == 0) {
							schet1[0] += 1;
							ochki1 += 200;
						}
						b[i].x = 600;
						b[i].y = 600;
						F[j].x1 = F[j].x;
						F[j].y1 = F[j].y;
						F[j].dir1 = F[j].f;
						F[j].anim = true;
						b[i].sprite.setPosition(b[i].x, b[i].y);
						colvo -= 1;
						b[i].death = true;
					}
					if ((b[i].lvl == 3) && (b[i].hp == 3)) {
						if (i == 3) {
							q[0].j = rand() % 6;

							int x = rand() % 26 * 20 + 40;
							int y = rand() % 26 * 20 + 40;
							if (q[0].j == 0)
								q[0].New("tanks/levelup.tga", x, y, 0, 0, 32, 32);
							if (q[0].j == 1)
								q[0].New("tanks/boom.tga", x, y, 0, 0, 32, 32);
							if (q[0].j == 2)
								q[0].New("tanks/timer.tga", x, y, 0, 0, 32, 32);
							if (q[0].j == 3)
								q[0].New("tanks/health.tga", x, y, 0, 0, 32, 32);
							if (q[0].j == 4)
								q[0].New("tanks/armor.tga", x, y, 0, 0, 32, 32);
							if (q[0].j == 5)
								q[0].New("tanks/life.tga", x, y, 0, 0, 32, 32);
						}
						if (i == 10) {
							q[1].j = rand() % 6;
							int x = rand() % 26 * 20 + 40;
							int y = rand() % 26 * 20 + 40;
							if (q[1].j == 0)
								q[1].New("tanks/levelup.tga", x, y, 0, 0, 32, 32);
							if (q[1].j == 1)
								q[1].New("tanks/boom.tga", x, y, 0, 0, 32, 32);
							if (q[1].j == 2)
								q[1].New("tanks/timer.tga", x, y, 0, 0, 32, 32);
							if (q[1].j == 3)
								q[1].New("tanks/health.tga", x, y, 0, 0, 32, 32);
							if (q[1].j == 4)
								q[1].New("tanks/armor.tga", x, y, 0, 0, 32, 32);
							if (q[1].j == 5)
								q[1].New("tanks/life.tga", x, y, 0, 0, 32, 32);
						}
						if (i == 17) {
							q[2].j = rand() % 6;
							int x = rand() % 26 * 20 + 40;
							int y = rand() % 26 * 20 + 40;
							if (q[2].j == 0)
								q[2].New("tanks/levelup.tga", x, y, 0, 0, 32, 32);
							if (q[2].j == 1)
								q[2].New("tanks/boom.tga", x, y, 0, 0, 32, 32);
							if (q[2].j == 2)
								q[2].New("tanks/timer.tga", x, y, 0, 0, 32, 32);
							if (q[2].j == 3)
								q[2].New("tanks/health.tga", x, y, 0, 0, 32, 32);
							if (q[2].j == 4)
								q[2].New("tanks/armor.tga", x, y, 0, 0, 32, 32);
							if (q[2].j == 5)
								q[2].New("tanks/life.tga", x, y, 0, 0, 32, 32);
						}
					}
					if (b[i].lvl != 3) {
						if (i == 3) {
							q[0].j = rand() % 6;

							int x = rand() % 26 * 20 + 40;
							int y = rand() % 26 * 20 + 40;
							if (q[0].j == 0)
								q[0].New("tanks/levelup.tga", x, y, 0, 0, 32, 32);
							if (q[0].j == 1)
								q[0].New("tanks/boom.tga", x, y, 0, 0, 32, 32);
							if (q[0].j == 2)
								q[0].New("tanks/timer.tga", x, y, 0, 0, 32, 32);
							if (q[0].j == 3)
								q[0].New("tanks/health.tga", x, y, 0, 0, 32, 32);
							if (q[0].j == 4)
								q[0].New("tanks/armor.tga", x, y, 0, 0, 32, 32);
							if (q[0].j == 5)
								q[0].New("tanks/life.tga", x, y, 0, 0, 32, 32);
						}
						if (i == 10) {
							q[1].j = rand() % 6;
							int x = rand() % 26 * 20 + 40;
							int y = rand() % 26 * 20 + 40;
							if (q[1].j == 0)
								q[1].New("tanks/levelup.tga", x, y, 0, 0, 32, 32);
							if (q[1].j == 1)
								q[1].New("tanks/boom.tga", x, y, 0, 0, 32, 32);
							if (q[1].j == 2)
								q[1].New("tanks/timer.tga", x, y, 0, 0, 32, 32);
							if (q[1].j == 3)
								q[1].New("tanks/health.tga", x, y, 0, 0, 32, 32);
							if (q[1].j == 4)
								q[1].New("tanks/armor.tga", x, y, 0, 0, 32, 32);
							if (q[1].j == 5)
								q[1].New("tanks/life.tga", x, y, 0, 0, 32, 32);
						}
						if (i == 17) {
							q[2].j = rand() % 6;
							int x = rand() % 26 * 20 + 40;
							int y = rand() % 26 * 20 + 40;
							if (q[2].j == 0)
								q[2].New("tanks/levelup.tga", x, y, 0, 0, 32, 32);
							if (q[2].j == 1)
								q[2].New("tanks/boom.tga", x, y, 0, 0, 32, 32);
							if (q[2].j == 2)
								q[2].New("tanks/timer.tga", x, y, 0, 0, 32, 32);
							if (q[2].j == 3)
								q[2].New("tanks/health.tga", x, y, 0, 0, 32, 32);
							if (q[2].j == 4)
								q[2].New("tanks/armor.tga", x, y, 0, 0, 32, 32);
							if (q[2].j == 5)
								q[2].New("tanks/life.tga", x, y, 0, 0, 32, 32);
						}
					}
				}
			}
		}
	}

	for (int j = 0; j < 3;j++) {
		for (int i = 0; i < 20;i++) {
			if ((F[j].x - 20 < b[i].x) && (F[j].x + 20 > b[i].x) && (F[j].y - 20 < b[i].y) && (F[j].y + 20 > b[i].y)) {
				F[j].vistreldvish = false; F[j].vistrelzakonchen = true; F[j].vistrel = false;
				if (b[i].lvl == 3) {
					b[i].hp -= 1;
					F[j].x1 = F[j].x;
					F[j].y1 = F[j].y;
					F[j].dir1 = F[j].f;
					F[j].anim = true;
					if (b[i].hp <= 0) {
						b[i].x = 600;
						b[i].y = 600;
						b[i].sprite.setPosition(b[i].x, b[i].y);
						colvo -= 1;
						b[i].death = true;
						schet[3] += 1;
						ochki += 800;
					}
				}
				else {
					if (b[i].lvl == 2) {
						schet[2] += 1;
						ochki += 600;
					}
					if (b[i].lvl == 1) {
						schet[1] += 1;
						ochki += 400;
					}
					if (b[i].lvl == 0) {
						schet[0] += 1;
						ochki += 200;
					}
					b[i].x = 600;
					b[i].y = 600;
					F[j].x1 = F[j].x;
					F[j].y1 = F[j].y;
					F[j].dir1 = F[j].f;
					F[j].anim = true;
					b[i].sprite.setPosition(b[i].x, b[i].y);
					colvo -= 1;
					b[i].death = true;
				}
				if ((b[i].lvl == 3) && (b[i].hp == 3)) {
					if (i == 3) {
						q[0].j = rand() % 6;

						int x = rand() % 26 * 20 + 40;
						int y = rand() % 26 * 20 + 40;
						if (q[0].j == 0)
							q[0].New("tanks/levelup.tga", x, y, 0, 0, 32, 32);
						if (q[0].j == 1)
							q[0].New("tanks/boom.tga", x, y, 0, 0, 32, 32);
						if (q[0].j == 2)
							q[0].New("tanks/timer.tga", x, y, 0, 0, 32, 32);
						if (q[0].j == 3)
							q[0].New("tanks/health.tga", x, y, 0, 0, 32, 32);
						if (q[0].j == 4)
							q[0].New("tanks/armor.tga", x, y, 0, 0, 32, 32);
						if (q[0].j == 5)
							q[0].New("tanks/life.tga", x, y, 0, 0, 32, 32);
					}
					if (i == 10) {
						q[1].j = rand() % 6;
						int x = rand() % 26 * 20 + 40;
						int y = rand() % 26 * 20 + 40;
						if (q[1].j == 0)
							q[1].New("tanks/levelup.tga", x, y, 0, 0, 32, 32);
						if (q[1].j == 1)
							q[1].New("tanks/boom.tga", x, y, 0, 0, 32, 32);
						if (q[1].j == 2)
							q[1].New("tanks/timer.tga", x, y, 0, 0, 32, 32);
						if (q[1].j == 3)
							q[1].New("tanks/health.tga", x, y, 0, 0, 32, 32);
						if (q[1].j == 4)
							q[1].New("tanks/armor.tga", x, y, 0, 0, 32, 32);
						if (q[1].j == 5)
							q[1].New("tanks/life.tga", x, y, 0, 0, 32, 32);
					}
					if (i == 17) {
						q[2].j = rand() % 6;
						int x = rand() % 26 * 20 + 40;
						int y = rand() % 26 * 20 + 40;
						if (q[2].j == 0)
							q[2].New("tanks/levelup.tga", x, y, 0, 0, 32, 32);
						if (q[2].j == 1)
							q[2].New("tanks/boom.tga", x, y, 0, 0, 32, 32);
						if (q[2].j == 2)
							q[2].New("tanks/timer.tga", x, y, 0, 0, 32, 32);
						if (q[2].j == 3)
							q[2].New("tanks/health.tga", x, y, 0, 0, 32, 32);
						if (q[2].j == 4)
							q[2].New("tanks/armor.tga", x, y, 0, 0, 32, 32);
						if (q[2].j == 5)
							q[2].New("tanks/life.tga", x, y, 0, 0, 32, 32);
					}
				}
				if (b[i].lvl != 3) {
					if (i == 3) {
						q[0].j = rand() % 6;;

						int x = rand() % 26 * 20 + 40;
						int y = rand() % 26 * 20 + 40;
						if (q[0].j == 0)
							q[0].New("tanks/levelup.tga", x, y, 0, 0, 32, 32);
						if (q[0].j == 1)
							q[0].New("tanks/boom.tga", x, y, 0, 0, 32, 32);
						if (q[0].j == 2)
							q[0].New("tanks/timer.tga", x, y, 0, 0, 32, 32);
						if (q[0].j == 3)
							q[0].New("tanks/health.tga", x, y, 0, 0, 32, 32);
						if (q[0].j == 4)
							q[0].New("tanks/armor.tga", x, y, 0, 0, 32, 32);
						if (q[0].j == 5)
							q[0].New("tanks/life.tga", x, y, 0, 0, 32, 32);
					}
					if (i == 10) {
						q[1].j = rand() % 6;;
						int x = rand() % 26 * 20 + 40;
						int y = rand() % 26 * 20 + 40;
						if (q[1].j == 0)
							q[1].New("tanks/levelup.tga", x, y, 0, 0, 32, 32);
						if (q[1].j == 1)
							q[1].New("tanks/boom.tga", x, y, 0, 0, 32, 32);
						if (q[1].j == 2)
							q[1].New("tanks/timer.tga", x, y, 0, 0, 32, 32);
						if (q[1].j == 3)
							q[1].New("tanks/health.tga", x, y, 0, 0, 32, 32);
						if (q[1].j == 4)
							q[1].New("tanks/armor.tga", x, y, 0, 0, 32, 32);
						if (q[1].j == 5)
							q[1].New("tanks/life.tga", x, y, 0, 0, 32, 32);
					}
					if (i == 17) {
						q[2].j = rand() % 6;;
						int x = rand() % 26 * 20 + 40;
						int y = rand() % 26 * 20 + 40;
						if (q[2].j == 0)
							q[2].New("tanks/levelup.tga", x, y, 0, 0, 32, 32);
						if (q[2].j == 1)
							q[2].New("tanks/boom.tga", x, y, 0, 0, 32, 32);
						if (q[2].j == 2)
							q[2].New("tanks/timer.tga", x, y, 0, 0, 32, 32);
						if (q[2].j == 3)
							q[2].New("tanks/health.tga", x, y, 0, 0, 32, 32);
						if (q[2].j == 4)
							q[2].New("tanks/armor.tga", x, y, 0, 0, 32, 32);
						if (q[2].j == 5)
							q[2].New("tanks/life.tga", x, y, 0, 0, 32, 32);
					}
				}
			}
		}
	}

	for (int j = 0; j < 2;j++) {
		for (int i = 0; i < 26;i++) {
			if ((F[i].x - 20 < s[j].x) && (F[i].x + 20 > s[j].x) && (F[i].y - 20 < s[j].y) && (F[i].y + 20 > s[j].y)) {
				if (i >= 6) {
					F[i].vistreldvish = false; F[i].vistrelzakonchen = true; F[i].vistrel = false;
				}
				if (armor[j] == false) {
					if (j == 0) {
						if ((i >= 2) && (i < 6)) {
							s[0].zamiranie = true;
							s[0].zamiranietimer = 0;
							F[i].x1 = F[i].x;
							F[i].y1 = F[i].y;
							F[i].dir1 = F[i].f;
							F[i].anim = true;
							F[i].vistreldvish = false; F[i].vistrelzakonchen = true; F[i].vistrel = false;
						}
						if (i >= 6) {
							s[j].x = 200;
							s[j].y = 520;
							F[i].vistreldvish = false; F[i].vistrelzakonchen = true; F[i].vistrel = false;
						}
					}
					if (j == 1) {
						if ((i >= 0) && (i < 3)) {
							s[1].zamiranietimer = 0;
							s[1].zamiranie = true;
							F[i].x1 = F[i].x;
							F[i].y1 = F[i].y;
							F[i].dir1 = F[i].f;
							F[i].anim = true;
							F[i].vistreldvish = false; F[i].vistrelzakonchen = true; F[i].vistrel = false;
						}
						if (i >= 6) {
							s[j].x = 360;
							s[j].y = 520;
							F[i].vistreldvish = false; F[i].vistrelzakonchen = true; F[i].vistrel = false;
						}
					}
					if (i >= 6) {
						armor[j] = true;
						armortimer[j] = 23000;
						s[j].sprite.setPosition(s[j].x, s[j].y);
						s[j].life -= 1;
						s[j].zvezda = 0;
						s[j].obnovlenie = true;

						F[i].x1 = F[i].x;
						F[i].y1 = F[i].y;
						F[i].dir1 = F[i].f;
						F[i].anim = true;
					}
				}

			}
		}
	}


	
	
	

	// бонусы
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < 3; i++) {
			if ((s[j].x - 40 < q[i].x) && (s[j].x + 40 > q[i].x) && (s[j].y - 40 < q[i].y) && (s[j].y + 40 > q[i].y)) {
				bonusplay = true;
				q[i].x = 500;
				q[i].y = 600;
				q[i].sprite.setPosition(q[i].x, q[i].y);
				q[i].vrem = 0;
				if (q[i].j == 0) {
					if (s[j].zvezda < 3) {
						s[j].zvezda += 1;
						s[j].obnovlenie = true;
					}
				}
				if (q[i].j == 1) {
					for (int i = 0; i < nomer;i++) {
						if (b[i].death == false) {
							b[i].x = 600;
							b[i].y = 600;
							F[j].x1 = F[j].x;
							F[j].y1 = F[j].y;
							F[j].dir1 = F[j].f;
							F[j].anim = true;
							b[i].sprite.setPosition(b[i].x, b[i].y);
							colvo -= 1;
							b[i].death = true;
						}
					}
				}
				if (q[i].j == 2) {
					timer = true;
					timertimer = 0;
				}
				if (q[i].j == 3) {
					shtab = true;
					shtabtimer = 0;
				}
				if (q[i].j == 4) {
					armor[j] = true;
					armortimer[j] = 0;
				}
				if (q[i].j == 5) {
					s[j].life += 1;
				}
			}
		}
}


void dvish(float time, float x1, float y1, int i1) {
	float x = x1;
	float y = y1;
	int i = i1;
	if (b[i].death == false) {
		//проверка
		if ((b[i].x > x) && (b[i].y < y))
		{
			if (dv[i] > 4) {
				if (rand() % 2 == 0)
					dv[i] = 0;
				else
					dv[i] = 1;
			}
		}
		if ((b[i].x > x) && (b[i].y > y))
		{
			if (dv[i] > 4) {
				if (rand() % 2 == 0)
					dv[i] = 1;
				else
					dv[i] = 2;
			}
		}
		if ((b[i].x < x) && (b[i].y > y))
		{
			if (dv[i] > 4) {
				if (rand() % 2 == 0)
					dv[i] = 2;
				else
					dv[i] = 3;
			}
		}
		if ((b[i].x < x) && (b[i].y < y))
		{
			if (dv[i] > 4) {
				if (rand() % 2 == 0)
					dv[i] = 3;
				else
					dv[i] = 0;
			}
		}
		if (player1 == false) {
				for (int i = 0;i < 20;i++) {
					if (b[i].dir == 3) {
						for (int j = 0;j < 2;j++) {
							
								if ((b[i].x + 30 >= s[j].x) && (b[i].x - 30 <= s[j].x) && (b[i].y >= s[j].y) && (b[i].y - 40 <= s[j].y)) {
									dv[i] = rand() % 4;
								}
							
						}
					}
					if (b[i].dir == 2) {
						for (int j = 0;j < 2;j++) {
							
								if ((b[i].x + 30 >= s[j].x) && (b[i].x - 30 <= s[j].x) && (b[i].y + 40 >= s[j].y) && (b[i].y <= s[j].y)) {
									dv[i] = rand() % 4;
								}
							
						}

					}
					if (b[i].dir == 1) {
						for (int j = 0;j < 2;j++) {
							
								if ((b[i].x >=s[j].x) && (b[i].x - 35 <= s[j].x) && (b[i].y + 30 >=s[j].y) && (b[i].y - 30 <= s[j].y)) {
									dv[i] = rand() % 4;
								}
							
						}


					}
					if (b[i].dir == 0) {
						for (int j = 0;j < 2;j++) {
							
								if ((b[i].x + 35 >= s[j].x) && (b[i].x <= s[j].x) && (b[i].y + 30 >= s[j].y) && (b[i].y - 30 <= s[j].y)) {
									dv[i] = rand() % 4;
								}
							
						}


					}

				}
			
		}
		else {
			for (int i = 0;i < 20;i++) {
				if (b[i].dir == 3) {
					for (int j = 0;j < 1;j++) {

						if ((b[i].x + 30 >= s[j].x) && (b[i].x - 30 <= s[j].x) && (b[i].y >= s[j].y) && (b[i].y - 40 <= s[j].y)) {
							dv[i] = rand() % 4;
						}

					}
				}
				if (b[i].dir == 2) {
					for (int j = 0;j < 1;j++) {

						if ((b[i].x + 30 >= s[j].x) && (b[i].x - 30 <= s[j].x) && (b[i].y + 40 >= s[j].y) && (b[i].y <= s[j].y)) {
							dv[i] = rand() % 4;
						}

					}

				}
				if (b[i].dir == 1) {
					for (int j = 0;j < 1;j++) {

						if ((b[i].x >= s[j].x) && (b[i].x - 35 <= s[j].x) && (b[i].y + 30 >= s[j].y) && (b[i].y - 30 <= s[j].y)) {
							dv[i] = rand() % 4;
						}

					}


				}
				if (b[i].dir == 0) {
					for (int j = 0;j < 1;j++) {

						if ((b[i].x + 35 >= s[j].x) && (b[i].x <= s[j].x) && (b[i].y + 30 >= s[j].y) && (b[i].y - 30 <= s[j].y)) {
							dv[i] = rand() % 4;
						}

					}


				}

			}

		}
		for (int i = 0;i < 20;i++) {
				
					if (b[i].dir == 3) {
						for (int j = 0;j < 20;j++) {
							if (j != i) {
								if ((b[i].x + 30 >= b[j].x) && (b[i].x - 30 <= b[j].x) && (b[i].y >= b[j].y) && (b[i].y - 40 <= b[j].y)) {
									dv[i] = rand() % 4;
								}
							}
						}
					}
					if (b[i].dir == 2) {
						for (int j = 0;j < 20;j++) {
							if (j != i) {
								if ((b[i].x + 30 >= b[j].x) && (b[i].x - 30 <= b[j].x) && (b[i].y + 40 >= b[j].y) && (b[i].y <= b[j].y)) {
									dv[i] = rand() % 4;
								}
							}
						}

					}
					if (b[i].dir == 1) {
						for (int j = 0;j < 20;j++) {
							if (j != i) {
								if ((b[i].x >= b[j].x) && (b[i].x - 35 <= b[j].x) && (b[i].y + 30 >= b[j].y) && (b[i].y - 30 <= b[j].y)) {
									dv[i] = rand() % 4;
								}
							}
						}
						

					}
					if (b[i].dir == 0) {
						for (int j = 0;j < 20;j++) {
							if (j != i) {
								if ((b[i].x + 35 >= b[j].x) && (b[i].x <= b[j].x) && (b[i].y + 30 >= b[j].y) && (b[i].y - 30 <= b[j].y)) {
									dv[i] = rand() % 4;
								}
							}
						}
						

					}
				

			}
		
		
		//выполнение
		if ((i == 3) || (i == 10) || (i == 17)) {
			if (dv[i] == 3) {
				int ii = (b[i].y) / 20;
				int j = (b[i].x + 40) / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				ii = (b[i].y + 20) / 20;
				j = (b[i].x + 40) / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				b[i].dir = 0; if (b[i].lvl == 1)b[i].speed = 0.05; else b[i].speed = 0.025;//направление вниз, см выше
				CurrentFrame1[i] += 0.005*time;
				if (CurrentFrame1[i] > 4) CurrentFrame1[i] -= 4;
				b[i].sprite.setTextureRect(IntRect(35 * int(CurrentFrame1[i]), 1, 35, 35));
			}
			if (dv[i] == 2) {
				int ii = (b[i].y - 5) / 20;
				int j = b[i].x / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				ii = (b[i].y - 5) / 20;
				j = (b[i].x + 20) / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}

				b[i].dir = 3; if (b[i].lvl == 1)b[i].speed = 0.05; else b[i].speed = 0.025;//направление вниз, см выше
				CurrentFrame1[i] += 0.005*time;
				if (CurrentFrame1[i] > 4) CurrentFrame1[i] -= 4;
				b[i].sprite.setTextureRect(IntRect(140, 1 + 35 * int(CurrentFrame1[i]), 37, 35));
			}
			if (dv[i] == 0) {
				int ii = (b[i].y + 40) / 20;
				int j = b[i].x / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				ii = (b[i].y + 40) / 20;
				j = (b[i].x + 20) / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				b[i].dir = 2; if (b[i].lvl == 1)b[i].speed = 0.05; else b[i].speed = 0.025;
				CurrentFrame1[i] += 0.005*time;
				if (CurrentFrame1[i] > 4) CurrentFrame1[i] -= 4;
				b[i].sprite.setTextureRect(IntRect(180, 1 + 35 * int(CurrentFrame1[i]), 40, 35));
			}
			if (dv[i] == 1) {
				int ii = b[i].y / 20;
				int j = (b[i].x - 1) / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				ii = (b[i].y + 20) / 20;
				j = (b[i].x - 5) / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				b[i].dir = 1; if (b[i].lvl == 1)b[i].speed = 0.05; else b[i].speed = 0.025; //dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
				CurrentFrame1[i] += 0.005*time;
				if (CurrentFrame1[i] > 4) CurrentFrame1[i] -= 4;
				b[i].sprite.setTextureRect(IntRect(35 * int(CurrentFrame1[i]), 40, 35, 35)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

			}
		}
		else {
			if (dv[i] == 3) {
				int ii = (b[i].y) / 20;
				int j = (b[i].x + 40) / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				ii = (b[i].y + 20) / 20;
				j = (b[i].x + 40) / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				b[i].dir = 0; if (b[i].lvl == 1)b[i].speed = 0.05; else b[i].speed = 0.025;//направление вниз, см выше
				CurrentFrame1[i] += 0.005*time;
				if (CurrentFrame1[i] > 2) CurrentFrame1[i] -= 2;
				b[i].sprite.setTextureRect(IntRect(35 * int(CurrentFrame1[i]), 1, 35, 35));
			}
			if (dv[i] == 2) {
				int ii = (b[i].y - 5) / 20;
				int j = b[i].x / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				ii = (b[i].y - 5) / 20;
				j = (b[i].x + 20) / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}

				b[i].dir = 3; if (b[i].lvl == 1)b[i].speed = 0.05; else b[i].speed = 0.025;//направление вниз, см выше
				CurrentFrame1[i] += 0.005*time;
				if (CurrentFrame1[i] > 2) CurrentFrame1[i] -= 2;
				b[i].sprite.setTextureRect(IntRect(140, 1 + 35 * int(CurrentFrame1[i]), 37, 35));
			}
			if (dv[i] == 0) {
				int ii = (b[i].y + 40) / 20;
				int j = b[i].x / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				ii = (b[i].y + 40) / 20;
				j = (b[i].x + 20) / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				b[i].dir = 2; if (b[i].lvl == 1)b[i].speed = 0.05; else b[i].speed = 0.025;
				CurrentFrame1[i] += 0.005*time;
				if (CurrentFrame1[i] > 2) CurrentFrame1[i] -= 2;
				b[i].sprite.setTextureRect(IntRect(180, 1 + 35 * int(CurrentFrame1[i]), 40, 35));
			}
			if (dv[i] == 1) {
				int ii = b[i].y / 20;
				int j = (b[i].x - 1) / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				ii = (b[i].y + 20) / 20;
				j = (b[i].x - 5) / 20;
				if ((TileMap[ii][j] != 'o') && (TileMap[ii][j] != 'j') && (TileMap[ii][j] != 'u')) {
					dv[i] = 5;
				}
				b[i].dir = 1; if (b[i].lvl == 1)b[i].speed = 0.05; else b[i].speed = 0.025;// вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
				CurrentFrame1[i] += 0.005*time;
				if (CurrentFrame1[i] > 2) CurrentFrame1[i] -= 2;
				b[i].sprite.setTextureRect(IntRect(35 * int(CurrentFrame1[i]), 40, 35, 35)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

			}
		}
		//хаотичное движение если никуда не едет.
		if (dv[i] > 4) {
			Rand = rand() % 1000;
			if (Rand == 1) {
				dv[i] = 1;
				b[i].dir = 1; //dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
				CurrentFrame1[i] += 0.005*time;
				if (CurrentFrame1[i] > 4) CurrentFrame1[i] -= 3;
				b[i].sprite.setTextureRect(IntRect(35 * int(CurrentFrame1[i]), 40, 35, 35)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

			}
			if (Rand == 0) {
				dv[i] = 3;
				b[i].dir = 0; //направление вправо, см выше
				CurrentFrame1[i] += 0.005*time;
				if (CurrentFrame1[i] > 4) CurrentFrame1[i] -= 3;
				b[i].sprite.setTextureRect(IntRect(35 * int(CurrentFrame1[i]), 0, 35, 40)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

			}
			if (Rand == 3) {
				dv[i] = 2;
				b[i].dir = 3; //направление вниз, см выше
				CurrentFrame1[i] += 0.005*time;
				if (CurrentFrame1[i] > 4) CurrentFrame1[i] -= 4;
				b[i].sprite.setTextureRect(IntRect(140, 1 + 35 * int(CurrentFrame1[i]), 37, 35)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)


			}
			if (Rand == 2) {
				dv[i] = 0;
				b[i].dir = 2;
				CurrentFrame1[i] += 0.005*time;
				if (CurrentFrame1[i] > 4) CurrentFrame1[i] -= 4;
				b[i].sprite.setTextureRect(IntRect(180, 1 + 35 * int(CurrentFrame1[i]), 40, 35));

			}
			if (b[i].lvl == 1)b[i].speed = 0.05; else b[i].speed = 0.025;

		}
		b[i].update(time);
	}
}


void animationbonus(float time) {
	bonustimer += 0.005*time;
	if (bonustimer < 4)
		q[0].sprite.setTextureRect(IntRect(32 * int(bonustimer), 0, 32, 32));
	else if (bonustimer < 8)
		q[0].sprite.setTextureRect(IntRect(32 * int(bonustimer - 4), 32, 32, 32));
	else if (bonustimer < 12)
		q[0].sprite.setTextureRect(IntRect(32 * int(bonustimer - 8), 64, 32, 32));
	else if (bonustimer < 16)
		q[0].sprite.setTextureRect(IntRect(32 * int(bonustimer - 12), 96, 32, 32));
	else bonustimer -= 16;


	bonustimer1 += 0.005*time;
	if (bonustimer1 < 4)
		q[1].sprite.setTextureRect(IntRect(32 * int(bonustimer1), 0, 32, 32));
	else if (bonustimer1 < 8)
		q[1].sprite.setTextureRect(IntRect(32 * int(bonustimer1 - 4), 32, 32, 32));
	else if (bonustimer1 < 12)
		q[1].sprite.setTextureRect(IntRect(32 * int(bonustimer1 - 8), 64, 32, 32));
	else if (bonustimer1 < 16)
		q[1].sprite.setTextureRect(IntRect(32 * int(bonustimer1 - 12), 96, 32, 32));
	else bonustimer1 -= 16;


	bonustimer2 += 0.005*time;
	if (bonustimer2 < 4)
		q[2].sprite.setTextureRect(IntRect(32 * int(bonustimer2), 0, 32, 32));
	else if (bonustimer2 < 8)
		q[2].sprite.setTextureRect(IntRect(32 * int(bonustimer2 - 4), 32, 32, 32));
	else if (bonustimer2 < 12)
		q[2].sprite.setTextureRect(IntRect(32 * int(bonustimer2 - 8), 64, 32, 32));
	else if (bonustimer2 < 16)
		q[2].sprite.setTextureRect(IntRect(32 * int(bonustimer2 - 12), 96, 32, 32));
	else bonustimer2 -= 16;
}


void obnov(int i) {
	if (s[i].zvezda == 0)
		s[i].New("tanks/pla1.bmp", s[i].x, s[i].y, 40, 0, 35, 38);
	if (s[i].zvezda == 1)
		s[i].New("tanks/pla2.bmp", s[i].x, s[i].y, 40, 0, 35, 38);
	if (s[i].zvezda == 2)
		s[i].New("tanks/pla3.bmp", s[i].x, s[i].y, 40, 0, 35, 38);
	if (s[i].zvezda == 3)
		s[i].New("tanks/v5.bmp", s[i].x, s[i].y, 40, 0, 35, 38);
	s[i].obnovlenie = false;
}

bool startgame() {
	setlocale(0, "");
	std::cout << "Краткий обзор по игре Battle City2:" << std::endl;
	std::cout << "для управления первым танком используйте: стрелочки и 'Enter'" << std::endl;
	std::cout << "для управления вторым танком используйте: 'W' 'A' 'S' 'D' и 'G'" << std::endl;
	std::cout << "для того чтобы поделится жизнью, используйте 'Tab'" << std::endl;
	std::cout << "для того чтобы поставить игру на паузу, используйте 'Esc'" << std::endl;
	std::cout << "для того чтобы открыть магазин, испоьзуйте 'M'" << std::endl;
	std::cout << "для запуска игры нажмите 1, затем enter" << std::endl;
	std::cout << "Удачи в боях!" << std::endl;
	std::cout << "версия продукта: v4.9" << std::endl;
	vvod = true;
	while (vvod == true) {
		int op;
		std::cin >> op;
		if (op == 1) vvod = false;
		if (op == 138) {
			igra = true;
			std::cin >> op;
			lvl = op;
		}
		if (op == 520) {
			std::cin >> op;
			if (op == 1) {
				std::cin >> op;
				ochki = op;
			}
			if (op == 2) {
				std::cin >> op;
				ochki1 = op;
			}
		}
		if (op == 333) {
			std::cin >> op;
			if (op == 0) {
				closhnost = 0;
			}
			if (op == 1) {
				closhnost = 1;
			}
			if (op == 2) {
				closhnost = 2;
			}
			if (op == 3) {
				closhnost = 3;
			}
			if (op == 4) {
				closhnost = 4;
			}
		}
	}



	srand(time(0));
	for (int i = 0; i < 26; i++) {
		if (i<3)
			F[i].f = s[0].dir;
		else if (i<6)
			F[i].f = s[1].dir;
		else {
			F[i].f = b[i-6].dir;
		}
	}
	b[18].lvl = 1;
	b[19].lvl = 1;
	RenderWindow window(sf::VideoMode(680, 520), "battle city 2");
	view.reset(sf::FloatRect(0, 0, 680, 520));
	menu11(window);//вызов меню
	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/tanks/k1.png");//загружаем файл для карты
	map_image.createMaskFromColor(Color(255, 255, 255));
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
	view.setSize(680, 520);


	
	Image e;//объект изображения для карты
	e.loadFromFile("images/tanks/111.png");
	Texture p1;//текстура карты
	p1.loadFromImage(e);//заряжаем текстуру картинкой
	Sprite maga;//создаём спрайт для карты
	maga.setTexture(p1);
	Sprite maga1;//создаём спрайт для карты
	maga1.setTexture(s[0].texture);//заливаем текстуру спрайтом
	Sprite maga2;//создаём спрайт для карты
	maga2.setTexture(s[0].texture);//заливаем текстуру спрайтом
	


	
	Image map1_image;//объект изображения для карты
	map1_image.loadFromFile("images/tanks/1.png");//загружаем файл для карты
	map1_image.createMaskFromColor(Color(255, 255, 255));
	Texture ma1p;//текстура карты
	ma1p.loadFromImage(map1_image);//заряжаем текстуру картинкой
	Sprite s1_map;//создаём спрайт для карты
	s1_map.setTexture(ma1p);//заливаем текстуру спрайтом
	s1_map.setTextureRect(IntRect(0, 0, 41, 40));
	s1_map.setPosition(560, 400);

	Image mage;//объект изображения для карты
	mage.loadFromFile("images/tanks/1.png");//загружаем файл для карты
	mage.createMaskFromColor(Color(255, 255, 255));
	Texture p;//текстура карты
	p.loadFromImage(mage);//заряжаем текстуру картинкой
	Sprite p2;//создаём спрайт для карты
	p2.setTexture(p);//заливаем текстуру спрайтом
	p2.setTextureRect(IntRect(50, 0, 41, 40));
	p2.setPosition(560, 450);
	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);

	Font font1;
	font1.loadFromFile("CyrilicOld.ttf");
	Text text1("", font, 20);

	Font font2;
	font2.loadFromFile("CyrilicOld.ttf");
	Text text2("", font, 20);



	Text magazin("", font, 20);
	Text magazin1("", font, 20);
	Text magazin2("", font, 20);
	Text magazin3("", font, 20);
	Text magazin4("", font, 20);
	Text magazin5("", font, 20);
	Text magazin6("", font, 20);


	Font font3;
	font3.loadFromFile("CyrilicOld.ttf");
	Text text3("", font, 20);
	Text text21("", font, 20);
	Text text22("", font, 20);
	Text text23("", font, 20);
	Text text24("", font, 20);
	Text text11("", font, 20);
	Text text12("", font, 20);
	Text text13("", font, 20);
	Text text14("", font, 20);
	Text och("", font, 20);
	Text och1("", font, 20);

	Font y;
	y.loadFromFile("CyrilicOld.ttf");
	Text yr("", font, 20);

	AudioDevicePtr device[6];
	for (int i = 0; i < 6; i++) {
		device[i] = OpenDevice();
	}
	OutputStreamPtr soundvistrel[6];
	for (int i = 0; i < 6; i++) {
		soundvistrel[i] = OpenSound(device[i], "i.wav", false);
	}

	AudioDevicePtr device1 = OpenDevice();
	OutputStreamPtr bonus = OpenSound(device1, "Bonus_take.wav", false);
	AudioDevicePtr device3[15];
	OutputStreamPtr music[15];
	for (int i = 3; i < 15; i++) {
		device3[i] = OpenDevice();
	}
	music[3] = OpenSound(device3[3], "3.ogg", true);
	music[4] = OpenSound(device3[4], "4.ogg", true);
	music[5] = OpenSound(device3[5], "5.ogg", true);
	music[6] = OpenSound(device3[6], "6.ogg", true);
	music[7] = OpenSound(device3[7], "7.ogg", true);
	music[8] = OpenSound(device3[8], "8.ogg", true);
	music[9] = OpenSound(device3[9], "9.ogg", true);
	music[10] = OpenSound(device3[10], "10.ogg", true);
	music[11] = OpenSound(device3[11], "11.ogg", true);
	music[12] = OpenSound(device3[12], "12.ogg", true);
	music[13] = OpenSound(device3[13], "13.ogg", true);
	music[14] = OpenSound(device3[14], "14.ogg", true);

	Image image1;//объект изображения для карты
	image1.loadFromFile("images/tanks/v1.bmp");//загружаем файл для карты
	image1.createMaskFromColor(Color(255, 255, 255));
	Texture map1;//текстура карты
	map1.loadFromImage(image1);//заряжаем текстуру картинкой
	Sprite inf[20];//создаём спрайт для карты
	for (int i = 0; i < 20; i++) {
		inf[i].setTexture(map1);//заливаем текстуру спрайтом
		inf[i].setTextureRect(IntRect(70, 80, 25, 25));
		if (i % 2 == 1) {
			inf[i].setPosition(630, 50 + (30 * (i / 2)));
		}
		else {
			inf[i].setPosition(600, 50 + (30 * (i / 2)));
		}
	}

	s[0].New("tanks/pla1.bmp", 200, 520, 40, 0, 38, 38);
	if (player1 == false) {
		s[1].New("tanks/pla1.bmp", 360, 520, 40, 0, 38, 38);

	}
	Sprite onelife;//создаём спрайт для карты
	onelife.setTexture(s[0].texture);//заливаем текстуру спрайтом
	onelife.setPosition(600, 400);

	Sprite onelife1;//создаём спрайт для карты
	onelife1.setTexture(s[1].texture);//заливаем текстуру спрайтом
	onelife1.setPosition(600, 450);

	for (int i = 0; i < 20;i++) {
		b[i].x = 600;
		b[i].y = 600;
		b[i].sprite.setPosition(b[i].x, b[i].y);
		b[i].death = true;
		b[i].hp = 4;
	}

	bonusplay = false;
	Clock clock;
	while (window.isOpen())
	{

	
		

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;
		logictimer += time;
		if (pause == false) {
			if (poiavlenie == true) {
				spaunertimer += time;//прибавляем к нашей переменной time

				if (spaunertimer > 5000+(1000*(closhnost - 2))) {
					if (nomer % 3 == 0) {
						if (b[nomer].lvl == 0)
							b[nomer].New("tanks/v1.bmp", 40, 40, 0, 0, 35, 38);
						if (b[nomer].lvl == 1)
							b[nomer].New("tanks/v2.bmp", 40, 40, 0, 0, 35, 38);
						if (b[nomer].lvl == 2)
							b[nomer].New("tanks/v3.bmp", 40, 40, 0, 0, 35, 38);
						if (b[nomer].lvl == 3)
							b[nomer].New("tanks/v4.bmp", 40, 40, 0, 0, 35, 38);
					}
					else
						if ((nomer == 2) || (nomer == 5) || (nomer == 8) || (nomer == 11) || (nomer == 14) || (nomer == 17)) {
							if (b[nomer].lvl == 0)
								b[nomer].New("tanks/v1.bmp", 520, 40, 0, 0, 35, 38);
							if (b[nomer].lvl == 1)
								b[nomer].New("tanks/v2.bmp", 520, 40, 0, 0, 35, 38);
							if (b[nomer].lvl == 2)
								b[nomer].New("tanks/v3.bmp", 520, 40, 0, 0, 35, 38);
							if (b[nomer].lvl == 3)
								b[nomer].New("tanks/v4.bmp", 520, 40, 0, 0, 35, 38);
						}
						else {
							if (b[nomer].lvl == 0)
								b[nomer].New("tanks/v1.bmp", 280, 40, 0, 0, 35, 38);
							if (b[nomer].lvl == 1)
								b[nomer].New("tanks/v2.bmp", 280, 40, 0, 0, 35, 38);
							if (b[nomer].lvl == 2)
								b[nomer].New("tanks/v3.bmp", 280, 40, 0, 0, 35, 38);
							if (b[nomer].lvl == 3)
								b[nomer].New("tanks/v4.bmp", 280, 40, 0, 0, 35, 38);
						}
						b[nomer].death = false;
						nomer++;
						spaunertimer = 0;
				}

				if (nomer > 19)
					poiavlenie = false;
			}
		}



		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		getplayercoordinateforview();


		//управление танком
		if (pause == false) {
			if (s[0].obnovlenie == true)
				obnov(0);
			if (player1 == false)
				if (s[1].obnovlenie == true)
					obnov(1);
			if (death1 == false) {
				if (s[0].zamiranie == false) {
					if (Keyboard::isKeyPressed(Keyboard::Left)) {
						s[0].dir = 1; s[0].speed = 0.07;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
						CurrentFrame[0] += 0.005*time;
						if (CurrentFrame[0] > 4) CurrentFrame[0] -= 3;
						s[0].sprite.setTextureRect(IntRect(76 + 38 * int(CurrentFrame[0]), 41, 38, 40)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

					}
					if (Keyboard::isKeyPressed(Keyboard::Right)) {
						s[0].dir = 0; s[0].speed = 0.07;//направление вправо, см выше
						CurrentFrame[0] += 0.005*time;
						if (CurrentFrame[0] > 4) CurrentFrame[0] -= 3;
						s[0].sprite.setTextureRect(IntRect(78 + 38 * int(CurrentFrame[0]), 3, 38, 36)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

					}
					if (Keyboard::isKeyPressed(Keyboard::Up)) {
						s[0].dir = 3; s[0].speed = 0.07;//направление вниз, см выше
						CurrentFrame[0] += 0.005*time;
						if (CurrentFrame[0] > 4) CurrentFrame[0] -= 4;
						s[0].sprite.setTextureRect(IntRect(38, 0 + 40 * int(CurrentFrame[0]), 38, 40)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)


					}
					if (Keyboard::isKeyPressed(Keyboard::Down)) { //если нажата клавиша стрелка влево или англ буква А
						s[0].dir = 2; s[0].speed = 0.07;//направление вверх, см выше
						CurrentFrame[0] += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
						if (CurrentFrame[0] > 4) CurrentFrame[0] -= 4; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
						s[0].sprite.setTextureRect(IntRect(1, 1 + 40 * int(CurrentFrame[0]), 35, 40)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96

					}
				}
			}
			if (player1 == false) {
				if (death2 == false) {
					if (s[1].zamiranie == false) {
						if (Keyboard::isKeyPressed(Keyboard::A)) {
							s[1].dir = 1; s[1].speed = 0.07;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
							CurrentFrame[1] += 0.005*time;
							if (CurrentFrame[1] > 4) CurrentFrame[1] -= 3;
							s[1].sprite.setTextureRect(IntRect(76 + 38 * int(CurrentFrame[1]), 41, 38, 40)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

						}
						if (Keyboard::isKeyPressed(Keyboard::D)) {
							s[1].dir = 0; s[1].speed = 0.07;//направление вправо, см выше
							CurrentFrame[1] += 0.005*time;
							if (CurrentFrame[1] > 4) CurrentFrame[1] -= 3;
							s[1].sprite.setTextureRect(IntRect(78 + 38 * int(CurrentFrame[1]), 3, 38, 36)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

						}
						if (Keyboard::isKeyPressed(Keyboard::W)) {
							s[1].dir = 3; s[1].speed = 0.07;//направление вниз, см выше
							CurrentFrame[1] += 0.005*time;
							if (CurrentFrame[1] > 4) CurrentFrame[1] -= 4;
							s[1].sprite.setTextureRect(IntRect(38, 0 + 40 * int(CurrentFrame[1]), 38, 40)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)


						}
						if (Keyboard::isKeyPressed(Keyboard::S)) { //если нажата клавиша стрелка влево или англ буква А
							s[1].dir = 2; s[1].speed = 0.07;//направление вверх, см выше
							CurrentFrame[1] += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
							if (CurrentFrame[1] > 4) CurrentFrame[1] -= 4; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
							s[1].sprite.setTextureRect(IntRect(1, 1 + 40 * int(CurrentFrame[1]), 35, 40)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96

						}
					}
				}
			}
		}
		animationbonus(time);


		for (int i = 0; i < 2; i++) {
			if (s[i].zamiranie == true) {
				s[i].zamiranietimer += time;
				if (int(s[i].zamiranietimer) % 2 == 0) {
					s[i].sprite.setColor(Color(255, 255, 255, 80));
				}
				else s[i].sprite.setColor(Color(255, 255, 255, 255));
				if (s[i].zamiranietimer > 9000) {
					s[i].zamiranietimer = 0;
					s[i].zamiranie = false;
					s[i].sprite.setColor(Color(255, 255, 255, 255));
				}
			}
		}


		//выстрелы
		if (pause == false) {
			if (player1 == false)
				if (death2 == false)
					if (Keyboard::isKeyPressed(Keyboard::G)) {

						if (interval[1] == true) {
							vistreltimer[1] = 0;
							interval[1] = false;
							if (s[1].zvezda < 2) {
								F[3].vistrel = true;
								F[3].vistreldrow = true;
								F[3].vistreldvish = true;
							}
							else {
								if (F[3].vistrelzakonchen == true) {
									F[3].vistrel = true;
									F[3].vistreldrow = true;
									F[3].vistreldvish = true;
								}
								else {
									F[4].vistrel = true;
									F[4].vistreldrow = true;
									F[4].vistreldvish = true;
								}
							}
						}
					}
			if (death1 == false)
				if (Keyboard::isKeyPressed(Keyboard::Return)) {

					if (interval[0] == true) {
						vistreltimer[0] = 0;
						interval[0] = false;
						if (s[0].zvezda < 2) {
							F[0].vistrel = true;
							F[0].vistreldrow = true;
							F[0].vistreldvish = true;
						}
						else {
							if (F[0].vistrelzakonchen == true) {
								F[0].vistrel = true;
								F[0].vistreldrow = true;
								F[0].vistreldvish = true;
							}
							else {
								F[1].vistrel = true;
								F[1].vistreldrow = true;
								F[1].vistreldvish = true;
							}
						}
					}
				}
			for (int i = 0; i < 26; i++) {
				if (i >= 6) {
					if (timer == false) {
						if (b[i - 6].death == false) {
							if (rand() % (700 + (150*(closhnost-2)))== 1) {
								F[i].vistrel = true;
								F[i].vistreldrow = true;
								F[i].vistreldvish = true;
							}
						}
					}
				}
				if (F[i].vistrelzakonchen == true) {
					if (F[i].vistrel == false) {

						F[i].x = 550;
						F[i].y = 600;
						F[i].sprite.setPosition(F[i].x, F[i].y);
						if (i < 3) {
							vistreltimer[0] += time;
							if (vistreltimer[0] > 1600) {
								vistreltimer[0] = 0;
								interval[0] = true;
							}
						}
						else if (i < 6) {
							if (player1 == false) {
								vistreltimer[1] += time;
								if (vistreltimer[1] > 1600) {
									vistreltimer[1] = 0;
									interval[1] = true;
								}
							}
						}
					}

				}
				if (F[i].vistrelzakonchen == true) {
					if (F[i].vistrel == true) {
						if (i < 3) {
							F[i].New("tanks/i.png", s[0].x, s[0].y, 5, 12, 26, 24);
							soundvistrel[i]->play();
							F[i].vistrel = false;
							F[i].vistrelzakonchen = false;
						}
						else if (i < 6) {
							if (player1 == false) {
								soundvistrel[i]->play();
								F[i].New("tanks/i.png", s[1].x, s[1].y, 5, 12, 26, 24);
								F[i].vistrel = false;
								F[i].vistrelzakonchen = false;
							}
						}
						if (i >= 6) {
							soundvistrel[2]->play();
							F[i].New("tanks/i.png", b[i - 6].x, b[i - 6].y, 5, 12, 26, 24);
							F[i].vistreldvish = true;
							F[i].vistrel = false;
							F[i].vistrelzakonchen = false;
						}
					}
				}
			}
		}


		//выстрелы и анимация
		if (pause == false) {
			for (int i = 0; i < 26;i++) {
				if (F[i].anim == true) {
					F[i].animation(i, F[i].x1, F[i].y1, F[i].dir1);
				}
			}
		}

		//смерть одного танка
		if (player1 == false) {
			if (s[0].life <= 0) {
				death1 = true;
				s[0].x = 350;
				s[0].y = 600;
				s[0].sprite.setPosition(s[0].x, s[0].y);
			}
			if (s[1].life <= 0) {
				death2 = true;
				s[1].x = 350;
				s[1].y = 600;
				s[1].sprite.setPosition(s[1].x, s[1].y);
			}
		}


		// бонусы
		if (pause == false) {
			if (timer == false) {
				if (logictimer <= 23000) {
					for (int i = 0;i < 20;i++) {
						if (player1 == false) {
							if (i % 2 == 0)
								dvish(time, s[0].x, s[0].y, i);
							else
								dvish(time, s[1].x, s[1].y, i);
						}
						else
							dvish(time, s[0].x, s[0].y, i);
					}
				}
				if (logictimer > 23000) {
					for (int i = 0;i < 20;i++) {
						dvish(time, 260, 520, i);
					}
				}
				if (logictimer > 50000)
					logictimer = 0;
			}
			if (timer == true) {
				timertimer += time;
				if (timertimer > 20000) {
					timertimer = 0;
					timer = false;
				}
			}
			if (shtab == true) {
				TileMap[27][13] = 'm';
				TileMap[26][13] = 'm';
				TileMap[25][13] = 'm';
				TileMap[25][14] = 'm';
				TileMap[25][15] = 'm';
				TileMap[25][16] = 'm';
				TileMap[26][16] = 'm';
				TileMap[27][16] = 'm';
				shtabtimer += time;
				if (shtabtimer > 40000) {
					shtabtimer = 0;
					shtab = false;
					TileMap[27][13] = 'k';
					TileMap[26][13] = 'k';
					TileMap[25][13] = 'k';
					TileMap[25][14] = 'k';
					TileMap[25][15] = 'k';
					TileMap[25][16] = 'k';
					TileMap[26][16] = 'k';
					TileMap[27][16] = 'k';
				}
			}
			for (int i = 0; i < 2; i++) {
				if (armor[i] == true) {
					armortimer[i] += time;
					if (int(armortimer[i]) % 2 == 0)
						s[i].sprite.setColor(Color::Blue);
					if (int(armortimer[i]) % 2 == 1)
						s[i].sprite.setColor(Color::Red);
					if (armortimer[i] > 30000) {
						armortimer[i] = 0;
						armor[i] = false;
						s[i].sprite.setColor(Color(255, 255, 255, 255));
					}
				}
			}
			for (int i = 0; i < 3; i++) {
				if ((q[i].x != 500) && (q[i].y != 600)) {
					q[i].vrem += time;
					if (q[i].vrem > 30000) {
						q[i].vrem = 0;
						q[i].x = 500;
						q[i].y = 600;
						q[i].sprite.setPosition(q[i].x, q[i].y);
					}
				}
			}
			if (bonusplay == true) {
				bonus->play();
				bonusplay = false;
			}
		}

		std::ostringstream yro;    // объявили переменную
		yro << lvl;		//занесли в нее число очк
		yr.setString("уровень:" + yro.str());
		yr.setPosition(600, 500);
		if (player1 == false) {
			std::ostringstream yro1;    // объявили переменную
			yro1 << ochki;		//занесли в нее число очк
			och.setString("очки 1p:" + yro1.str());
			och.setPosition(600, 470);

			std::ostringstream yro2;    // объявили переменную
			yro2 << ochki1;		//занесли в нее число очк
			och1.setString("очки 2p:" + yro2.str());
			och1.setPosition(600, 485);
		}
		else {
			std::ostringstream yro1;    // объявили переменную
			yro1 << ochki;		//занесли в нее число очк
			och.setString("очки 1p:" + yro1.str());
			och.setPosition(600, 470);
		}

		//смена уровней
		if (pause == false) {
			if (colvo <= 0) {
				lvltimer += time;
				if (player1 == false) {
					if (lvltimer > 5000) {
						std::ostringstream playerScoreString;
						std::ostringstream player2ScoreString;// объявили переменную
						playerScoreString << schet[0];
						player2ScoreString << schet1[0];//занесли в нее число очк
						text.setString("уничтожено танков первой категории:");
						text.setPosition(150, 300);
						text11.setString("1player:" + playerScoreString.str());
						text11.setPosition(150, 315);
						text21.setString("2player:" + player2ScoreString.str());
						text21.setPosition(150, 330);
						drowtext = true;
					}
					if (lvltimer > 10000) {
						std::ostringstream playerScoreString1;
						std::ostringstream player2ScoreString1;  // объявили переменную
						playerScoreString1 << schet[1];
						player2ScoreString1 << schet1[1];	//занесли в нее число очк
						text1.setString("уничтожено танков второй категории:");
						text1.setPosition(150, 350);
						text12.setString("1player:" + playerScoreString1.str());
						text12.setPosition(150, 365);
						text22.setString("2player:" + player2ScoreString1.str());
						text22.setPosition(150, 380);
						drowtext1 = true;
					}
					if (lvltimer > 15000) {
						std::ostringstream playerScoreString2;
						std::ostringstream player2ScoreString2;// объявили переменную
						playerScoreString2 << schet[2];
						player2ScoreString2 << schet1[2];//занесли в нее число очк
						text2.setString("уничтожено танков третьей категории:");
						text2.setPosition(150, 400);
						text13.setString("1player:" + playerScoreString2.str());
						text13.setPosition(150, 415);
						text23.setString("2player:" + player2ScoreString2.str());
						text23.setPosition(150, 430);
						drowtext2 = true;
					}
					if (lvltimer > 20000) {
						std::ostringstream playerScoreString3;
						std::ostringstream player2ScoreString3;// объявили переменную
						playerScoreString3 << schet[3];
						player2ScoreString3 << schet1[3];	//занесли в нее число очк
						text3.setString("уничтожено танков четвертой категории:");
						text3.setPosition(150, 450);
						text14.setString("1player:" + playerScoreString3.str());
						text14.setPosition(150, 465);
						text24.setString("2player:" + player2ScoreString3.str());
						text24.setPosition(150, 480);
						drowtext3 = true;

					}
				}
				else {
					if (lvltimer > 5000) {
						std::ostringstream playerScoreString;    // объявили переменную
						playerScoreString << schet[0];		//занесли в нее число очк
						text.setString("уничтожено танков первой категории:" + playerScoreString.str());
						text.setPosition(150, 300);
						drowtext = true;
					}
					if (lvltimer > 10000) {
						std::ostringstream playerScoreString1;    // объявили переменную
						playerScoreString1 << schet[1];		//занесли в нее число очк
						text1.setString("уничтожено танков второй категории:" + playerScoreString1.str());
						text1.setPosition(150, 350);
						drowtext1 = true;
					}
					if (lvltimer > 15000) {
						std::ostringstream playerScoreString2;    // объявили переменную
						playerScoreString2 << schet[2];		//занесли в нее число очк
						text2.setString("уничтожено танков третьей категории:" + playerScoreString2.str());
						text2.setPosition(150, 400);
						drowtext2 = true;
					}
					if (lvltimer > 20000) {
						std::ostringstream playerScoreString3;    // объявили переменную
						playerScoreString3 << schet[3];		//занесли в нее число очк
						text3.setString("уничтожено танков четвертой категории:" + playerScoreString3.str());
						text3.setPosition(150, 450);
						drowtext3 = true;

					}
				}
				if (lvltimer > 25000) {
					drowtext = false;drowtext1 = false;drowtext2 = false;drowtext3 = false;
					for (int i = 0; i < 4; i++) {
						schet[i] = 0;
						if (player1 == false)
							schet1[i] = 0;

					}
					for (int i = 0; i < 26;i++) {
						F[i].vistreldvish = false; F[i].vistrelzakonchen = true; F[i].vistrel = false;
					}
					armor[0] = true;
					armortimer[0] = 23000;
					armor[1] = true;
					armortimer[1] = 23000;
					igra = true;
					if (lvl < 35)
						lvl += 1;
					else lvl = 1;
					colvo = 20;
					lvltimer = 0;
					obnov(0);
					s[0].x = 200;
					s[0].y = 520;
					s[0].dir = 3;
					s[0].sprite.setPosition(s[0].x, s[0].y);
					obnov(1);
					s[1].x = 360;
					s[1].dir = 3;
					s[1].y = 520;
					s[1].sprite.setPosition(s[1].x, s[1].y);
					for (int i = 0; i < 20;i++) {
						b[i].x = 600;
						b[i].y = 600;
						b[i].sprite.setPosition(b[i].x, b[i].y);
						b[i].hp = 4;
					}
					poiavlenie = true;
					nomer = 0;
					for (int i = 0; i < 3; i++) {
						q[i].x = 500;
						q[i].y = 600;
						q[i].sprite.setPosition(q[i].x, q[i].y);
						q[i].vrem = 0;

					}
				}

			}
			if (igra == true) {
				qwe(lvl);
				if (lvl == 1) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 0;
					b[7].lvl = 0;
					b[8].lvl = 0;
					b[9].lvl = 0;
					b[10].lvl = 0;
					b[11].lvl = 0;
					b[12].lvl = 0;
					b[13].lvl = 0;
					b[14].lvl = 0;
					b[15].lvl = 0;
					b[16].lvl = 0;
					b[17].lvl = 0;
					b[18].lvl = 1;
					b[19].lvl = 1;
				}
				if (lvl == 2) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 0;
					b[7].lvl = 0;
					b[8].lvl = 0;
					b[9].lvl = 0;
					b[10].lvl = 0;
					b[11].lvl = 0;
					b[12].lvl = 0;
					b[13].lvl = 0;
					b[14].lvl = 1;
					b[15].lvl = 1;
					b[16].lvl = 1;
					b[17].lvl = 1;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 3) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 0;
					b[7].lvl = 0;
					b[8].lvl = 0;
					b[9].lvl = 0;
					b[10].lvl = 0;
					b[11].lvl = 0;
					b[12].lvl = 0;
					b[13].lvl = 0;
					b[14].lvl = 1;
					b[15].lvl = 1;
					b[16].lvl = 1;
					b[17].lvl = 1;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 4) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 2;
					b[8].lvl = 2;
					b[9].lvl = 2;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 2;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 5) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 0;
					b[7].lvl = 0;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 1;
					b[11].lvl = 1;
					b[12].lvl = 1;
					b[13].lvl = 2;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 2;
					b[17].lvl = 2;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 6) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 0;
					b[7].lvl = 0;
					b[8].lvl = 0;
					b[9].lvl = 1;
					b[10].lvl = 1;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 2;
					b[17].lvl = 2;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 7) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 0;
					b[7].lvl = 0;
					b[8].lvl = 0;
					b[9].lvl = 0;
					b[10].lvl = 1;
					b[11].lvl = 1;
					b[12].lvl = 1;
					b[13].lvl = 1;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 2;
					b[17].lvl = 2;
					b[18].lvl = 2;
					b[19].lvl = 2;
				}
				if (lvl == 8) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 2;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 9) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 0;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 1;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 2;
					b[17].lvl = 2;
					b[18].lvl = 3;
					b[19].lvl = 3;

				}
				if (lvl == 10) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 0;
					b[7].lvl = 0;
					b[8].lvl = 0;
					b[9].lvl = 0;
					b[10].lvl = 0;
					b[11].lvl = 0;
					b[12].lvl = 1;
					b[13].lvl = 1;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 2;
					b[17].lvl = 2;
					b[18].lvl = 3;
					b[19].lvl = 3;

				}
				if (lvl == 11) {
					b[0].lvl = 1;
					b[1].lvl = 1;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 12) {
					b[0].lvl = 1;
					b[1].lvl = 1;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 2;
					b[7].lvl = 2;
					b[8].lvl = 2;
					b[9].lvl = 2;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 13) {
					b[0].lvl = 1;
					b[1].lvl = 1;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 2;
					b[9].lvl = 2;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 14) {
					b[0].lvl = 1;
					b[1].lvl = 1;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 2;
					b[5].lvl = 2;
					b[6].lvl = 2;
					b[7].lvl = 2;
					b[8].lvl = 2;
					b[9].lvl = 2;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 15) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 1;
					b[11].lvl = 1;
					b[12].lvl = 3;
					b[13].lvl = 3;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 16) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 0;
					b[7].lvl = 0;
					b[8].lvl = 0;
					b[9].lvl = 0;
					b[10].lvl = 0;
					b[11].lvl = 0;
					b[12].lvl = 0;
					b[13].lvl = 0;
					b[14].lvl = 0;
					b[15].lvl = 0;
					b[16].lvl = 1;
					b[17].lvl = 1;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 17) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 0;
					b[7].lvl = 0;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 2;
					b[17].lvl = 2;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 18) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 19) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 2;
					b[9].lvl = 2;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 3;
					b[13].lvl = 3;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;

				}
				if (lvl == 20) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 3;
					b[13].lvl = 3;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;

				}
				if (lvl == 21) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 2;
					b[9].lvl = 2;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 22) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 1;
					b[11].lvl = 1;
					b[12].lvl = 1;
					b[13].lvl = 1;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 23) {
					b[0].lvl = 1;
					b[1].lvl = 1;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 24) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 0;
					b[7].lvl = 0;
					b[8].lvl = 0;
					b[9].lvl = 0;
					b[10].lvl = 1;
					b[11].lvl = 1;
					b[12].lvl = 1;
					b[13].lvl = 1;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 2;
					b[17].lvl = 2;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 25) {
					b[0].lvl = 1;
					b[1].lvl = 1;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 2;
					b[9].lvl = 2;
					b[10].lvl = 3;
					b[11].lvl = 3;
					b[12].lvl = 3;
					b[13].lvl = 3;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 26) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 27) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 3;
					b[13].lvl = 3;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 28) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 0;
					b[7].lvl = 0;
					b[8].lvl = 0;
					b[9].lvl = 0;
					b[10].lvl = 0;
					b[11].lvl = 0;
					b[12].lvl = 0;
					b[13].lvl = 0;
					b[14].lvl = 0;
					b[15].lvl = 1;
					b[16].lvl = 1;
					b[17].lvl = 2;
					b[18].lvl = 2;
					b[19].lvl = 3;
				}
				if (lvl == 29) {
					b[0].lvl = 1;
					b[1].lvl = 1;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 2;
					b[5].lvl = 2;
					b[6].lvl = 2;
					b[7].lvl = 2;
					b[8].lvl = 2;
					b[9].lvl = 2;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;

				}
				if (lvl == 30) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 1;
					b[11].lvl = 1;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 2;
					b[15].lvl = 2;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;

				}
				if (lvl == 31) {
					b[0].lvl = 1;
					b[1].lvl = 1;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 2;
					b[9].lvl = 2;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 32) {
					b[0].lvl = 0;
					b[1].lvl = 0;
					b[2].lvl = 0;
					b[3].lvl = 0;
					b[4].lvl = 0;
					b[5].lvl = 0;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 3;
					b[13].lvl = 3;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 33) {
					b[0].lvl = 1;
					b[1].lvl = 1;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 2;
					b[9].lvl = 2;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 3;
					b[13].lvl = 3;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 34) {
					b[0].lvl = 1;
					b[1].lvl = 1;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 1;
					b[7].lvl = 1;
					b[8].lvl = 1;
					b[9].lvl = 1;
					b[10].lvl = 2;
					b[11].lvl = 2;
					b[12].lvl = 2;
					b[13].lvl = 2;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				if (lvl == 35) {
					b[0].lvl = 1;
					b[1].lvl = 1;
					b[2].lvl = 1;
					b[3].lvl = 1;
					b[4].lvl = 1;
					b[5].lvl = 1;
					b[6].lvl = 2;
					b[7].lvl = 2;
					b[8].lvl = 2;
					b[9].lvl = 2;
					b[10].lvl = 3;
					b[11].lvl = 3;
					b[12].lvl = 3;
					b[13].lvl = 3;
					b[14].lvl = 3;
					b[15].lvl = 3;
					b[16].lvl = 3;
					b[17].lvl = 3;
					b[18].lvl = 3;
					b[19].lvl = 3;
				}
				igra = false;
			}
		}



		//передача жизни
		if (pause == false) {
			if (player1 == false) {
				if (Keyboard::isKeyPressed(Keyboard::Tab)) {
					peredacha = true;
				}
			}
			if (peredacha == true) {
				peredachatimer += time;
				if (peredachatimer >= 1500) {
					peredachatimer = 0;
					peredacha = false;
					if ((death1 == false) && (death2 == false)) {
						if (s[0].life > s[1].life) {
							s[0].life -= 1;
							s[1].life += 1;
						}
						else {
							s[0].life += 1;
							s[1].life -= 1;
						}
					}
				}
			}
		}

		//покраска
		
			if (player1 == false)
				if (armor[1] == false) {
					if (s[1].zamiranie == false)
						s[1].sprite.setColor(Color::Yellow);
				}
		
		for (int i = 0; i < 20;i++) {
			if (b[i].hp == 4) {
				b[i].sprite.setColor(Color(255, 255, 255, 255));
			}
			if (b[i].hp == 3) {
				b[i].sprite.setColor(Color::Green);
			}
			if (b[i].hp == 2) {
				b[i].sprite.setColor(Color::Blue);
			}
			if (b[i].hp == 1) {
				b[i].sprite.setColor(Color::Red);
			}
		}


		//перезапуск игры
		if (player1 == false) {
			if ((s[0].life <= 0) && (s[1].life <= 0)) {
				for (int i = 0; i < 26;i++) {
					F[i].vistreldvish = false; F[i].vistrelzakonchen = true; F[i].vistrel = false;
				}
				armor[0] = true;
				armortimer[0] = 23000;
				armor[1] = true;
				armortimer[1] = 23000;
				poiavlenie = true;
				menu1 = true;
				ochki = 0;
				ochki1 = 0;
				perezapusk = true;
				for (int i = 0; i < 4; i++)
					schet[i] = 0;
				igra = true;
				lvl = 1;
				colvo = 20;
				lvltimer = 0;
				obnov(0);
				death1 = false;
				death2 = false;
				s[0].life = 3;
				s[0].x = 200;
				s[0].y = 520;
				s[0].zvezda = 0;
				s[0].dir = 3;
				s[0].sprite.setPosition(s[0].x, s[0].y);
				obnov(1);
				s[1].life = 3;
				s[1].x = 360;
				s[1].y = 520;
				s[1].zvezda = 0;
				s[1].dir = 3;
				s[1].sprite.setPosition(s[1].x, s[1].y);
				for (int i = 0; i < 20;i++) {
					b[i].x = 600;
					b[i].y = 600;
					b[i].sprite.setPosition(b[i].x, b[i].y);
					b[i].death = true;
					b[i].hp = 4;
				}

				nomer = 0;
				for (int i = 0; i < 3; i++) {
					q[i].x = 500;
					q[i].y = 600;
					q[i].sprite.setPosition(q[i].x, q[i].y);
					q[i].vrem = 0;
				}
				return true;
			}
		}
		else {
			if (s[0].life <= 0) {
				ochki = 0;
				armor[0] = true;
				armortimer[0] = 23000;
				menu1 = true;
				perezapusk = true;
				for (int i = 0; i < 4; i++)
					schet[i] = 0;
				for (int i = 0; i < 26;i++) {
					F[i].vistreldvish = false; F[i].vistrelzakonchen = true; F[i].vistrel = false;
				}
				lvl = 1;
				igra = true;
				poiavlenie = true;
				death1 = false;
				colvo = 20;
				lvltimer = 0;
				obnov(0);
				s[0].life = 3;
				s[0].x = 200;
				s[0].y = 520;
				s[0].dir = 3;
				s[0].sprite.setPosition(s[0].x, s[0].y);
				s[0].zvezda = 0;
				s[1].life = 3;
				s[1].x = 360;
				s[1].y = 520;
				s[1].dir = 3;
				s[1].sprite.setPosition(s[0].x, s[0].y);
				s[1].zvezda = 0;
				
				for (int i = 0; i < 20;i++) {
					b[i].x = 600;
					b[i].y = 600;
					b[i].sprite.setPosition(b[i].x, b[i].y);
					b[i].death = true;
					b[i].hp = 4;
				}

				nomer = 0;
				for (int i = 0; i < 3; i++) {
					q[i].x = 500;
					q[i].y = 600;
					q[i].sprite.setPosition(q[i].x, q[i].y);
					q[i].vrem = 0;
				}
				return true;
			}
		}
		if (perezapusk == true) {
			perezapusktime += time;
			if (perezapusk > 4000) {
				poiavlenie = true;
				perezapusktime = 0;
				perezapusk = false;

			}
		}



		if (magazine == false) {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { paus = true; }
			if (paus == true) {
				pausetimer += time;
				if (pausetimer >= 1000) {
					pausetimer = 0;
					paus = false;
					if (pause == true)
						pause = false;
					else
						pause = true;
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::M)) { mag = true; }
		if (mag == true) {
			magazinetimer += time;
			if (magazinetimer >= 1000) {
				magazinetimer = 0;
				mag = false;
				if (magazine == true) {
					magazine = false;
					pause = false;
				}
				else {
					magazine = true;
					pause = true;
				}
			}
		}



		//магазин
		if (magazine == true) {
			maga.setTextureRect(IntRect(0, 0, 270, 300));
			maga.setPosition(110, 100);
			magazin.setString("МАГАЗИН");
			magazin.setPosition(140, 115);
			magazin1.setString("купить жизнь:  20 000");
			magazin1.setPosition(115, 170);
			magazin2.setString("купить звезду: 40 000");
			magazin2.setPosition(115, 195);
			magazin3.setString("купить броню:   25 000");
			magazin3.setPosition(115, 220);
			magazin4.setString("купить время:   30 000");
			magazin4.setPosition(115, 245);
			magazin5.setString("купить штаб:    35 000");
			magazin5.setPosition(115, 270);
			magazin6.setString("купить гранату:50 000");
			magazin6.setPosition(115, 295);
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				if (poloshenie > 0)
					vnis = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) { //если нажата клавиша стрелка влево или англ буква А
				if (poloshenie < 5)
					vverx = true;
			}
			if (vnis == true) {
				vnistimer += time;
				if (vnistimer >= 500) {
					vnistimer = 0;
					vnis = false;
					poloshenie--;
				}
			}
			if (vverx == true) {
				vverxtimer += time;
				if (vverxtimer >= 500) {
					vverxtimer = 0;
					vverx = false;
					poloshenie++;
				}
			}
			maga1.setTextureRect(IntRect(110, 90, 21, 13));
			maga1.setPosition(320, 175 + (25 * poloshenie));
			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				enter = true;
			}
			if (enter == true) {
				poloshenietimer += time;
				if (poloshenietimer >= 500) {
					poloshenietimer = 0;
					enter = false;
					if (poloshenie == 0) {
						if (ochki >= 20000) {
							ochki -= 20000;
							s[0].life++;
						}
					}
					if (poloshenie == 1) {
						if (ochki >= 40000) {
							ochki -= 40000;
							s[0].zvezda++;
							obnov(0);
						}
					}
					if (poloshenie == 2) {
						if (ochki >= 25000) {
							ochki -= 25000;
							armortimer[0] = 0;
							armor[0] = true;
						}
					}
					if (poloshenie == 3) {
						if (ochki >= 30000) {
							ochki -= 30000;
							timertimer = 0;
							timer = true;
						}
					}
					if (poloshenie == 4) {
						if (ochki >= 35000) {
							ochki -= 35000;
							shtabtimer = 0;
							shtab = true;
						}
					}
					if (poloshenie == 5) {
						if (ochki >= 50000) {
							ochki -= 50000;
							for (int i = 0; i < nomer;i++) {
								if (b[i].death == false) {
									b[i].x = 600;
									b[i].y = 600;
									b[i].sprite.setPosition(b[i].x, b[i].y);
									colvo -= 1;
									b[i].death = true;
								}
							}
						}
					}
				}
			}



			if (player1 == false) {
				if (Keyboard::isKeyPressed(Keyboard::W)) {
					if (poloshenie1 > 0)
						vnis1 = true;
				}
				if (Keyboard::isKeyPressed(Keyboard::S)) { //если нажата клавиша стрелка влево или англ буква А
					if (poloshenie1 < 5)
						vverx1 = true;
				}
				if (vnis1 == true) {
					vnistimer1 += time;
					if (vnistimer1 >= 500) {
						vnistimer1 = 0;
						vnis1 = false;
						poloshenie1--;
					}
				}
				if (vverx1 == true) {
					vverxtimer1 += time;
					if (vverxtimer1 >= 500) {
						vverxtimer1 = 0;
						vverx1 = false;
						poloshenie1++;
					}
				}
				maga2.setTextureRect(IntRect(110, 90, 21, 13));
				maga2.setPosition(345, 175 + (25 * poloshenie1));
				if (Keyboard::isKeyPressed(Keyboard::G)) {
					enter1 = true;
				}
				if (enter1 == true) {
					poloshenietimer1 += time;
					if (poloshenietimer1 >= 500) {
						poloshenietimer1 = 0;
						enter1 = false;
						if (poloshenie1 == 0) {
							if (ochki1 >= 20000) {
								ochki1 -= 20000;
								s[1].life++;
							}
						}
						if (poloshenie1 == 1) {
							if (ochki1 >= 40000) {
								ochki1 -= 40000;
								s[1].zvezda++;
								obnov(1);
							}
						}
						if (poloshenie1 == 2) {
							if (ochki1 >= 25000) {
								ochki1 -= 25000;
								armortimer[1] = 0;
								armor[1] = true;
							}
						}
						if (poloshenie1 == 3) {
							if (ochki1 >= 30000) {
								ochki1 -= 30000;
								timertimer = 0;
								timer = true;
							}
						}
						if (poloshenie1 == 4) {
							if (ochki1 >= 35000) {
								ochki1 -= 35000;
								shtabtimer = 0;
								shtab = true;
							}
						}
						if (poloshenie1 == 5) {
							if (ochki1 >= 50000) {
								ochki1 -= 50000;
								for (int i = 0; i < nomer;i++) {
									if (b[i].death == false) {
										b[i].x = 600;
										b[i].y = 600;
										b[i].sprite.setPosition(b[i].x, b[i].y);
										colvo -= 1;
										b[i].death = true;
									}
								}
							}
						}
					}
				}
			}
		}


		//музыка
		musicplay = false;
		for (int i = 3; i < 11; i++) {
			if (music[i]->isPlaying() == true)
				musicplay = true;
		}
		if (musicplay == false) {
			do musicnomer = rand() % 15;
			while (musicnomer < 3);
			music[musicnomer]->play();

		}
		for (int i = 0; i < 26;i++) {
			F[i].interactionWithMap1(i);
		}



		s[0].proverka_na_stolknovenie(time, 1);
		if (player1 == false)
			s[1].proverka_na_stolknovenie(time, 0);

		window.setView(view);
		window.clear();
		for (int i = 0; i < HEIGHT_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == 'o') { s_map.setTextureRect(IntRect(40, 0, 20, 20)); s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'k') { s_map.setTextureRect(IntRect(0, 0, 20, 20));  s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'l') { s_map.setTextureRect(IntRect(80, 0, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'q') { s_map.setTextureRect(IntRect(0, 80, 20, 10));s_map.setPosition(j * 20, i * 20 + 10); }
				if (TileMap[i][j] == 'w') { s_map.setTextureRect(IntRect(20, 70, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'e') { s_map.setTextureRect(IntRect(40, 70, 20, 20)); s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'r') { s_map.setTextureRect(IntRect(70, 70, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'a') { s_map.setTextureRect(IntRect(50, 100, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 's') { s_map.setTextureRect(IntRect(20, 100, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'd') { s_map.setTextureRect(IntRect(60, 100, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'f') { s_map.setTextureRect(IntRect(40, 100, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'm') { s_map.setTextureRect(IntRect(90, 70, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'v') { s_map.setTextureRect(IntRect(130, 70, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'j') { s_map.setTextureRect(IntRect(150, 70, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'g') { s_map.setTextureRect(IntRect(100, 100, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'h') { s_map.setTextureRect(IntRect(120, 100, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'b') { s_map.setTextureRect(IntRect(100, 120, 20, 20));s_map.setPosition(j * 20, i * 20); }
				if (TileMap[i][j] == 'n') { s_map.setTextureRect(IntRect(120, 120, 20, 20));s_map.setPosition(j * 20, i * 20); }
				window.draw(s_map);
			}
		}


		for (int i = 0; i < 26; i++) {
			if (F[i].vistrelzakonchen == false)
				window.draw(F[i].sprite);
		}

		window.draw(q[0].sprite);
		window.draw(q[1].sprite);
		window.draw(q[2].sprite);

		for (int i = 0; i < 20; i++)
			if (b[i].death == false)
				window.draw(b[i].sprite);

		for (int i = 0; i < colvo; i++) {
			window.draw(inf[i]);
		}
		if (death1 == false) {
			window.draw(s[0].sprite);
		}
		if (player1 == false)
			if (death2 == false)
				window.draw(s[1].sprite);
		window.draw(s1_map);

		for (int i = 0; i < 26; i++) {
			if (F[i].anim == true)
				window.draw(F[i].sprite1);
		}

		for (int i = 0; i < HEIGHT_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++) {
				if (TileMap[i][j] == 'u') { s_map.setTextureRect(IntRect(110, 70, 20, 20));s_map.setPosition(j * 20, i * 20); }
				window.draw(s_map);
			}
		}
		if (player1 == false) {
			if (drowtext == true) {
				window.draw(text);
				window.draw(text11);
				window.draw(text21);
			}
			if (drowtext1 == true) {
				window.draw(text1);
				window.draw(text12);
				window.draw(text22);
			}
			if (drowtext2 == true) {
				window.draw(text2);
				window.draw(text13);
				window.draw(text23);
			}
			if (drowtext3 == true) {
				window.draw(text14);
				window.draw(text24);
				window.draw(text3);
			}
		}
		else {
			if (drowtext == true)
				window.draw(text);
			if (drowtext1 == true)
				window.draw(text1);
			if (drowtext2 == true)
				window.draw(text2);
			if (drowtext3 == true)
				window.draw(text3);
		}
		
		window.draw(yr);
		window.draw(och);
		if (player1 == false)
			window.draw(och1);
		Tick();
		if (death1 == false) {
			if (s[0].life < 12) {
				onelife.setTextureRect(IntRect(110, 90, 21 * s[0].life, 13));
				window.draw(onelife);
			}
			if (s[0].life > 6) {
				onelife.setTextureRect(IntRect(110, 90, 21 * (s[0].life - 6), 28));
				window.draw(onelife);
			}
		}
		if (player1 == false) {
			if (death2 == false) {
				window.draw(p2);
				if (s[1].life < 12) {
					onelife1.setTextureRect(IntRect(110, 90, 21 * s[1].life, 13));
					window.draw(onelife1);
				}
				if (s[1].life > 6) {
					onelife1.setTextureRect(IntRect(110, 90, 21 * (s[1].life - 6), 28));
					window.draw(onelife1);
				}
			}
		}
		if (magazine == true) {
			window.draw(maga);
			window.draw(maga1);
			window.draw(magazin);
			window.draw(magazin1);
			window.draw(magazin2);
			window.draw(magazin3);
			window.draw(magazin4);
			window.draw(magazin5);
			window.draw(magazin6);
			if(player1 == false)
				window.draw(maga2);
		}
		window.display();
		
		if ((s[0].dx == 0) && (s[0].dy == 0))
			s[0].skolshenie = 4;
		if (player1 == false)
			if ((s[1].dx == 0) && (s[1].dy == 0))
				s[1].skolshenie = 4;

	}
}

void gameRunning() {
	
	if (startgame()) { gameRunning(); }////если startGame() == true, то вызываем занова ф-цию isGameRunning, которая в свою очередь опять вызывает startGame() 
}
