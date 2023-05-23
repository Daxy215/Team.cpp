#include "scene_app.h"

#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <input/touch_input_manager.h>
#include <maths/math_utils.h>
#include <graphics/scene.h>
#include <animation/skeleton.h>
#include <animation/animation.h>
#include <graphics/image_data.h>

#include <SplashScreen.h>
#include <MainMenu.h>
#include <Options.h>
#include <Credits.h>
#include <Level1.h>

#include "Enemy.h"

//Checks if a class is instance of. For example, "Player" can be,
//an instance of Entity as it, inherits from "Entity".
//Usuage ex: isInstance(entity, Player);
#define isInstance(ptr, clazz) (dynamic_cast<const clazz*>(ptr) != NULL)

SceneApp* SceneApp::instance;

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	font_(NULL),
	input_manager_(NULL),
	audio_manager_(NULL),
	scene_assets_(NULL) {
	
	
}

void SceneApp::Init() {
	instance = this;

	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	input_manager_ = gef::InputManager::Create(platform_);
	audio_manager_ = gef::AudioManager::Create();

	// make sure if there is a panel to detect touch input, then activate it
	if (input_manager_ && input_manager_->touch_manager() && (input_manager_->touch_manager()->max_num_panels() > 0))
		input_manager_->touch_manager()->EnablePanel(0);

	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);
	
	//Create world
	b2Vec2 gravity(0.0f, -9.8);
	world_ = new b2World(gravity);

	//To load a texture
	/*gef::PNGLoader png_loader;
	gef::ImageData imageData;

	png_loader.Load("imagePath", platform_, imageData);

	if (imageData != nullptr) {
		gef::Texture* texture = gef::Texture::Create(platform_, imageData);
	}*/

	InitFont();
	SetupLights();

	scene_assets_ = new gef::Scene();
	scene_assets_->ReadSceneFromFile(platform_, "tesla/tesla.scn");

	scene_assets_->CreateMaterials(platform_);

	//Create scenes
	SceneManager::addScene(new SplashScreen("SplashScreen", input_manager_));
	SceneManager::addScene(new MainMenu("MainMenu", input_manager_));
	SceneManager::addScene(new Options("Options", platform_));
	SceneManager::addScene(new Credits("Credits"));

	SceneManager::addScene(new Level1("Level 1", renderer_3d_, primitive_builder_, world_, input_manager_));

	SceneManager::loadScene(SceneManager::scenes[4]); //Change it to '0' later.
}

void SceneApp::CleanUp() {
	CleanUpFont();

	//delete scene_assets_;
	//scene_assets_ = NULL;

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete input_manager_;
	input_manager_ = NULL;
	
	delete audio_manager_;
	audio_manager_ = NULL;

	delete world_;
	world_ = NULL;
}

bool SceneApp::Update(float frame_time) {
	fps_ = 1.0f / frame_time;
	
	mousePos = input_manager_->touch_manager()->mouse_position();

	float time_step = 1.0f / 60.0f;
	int32 velecoity_iterations = 6;
	int32 position_iterations = 2;

	input_manager_->Update();
	
	world_->Step(time_step, velecoity_iterations, position_iterations);
	
	//Collision detection
	// get the head of the contact list
	b2Contact* contact = world_->GetContactList();
	// get contact count
	int contact_count = world_->GetContactCount();

	if (contact == nullptr)
		return true;

	for (int contact_num = 0; contact_num < contact_count; ++contact_num) {
		if (contact != nullptr && contact->IsTouching()) {
			// get the colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();
			
			// DO COLLISION RESPONSE HERE
			Entity* entityA = (Entity*)bodyA->GetUserData().pointer;
			Entity* entityB = (Entity*)bodyB->GetUserData().pointer;

			//If either is null then,
			//a collision check will be pointles,
			if (!entityA || !entityB)
				continue;

			//Check if entityA is a player.
			if (isInstance(entityA, Player) && isInstance(entityB, Enemy)) {
				Player* player = dynamic_cast<Player*>(entityA);

				player->damage(0);
				entityB->destroy();

				return true;
			}
			
			if (isInstance(entityB, Player) && isInstance(entityA, Enemy)) {
				Player* player = dynamic_cast<Player*>(entityB);

				player->damage(0);
				entityA->destroy();

				return true;
			}
		}

		// Get next contact point
		contact = contact->GetNext();
	}

	if (SceneManager::currentActiveScene != nullptr) {
		SceneManager::currentActiveScene->update();
	}

	return true;
}

