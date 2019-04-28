#pragma once

#include "imageEditor.h"

/**
* Виртуальный класс описывающий состояние программы
*/
class State
{
public:
	ImageEditor* imageEditor;

	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void handleInput() = 0;

};

