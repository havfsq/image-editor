#pragma once

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#include "ImageEditorState.h"

class ImageEditorStateMainMenu
	: public ImageEditorState
{
public:
	ImageEditorStateMainMenu(ImageEditor* imageEditor);
	~ImageEditorStateMainMenu();

	virtual void update(const float dt);
	virtual void draw(const float dt);
	virtual void handleInput();

private:
	sf::View view;

	char imagePath[255] = " ";

	void initGui();

	void loadEditor();
};

