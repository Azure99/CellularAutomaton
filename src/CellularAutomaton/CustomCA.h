#pragma once
#include "BaseCA.h"
class CustomCA : public BaseCA
{
public:
	CustomCA(int width, int height);
	~CustomCA();
public:
	bool CheckCell(int x, int y) override;
};

