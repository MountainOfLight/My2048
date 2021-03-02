#pragma once
#include "My2048.h"
class GUIsettings
{
protected:
	CRect rect_2048wnd;
	CRect rect_title;
	CRect rect_menuitem;
	CRect rect_menuitem_newgame;
	CRect rect_menuitem_loadgame;
	CRect rect_menuitem_exitgame;
	CRect rect_button_restart;
	CRect rect_button_menu;
	CRect rect_score;

	CPoint nodes[5][5];

	CFont font_title;
	CFont font_menuitem;
	CFont font_button;
	CFont font_lattice;
	CFont font_score;

	COLORREF color_background;
	COLORREF color_title_background;
	COLORREF color_title_text;
	COLORREF color_menuitem;
	COLORREF color_menuitem_highlighted;
	COLORREF color_frame;
	COLORREF color_lattice;
	COLORREF color_button_background;
	COLORREF color_button_text;
	COLORREF color_button_text_highlighted;
	COLORREF color_score_background;
	COLORREF color_score_text;
	COLORREF color_2_background;
	COLORREF color_2_text;
	COLORREF color_4_background;
	COLORREF color_4_text;
	COLORREF color_8_background;
	COLORREF color_8_text;
	COLORREF color_16_background;
	COLORREF color_16_text;
	COLORREF color_32_background;
	COLORREF color_32_text;
	COLORREF color_64_background;
	COLORREF color_64_text;
	COLORREF color_128_background;
	COLORREF color_128_text;
	COLORREF color_256_background;
	COLORREF color_256_text;
	COLORREF color_512_background;
	COLORREF color_512_text;
	COLORREF color_1024_background;
	COLORREF color_1024_text;
	COLORREF color_2048_background;
	COLORREF color_2048_text;

	CPen pen_frame;
public:
	GUIsettings();
	virtual ~GUIsettings();

	friend class CMy2048Doc;
	friend class CMy2048View;
};

