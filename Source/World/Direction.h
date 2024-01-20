#pragma once
#include <set>

typedef enum{DIR_NORTH = 1, DIR_WEST = 3, DIR_SOUTH = 2, DIR_EAST = 6, DIR_NORTHEAST = 7, DIR_NORTHWEST = 4, DIR_SOUTHWEST = 5, DIR_SOUTHEAST = 8} Direction;

Direction addDirections(Direction first, Direction second);
std::set<Direction> cardinalDirections();
std::set<Direction> intermediateDirections();
std::set<Direction> allDirections();
Direction reverseDirection(Direction direction);