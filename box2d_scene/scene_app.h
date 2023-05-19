#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system/application.h>
#include <maths/vector4.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <box2d/box2d.h>
#include "graphics/scene.h"
#include <audio/audio_manager.h>

#include <vector>

#include <Entity.h>
#include <SceneManager.h>

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}

class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();

	gef::Scene* LoadSceneAssets(const char* filename);
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);
public:
	static SceneApp* instance;
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();
	void SetupLights();
	
	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::Renderer3D* renderer_3d_;
	gef::InputManager* input_manager_;
	gef::AudioManager* audio_manager_;

	PrimitiveBuilder* primitive_builder_;

	gef::Scene* scene_assets_;

	b2World* world_;

	float fps_;
};

#endif // _SCENE_APP_H
