#include "stdafx.h"
#include "CAFactory.h"


CAFactory::CAFactory()
{
}


CAFactory::~CAFactory()
{
}

BaseCA* CAFactory::Create(RunOptions options)
{
	BaseCA* ca = nullptr;

	if (options.Rule == CA_CLASSICAL)
	{
		ca = new ClassicalCA(options.Width, options.Height);
	}
	else if (options.Rule == CA_CUSTOM)
	{
		ca = new CustomCA(options.Width, options.Height);
	}
	else if (options.Rule == CA_CUSTOM2)
	{
		ca = new Custom2CA(options.Width, options.Height);
	}

	if (ca != nullptr)
	{
		ca->CARule = options.Rule;
		ca->DeadRate = options.DeadRate;
		ca->LiveRate = options.LiveRate;
		ca->LowerLine = options.LowerLine;
		ca->UpperLine = options.UpperLine;
		if (options.FillMap)
		{
			ca->FillArea();
		}
	}

	return ca;
}