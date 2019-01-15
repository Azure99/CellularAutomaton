#include "stdafx.h"
#include "CustomCA.h"


CustomCA::CustomCA(int width, int height) : BaseCA(width, height)
{

}


CustomCA::~CustomCA()
{

}

bool CustomCA::CheckCell(int x, int y)
{
	bool live = GetCell(x, y);
	int count = CountAround(x, y);

	if (live && count >= UpperLine)
	{
		if ((rand() % 100) <= DeadRate)
		{
			return false;
		}

		return true;
	}

	if (!live && count >= LowerLine)
	{
		if ((rand() % 100) <= LiveRate)
		{
			return true;
		}

		return false;
	}

	return live;
}