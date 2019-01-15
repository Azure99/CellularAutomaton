#include "stdafx.h"
#include "CASerializaer.h"

using namespace std;

CASerializaer::CASerializaer()
{
}


CASerializaer::~CASerializaer()
{
}

void CASerializaer::Serialize(BaseCA* ca)
{
	ofstream out("ca.txt");
	out << ca->CARule << ' ';
	out << ca->DeadRate << ' ';
	out << ca->Frame << ' ';
	out << ca->Height << ' ';
	out << ca->LiveRate << ' ';
	out << ca->LowerLine << ' ';
	out << ca->NowLive << ' ';
	out << ca->UpperLine << ' ';
	out << ca->Width << ' ';

	int mapLen = ca->Height * ca->Width;
	for (int i = 0; i < mapLen; i++)
	{
		out << ca->map[i] << ' ';
	}
}

BaseCA* CASerializaer::DeSerialize()
{
	int frame, nowlive;
	ifstream in("ca.txt");
	RunOptions options;
	in >> options.Rule;
	in >> options.DeadRate;
	in >> frame;
	in >> options.Height;
	in >> options.LiveRate;
	in >> options.LowerLine;
	in >> nowlive;
	in >> options.UpperLine;
	in >> options.Width;

	options.FillMap = false;

	BaseCA* ca = CAFactory::Create(options);
	ca->Frame = frame;
	ca->NowLive = frame;

	int mapLen = ca->Height * ca->Width;
	for (int i = 0; i < mapLen; i++)
	{
		in >> ca->map[i];
	}

	return ca;
}