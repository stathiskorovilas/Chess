
#pragma once
#include "defines.h"
#include "Piece.h"
#include "graphics.h"
#include <string>
#include <vector>



class Bishop : public Piece {
	std::string image = "";
public:
	inline Bishop(float x, float y, PLAYER player) : Piece(x, y, player , BISHOP), image(player ? "w-bishop.png" : "b-bishop.png"){}


	void draw();
	

	//Diagonal
	std::vector < std::vector < std::vector <int>>> legalMoves(int board_x , int board_y);
};

void Bishop::draw()
{
	graphics::Brush br;
	br.texture = ASSET_PATH + image;
	br.outline_opacity = 0.0f;
	graphics::drawRect(getX(), getY(), 100, 100, br);

}



std::vector<std::vector<std::vector<int>>> Bishop::legalMoves(int board_x, int board_y)
{
	std::vector < std::vector < std::vector <int>>> vec;
	vec.push_back(getUpLeftSquares(board_x, board_y));
	vec.push_back(getUpRightSquares(board_x, board_y));
	vec.push_back(getDownLeftSquares(board_x, board_y));
	vec.push_back(getDownRightSquares(board_x, board_y));
	return vec;
}

