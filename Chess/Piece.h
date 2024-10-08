#pragma once
#include "defines.h"
#include <string>
#include <vector>



class Piece 
{

	PLAYER player; 
	PIECE piece_id;
	int moves = 0;

	//Pixel position on the canvas
	float pos_x;
	float pos_y;




public:
	inline Piece(float pos_x, float pos_y , PLAYER player , PIECE piece_id): pos_x(pos_x) , pos_y(pos_y) , player(player) , piece_id(piece_id) {}



	/////////////////////////////////////////////////////////////
	////////////VISUAL REPRESENTATION OF THE PIECE////////////
	/////////////////////////////////////////////////////////////
	virtual void draw() = 0;
	

	/*
	* All possible moves -based on the position (x,y) of the piece calling it- for a piece will be saved in this vector.
	* Example:
	*legalMoves = { {(1,0) , (2,0) , ...} , {...} , {...} , ... }
	* 
	* Where the vectors inside legalMoves , are directions , and the vectors inside directions is a (x,y) position
	* Except King , Pawn , Knight which have their own method for calculating possible positions.
	*/
	virtual std::vector<std::vector<std::vector<int>>> legalMoves(int , int) = 0;


	///////////////////////////////
	////////////SETTERS////////////
	///////////////////////////////
	inline void setXY(float x, float y) { pos_x = x; pos_y = y; }
	
	

	/////////////////////////////
	////////////OTHER////////////
	/////////////////////////////
	inline void addMoves() { moves++; }



	///////////////////////////////
	////////////GETTERS////////////
	///////////////////////////////
	inline float getX() { return pos_x; }
	inline float getY() { return pos_y; }
	inline short getPlayer() { return player; }
	inline int getMoves() { return moves; }
	inline int getPieceID() { return piece_id; }



	/////////////////////////////////////////////////////////////
	////////////DEFINITION OF DIRECTION FUNCTIONS////////////
	/////////////////////////////////////////////////////////////
	

	//USED BY: Rook , Queen , Bishop
	inline std::vector<std::vector<int>> getUpSquares(int x, int y);
	inline std::vector<std::vector<int>> getDownSquares(int x, int y);
	inline std::vector<std::vector<int>> getRightSquares(int x, int y);
	inline std::vector<std::vector<int>> getLeftSquares(int x, int y);
	inline std::vector<std::vector<int>> getUpLeftSquares(int x, int y);
	inline std::vector<std::vector<int>> getUpRightSquares(int x, int y);
	inline std::vector<std::vector<int>> getDownLeftSquares(int x, int y);
	inline std::vector<std::vector<int>> getDownRightSquares(int x, int y);


	//For King
	inline std::vector < std::vector<int>> getKingSquares(int x, int y);


	//For Pawn (We include Up-Left & Up-Right in case there is a piece to capture there.
	inline std::vector<std::vector<int>> getPawnUPSquares(int x, int y, bool fm , PLAYER player);
	inline std::vector<std::vector<int>> getPawnUPLeftSquares(int x, int y, PLAYER player);
	inline std::vector<std::vector<int>> getPawnUPRightSquares(int x, int y, PLAYER player);


	//For Knight
	inline std::vector < std::vector<int>> getKnightSquares(int x, int y);


};




/////////////////////////////////////////////////////////////
////////////IMPLEMENTATION OF DIRECTION FUNCTIONS////////////
/////////////////////////////////////////////////////////////



std::vector<std::vector<int>> Piece::getUpSquares(int x, int y)
{
	std::vector<std::vector<int>> vec;

	for (int i = x; i <= 7; i++)
	{
		vec.push_back({ i , y });
	}
	return vec;

}


std::vector<std::vector<int>> Piece::getDownSquares(int x, int y)
{
	std::vector<std::vector<int>> vec;

	for (int i = x; i >= 0; i--)
	{
		vec.push_back({ i , y });
	}

	return vec;

}


