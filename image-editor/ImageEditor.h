#pragma once

#include <stack>
#include <map>

#include <SFML/Graphics.hpp>

class State;

class ImageEditor
{
public:
	ImageEditor();
	~ImageEditor();

	std::stack<State*> states;

	sf::RenderWindow window;

	std::map<std::string, sf::Font> fonts;

	void pushState(State* state);
	void popState();
	void changeState(State* state);
	State* peekState();

	void mainLoop();

private:
	void loadStylesheets();
	void loadFonts();

};

