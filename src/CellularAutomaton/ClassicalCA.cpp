#include "stdafx.h"
#include "ClassicalCA.h"

ClassicalCA::ClassicalCA(int width, int height) : BaseCA(width, height)
{
}


ClassicalCA::~ClassicalCA()
{
}

bool ClassicalCA::CheckCell(int x, int y)
{
	bool live = GetCell(x, y);
	int count = CountAround(x, y);
	if (live)
	{
		return (count == 2 || count == 3);
	}
	else
	{
		return (count == 3);
	}
}