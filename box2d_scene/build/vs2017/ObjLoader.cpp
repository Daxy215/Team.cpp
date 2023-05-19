#include "ObjLoader.h"

#include <scene_app.h>
#include <system/debug_log.h>

gef::MeshInstance* ObjLoader::loadMesh(const char* path) {
	//const char* scene_asset_filename = "world.scn";
	auto scene_assets_ = SceneApp::instance->LoadSceneAssets(path);

	gef::MeshInstance* mesh{};

	if (scene_assets_) {
		mesh->set_mesh(SceneApp::instance->GetMeshFromSceneAssets(scene_assets_));
	} else {
		gef::DebugOut("Scene file %s failed to load\n", path);
	}

    return mesh;
}