std::vector<std::vector<int>> Piece::getRightSquares(int x, int y)
{
	std::vector<std::vector<int>> vec;

	for (int i = y; i >= 0; i--)
	{
		vec.push_back({ x , i });
	}

	return vec;

}


std::vector<std::vector<int>> Piece::getLeftSquares(int x, int y)
{
	std::vector<std::vector<int>> vec;

	for (int i = y; i <= 7; i++)
	{
		vec.push_back({ x , i });
	}

	return vec;

}


std::vector<std::vector<int>> Piece::getUpLeftSquares(int x, int y)
{
	std::vector<std::vector<int>> vec;

	for (int i = x, j = y; i >= 0 && j >= 0; i--, j--)
	{
		vec.push_back({ i , j });
	}

	return vec;

}


std::vector<std::vector<int>> Piece::getUpRightSquares(int x, int y)
{
	std::vector<std::vector<int>> vec;

	for (int i = x, j = y; i >= 0 && j <= 7; i--, j++)
	{
		vec.push_back({ i , j });
	}

	return vec;

}


std::vector<std::vector<int>> Piece::getDownLeftSquares(int x, int y)
{
	std::vector<std::vector<int>> vec;

	for (int i = x, j = y; i <= 7 && j >= 0; i++, j--)
	{
		vec.push_back({ i , j });
	}


	return vec;

}


std::vector<std::vector<int>> Piece::getDownRightSquares(int x, int y)
{
	std::vector<std::vector<int>> vec;

	for (int i = x, j = y; i <= 7 && j <= 7; i++, j++)
	{
		vec.push_back({ i , j });
	}

	return vec;

}


std::vector<std::vector<int>> Piece::getKingSquares(int x, int y)
{
	std::vector<std::vector<int>> vec;
	int i = x;
	int j = y;

	if (++i <= 7 && --j >= 0) vec.push_back({ i , j });
	i = x; j = y;
	if (++i <= 7 && ++j <= 7) vec.push_back({ i , j });
	i = x; j = y;
	if (--i >= 0 && --j >= 0) vec.push_back({ i , j });
	i = x; j = y;
	if (--i >= 0 && ++j <= 7) vec.push_back({ i , j });
	i = x; j = y;
	if (++j <= 7) vec.push_back({ i , j });
	i = x; j = y;
	if (--j >= 0) vec.push_back({ i , j });
	i = x; j = y;
	if (--i >= 0) vec.push_back({ i , j });
	i = x; j = y;
	if (++i <= 7) vec.push_back({ i , j });

	return vec;

}


std::vector<std::vector<int>> Piece::getPawnUPSquares(int x, int y, bool fm , PLAYER player)
{
	std::vector<std::vector<int>> vec;
	if (fm)
	{
		if (player)
		{
			vec.push_back({ --x , y });
			vec.push_back({ --x , y });
		}
		if (!player)
		{
			vec.push_back({ ++x , y });
			vec.push_back({ ++x , y });
		}
	}
	else
	{
		if (player)
		{
			vec.push_back({ --x , y });
		}
		if (!player)
		{
			vec.push_back({ ++x , y });
		}
	}

	return vec;
}


std::vector<std::vector<int>> Piece::getPawnUPLeftSquares(int x, int y, PLAYER player)
{
	std::vector<std::vector<int>> vec;

	if (player && y!=0)
	{	
		vec.push_back({ --x , --y });
	}
	if (!player && y!=0)
	{
		vec.push_back({ ++x , --y });
	}
	
	return vec;
}


std::vector<std::vector<int>> Piece::getPawnUPRightSquares(int x, int y, PLAYER player )
{
	std::vector<std::vector<int>> vec;
	if (player && y!=7)
	{
		vec.push_back({ --x , ++y });
	}
	if (!player && y!=7)
	{
		vec.push_back({ ++x , ++y });
	}
	

	return vec;
}


std::vector < std::vector<int>> Piece::getKnightSquares(int x, int y)
{
	std::vector<std::vector<int>> vec;
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (abs(i - x) * abs(y - j) == 2)
			{
				vec.push_back({ i , j });
			}
		}
	}
	return vec;
}
