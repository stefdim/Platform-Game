#pragma once
#include "gameobject.h"
#include "sgg/graphics.h"
#include <list>
#include <vector>
#include <string>
#include "box.h"
#include <random>


class Level : public GameObject
{
	graphics::Brush m_brush_background;
	graphics::Brush m_brush_background2;
	
	
	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	const float m_block_size = 1.0f;
	float enemy_pos_x ;
	float enemy_pos_y ;
	float enemy_size = 1.0f;
	float enemy_move = 360 * rand() / (float)RAND_MAX;
	float enemy_speed = 7.5f;
	
	

	std::vector <GameObject*> m_static_objects;
	std::list <GameObject*> m_dynamic_objects;

	std::vector <Box> m_blocks;
	std::vector <Box> m_floor_block;
	std::vector <Box> m_enemies_blocks;
	std::vector <Box> m_finish_blocks;
	
	std::vector <std::string> m_finish_blocks_names;
	std::vector <std::string> m_block_names;
	std::vector <std::string> m_floor_name;
	std::vector <std::string> m_enemies_names;

    

	graphics::Brush m_block_brush;
	graphics::Brush m_floor_brush;
	graphics::Brush m_enemies_brush;
	graphics::Brush m_start_brush;
	graphics::Brush m_finish_brush;
	
	graphics::Brush m_block_brush_debug;
	graphics::Brush m_floor_brush_debug;
	graphics::Brush m_enemies_brush_debug;
	
	


	void drawBlock(int i);
	void drawFloorBlock(int i);
	void drawEnemiesBlock(int i);
	void drawFinishBlock(int i);

	void checkCollisions();


public:

	void update(float dt) override;
	void init() override;
	void draw() override;
	
	Level(const std::string& name = "level0");
	~Level();
};
