#pragma once
#include <string>
#include "defines.h"
#include "Piece.h"
#include "Button.h"
#include "BoardSquare.h"
#include <vector>



class Game {
	enum turn_state { BLACK_TURN , WHITE_TURN };
	enum game_state { PLAYING , ENDED};
protected:
	BoardSquare* board[8][8];
	BoardSquare* active_player = nullptr; //this variable will store the block that the cursor has clicked upon (also it must be a square that has a piece in it)
	std::vector<std::vector<std::vector<int>>> legal_moves;
	turn_state turns = WHITE_TURN;
	game_state gstate = PLAYING;
	std::string winner;
	Button* restart = new Button(50.0f, 250.0f, "Restart");

public:
	void draw();
	void update();
	void init();

	~Game();

};