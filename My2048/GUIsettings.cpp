#include "stdafx.h"
#include "GUIsettings.h"


GUIsettings::GUIsettings()
{
	rect_2048wnd = CRect(0, 0, theApp.rect_2048wnd.Width(), theApp.rect_2048wnd.Height());
	rect_menuitem = CRect(0, 0, 200, 40);
	int title_width = 300, title_height = 100;
	rect_title = CRect((rect_2048wnd.Width() - title_width) / 2, 50, (rect_2048wnd.Width() + title_width) / 2, 50 + title_height);
	CPoint point_topleft((rect_2048wnd.Width() - rect_menuitem.Width()) / 2, 200);
	CPoint point_current = point_topleft;
	int interval = (int)(1.5*rect_menuitem.Height());
	rect_menuitem_newgame = CRect(point_current.x, point_current.y, point_current.x + rect_menuitem.Width(), point_current.y + rect_menuitem.Height());
	point_current.y += interval;
	rect_menuitem_loadgame = CRect(point_current.x, point_current.y, point_current.x + rect_menuitem.Width(), point_current.y + rect_menuitem.Height());
	point_current.y += interval;
	rect_menuitem_exitgame = CRect(point_current.x, point_current.y, point_current.x + rect_menuitem.Width(), point_current.y + rect_menuitem.Height());
	point_current.y += interval;
	rect_button_restart = CRect(340, 30, 400, 70);
	rect_button_menu = CRect(420, 30, 480, 70);
	rect_score = CRect(160, 30, 320, 70);

	int resolutionX = rect_2048wnd.Width(), resolutionY = rect_2048wnd.Height();
	interval = (int)(resolutionX / 8);
	int frame_top = 100;
	int coordinatesX[] = { (int)(resolutionX / 2) - 2 * interval, (int)(resolutionX / 2) - 1 * interval, (int)(resolutionX / 2), (int)(resolutionX / 2) + 1 * interval, (int)(resolutionX / 2) + 2 * interval };
	int coordinatesY[] = { frame_top, frame_top + 1 * interval, frame_top + 2 * interval, frame_top + 3 * interval, frame_top + 4 * interval };
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			nodes[i][j].x = coordinatesX[i];
			nodes[i][j].y = coordinatesY[j];
		}
	}

	font_title.CreateFontW(80, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Arial Black"));
	font_menuitem.CreateFontW(30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("ºÚÌå"));
	font_button.CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Arial"));
	font_lattice.CreateFontW(40, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Arial Black"));
	font_score.CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Arial"));

	color_background = RGB(251, 248, 237);
	color_title_background = RGB(149, 118, 94);
	color_title_text = RGB(250, 246, 241);
	color_menuitem = RGB(120, 107, 94);
	color_menuitem_highlighted = RGB(195, 171, 152);
	color_frame = RGB(195, 171, 152);
	color_lattice = RGB(211, 193, 174);
	color_button_background = RGB(195, 171, 152);
	color_button_text = RGB(242, 229, 211);
	color_button_text_highlighted = RGB(250, 246, 241);
	color_score_background = RGB(195, 171, 152);
	color_score_text = RGB(250, 246, 241);
	color_2_background = RGB(241, 229, 215);
	color_2_text = RGB(120, 107, 94);
	color_4_background = RGB(242, 225, 195);
	color_4_text = RGB(120, 107, 94);
	color_8_background = RGB(255, 173, 109);
	color_8_text = RGB(250, 246, 241);
	color_16_background = RGB(255, 141, 86);
	color_16_text = RGB(250, 246, 241);
	color_32_background = RGB(255, 113, 80);
	color_32_text = RGB(250, 246, 241);
	color_64_background = RGB(254, 82, 39);
	color_64_text = RGB(250, 246, 241);
	color_128_background = RGB(246, 207, 105);
	color_128_text = RGB(250, 246, 241);
	color_256_background = RGB(247, 204, 90);
	color_256_text = RGB(250, 246, 241);
	color_512_background = RGB(247, 200, 76);
	color_512_text = RGB(250, 246, 241);
	color_1024_background = RGB(248, 196, 63);
	color_1024_text = RGB(250, 246, 241);
	color_2048_background = RGB(236, 196, 0);
	color_2048_text = RGB(250, 246, 241);

	pen_frame.CreatePen(PS_SOLID, 5, color_frame);
}


GUIsettings::~GUIsettings()
{
}
