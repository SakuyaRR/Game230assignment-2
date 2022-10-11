#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

Sprite* tileset;
Texture* tileTexture;
int** Level;
Sprite** Map;
int nUm;
int tilenow;
int a;
int b;

void start();
void handleInput(RenderWindow& window, Event& e);
void render(RenderWindow& window);
void update(RenderWindow& window);

Vector2<int> mouseposinMap(RenderWindow& window);

int main()
{

	RenderWindow window(VideoMode(700, 700), "SFML works!");
	start();
	while (window.isOpen())
	{

		Event event;

		while (window.pollEvent(event))
		{
			handleInput(window, event);
		}
		
		update(window);
		render(window);



	}


	return 0;
}




void start() 
{
	tileTexture = new Texture[21];
	tileset = new Sprite[21];
	for (int nUm = 0; nUm < 21; nUm++)
	{
		if (!tileTexture[nUm].loadFromFile("Tileset/Platformer-" + to_string(nUm) + ".png"))
		{
			cout << "failed to load from files" << endl;

		}
		
		tileset[nUm].setTexture(tileTexture[nUm]);

		cout << "load Platformer-" << to_string(nUm) << ".png success" << endl;
		
		
	}

	tilenow = 0;

	Level = new int* [10];
	Map = new Sprite * [10];
	for (int a = 0; a < 10; a++)
	{
		Level[a] = new int[10];
		Map[a] = new Sprite[10];
		for (int b = 0; b < 10; b++)
		{
			Level[a][b] = -1;
			Map[a][b].setPosition(b * 70 + 35, a * 70 + 35);
			cout << Level[a][b] << " ";
		}
		cout << endl;

		return;
	}
}

void handleInput(RenderWindow& window, Event& e)
{
	if (e.type == Event::Closed)
	{
		window.close();
	}
	if (e.type == Event::KeyReleased)
	{
		/*the next tile*/
		if (tilenow <= 20 && e.key.code == Keyboard::Up)
		{
			tilenow++;
		}
	    /*	the former tile*/
		if (tilenow > 0 && e.key.code == Keyboard::Down)

		{
			tilenow--;
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2<int> mousePos = mouseposinMap(window);
			Level[mousePos.y][mousePos.x] = tilenow;
		}
		if (e.key.code == Keyboard::S) {
			ofstream file("level.txt");
			if (file.is_open())
			{
				for (a = 0; a < 10; a++) {
					for (b = 0; b < 10; b++) {
						file << Level[a][b];
					}
					file << endl;
				}	
				file.close();
			}
			else cout << "Unable to open file";
		}

		//screenshot

		if (e.key.code == sf::Keyboard::Space)
		{
			Texture texture;
			texture.create(window.getSize().x, window.getSize().y);

			if (texture.copyToImage().saveToFile("Homework 2 Screenshot.png"))
			{
				cout << "save LLR Homework 2 Screenshot.png" << endl;
			}
		}

	}

}

void render(RenderWindow& window)
{
	window.clear();
	/*draw grid*/
	for (int a = 0; a < 10; a++) 
	{
		for (int b = 0; b < 10; b++) 
		{
			if (Level[a][b] < 21 && Level[a][b] >= 0) 
			{
			Map[a][b].setTexture(tileTexture[Level[a][b]]);
			window.draw(Map[a][b]);
			}
		}
		

	}
	Vector2<int> mousePos = mouseposinMap(window);
	Map[mousePos.y][mousePos.x].setTexture(tileTexture[tilenow]);
	window.draw(Map[mousePos.y][mousePos.x]);
	window.display();
	return;
	
}
	

void update(RenderWindow& window)
{
	return;
}

Vector2<int>mouseposinMap(RenderWindow& window)
{
	int i;
	int j;
	i = (Mouse::getPosition(window).x - 35) / 70;
	j = (Mouse::getPosition(window).y - 35) / 70;
	return Vector2<int>(i, j);
}