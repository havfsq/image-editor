#include "imageEditor.h"

#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "ImageEditorState.h"

ImageEditor::ImageEditor()
{
	this->loadFonts();
	this->loadStylesheets();

	this->window.create(sf::VideoMode(1280, 720), L"Редактор изображений", sf::Style::Close);
	this->window.setFramerateLimit(60);
}

ImageEditor::~ImageEditor()
{
	while (this->states.empty())
		popState();
}

void ImageEditor::pushState(ImageEditorState * state)
{
	this->states.push(state);

	return;
}

void ImageEditor::popState()
{
	delete this->states.top();
	this->states.pop();

	return;
}

void ImageEditor::changeState(ImageEditorState* state)
{
	if (!this->states.empty())
		popState();
	pushState(state);

	return;
}

ImageEditorState* ImageEditor::peekState()
{
	if (this->states.empty())
		return nullptr;
	return this->states.top();
}

void ImageEditor::mainLoop()
{
	sf::Clock clock;

	while (this->window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (this->peekState() == nullptr)
			continue;
		peekState()->handleInput();
		peekState()->update(dt);
		//this->window.clear();
		peekState()->draw(dt);
		this->window.display();
	}
}

// PRIVATE

void ImageEditor::loadFonts()
{
	sf::Font font;
	font.loadFromFile("media/font.ttf");
	this->fonts["main_font"] = font;

	return;
}

// Определение стилей GUI
void ImageEditor::loadStylesheets()
{
	

	return;
}