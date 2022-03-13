#include "graphics.h"
#include "game.h"
#include "defines.h"
#include <string>

void draw(){
	Game* mygame = (Game *)graphics::getUserData();
	mygame->draw();
}

void update(float ms) {
	Game* mygame = (Game*)graphics::getUserData();
	mygame->update();
	
	
	
}


int main() {
	graphics::createWindow(CANVAS_WH, CANVAS_WH, "Chess v0.1");

	Game* game = new Game();
	game->init();

	graphics::setUserData(game);

	graphics::setCanvasSize(CANVAS_WH , CANVAS_WH);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::playMusic(ASSET_PATH + std::string("gnossienes.mp3"), 0.3f);

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::startMessageLoop();

	delete game;
	
	return 0;
}