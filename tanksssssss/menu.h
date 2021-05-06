#include <SFML/Graphics.hpp>
#include "windows.h"
#include "audiere.h"
using namespace sf;
using namespace audiere;
bool animation = true;
bool player1 = true;
bool menu1 = true;
int numm = 0;
int i = 0;
int j = 0;
int z = 1440;
int x = 800;
int y = 0;
int u = 0;
void menu11(RenderWindow & window) {
	AudioDevicePtr device2 = OpenDevice();
	OutputStreamPtr m2 = OpenSound(device2, "21.ogg", true);
	AudioDevicePtr device200 = OpenDevice();
	OutputStreamPtr m200 = OpenSound(device2, "100.ogg", true);
	if (animation == true) {
		m2->play();
		m2->setVolume(0.3);
	}
	else {
		m200->play();
		m200->setRepeat(true);
	}
	Image image2;
	image2.loadFromFile("images/tanks/menu.jpg");
	Texture map2;
	map2.loadFromImage(image2);
	Sprite menu;
	menu.setTexture(map2);
	menu.setTextureRect(IntRect(0, 0, 700, 600));
	menu.setPosition(0, 0);

	Image image11;
	image11.loadFromFile("images/tanks/11.png");
	Texture map11;
	map11.loadFromImage(image11);
	Sprite sprite11;
	sprite11.setTexture(map11);

	Image image22;
	image22.loadFromFile("images/tanks/22.png");
	Texture map22;
	map22.loadFromImage(image22);
	Sprite sprite22;
	sprite22.setTexture(map22);

	Image image33;
	image33.loadFromFile("images/tanks/33.png");
	Texture map33;
	map33.loadFromImage(image33);
	Sprite sprite33;
	sprite33.setTexture(map33);


	Image image44;
	image44.loadFromFile("images/tanks/44.png");
	Texture map44;
	map44.loadFromImage(image44);
	Sprite sprite44;
	sprite44.setTexture(map44);


	Image image55;
	image55.loadFromFile("images/tanks/55.png");
	Texture map55;
	map55.loadFromImage(image55);
	Sprite sprite55;
	sprite55.setTexture(map55);


	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);

	


	while (menu1)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		
		if (animation == true) {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				animation = false;
				m2->stop();
				m200->play();
				m200->setRepeat(true);
			}
			int k = m2->getPosition();
			sprite11.setTextureRect(IntRect(0, 0, 700, i / 250));
			window.draw(sprite11);
			sprite22.setTextureRect(IntRect(0, 0, j / 150, 485));
			window.draw(sprite22);
			sprite33.setTextureRect(IntRect(0, 0, z / 250, 485));
			window.draw(sprite33);
			sprite44.setTextureRect(IntRect(0, 0, 700, x / 300));
			window.draw(sprite44);
			sprite55.setTextureRect(IntRect(0, 0, 700, y / 300));
			window.draw(sprite55);
			if (k < 150000) {
				i = k;

			}
			else if (k < 250000) {
				j = k - 150000;

			}
			else if (k < 400000) {
				z = k - 250000;

			}
			else if (k < 550000) {
				x = k - 400000;

			}
			else if (k < 700000) {
				y = k - 550000;

			}
			else if (k < 895000) {
			}
			else {
				animation = false;
				m2->stop();
				m200->play();
				m200->setRepeat(true);
			}

		}
		else {
			
			window.draw(menu);
			text.setString("выберите режим:");
			text.setPosition(35, 270);
			window.draw(text);//рисую этот текст
			text.setString("(используйте стрелочки)");
			text.setPosition(35, 285);
			window.draw(text);//рисую этот текст
			if (player1 == true) {
				text.setString("один игрок");
				text.setPosition(50, 300);
				window.draw(text);//рисую этот текст
			}
			if (player1 == false) {
				text.setString("два игрока");
				text.setPosition(50, 300);
				window.draw(text);//рисую этот текст
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				player1 = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				player1 = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				menu1 = false;
			}
		}
		window.display();

	}
}
