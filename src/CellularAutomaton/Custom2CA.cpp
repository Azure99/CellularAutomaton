#include "stdafx.h"
#include "Custom2CA.h"


Custom2CA::Custom2CA(int width, int height) : BaseCA(width, height)
{

}


Custom2CA::~Custom2CA()
{

}

bool Custom2CA::CheckCell(int x, int y)
{
	bool live = GetCell(x, y);
	int count = CountAround(x, y);

	if (live && count < LowerLine || count > UpperLine)
	{
		if ((rand() % 100) < DeadRate)
		{
			return false;
		}

		return true;
	}

	if (!live && count > LowerLine && count < UpperLine)
	{
		if ((rand() % 100) < LiveRate)
		{
			return true;
		}

		return false;
	}

	return live;
}