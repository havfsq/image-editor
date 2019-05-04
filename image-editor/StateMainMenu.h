#pragma once

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#include "State.h"

class StateMainMenu
	: public State
{
public:
	StateMainMenu(ImageEditor* imageEditor);
	~StateMainMenu();

	virtual void update(const float dt);
	virtual void draw(const float dt);
	virtual void handleInput();

private:
	sf::View view;

	// Путь из файлового менеджера
	std::string browserPath;
	// Путь к картинке
	char imagePath[255] = " ";

	void initGui();

	void loadEditor();
};

