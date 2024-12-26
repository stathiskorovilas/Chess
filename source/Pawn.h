#pragma once
#include "Piece.h"
#include "graphics.h"
#include <string>
#include <vector>




class Pawn : public Piece {
	std::string image = "";
public:
	inline Pawn(float x , float y , PLAYER player) : Piece(x , y , player , PAWN) , image(player ? "w-pawn.png" : "b-pawn.png") {}


	void draw();

	//UP(2 if first move , 1 if not) , Up/Left - Up/Right (Only for capture)
	std::vector < std::vector < std::vector <int>>> legalMoves(int board_x, int board_y);

};

void Pawn::draw()
{
	graphics::Brush br;
	br.texture = ASSET_PATH + image;
	br.outline_opacity = 0.0f;
	graphics::drawRect(getX() , getY() , 100 , 100 , br);

}

std::vector < std::vector < std::vector <int>>> Pawn::legalMoves(int board_x, int board_y)
{
	std::vector < std::vector < std::vector <int>>> vec;
	vec.push_back(getPawnUPSquares(board_x, board_y, getMoves() == 0 ? 1 : 0, getPlayer()));
	vec.push_back(getPawnUPLeftSquares(board_x, board_y, getPlayer()));
	vec.push_back(getPawnUPRightSquares(board_x, board_y, getPlayer()));

	return vec;
}

