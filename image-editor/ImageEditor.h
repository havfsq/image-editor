#pragma once

#include <stack>
#include <map>

#include <SFML/Graphics.hpp>

class ImageEditorState;

class ImageEditor
{
public:
	ImageEditor();
	~ImageEditor();

	std::stack<ImageEditorState*> states;

	sf::RenderWindow window;

	std::map<std::string, sf::Font> fonts;

	void pushState(ImageEditorState* state);
	void popState();
	void changeState(ImageEditorState* state);
	ImageEditorState* peekState();

	void mainLoop();

private:
	void loadStylesheets();
	void loadFonts();

};

