#include "Direction.h"

Direction addDirections(Direction first, Direction second){
    return static_cast<Direction>(int(first) + int(second));
}

std::set<Direction> cardinalDirections(){
    return {DIR_NORTH, DIR_WEST, DIR_SOUTH, DIR_EAST};
}

std::set<Direction> intermediateDirections(){
    return {DIR_NORTHEAST, DIR_NORTHWEST, DIR_SOUTHWEST, DIR_SOUTHEAST};
}

std::set<Direction> allDirections(){
    return {DIR_NORTH, DIR_WEST, DIR_SOUTH, DIR_EAST, DIR_NORTHEAST, DIR_NORTHWEST, DIR_SOUTHWEST, DIR_SOUTHEAST};
}

Direction reverseDirection(Direction direction){
    switch (direction){
        case DIR_NORTH:
            direction = DIR_SOUTH;
            break;
        case DIR_WEST:
            direction = DIR_EAST;
            break;
        case DIR_SOUTH:
            direction = DIR_NORTH;
            break;
        case DIR_EAST:
            direction = DIR_WEST;
            break;
        case DIR_NORTHEAST:
            direction = DIR_SOUTHWEST;
            break;
        case DIR_NORTHWEST:
            direction = DIR_SOUTHEAST;
            break;
        case DIR_SOUTHWEST:
            direction = DIR_NORTHEAST;
            break;
        case DIR_SOUTHEAST:
            direction = DIR_NORTHWEST;
            break;
    }

    return direction;
}