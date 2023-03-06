#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>
#include <maths/matrix44.h>
#include <input/sony_controller_input_manager.h>
#include <input/input_manager.h>

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	font_(NULL),
	controller_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL) {
	
}

void SceneApp::Init() {
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	gef::Matrix44 projection = platform_.PerspectiveProjectionFov(100, (float)platform_.width() / platform_.height(), 0.1, 100);
	renderer_3d_->set_projection_matrix(projection);
	
	gef::Matrix44 view;
	view.LookAt(gef::Vector4(0, 2, 25), gef::Vector4(0, 0, 0), gef::Vector4(0, 1, 0));
	renderer_3d_->set_view_matrix(view);

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);
	
	// initialise input
	input_ = gef::InputManager::Create(platform_);
	controller_ = input_->controller_input()->GetController(0);
	keyboard_ = input_->keyboard();

	player = new Player();
	player->init(primitive_builder_);
	
	InitFont();
}

void SceneApp::CleanUp()
{
	CleanUpFont();

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;
}

bool SceneApp::Update(float frame_time) {
	fps_ = 1.0f / frame_time;

	player->update(controller_, keyboard_);

	input_->Update();
	
	return true;
}

void SceneApp::Render()
{
	// draw 3d geometry
	renderer_3d_->Begin();

	player->render(renderer_3d_);

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
