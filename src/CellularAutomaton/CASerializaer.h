#pragma once
#include "BaseCA.h"
#include "CAFactory.h"
#include "RunOptions.h"
#include <iostream>
#include <fstream>

class CASerializaer
{
public:
	CASerializaer();
	~CASerializaer();
public:
	static void Serialize(BaseCA* ca);
	static BaseCA* DeSerialize();
};

