#pragma once

const int CA_CLASSICAL = 0;
const int CA_CUSTOM = 1;
const int CA_CUSTOM2 = 2;

struct RunOptions
{
	int Rule = CA_CLASSICAL;
	bool FillMap = false;
	int Width = 200;
	int Height = 200;
	int UpperLine = 6;
	int LowerLine = 2;
	int LiveRate = 100;
	int DeadRate = 100;
	int Interval = 100;
};