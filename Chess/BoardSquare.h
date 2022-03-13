#pragma once
#include "Piece.h"
#include <vector>
#include "defines.h"
#include "graphics.h"

class BoardSquare {
	Piece* p;
	float pos_x;  //position x on the canvas
	float pos_y;  //position y on the canvas
	int board_x;  //position x on the board (array)
	int board_y;  //position y on the board (array
	bool highlighted = 0; //when hovered upon
	bool active = 0; //when it is clicked upon
	bool legal_square = 0; //when a piece on the map has been clicked and this square is a legal move for him to go
public:
	BoardSquare(Piece* , float , float ,  int , int);
	~BoardSquare();

	//anything related with a piece on this particular square
	inline bool isThereAPiece() const{ return p!=nullptr ? 1 : 0; } //return true if there is a piece in that square , false if its not

	
	//Piece getters
	inline short getPiecePlayer() const{ return p->getPlayer(); }   //Get the player of the piece on that square (1 for white 0 for black)
	inline Piece* getPiece() const{ return p; }
	inline int getpieceID() { return p->getPieceID(); }

	
	//Piece setters
	inline void setPiece(Piece* piece) { p = piece; }
	inline void setPieceXY(float x, float y) { p->setXY(x , y); }   //Set the piece position
	inline void resetPieceXY() { p->setXY(pos_x, pos_y); }          //reset the piece to the center of that particular square
	inline void setPieceMoves() { p->addMoves(); }

	
	//removing a piece
	inline void removePiece() { p = nullptr; }                      //removePiece (for when we want to move it)
	inline void deletePiece() { delete p; }					        //deletePiece (for when we want to remove it from the board)


	//all legal moves for the piece in our square
	inline std::vector<std::vector<std::vector<int>>> legalSquaresPositions(int x, int y) { return p->legalMoves(x, y); } // returns a list with all the square positions on the board that are legal for this piece




	//getters
	inline float getposX() const{ return pos_x; }
	inline float getposY() const{ return pos_y; }
	inline bool isLegal() const { return legal_square; }
	inline int getBoardX() const { return board_x; }
	inline int getBoardY() const { return board_y; }

	//setters
	inline void setHighlighted(bool h) { highlighted = h; }
	inline void setActive(bool a) { active = a; }
	inline void setLegalMove(bool x) { legal_square = x; }




	//helpfull function to find the distance between two point
	inline bool contains(float x, float y) { return distance(x, y, pos_x, pos_y) < 50; }

	void draw();
	void update();
};