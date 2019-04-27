#pragma once

#include <SFML/Graphics.hpp>

#include "ImageEditorState.h"

class ImageEditorStateMainMenu
	: public ImageEditorState
{
public:
	ImageEditorStateMainMenu(ImageEditor* imageEditor);
	~ImageEditorStateMainMenu();

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

private:
	sf::View view;

	void loadEditor();
};

