#include "player.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include "util.h"


void Player::movePlayer(float dt)
{
	float delta_time = dt / 1000.f; // Απλά αλλάζει το dt που είναι σε ms. Δεν είναι απαραίτητο.
	float move = 0.0f;



   if (graphics::getKeyState(graphics::SCANCODE_A))
	   move -= 1.0f;
   if (graphics::getKeyState(graphics::SCANCODE_D))
	   move += 1.0f;

   m_vx = std::min(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
   m_vx = std::max(-m_max_velocity, m_vx);


   m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx)); // antistasi aera.

  // m_pos_x += delta_time * m_vx;
   if (fabs(m_vx) < 0.01f)
	   m_vx = 0.0f;
   m_pos_x += delta_time * m_vx;

   if (m_vy == 0.0f)
	   m_vy -= (graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f) * 0.02f;

   m_vy += delta_time * m_gravity;

   m_pos_y += m_vy * delta_time;
}



void Player::update(float dt) {
	

	float delta_time = dt / 1000.f;
	float pl = 0.5f + fabs(cos(graphics::getGlobalTime() / 1000.0f));
	
	movePlayer(dt);
	
	

	m_state->m_global_offsetX = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offsetY = m_state->getCanvasHeight() / 2.0f - m_pos_y; // Ουσιαστικα δεν κινω τον παιχτη αλλα το background.

	

	GameObject::update(dt);
}

void Player::init() {
	
	m_pos_x = 2.0f;
	m_pos_y = 5.0f;
	

	m_state->m_global_offsetX = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offsetY = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	
	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;


	
		m_sprites.push_back(m_state->getFullAssetPath("character1.png"));
		m_sprites.push_back(m_state->getFullAssetPath("character2.png"));
		m_sprites.push_back(m_state->getFullAssetPath("character3.png"));
		m_sprites.push_back(m_state->getFullAssetPath("character4.png"));
		m_sprites.push_back(m_state->getFullAssetPath("character5.png"));
		m_sprites.push_back(m_state->getFullAssetPath("character6.png"));
		m_sprites.push_back(m_state->getFullAssetPath("character7.png"));
		m_sprites.push_back(m_state->getFullAssetPath("character8.png"));
	

		m_width /= 2.0f;

		m_brush_player_debug.fill_opacity = 0.5f;
		SETCOLOR(m_brush_player_debug.fill_color, 1.2f, 0.0f, 0.1f);
		SETCOLOR(m_brush_player_debug.outline_color, 1.3f, 1.0f, 0.2f);

		
		
	
}
void Player::draw() {
	
	int s = (int)fmodf(1000.0f-m_pos_x , m_sprites.size());
	m_brush_player.texture = m_sprites[s];

	    graphics::drawRect(m_state->getCanvasWidth() / 2.0f, m_state->getCanvasHeight() /2.0f, 1.0f, 1.0f, m_brush_player);

	if (m_state->m_debugging) {
		graphics::drawRect(m_state->getCanvasWidth() / 2.0f, m_state->getCanvasHeight() / 2.0f, 1.0f, 1.0f, m_brush_player_debug);
	}

}
