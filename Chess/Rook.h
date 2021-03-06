#pragma once
#include "Piece.h"
#include "graphics.h"
#include <string>
#include <vector>




class Rook : public Piece {
	std::string image = "";

public:
	inline Rook(float x , float y , bool player) : Piece(x , y , player , 1) , image(player ? "w-rook.png" : "b-rook.png") {}


	void draw();
	void update();

	//Legal moves for rook will be all the squares left or right  , up or down from it.
	std::vector<std::vector<std::vector<int>>> legalMoves(int board_x, int board_y);
};

void Rook::draw()
{
	graphics::Brush br;
	br.texture = ASSET_PATH + image;
	br.outline_opacity = 0.0f;
	graphics::drawRect(getX(), getY(), 100, 100, br);

}


std::vector<std::vector<std::vector<int>>> Rook::legalMoves(int board_x, int board_y)
{
	std::vector < std::vector < std::vector <int>>> vec;
	vec.push_back(getUpSquares(board_x, board_y));
	vec.push_back(getDownSquares(board_x, board_y));
	vec.push_back(getLeftSquares(board_x, board_y));
	vec.push_back(getRightSquares(board_x, board_y));
	return vec;
}




void Rook::update()
{
}

