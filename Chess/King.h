#pragma once
#include "defines.h"
#include "Piece.h"
#include "graphics.h"
#include <string>
#include <vector>



class King : public Piece 
{
	std::string image = "";
public:
	inline King(float x, float y, bool player) : Piece(x, y, player , 3) , image(player?"w-king.png":"b-king.png"){}


	void draw();
	void update();

	//king moves in any direction but only one block away
	std::vector < std::vector < std::vector <int>>> legalMoves(int board_x, int board_y);
};

void King::draw()
{
	graphics::Brush br;
	br.texture = ASSET_PATH + image;
	br.outline_opacity = 0.0f;
	graphics::drawRect(getX(), getY(), 100, 100, br);

}


std::vector < std::vector < std::vector <int>>> King::legalMoves(int board_x, int board_y)
{
	std::vector < std::vector < std::vector <int>>> vec;
	vec.push_back(getKingSquares(board_x, board_y));
	return vec;
}





void King::update()
{
}

