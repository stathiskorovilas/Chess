#pragma once
#include "defines.h"
#include <string>
#include <vector>

/*
* This is the interface for our pieces
*/


class Piece 
{
	int piece_id;
	/*
	* 1: Rook
	* 2: Queen
	* 3: King
	* 4: Knight
	* 5: Pawn
	* 6: Bishop
	*/
	
	float pos_x;
	float pos_y;
	bool player; //0 if black 1 if white
	int moves = 0;


public:
	inline Piece(float pos_x, float pos_y , bool player , int piece_id): pos_x(pos_x) , pos_y(pos_y) , player(player) , piece_id(piece_id) {}

	//functions to be overriden by child classes
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual std::vector<std::vector<std::vector<int>>> legalMoves(int , int) = 0;

	//setters - add
	inline void setXY(float x, float y) { pos_x = x; pos_y = y; }
	inline void addMoves() { moves++; }


	//getters
	inline float getX() { return pos_x; }
	inline float getY() { return pos_y; }
	inline short getPlayer() { return player; }
	inline int getMoves() { return moves; }
	inline int getPieceID() { return piece_id; }


	//-------------------------DIRECTION FUNCTIONS-------------------------\\
	//Based on an initial position these functions show the squars available from any direction (these functions will be used from each piece diffrently)
	

	//All these functions return all the available points for a direction , given an initial x/y on the board (ex. board[1][0])
	inline std::vector<std::vector<int>> getUpSquares(int x, int y);
	inline std::vector<std::vector<int>> getDownSquares(int x, int y);
	inline std::vector<std::vector<int>> getRightSquares(int x, int y);
	inline std::vector<std::vector<int>> getLeftSquares(int x, int y);
	inline std::vector<std::vector<int>> getUpLeftSquares(int x, int y);
	inline std::vector<std::vector<int>> getUpRightSquares(int x, int y);
	inline std::vector<std::vector<int>> getDownLeftSquares(int x, int y);
	inline std::vector<std::vector<int>> getDownRightSquares(int x, int y);


	//all possible moves for King
	inline std::vector < std::vector<int>> getKingSquares(int x, int y);


	//all possible moves for pawn (fm indicates if its the pawn's first move or not) , we also need the player (black or white) because black pieces go down , white goes up
	inline std::vector<std::vector<int>> getPawnUPSquares(int x, int y, bool fm , bool player);
	inline std::vector<std::vector<int>> getPawnUPLeftSquares(int x, int y, bool player);
	inline std::vector<std::vector<int>> getPawnUPRightSquares(int x, int y, bool player);


	//all possible moves for Knight
	inline std::vector < std::vector<int>> getKnightSquares(int x, int y);


};


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


std::vector<std::vector<int>> Piece::getPawnUPSquares(int x, int y, bool fm , bool player)
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


std::vector<std::vector<int>> Piece::getPawnUPLeftSquares(int x, int y, bool player)
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


std::vector<std::vector<int>> Piece::getPawnUPRightSquares(int x, int y, bool player )
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
