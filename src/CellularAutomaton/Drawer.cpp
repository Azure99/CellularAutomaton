#include "stdafx.h"
#include "Drawer.h"


Drawer::Drawer(CDC* dc)
{
	this->baseDC = dc;
}

Drawer::Drawer()
{

}


Drawer::~Drawer()
{

}

void Drawer::SetDC(CDC* dc)
{
	this->baseDC = dc;
}

void Drawer::Clear(CRect rect)
{
	CBrush whiteBrush;
	whiteBrush.CreateSolidBrush(RGB(255, 255, 255));

	this->baseDC->FillRect(rect, &whiteBrush);
}

void Drawer::DrawCell(bool* map, int width, int height)
{
	CDC dc;
	dc.CreateCompatibleDC(this->baseDC);
	CBitmap bufferBitmap;
	bufferBitmap.CreateCompatibleBitmap(this->baseDC, width * 4, height * 4);
	dc.SelectObject(bufferBitmap);

	CBrush whiteBrush, blackBrush;
	whiteBrush.CreateSolidBrush(RGB(255, 255, 255));
	blackBrush.CreateSolidBrush(RGB(0, 0, 0));
	dc.SelectObject(&whiteBrush);

	dc.Rectangle(0, 0, width * 4, height * 4);

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (map[y * width + x])
			{
				CRect rect(x * 4, y * 4, x * 4 + 3, y * 4 + 3);
				dc.FillRect(&rect, &blackBrush);
			}
		}
	}

	this->baseDC->BitBlt(0, 0, width * 4, height * 4, &dc, 0, 0, SRCCOPY);

	bufferBitmap.DeleteObject();
	dc.DeleteDC();
}

void Drawer::DrawOneCell(int x, int y, bool status)
{
	CRect rect(x * 4, y * 4, x * 4 + 3, y * 4 + 3);
	if (status)
	{
		CBrush brush;
		brush.CreateSolidBrush(RGB(0, 0, 0));
		baseDC->FillRect(&rect, &brush);
	}
	else
	{
		CBrush brush;
		brush.CreateSolidBrush(RGB(255, 255, 255));
		baseDC->FillRect(&rect, &brush);
	}
	
}
