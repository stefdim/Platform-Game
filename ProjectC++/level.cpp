#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "sgg/graphics.h"
#include "util.h"




void Level::drawFloorBlock(int i) {
Box& box_floor = m_floor_block[i];
	float x = box_floor.m_pos_x + m_state->m_global_offsetX; // thesi pou tha sxidiastei to block.
	float y = box_floor.m_pos_y + m_state->m_global_offsetY;

	
	m_floor_brush.texture = m_state->getFullAssetPath(m_floor_name[i]);
	graphics::drawRect(box_floor.m_pos_x + m_state->m_global_offsetX ,
		box_floor.m_pos_y + m_state->m_global_offsetY, m_block_size, m_block_size, m_floor_brush);
	
	if (m_state->m_debugging) {

		graphics::drawRect(x, y, m_block_size, m_block_size, m_floor_brush_debug);
	}

}

void Level::drawEnemiesBlock(int i)
{
	Box& box_enemies = m_enemies_blocks[i];

	float x = box_enemies.m_pos_x + m_state->m_global_offsetX; // thesi pou tha sxidiastei to block.
	float y = box_enemies.m_pos_y + m_state->m_global_offsetY;
	m_block_brush.texture = m_state->getFullAssetPath(m_enemies_names[i]);
	graphics::setOrientation(enemy_move);
	graphics::drawRect( x,  y, enemy_size, enemy_size, m_enemies_brush);
	m_enemies_brush.texture = m_state->getFullAssetPath("bird.png");
	graphics::resetPose();

	if (m_state->m_debugging) {
		graphics::drawRect(enemy_pos_x + x, enemy_pos_y + y, enemy_size, enemy_size, m_enemies_brush_debug);

	}
}



void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	
	float x = box.m_pos_x + m_state->m_global_offsetX; // thesi pou tha sxidiastei to block.
	float y = box.m_pos_y + m_state->m_global_offsetY;
	m_block_brush.texture = m_state->getFullAssetPath(m_block_names[i]);
	graphics::drawRect(x, y ,  m_block_size,  m_block_size , m_block_brush);

	if(m_state->m_debugging){
		graphics::drawRect(x , y, m_block_size, m_block_size, m_block_brush_debug);
	
	}
}


void Level::drawFinishBlock(int i)
{
	Box& box_finish = m_finish_blocks[i];

	float x = box_finish.m_pos_x + m_state->m_global_offsetX; // thesi pou tha sxidiastei to block.
	float y = box_finish.m_pos_y + m_state->m_global_offsetY;
	m_finish_brush.texture = m_state->getFullAssetPath(m_finish_blocks_names[i]);
	graphics::drawRect(x, y, m_block_size, m_block_size, m_finish_brush);
}

void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);


	enemy_pos_x -= enemy_speed * dt/1000.0f;
	enemy_move += 30.0f * dt/1000.0f;
	
	enemy_move = fmodf(enemy_move, 360);

	checkCollisions();

	GameObject::update(dt);
}



