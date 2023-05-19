#ifndef OBJLOADER_H

#include <string>

#include <graphics/mesh_instance.h>

class ObjLoader {
public:
	static gef::MeshInstance* loadMesh(const char* path);
};

#endif // !OBJLOADER_H

