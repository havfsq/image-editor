#pragma once

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#include "State.h"

class StateEditor
	: public State
{
public:
	StateEditor(ImageEditor* imageEditor);
	~StateEditor();

	virtual void update(const float dt);
	virtual void draw(const float dt);
	virtual void handleInput();

private:
	sf::View view;

	ImVec2 MainGuiWindowSize;
	void initGui();
};

