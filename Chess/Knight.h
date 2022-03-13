#pragma once
#include "Piece.h"
#include "graphics.h"
#include <string>
#include <vector>



class Knight : public Piece {
	std::string image = "";
public:
	inline Knight(float x, float y, bool player): Piece(x , y , player , 4) , image(player ? "w-knight.png" : "b-knight.png") {}


	void draw();
	void update();

	//legal moves for knight will be the squares that are 2 up/down and 1 left or right from it
	std::vector < std::vector < std::vector <int>>> legalMoves(int board_x, int board_y);
};

void Knight::draw()
{
	graphics::Brush br;
	br.texture = ASSET_PATH + image;
	br.outline_opacity = 0.0f;
	graphics::drawRect(getX(), getY(), 100, 100, br);

}


std::vector < std::vector < std::vector <int>>> Knight::legalMoves(int board_x, int board_y)
{
	std::vector < std::vector < std::vector <int>>> vec;
	vec.push_back(getKnightSquares(board_x, board_y));
	return vec;
}



void Knight::update()
{
}
