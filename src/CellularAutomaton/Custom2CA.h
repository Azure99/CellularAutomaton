#pragma once
#include "BaseCA.h"
class Custom2CA : public BaseCA
{
public:
	Custom2CA(int width, int height);
	~Custom2CA();
public:
	bool CheckCell(int x, int y) override;
};
