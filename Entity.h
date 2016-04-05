#ifndef _ENTITY_H
#define _ENTITY_H

#include <SDL.h>
#include "Window.h"

enum EntityMoveState
{
    MOVE_NONE =  0x00,
    MOVE_UP =    0x01,
    MOVE_DOWN =  0x02,
    MOVE_LEFT =  0x04,
    MOVE_RIGHT = 0x08,
    MOVE_ALL =   0x10
};

class Entity
{
    public:
        Entity(Window* window, const std::string& textureName, int xPos, int yPos);
        ~Entity();

        SDL_Texture* getTexture() { return texture; }
        int getX() { return xPos; }
        int getY() { return yPos; }
        int getMoveRate() { return moveRate; }
        // true if moving, false otherwise
        bool isMoving(int direction);

        void setMoveRate(int rate) { moveRate = rate; }

        // moves the entity in 'direction'
        // see EntityMoveState for options
        void startMoving(int direction);

        //stops entity's movement in 'direction'
        // see EntityMoveState for options
        void stopMoving(int direction);
        
        // update the entity's position and draw it to the window
        virtual void update();

        // removes the entity from the screen
        void remove();

    protected:
        Window* window;
        SDL_Texture* texture = NULL;
        const std::string textureName;

        // the position of the top-left corner of the entity
        int xPos;
        int yPos;

        // width and height of the entity's texture
        int width;
        int height;

        unsigned int moveState = MOVE_NONE;
        int moveRate = 0;
};

#endif
