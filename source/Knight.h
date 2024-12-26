#pragma once
#include "Piece.h"
#include "graphics.h"
#include <string>
#include <vector>



class Knight : public Piece {
	std::string image = "";
public:
	inline Knight(float x, float y, PLAYER player): Piece(x , y , player , KNIGHT) , image(player ? "w-knight.png" : "b-knight.png") {}


	void draw();


	//2 Up/Down & 1 Left/Right
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

