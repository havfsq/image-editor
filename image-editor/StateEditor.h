#pragma once

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#include "State.h"
#include "ImageManager.h"

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

	ImageManager* imageManager;

	// TO DO: ПЕРЕНЕСТИ ЭТО \/ В ИМАДЖЕ МЕНЕДЖЕР!!!
	gd_GIF *gif;
	void gifTestProc();
	// TO DO: ПЕРЕНЕСТИ ЭТО /\ В ИМАДЖЕ МЕНЕДЖЕР!!!

	void initGui();
};

