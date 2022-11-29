#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <fstream>
#include <string>

// Namespaces
using namespace sf;
using namespace std;

//Variables
int txnumber;
sf::Texture tx;
sf::Texture tiles[21];
int gridX;
int gridY;
int grid[10][10];
float tilespX;
float tilespY;
Sprite tilesp;
int spX;
int spY;
Sprite gridsp[10][10];
int a;
int b;


void setup(RenderWindow& window);
void handleInput(RenderWindow& window, Event& e);
void update(RenderWindow& window);
void render(RenderWindow& window);

int main()
{
	RenderWindow window(VideoMode(700, 700), "SFML works!");

	setup(window);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			handleInput(window, event);
			Event event;
			while (window.pollEvent(event))
			{
				handleInput(window, event);

			}

		}

		update(window);

		render(window);

	}


	return 0;
}


void setup(RenderWindow& window)
{
	for (txnumber = 0; txnumber < 21; txnumber++)
	{
		if (tx.loadFromFile("Tileset/Platformer-" + to_string(txnumber) + ".png"))
		{
			tiles[txnumber] = tx;
			cout << "Platformer-" + to_string(txnumber) + "_loaded" << endl;
		}
	}

	txnumber = 0;

	for (gridY = 0; gridY < 10; gridY++)
	{
		for (gridX = 0; gridX < 10; gridX++)
		{
			grid[gridX][gridY] = -1;
		}
		cout << endl;
	}
}

void handleInput(RenderWindow& window, Event& e)
{
	if (e.type == Event::Closed)
		window.close();

	tilespX = (Mouse::getPosition(window).x / 70) * 70;
	tilespY = (Mouse::getPosition(window).y / 70) * 70;
	tilesp.setPosition(tilespX, tilespY);

	if (e.type == Event::KeyReleased)
	{

		if (e.type == Event::MouseButtonPressed)
		{
			if (e.mouseButton.button == Mouse::Left)
			{
				grid[Mouse::getPosition(window).x / 70][Mouse::getPosition(window).y / 70] = txnumber;
			}

			spX = Mouse::getPosition(window).x / 70;
			spY = Mouse::getPosition(window).y / 70;

			gridsp[spX][spY].setTexture(tiles[txnumber]);
			gridsp[spX][spY].setPosition(tilespX, tilespY);
		}

	}

	if (e.type == Event::KeyReleased)
	{
		/*if (txnumber >= 0 && txnumber <= 20)
		{
			if (e.key.code == Keyboard::Up)
			{
				txnumber++;
				tilesp.setTexture(tiles[txnumber]);
				cout << txnumber;

			}
			else if (e.key.code == Keyboard::Down)
			{
				txnumber--;
				tilesp.setTexture(tiles[txnumber]);
				cout << txnumber;
			}
		}
		else if (txnumber > 20)
		{
			if (e.key.code == Keyboard::Down || e.key.code == Keyboard::Up)
			{
				txnumber = 20;
				tilesp.setTexture(tiles[txnumber]);
				cout << txnumber;
			}
		}
		else if (txnumber < 0)
		{
			if (e.key.code == Keyboard::Down || e.key.code == Keyboard::Up)
			{
				txnumber = 0;
				tilesp.setTexture(tiles[txnumber]);
				cout << txnumber;
			}

		}*/
		if (e.key.code == Keyboard::Up)
		{
			txnumber++;
			txnumber = txnumber % 21;
			cout << txnumber << endl;
			tilesp.setTexture(tiles[txnumber]);
		}
		else if (e.key.code == Keyboard::Down)
		{
			if (txnumber > 0)
			{
				txnumber--;
			}
			else {
				txnumber += 20;
			}
			cout << txnumber << endl;
			tilesp.setTexture(tiles[txnumber]);
		}
	}

}


void update(RenderWindow& window) {}


void render(RenderWindow& window)
{
	window.clear();

	for (b = 0; b < 10; b++)
	{
		for (a = 0; a < 10; a++)
		{
			window.draw(gridsp[a][b]);
		}
	}
	window.draw(tilesp);
	window.display();

}