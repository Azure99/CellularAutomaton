#pragma once
class BaseCA
{
public:
	BaseCA(int width, int height);
	~BaseCA();
	void SetCell(int x, int y, bool status);
	bool GetCell(int x, int y);
	void FillArea(int x1, int y1, int x2, int y2);
	void FillArea();
	void NextFrame();
public:
	int CARule = 0;
	int UpperLine = 6;
	int DeadRate = 100;
	int LowerLine = 2;
	int LiveRate = 100;
	int Width = 100;
	int Height = 100;
public:
	bool* map;
	int NowLive = 0;
	int Frame = 0;
private:
	bool* mapTemp;
protected:
	void SetTempCell(int x, int y, bool status);
	bool GetTempCell(int x, int y);
	int CountAround(int x, int y);
	virtual bool CheckCell(int x, int y) = 0;
};

