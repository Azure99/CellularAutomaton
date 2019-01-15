#include "stdafx.h"
#include "BaseCA.h"


BaseCA::BaseCA(int width, int height)
{
	Width = width;
	Height = height;

	int size = width * height;

	map = new bool[size];
	mapTemp = new bool[size];

	for (int i = 0; i < size; i++)
	{
		map[i] = false;
		mapTemp[i] = false;
	}
}

BaseCA::~BaseCA()
{
	delete[] map;
	delete[] mapTemp;
}

void BaseCA::NextFrame()
{
	NowLive = 0;
	Frame++;

	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			bool status = CheckCell(x, y);
			SetTempCell(x, y, status);
			if (status)
			{
				NowLive++;
			}
		}
	}

	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			SetCell(x, y, GetTempCell(x, y));
		}
	}
}

void BaseCA::FillArea(int x1, int y1, int x2, int y2)
{
	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			SetCell(x, y, true);
		}
	}
}

void BaseCA::FillArea()
{
	FillArea(1, 1, Width - 1, Height - 1);
}

void BaseCA::SetCell(int x, int y, bool status)
{
	map[y * Width + x] = status;
}

bool BaseCA::GetCell(int x, int y)
{
	return map[y * Width + x];
}

void BaseCA::SetTempCell(int x, int y, bool status)
{
	mapTemp[y * Width + x] = status;
}

bool BaseCA::GetTempCell(int x, int y)
{
	return mapTemp[y * Width + x];
}

int BaseCA::CountAround(int x, int y)
{
	int count = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int i2 = -1; i2 <= 1; i2++)
		{
			if (i == 0 && i2 == 0)
			{
				continue;
			}

			int newX = x + i;
			int newY = y + i2;

			if (newX >= 0 && newX < Width && newY >= 0 && newY < Height)
			{
				if (GetCell(newX, newY))
				{
					count++;
				}
			}
		}
	}

	return count;
}