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
		int ypos = 15;
		while (getline(myfile, line))
		{
			int xpos = 15;
			while (line.size() > 0)
			{
				char hp = line.at(0);
				int health = hp - '0';

				if (health > 0)
				{
					gameManager->addEntity(new Brick(gameManager->getWindow(), "paddle.bmp", xpos, ypos, health));
				}

				line.erase(0, 1);
				xpos += 30;
			}
			ypos += 15;
		}
		myfile.close();
	}


}