void SceneApp::Render() {
	// setup camera

	// projection
	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)platform_.width() / (float)platform_.height();
	gef::Matrix44 projection_matrix;
	projection_matrix = platform_.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderer_3d_->set_projection_matrix(projection_matrix);

	// view
	gef::Vector4 camera_eye(0.0f, 2.0f, 25.0f);
	gef::Vector4 camera_lookat(0.0f, 0.0f, 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderer_3d_->set_view_matrix(view_matrix);
	
	// draw 3d geometry
	renderer_3d_->Begin();
	
	//renderer_3d_->set_override_material(&primitive_builder_->red_material());
	/*for (auto it = entities.begin(); it < entities.end(); it++) {
		Entity* entity = (*it);
		const gef::MeshInstance* mesh = static_cast<gef::MeshInstance*>(entity);
		renderer_3d_->DrawMesh(*mesh);
	}*/
	
	if (SceneManager::currentActiveScene != nullptr) {
		SceneManager::currentActiveScene->render();
	}

	renderer_3d_->End();

	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer_->Begin(false);
	if (SceneManager::currentActiveScene != nullptr) {
		SceneManager::currentActiveScene->drawHUD(sprite_renderer_, font_);
	}

	DrawHUD();

	sprite_renderer_->End();
}

void SceneApp::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SceneApp::CleanUpFont()
{
	delete font_;
	font_ = NULL;
}

void SceneApp::DrawHUD()
{
	if(font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
	}
}

void SceneApp::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}

gef::Scene* SceneApp::LoadSceneAssets(const char* filename) {
	gef::Scene* scene = new gef::Scene();

	if (scene->ReadSceneFromFile(platform_, filename)) {
		// if scene file loads successful
		// create material and mesh resources from the scene data
		scene->CreateMaterials(platform_);
		scene->CreateMeshes(platform_);
	} else {
		delete scene;
		scene = NULL;
	}

	return scene;
}

gef::Mesh* SceneApp::GetMeshFromSceneAssets(gef::Scene* scene) {
	gef::Mesh* mesh = NULL;

	// if the scene data contains at least one mesh
	// return the first mesh
	if (scene && scene->meshes.size() > 0)
		mesh = scene->meshes.front();

	return mesh;
}

gef::Animation* SceneApp::LoadAnimation(const char* anim_scene_filename, const char* anim_name)
{
	gef::Animation* anim = NULL;

	gef::Scene anim_scene;
	if (anim_scene.ReadSceneFromFile(platform_, anim_scene_filename))
	{
		// if the animation name is specified then try and find the named anim
		// otherwise return the first animation if there is one
		std::map<gef::StringId, gef::Animation*>::const_iterator anim_node_iter;
		if (anim_name)
			anim_node_iter = anim_scene.animations.find(gef::GetStringId(anim_name));
		else
			anim_node_iter = anim_scene.animations.begin();

		if (anim_node_iter != anim_scene.animations.end())
			anim = new gef::Animation(*anim_node_iter->second);
	}

	return anim;
}

gef::Skeleton* SceneApp::GetFirstSkeleton()
{
	gef::Skeleton* skeleton = NULL;
	if (scene_assets_)
	{
		// check to see if there is a skeleton in the the scene file
		// if so, pull out the bind pose and create an array of matrices
		// that wil be used to store the bone transformations
		if (scene_assets_->skeletons.size() > 0)
			skeleton = scene_assets_->skeletons.front();
	}

	return skeleton;
}

gef::Mesh* SceneApp::GetFirstMesh()
{
	gef::Mesh* mesh = NULL;

	if (scene_assets_)
	{
		// now check to see if there is any mesh data in the file, if so lets create a mesh from it
		if (scene_assets_->mesh_data.size() > 0)
			mesh = scene_assets_->CreateMesh(platform_, scene_assets_->mesh_data.front());
	}

	return mesh;
}
