#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "sgg/graphics.h"
#include "util.h"
#include <string>

GameState::GameState()
{
}

void GameState::init()
{
	m_current_level = new Level();
	m_current_level->init();

	m_player = new Player("player");
	m_player->init();

	graphics::preloadBitmaps(getAssetDir()); //φορτωνει τα assets φωτογραφιες κλπ.
	graphics::setFont(getFullAssetPath("OpenSans-Regular.ttf"));

	SETCOLOR(m_text.fill_color,0.5f, 0.0f,0.0f);

	m_help_text1 = "A:Move left.D:Move right.W:Jump.";
	m_help_text2 = "Catch all the birds in order to finish." ; 

}

void GameState::draw()
{
	if (!m_current_level)
		return;

		m_current_level->draw();

		m_debugging = graphics::getKeyState(graphics::SCANCODE_0);

		
}

void GameState::update(float dt)
{
	if (dt > 500) // ms
		return;   //τσεκαρω αν αργει πολυ οποτε και δεν κανω update.

	if (!m_current_level)
		return;

	m_current_level->update(dt);
	d_time = dt / 1000.0f;
	
	graphics::drawText(getCanvasWidth() / 25, getCanvasHeight(), 1.0f, "H:help", m_text);

	if (graphics::getKeyState(graphics::SCANCODE_H)) {
		graphics::drawText(getCanvasWidth() / 25, getCanvasHeight() / 2, 1.0f, m_help_text1, m_text);
		graphics::drawText(getCanvasWidth() / 25, getCanvasHeight() /1.5, 1.0f, m_help_text2, m_text);
	}
	
}

GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr)
		m_unique_instance = new GameState();

	return m_unique_instance;
}
GameState::~GameState() {
	if (m_player)
		delete m_player;
	if (m_current_level)
		delete m_current_level;
	
}
void GameState::playerEffect()
{
	p = 0.5f + fabs(cos(graphics::getGlobalTime() / 100.0f));
	SETCOLOR(getPlayer()->m_brush_player.fill_color,p,p,p);

}
std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}

void GameState::sawEndText() const
{
	graphics::drawText(2.0f, 5.0f, 2.0f, "GAME OVER", m_text);
}

void GameState::sawExitText() const
{	
	std::string final_text = "Press SPACE to exit.";
	graphics::drawText(2.0f, 7.0f, 0.8f, 
		final_text, m_text);
}



GameState* GameState::m_unique_instance = nullptr; //αρχικοποιω την μεταβλητη.
