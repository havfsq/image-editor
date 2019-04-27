#include "ImageEditorStateMainMenu.h"



ImageEditorStateMainMenu::ImageEditorStateMainMenu(ImageEditor* imageEditor)
{
	this->imageEditor = imageEditor;
	
	sf::Vector2f pos = sf::Vector2f(this->imageEditor->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
}

ImageEditorStateMainMenu::~ImageEditorStateMainMenu()
{
}

void ImageEditorStateMainMenu::draw(const float dt)
{
	this->imageEditor->window.setView(this->view);

	this->imageEditor->window.clear(sf::Color(50, 50, 50));

	return;
}

void ImageEditorStateMainMenu::update(const float dt)
{
	//
}

void ImageEditorStateMainMenu::handleInput()
{
	sf::Event event;

	sf::Vector2f mousePos = this->imageEditor->window.mapPixelToCoords(
		sf::Mouse::getPosition(this->imageEditor->window), this->view);

	while (this->imageEditor->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			this->imageEditor->window.close();
			break;
		}
		case sf::Event::MouseMoved:
		{
			// Движение мыши
		}
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{

			}
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape)
				this->imageEditor->window.close();
			break;
		}
		default:
			break;
		}
	}

	return;
}

// PRIVATE

void ImageEditorStateMainMenu::loadEditor()
{
	// LOAD EDITOR
}