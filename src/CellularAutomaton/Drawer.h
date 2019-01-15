#pragma once
class Drawer
{
public:
	Drawer();
	Drawer(CDC* dc);
	~Drawer();
public:
	void SetDC(CDC* dc);
	void DrawCell(bool* map, int width, int height);
	void DrawOneCell(int x, int y, bool status);
	void Clear(CRect rect);
private:
	CDC* baseDC;
private:
	const COLORREF LIVECOLOR = RGB(0, 0, 0);
};