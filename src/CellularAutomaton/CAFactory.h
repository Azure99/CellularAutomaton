#pragma once
#include "BaseCA.h"
#include "RunOptions.h"
#include "ClassicalCA.h"
#include "CustomCA.h"
#include "Custom2CA.h"

class CAFactory
{
public:
	CAFactory();
	~CAFactory();
public:
	static BaseCA* Create(RunOptions options);
};