#ifndef LEVELMAKER_H
#define LEVELMAKER_H

#include <vector>
#include <Entity.h>

class LevelMaker {
public:
	static std::vector<Entity*> createLevel(int level[32][32], PrimitiveBuilder* primitive_builder, b2World* world_);
};

#endif // !LEVELMAKER_H
