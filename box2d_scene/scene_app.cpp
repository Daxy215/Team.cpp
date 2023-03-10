#include "scene_app.h"

#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>
#include <maths/quaternion.h>

#include <Player.h>

//Checks if a class is instance of. For example, "Player" can be,
//an instance of Entity as it, inherits from "Entity".
//Usuage ex: isInstance(entity, Player);
#define isInstance(ptr, clazz) (dynamic_cast<const clazz*>(ptr) != NULL)

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	font_(NULL) {

}

void SceneApp::Init() {
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);

	b2Vec2 gravity(0.0f, -9.8);
	world_ = new b2World(gravity);
	
	b2PolygonShape player_shape;
	player_shape.SetAsBox(0.5f, 0.5f);

	b2FixtureDef player_fixture_def;
	player_fixture_def.shape = &player_shape;
	player_fixture_def.density = 1.0f;

	//Player
	Player* player = new Player(*primitive_builder_, *world_, new gef::Vector4(0, 2, -2, 1), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(1, 1, 1, 1));
	player->init(player_fixture_def, b2_dynamicBody);

	entities.push_back(player);

	//Ground
	Entity* ground = new Entity(*primitive_builder_, *world_, new gef::Vector4(0, -2, -2, 1), new gef::Quaternion(0, 0, 0, 1), new gef::Vector4(10, 1, 1, 1));

	b2PolygonShape shape;
	shape.SetAsBox(ground->getScale()->x() * 0.5f, ground->getScale()->y() * 0.5f);

	// create the fixture
	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;

	ground->init(fixture_def, b2_staticBody);

	entities.push_back(ground);

	InitFont();
	SetupLights();
}

void SceneApp::CleanUp() {
	CleanUpFont();

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;
	
	delete world_;
	world_ = NULL;
}

bool SceneApp::Update(float frame_time) {
	fps_ = 1.0f / frame_time;
	
	float time_step = 1.0f / 60.0f;
	int32 velecoity_iterations = 6;
	int32 position_iterations = 2;

	world_->Step(time_step, velecoity_iterations, position_iterations);
	
	for (auto it = entities.begin(); it < entities.end(); it++)
		(*it)->update();

	//Collision detection
	// get the head of the contact list
	b2Contact* contact = world_->GetContactList();
	// get contact count
	int contact_count = world_->GetContactCount();

	for (int contact_num = 0; contact_num < contact_count; ++contact_num) {
		if (contact->IsTouching()) {
			// get the colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();
			
			// DO COLLISION RESPONSE HERE
			Entity* entityA = (Entity*)bodyA->GetUserData().pointer;
			Entity* entityB = (Entity*)bodyB->GetUserData().pointer;

			//Check if bodyA isn't null
			if(entityA) {
				//Check if entityA is a player.
				if (isInstance(entityA, Player)) {
					Player* player = dynamic_cast<Player*>(entityA);

					player->damage();
				}
			}
			
			if(entityB) {
				if (isInstance(entityB, Player)) {
					Player* player = dynamic_cast<Player*>(entityB);

					player->damage();
				}
			}
		}

		// Get next contact point
		contact = contact->GetNext();
	}

	return true;
}

void SceneApp::Render()
{
	// setup camera

	// projection
	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)platform_.width() / (float)platform_.height();
	gef::Matrix44 projection_matrix;
	projection_matrix = platform_.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderer_3d_->set_projection_matrix(projection_matrix);

	// view
	gef::Vector4 camera_eye(-2.0f, 2.0f, 5.0f);
	gef::Vector4 camera_lookat(0.0f, 0.0f, 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderer_3d_->set_view_matrix(view_matrix);
	
	// draw 3d geometry
	renderer_3d_->Begin();

	renderer_3d_->set_override_material(&primitive_builder_->red_material());
	for (auto it = entities.begin(); it < entities.end(); it++) {
		Entity* entity = (*it);
		const gef::MeshInstance* mesh = static_cast<gef::MeshInstance*>(entity);
		renderer_3d_->DrawMesh(*mesh);
	}
	
	renderer_3d_->set_override_material(NULL);

	renderer_3d_->End();

	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer_->Begin(false);
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
