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

#define BLOCK_WIDTH 90

// function for openeing and reading the file containing the map
void LevelLoader::openMap(const std::string& mapName, int& maxBlocks)
{
    Log::info("Loading " + mapName);
    string line;
	ifstream myFile(mapName);

		// check to see if the file is able to be opened
    if (!myFile.is_open())
    {
        Log::error("Couldn't open " + mapName);
        maxBlocks = 0;
    }

    int blockCount = 0;

	int ypos = 30;
	while (getline(myFile, line))
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

                blockCount++;
			}

			line.erase(0, 1);
			xpos += 100;

            // move on to the next row if the current row is rendering off-screen
            if (xpos > gameManager->getWindow()->getWidth() - BLOCK_WIDTH)
                break;
		}
		ypos += 30;

        // stop rendering bricks if they've gone past the screen
        if (ypos > gameManager->getWindow()->getHeight())
            break;
	}

	myFile.close();
    maxBlocks = blockCount;
	return;
}
