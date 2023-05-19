#ifndef LEVELMAKER_H
#define LEVELMAKER_H

#include <vector>
#include <Entity.h>

#define LevelSizeX 32
#define LevelSizeY 6

class LevelMaker {
public:
	static std::vector<Entity*> createLevel(int startX, int startY, int level[LevelSizeX][LevelSizeY], PrimitiveBuilder* primitive_builder, b2World* world_);
};

#endif // !LEVELMAKER_H
