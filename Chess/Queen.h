#pragma once
#include "Piece.h"
#include "graphics.h"
#include <string>
#include "defines.h"
#include <vector>




class Queen : public Piece {
	std::string image = "";
	
public:
	inline Queen(float x, float y, PLAYER player) : Piece(x, y, player , QUEEN) , image(player ? "w-queen.png" : "b-queen.png"){}


	void draw();

	//UP/DOWN , LEFT/RIGHT , DIAGONAL
	std::vector < std::vector < std::vector <int>>> legalMoves(int board_x, int board_y);

};

void Queen::draw()
{
	graphics::Brush br;
	br.texture = ASSET_PATH + image;
	br.outline_opacity = 0.0f;
	graphics::drawRect(getX(), getY(), 100, 100, br);

}


std::vector < std::vector < std::vector <int>>> Queen::legalMoves(int board_x, int board_y)
{
	std::vector < std::vector < std::vector <int>>> vec;
	vec.push_back(getDownSquares(board_x, board_y));
	vec.push_back(getUpSquares(board_x, board_y));
	vec.push_back(getLeftSquares(board_x, board_y));
	vec.push_back(getRightSquares(board_x, board_y));
	vec.push_back(getDownLeftSquares(board_x, board_y));
	vec.push_back(getDownRightSquares(board_x, board_y));
	vec.push_back(getUpLeftSquares(board_x, board_y));
	vec.push_back(getUpRightSquares(board_x, board_y));


	return vec;
}


