#include <iostream>
#include <time.h>
#include <array>
#include <SDL_mixer.h>
#include "GameManager.h"
#include "Log.h"
#include "Menu.h"
#include "Timer.h"
#include "levelLoader.h"

GameManager::GameManager(Window* window):
    window(window)
{
    currentState = STATE_MENU;
    _quit = false;
}
void GameManager::runGame()
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Music *music = NULL;
    std::string resPath = "res";
    std::string filePath = "";
    filePath = resPath + PATH_SEP + "backgroundmusic.wav";

    music = Mix_LoadMUS(filePath.c_str());

    if(!music)
        // TODO: Adapt this to Log::Error
        printf("Mix_LoadMUS(\"backgroundmusic.wav\"): %s\n", Mix_GetError());

    Mix_PlayMusic(music, -1);

    Entity* paddle = new Entity(window, "paddle.bmp", 305, 490);
    paddle->setMoveRate(8);
    entities.push_back(paddle);

    ball = new Ball(window, "ball.bmp", window->getWidth() / 2, window->getHeight() / 2, paddle);
    ball->setOnPaddle(true);

    //used for random powerup spwaning
    srand(time(NULL));
    randNum = rand() % 4;
    mod = new Mods(window, "PowerUP.bmp", 305, 0 );//makes a new power down object

    upNum = rand() % 2;
	downNum = rand() % 2;

    Timer fpsTimer;
    Timer capTimer;

    uint32_t frameCount = 0;
    fpsTimer.start();

    Menu mainMenu(this);
    mainMenu.addEntry("Play");
    mainMenu.addEntry("How to Play");
    mainMenu.addEntry("Credits");
    mainMenu.addEntry("Exit");

	currentLevel = 0;
    while (!_quit)
    {
        window->clear();

        capTimer.start();

        switch (currentState)
        {
        case STATE_MENU:
        {
            SDL_Texture* bgTexture = window->loadTexture("bg.bmp");
            window->renderTexture(bgTexture, 0, 0);
            mainMenu.tick();
            break;
        }
        case STATE_HOWTOPLAY:
            break;
        case STATE_CREDITS:
            break;
        case STATE_PLAYING:
            gameTick();
            break;
        default:
            Log::warn("Recieved unhandled gamestate: " + std::to_string(currentState));
            break;
        }
        // divide the amount of frames displayed by the runtime in seconds to get the average fps
        float avgFps = frameCount / (fpsTimer.getTicks() / 1000.f);
        if (avgFps > 2000000)
            avgFps = 0;

        window->renderText(std::to_string((int)avgFps), window->getWidth()-30, 0, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });

        window->render();

        frameCount++;

        // if our fps it too high, wait here until we're back to ~60fps
        if (capTimer.getTicks() < (1000 / window->getMaxFps()))
        {
            int waitTime = (1000 / window->getMaxFps()) - capTimer.getTicks();
            //Log::info("Waiting " + std::to_string(waitTime) + " MS");
            SDL_Delay(waitTime);
        }
    }
}

void GameManager::gameTick()
{
    SDL_PollEvent(&event);
    if(ball->getLives() < 1)
    {
        window->renderText("GAME OVER", window->getWidth()/3, window->getHeight()/4, {0,0,0}, 50, FONT_RENDER_BLENDED, {255,255,255});
        window->renderText("Score: ", window->getWidth()/3, window->getHeight()/2, {0,0,0}, 50, FONT_RENDER_BLENDED, {255,255,255});
        switch (event.type)
        {
        // if user clicks the red X
        case SDL_QUIT:
            _quit = true;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                _quit = true;
                break;
            case SDLK_SPACE:
                currentState = STATE_MENU;
                break;
            }
            break;
        }
        return;
    }
    // paddle is always added to the entities vector first, so this is fine
    Entity* paddle = entities[0];

    switch (event.type)
    {
    // if user clicks the red X
    case SDL_QUIT:
        _quit = true;
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            paddle->startMoving(MOVE_LEFT);
            break;
        case SDLK_RIGHT:
            paddle->startMoving(MOVE_RIGHT);
            break;
        case SDLK_SPACE:
            if (ball->isOnPaddle())
            {
              ball->detach();
            }
            isPressed = true;
            break;
        case SDLK_ESCAPE:
            currentState = STATE_MENU;
            break;
        }
        break;

    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            paddle->stopMoving(MOVE_LEFT);
            break;
        case SDLK_RIGHT:
            paddle->stopMoving(MOVE_RIGHT);
            break;
        }
        break;
    }

	LevelLoader* loader = new LevelLoader(this);
	if (currentLevel == 0)
	{
		loader->openMap("lvl2.txt");
		currentLevel = 12;
	}

    for (Entity* e : entities)
    {
        // don't think this is that cpu intensive but I guess it could be
        if (ball->collidedWith(e))
        {
            ball->handleCollision(e);

        }

        e->update();
    }

/************** Code segment used for powerup implementation ***************/
if(randNum == 0 && isPressed == true)
{
    mod->update();
        if(mod->collidedWith(paddle))
        {
         mod->fastPaddle();
         paddle->setMoveRate(7);
         mod->remove();
        }
}

if(randNum == 1 && isPressed == true)
{
  mod->update();
  if(mod->collidedWith(paddle))
  {
    paddle->setTexture("paddle_big.bmp");
    mod->largePaddle();
    mod->remove();
  }
}

if(randNum == 2 && isPressed == true)
{
    mod->update();
        if(mod->collidedWith(paddle))
        {
            mod->slowerPaddle();
            paddle->setMoveRate(3);
            mod->remove();
        }
    }
  if(randNum == 3 && isPressed == true)
  {
      mod->update();
        if(mod->collidedWith(paddle))
        {
            paddle->setTexture("paddle_small.bmp");
            mod->smallPaddle();
            mod->remove();
        }
    }
/***************************************************************************/

    ball->update();
    window->renderText("Lives: " + std::to_string(ball->getLives()), 0, 0, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });
}

void GameManager::addEntity(Entity* e)
{
	entities.push_back(e);
}
