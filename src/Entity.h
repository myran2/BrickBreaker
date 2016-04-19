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

enum TypeIDs
{
    TYPEID_ENTITY = 0,
    TYPEID_BALL   = 1,
    TYPEID_BRICK  = 2,
    TYPEID_MOD    = 3
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
        int getHeight() { return height; }
        int getWidth() { return width; }
        int getTypeId() { return typeId; }

        // updates the texture of the entity
        void setTexture(const std::string& textureName);

        void setX(int x) { xPos = x; }
        void setY(int y) { yPos = y; }

        // true if moving in the given direction, false otherwise
        bool isMoving(int direction);

        // returns true if the entity is visible on the screen
        bool isActive() { return active; }

        void setMoveRate(int rate) { moveRate = rate; }

        // moves the entity in 'direction'
        // see EntityMoveState enum for options
        void startMoving(int direction);

        // stops entity's movement in 'direction'
        // see EntityMoveState for options
        void stopMoving(int direction);
        
        // update the entity's position and draw it to the window
        virtual void update();

        // removes the entity from the screen
        void remove();

        // returns true if this entity is touching 'entity'
        bool collidedWith(Entity* entity);

        // == operator overload so we can see if 2 entities equal each other
        friend bool operator==(const Entity& left, const Entity& right);
        friend bool operator!=(const Entity& left, const Entity& right) { return !(left == right); }

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

		// Used to identify the sublcass of the entity. See TypeIDs enum for options
        int typeId;

        unsigned int moveState = MOVE_NONE;
        int moveRate = 0;

        // true if the entity is visible on the screen
        bool active;
};

#endif
