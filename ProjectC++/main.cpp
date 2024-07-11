#include "sgg/graphics.h"
#include "util.h" //SETCOLOR
#include "gamestate.h"


void draw() {

	GameState::getInstance()->draw();

}


void update(float dt) {
	GameState::getInstance()->update(dt);

}

void init() {

	GameState::getInstance()->init(); // ����� ������ ����� pointer.
}


int main(int argc, char** argv) {

	graphics::createWindow(600, 600, "MyGame"); // ��������� �������� �� �������� (width, height, ����� ���������).
	
	init();

	graphics::setDrawFunction(draw);     // ���� ��� draw, 
	graphics::setUpdateFunction(update); // update ����������.
	
	graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop(); //���������� ��� �� ��� ������� �� ��������.


	return 0;
}