void Level::init()
{
	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();				// φερνω ολα τα αντικειμενα που βρισκονται εκει.
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();
	
	m_blocks.push_back(Box(-3 + 0, 6.5f, m_block_size, m_block_size));
	m_blocks.push_back(Box(-3 + 1, 7.1f, m_block_size, m_block_size));
	m_blocks.push_back(Box(-3 + 2, 7.7f, m_block_size, m_block_size));
	m_blocks.push_back(Box(-3 + 3, 8.3f, m_block_size, m_block_size));
	m_blocks.push_back(Box(-3 + 4, 8.9f, m_block_size, m_block_size));
	m_blocks.push_back(Box(-3 + 5, 9.5f, m_block_size, m_block_size));
	m_blocks.push_back(Box(-3 + 6, 10.1f, m_block_size, m_block_size));
	m_blocks.push_back(Box(-3 + 7, 10.7f, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 , 7.0f, m_block_size, m_block_size));
	m_blocks.push_back(Box(10.8f , 7.2f, m_block_size, m_block_size));
	m_blocks.push_back(Box(15 , 6.8f, m_block_size, m_block_size));
	m_blocks.push_back(Box(18 , 4.8f, m_block_size, m_block_size));
	m_blocks.push_back(Box(18 , 7.5f, m_block_size, m_block_size));
	m_blocks.push_back(Box(20 , 4.0f, m_block_size, m_block_size));
	m_blocks.push_back(Box(21 , 4.0f, m_block_size, m_block_size));
	m_blocks.push_back(Box(22 , 2.0f, m_block_size, m_block_size));


	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	m_block_names.push_back("pipeDown.png");
	


	m_finish_blocks.push_back(Box(21, 2.5f, m_block_size, m_block_size));
	m_finish_blocks_names.push_back("flag.png");


	enemy_pos_x = m_state->getCanvasWidth() + 5.0f;
	enemy_pos_y = m_state->getCanvasHeight() / 3.8f;



	for(int i = 0; i < 30; i++){
     m_floor_block.push_back(Box(-7 + i * m_block_size, 12.0f, m_block_size, m_block_size));
	 m_floor_block.push_back(Box(-7 + i * m_block_size, 12.8f, m_block_size, m_block_size));
	 m_floor_block.push_back(Box(-7 + i * m_block_size, 13.6f, m_block_size, m_block_size));
	 m_floor_block.push_back(Box(-7 + i * m_block_size, 14.4f, m_block_size, m_block_size));
	 m_floor_name.push_back("sea.png");
	 m_floor_name.push_back("sea.png");
	 m_floor_name.push_back("sea.png");
	 m_floor_name.push_back("sea.png");
	}

	
		m_enemies_blocks.push_back(Box(4.5, 5.5, enemy_size, enemy_size));
		m_enemies_blocks.push_back(Box(6, 7, enemy_size, enemy_size));
		m_enemies_blocks.push_back(Box(8, 3, enemy_size, enemy_size));
		m_enemies_blocks.push_back(Box(10, 2, enemy_size, enemy_size));
		m_enemies_blocks.push_back(Box(12, 3.5, enemy_size, enemy_size));
		m_enemies_blocks.push_back(Box(14, 3, enemy_size, enemy_size));
		m_enemies_blocks.push_back(Box(17, 5.8, enemy_size, enemy_size));
		m_enemies_blocks.push_back(Box(18, 1, enemy_size, enemy_size));
		m_enemies_blocks.push_back(Box(20, 0.88, enemy_size, enemy_size));

		m_enemies_names.push_back("bird.png");
		m_enemies_names.push_back("bird.png");
		m_enemies_names.push_back("bird.png");
		m_enemies_names.push_back("bird.png");
		m_enemies_names.push_back("bird.png");
		m_enemies_names.push_back("bird.png");
		m_enemies_names.push_back("bird.png");
		m_enemies_names.push_back("bird.png");
		m_enemies_names.push_back("bird.png");


	m_enemies_brush.outline_opacity = 0.0f;
	

	m_block_brush.outline_opacity = 0.0f;
	m_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush_debug.fill_color, 1.2f, 0.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);

	m_floor_brush.outline_opacity = 0.0f;
	m_floor_brush_debug.fill_opacity = 0.5f;
	SETCOLOR(m_floor_brush_debug.fill_color, 1.2f, 0.0f, 0.1f);
	SETCOLOR(m_floor_brush_debug.outline_color, 1.3f, 1.0f, 0.2f);

	m_enemies_brush_debug.fill_opacity = 0.5f;
	SETCOLOR(m_enemies_brush_debug.fill_color, 1.2f, 0.0f, 0.1f);
	SETCOLOR(m_enemies_brush_debug.outline_color, 1.3f, 1.0f, 0.2f);

	SETCOLOR(m_start_brush.fill_color, 1.0f,1.0f, 1.0f);
	m_start_brush.texture = m_state->getFullAssetPath("start.png");
	m_start_brush.outline_opacity = 0.0f;

	
}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = m_state->m_global_offsetX + w / 2.0f;
	float offset_y = m_state->m_global_offsetY + h / 2.0f;

	graphics::drawRect(offset_x, offset_y, 2.0f * w, 2.0f * h, m_brush_background);

	graphics::drawRect(offset_x - 7.0f, offset_y, 4.0f, 3.0f, m_start_brush);

	for (int i = 0; i < m_blocks.size(); i++) {
		drawBlock(i);
	}

	for (int i = 0; i < m_finish_blocks.size(); i++) {
		drawFinishBlock(i);
	}

	for (int i = 0; i < m_floor_block.size(); i++) {
		drawFloorBlock(i);
	}

	for (int i = 0; i < m_enemies_blocks.size(); i++) {
		drawEnemiesBlock(i);
	}
	if (m_state->getPlayer()->isActive() )
		m_state->getPlayer()->draw();
	
}

Level::Level(const std::string& name) : GameObject(name)
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background.png");

	
}

Level::~Level()
{
	for (auto p_gob : m_static_objects)
		if (p_gob) delete p_gob;
	for (auto p_gob : m_dynamic_objects) // φερνω ολα τα αντικειμενα που βρισκονται εκει.
		if (p_gob) delete p_gob;

}

void Level::checkCollisions()
{
	//int count = 0;
	float offset = 0.0f;
	
		
	for (auto& box : m_blocks) 
	{
		if (offset = m_state->getPlayer()->intersectDown(box))
		{
			m_state->getPlayer()->m_pos_y += offset;
			m_state->getPlayer()->m_vy = 0.0f;		
			
			
			break;
		}
	}
	for (auto& box_enemies : m_enemies_blocks)
	{
		if (offset = m_state->getPlayer()->intersect(box_enemies))
		{

			//count++;
			m_state->total_score++;
			
			m_state->playerEffect();
			box_enemies.m_pos_y -= Level::enemy_pos_y * m_state->d_time * 1000;
			break;
		}
	}
	
	for (auto& box_finish : m_finish_blocks)
	{
		if (offset = m_state->getPlayer()->intersect(box_finish))
		{

			if (m_state->total_score < 9)
			{
				graphics::drawText(2.0f, 5.0f, 0.5f, "You MUST catch the birds in order to finish!", m_state->m_text);
			}else{
			       graphics::drawText(2.0f, 5.0f, 2.0f, "YOU WIN!!!", m_state->m_text);
			       m_state->getPlayer()->m_pos_y = 3.0f;
			       m_state->getPlayer()->m_pos_x = 21.0f;
			       m_state->sawExitText();

			    if (graphics::getKeyState(graphics::SCANCODE_SPACE)) 
				     graphics::stopMessageLoop();
				

			}
			
			break;
		}
	}
	
	 
	for (auto& box_floor : m_floor_block) {
		
		if (offset = m_state->getPlayer()->intersectDown(box_floor))
		{
			if(m_state->getPlayer()->m_vy > 1.0f){
			graphics::playSound(m_state->getFullAssetPath("splash.wav"), 0.5f);
			}

            m_state->getPlayer()->m_pos_y = 12.0f;
			m_state->getPlayer()->m_pos_x = 12.0f;
			m_state->sawEndText();
			m_state->sawExitText();
			if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
				graphics::stopMessageLoop();	
			}
			m_state->getPlayer()->m_vy = 0.0f;
	
		}
	}
	
	
}


