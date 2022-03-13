#pragma once
#include <string>
#include "defines.h"
#include "Piece.h"
#include "Button.h"
#include "BoardSquare.h"
#include <vector>

const std::string piece_image_names[][9] =
{
	{"w-rook.png" , "b-rook.png"},
	{"w-knight.png" , "b-knight.png"},
	{"w-bishop.png" , "b-bishop.png"},
	{"w-queen.png" , "b-queen.png"},
	{"w-king.png" , "b-king.png"},
	{"w-bishop.png" , "b-bishop.png"},
	{"w-knight.png" , "b-knight.png"},
	{"w-rook.png" , "b-rook.png"},
	{"w-pawn.png" , "b-pawn.png"}
};

class Game {

public:
	enum turn_state { BLACK_TURN , WHITE_TURN };
	enum game_state { PLAYING , ENDED};
protected:
	BoardSquare* board[8][8];
	BoardSquare* active_player = nullptr; //this variable will store the block that the cursor clicked upon
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