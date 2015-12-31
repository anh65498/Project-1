#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include "ResourcePath.h"
#include "Overlap.h"
using namespace std;				//don't need to write std:: anymore

//bug: After charizard gets so big, he would disappear and millions of cookies would fly around the screen

void handleCollision(sf::Sprite &charizardSprite, sf::Sprite & cookieSprite, int &eaten)					//check for collision
{
	if (overlap(charizardSprite, cookieSprite))
	{

		eaten++;
		reset(cookieSprite);
		charizardSprite.scale(1.1, 1.1);		//setscale: multiplying charizard size 1.5 by 1.5 const
												//scale : charizard gets 1.1 by 1.1 time bigger everytime it eat a cookie

	}
}

void reset(sf::Sprite & cookieSprite)					//reset the position of cookie everytime cookie is eaten
{
	cookieSprite.setPosition(rand() %700, rand() %500);		//2 parameters for x (divided by 700 because we don't want the cookie to go out of the window (window is 800 in this case)
															//and y position (divided randomly-generated number by 500 to get a y position less than the default window size
}


void handleEvent(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void update(sf::Sprite& charizardSprite, sf::Sprite& cookieSprite, int& eaten)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		charizardSprite.move(0, -5);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		charizardSprite.move(0, 5);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		charizardSprite.move(-5, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		charizardSprite.move(5, 0);
	handleCollision(charizardSprite, cookieSprite, eaten);
}


void draw(sf::RenderWindow& window, sf::Sprite& charizardSprite, sf::Sprite& cookieSprite, int& eaten)
{
	window.clear();
	window.draw(cookieSprite);
	window.draw(charizardSprite);
	window.display();
}

int main()
{
	srand(time(NULL));							//this line will make the srand truly random, doesn't repeat itself
												//helps reset function

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Works!");
	window.setVerticalSyncEnabled(true);

	sf::Texture charizardTexture;
	charizardTexture.loadFromFile(resourcePath() + "assets/charizard.png");
	sf::Sprite charizardSprite(charizardTexture);

	sf::Texture cookieTexture;
	cookieTexture.loadFromFile(resourcePath() + "assets/cookie.png");
	sf::Sprite cookieSprite(cookieTexture);
	cookieSprite.setPosition(400, 300);
	
	int eaten = 0;

	while (window.isOpen())
	{
		handleEvent(window);
		update(charizardSprite, cookieSprite, eaten);
		draw(window, charizardSprite, cookieSprite, eaten);
	}

	return 0;
}