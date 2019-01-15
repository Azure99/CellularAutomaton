#pragma once
#include "BaseCA.h"
class ClassicalCA : public BaseCA
{
public:
	ClassicalCA(int width, int height);
	~ClassicalCA();
public:
	bool CheckCell(int x, int y) override;
};

