#pragma once
#include "graphics.h"
#include "defines.h"


class Button
{
	float pos_x;
	float pos_y;
	bool hover = 0;
	bool clicked = 0;
	std::string txt;
public:
	inline Button(float pos_x, float pos_y, std::string txt):pos_x(pos_x) , pos_y(pos_y) , txt(txt) {}

	void draw();
	inline void setHover(bool h) { hover = h; }
	inline void setClicked(bool c) { clicked = c; }


	inline float getX() { return pos_x; }
	inline float getY() { return pos_y; }
	inline bool getHover() { return hover; }

	inline bool contains(float x, float y) { return distance(x, y, pos_x, pos_y) < 50; }
};

inline void Button::draw()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	if (hover)
	{
		br.fill_color[0] = 0.7f;
		br.fill_color[1] = 0.4f;
		br.fill_color[2] = 0.8f;
	}
	
	graphics::drawRect(pos_x, pos_y, 200, 80, br);


		
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	graphics::setFont(ASSET_PATH + std::string("SupermercadoOne-Regular.ttf"));
	graphics::drawText(pos_x-20 , pos_y+10, 30.0f, txt, br);
	
}