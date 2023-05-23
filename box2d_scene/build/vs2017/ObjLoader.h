#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>

#include <graphics/skinned_mesh_instance.h>
#include <graphics/mesh_instance.h>

class ObjLoader {
public:
	static gef::MeshInstance* loadMesh(const char* path);

};

#endif // !OBJLOADER_H

