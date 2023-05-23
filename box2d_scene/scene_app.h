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
	class Skeleton;
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
	gef::Animation* LoadAnimation(const char* anim_scene_filename, const char* anim_name);
	gef::Skeleton* GetFirstSkeleton();
	gef::Mesh* GetFirstMesh();
public:
	gef::SpriteRenderer* getSpriteRenderer() { return sprite_renderer_; }
	gef::AudioManager* getAudioManager() { return audio_manager_; }
public:
	static SceneApp* instance;
	
	gef::Vector2 mousePos;
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

	int score = 0;
	float fps_;

	int32 enemyDeathSound, playerDamaged;
};

#endif // _SCENE_APP_H
