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

	GameState::getInstance()->init(); // βελος επειδη ειναι pointer.
}


int main(int argc, char** argv) {

	graphics::createWindow(600, 600, "MyGame"); // Δημιουργώ παράθυρο με ορίσματα (width, height, όνομα παραθύρου).
	
	init();

	graphics::setDrawFunction(draw);     // Καλώ τις draw, 
	graphics::setUpdateFunction(update); // update αντίστοιχα.
	
	graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop(); //Απαραίτητο για να μην κλείνει το παράθυρο.


	return 0;
}