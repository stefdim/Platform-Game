#pragma once
#include "sgg/graphics.h"
#include <string>



class GameState {

private:
	std::string m_asset_path = "assets\\";

	float m_canvas_width = 15.0f;
	float m_canvas_height = 10.0f;
	
	static GameState* m_unique_instance;

	GameState(); // Constructor

	class Player* m_player = 0;
	class Level* m_current_level = 0;
	

	

public:
	float m_global_offsetX = 0.0f;
	float m_global_offsetY = 0.0f; // Τις χρησημοποιω για να αλλαξω το background σε σχεση με τον παιχτη, κατι τετοιο περιπου.
	bool m_debugging = false;
	float p;
	float d_time;
	int total_score = 0;
	std::string m_help_text1;
	std::string m_help_text2;
    
	graphics::Brush m_text; 

	void init();
	void draw();
	void update(float dt);

	static GameState* getInstance(); // Ξεκινάω το m_unique_instance, μου το επιστρεφει.

	~GameState();//destructor

	float getCanvasWidth() {
		return m_canvas_width;
	}
	float getCanvasHeight() {
		return m_canvas_height;
	}

	void playerEffect();
	std::string getAssetDir(); // returns m_asset_path.
	std::string getFullAssetPath(const std::string& asset); // Επιστρεφει το full path ενος string.

	class Player* getPlayer() { return m_player; }

	void sawEndText() const;
	void sawExitText() const;
	
};