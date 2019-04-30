#include "StateMainMenu.h"

#include "StateEditor.h"

StateMainMenu::StateMainMenu(ImageEditor* imageEditor)
{
	this->imageEditor = imageEditor;
	
	sf::Vector2f pos = sf::Vector2f(this->imageEditor->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
}

StateMainMenu::~StateMainMenu()
{

}

void StateMainMenu::update(const float dt)
{
	initGui();
}

void StateMainMenu::draw(const float dt)
{
	this->imageEditor->window.setView(this->view);

	return;
}

void StateMainMenu::handleInput()
{
	sf::Event event;

	sf::Vector2f mousePos = this->imageEditor->window.mapPixelToCoords(
		sf::Mouse::getPosition(this->imageEditor->window), this->view);

	while (this->imageEditor->window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

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

void StateMainMenu::initGui()
{
	ImGui::SetNextWindowSize(ImVec2(500, 200));
	ImGui::SetNextWindowPosCenter();
	ImGui::Begin(u8"Загрузка Изображения", NULL, 1 << 1 | 1 << 3 | 32);
	ImGui::InputText(u8"Путь к Изображению", this->imagePath, 255);
	if (ImGui::Button(u8"Загрузить в Редактор"))
	{
		this->loadEditor();
	}
	ImGui::End();
}

void StateMainMenu::loadEditor()
{
	this->imageEditor->pushState(new StateEditor(this->imageEditor));
}
