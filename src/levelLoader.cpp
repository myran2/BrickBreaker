#include <iostream>
#include <fstream>
#include <string>
#include "levelLoader.h"
#include "Brick.h"

using namespace std;

LevelLoader::LevelLoader(GameManager* gm)
{
	gameManager = gm;
}

void LevelLoader::openMap(const std::string& mapName)
{
	string line;
	ifstream myfile(mapName);

	if (myfile.is_open())
	{
		int ypos = 30;
		while (getline(myfile, line))
		{
			int xpos = 25;
			while (line.size() > 0)
			{
				char hp = line.at(0);
				int health = hp - '0';

				if (health > 0)
				{
					if (health == 3)
						gameManager->addEntity(new Brick(gameManager->getWindow(), "redBrick.bmp", xpos, ypos, health));
					if (health == 2)
						gameManager->addEntity(new Brick(gameManager->getWindow(), "yellowBrick.bmp", xpos, ypos, health));
					if (health == 1)
						gameManager->addEntity(new Brick(gameManager->getWindow(), "greenBrick.bmp", xpos, ypos, health));
				}

				line.erase(0, 1);
				xpos += 100;
			}
			ypos += 30;
		}
		myfile.close();
		return;
	}
	else
		Log::error("Couldn't open " + mapName);


}
