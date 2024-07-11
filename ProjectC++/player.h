#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"

class Player : public GameObject, public Box
{
    std::vector<std::string> m_sprites;

	
	graphics::Brush m_brush_player_debug;
	
	const float m_gravity = 10.0f;
	const float m_accel_vertical = 300.0f;
	const float m_accel_horizontal = 30.0f;
	const float m_max_velocity = 15.0f;

	//


public:
	float m_vx = 0.0f;
	float m_vy = 0.0f;
	graphics::Brush m_brush_player;

	Player(std::string name) : GameObject(name) {}

	void update(float dt) override;
	void init() override;
	void draw() override;
protected:
void movePlayer(float dt);

};