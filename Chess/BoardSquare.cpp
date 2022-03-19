#include "BoardSquare.h"

BoardSquare::BoardSquare(Piece* p, float pos_x, float pos_y , int board_x , int board_y) : p(p), pos_x(pos_x), pos_y(pos_y) , board_x(board_x) , board_y(board_y) {}



BoardSquare::~BoardSquare()
{
	if(p) delete p;
}






void BoardSquare::draw()
{
	//draw the piece if it exists
	if(p != nullptr) p->draw();

	float is_highlighted = 1.0f * highlighted;
	float is_active = 1.0f * active;
	float is_legal = 1.0f * legal_square;
	

	//the color when the mouse hover over the particular square
	graphics::Brush br;
	br.fill_color[0] = 0.1f * is_highlighted;
	br.fill_color[1] = 0.9f * is_highlighted;
	br.fill_color[2] = 0.2f * is_highlighted;
	br.fill_opacity = 0.3f * is_highlighted;
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x , pos_y , 100, 100, br);

	
	//the color if the square is active
	br.fill_color[0] = 0.1f * is_active;
	br.fill_color[1] = 0.3f * is_active;
	br.fill_color[2] = 1.0f * is_active;
	br.fill_opacity = 0.3f * is_active;
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 100, 100, br);


	//the color if the square is legal for a piece to go to
	br.fill_color[0] = 0.1f * is_legal;
	br.fill_color[1] = 0.1f * is_legal;
	br.fill_color[2] = 0.3f * is_legal;
	br.fill_opacity = 0.3f * is_legal;
	br.outline_opacity = 0.0f;
	graphics::drawDisk(pos_x, pos_y, 20.0f , br);
}


