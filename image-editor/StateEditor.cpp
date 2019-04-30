#include "StateEditor.h"

StateEditor::StateEditor(ImageEditor* imageEditor)
{
	this->imageEditor = imageEditor;

	sf::Vector2f pos = sf::Vector2f(this->imageEditor->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	MainGuiWindowSize = ImVec2(1282, 720);

	this->imageManager = new ImageManager();
	this->imageManager->loadAnimationImage("test");

	this->elapsedAfterFrame = 0;
	this->playAnimation = true;
}


StateEditor::~StateEditor()
{
}

void StateEditor::update(const float dt)
{
	if (playAnimation)
	{
		this->elapsedAfterFrame += dt;
		if (elapsedAfterFrame > this->imageManager->animationDeley)
		{
			this->imageManager->nextFrame();
			this->elapsedAfterFrame = 0;
		}
	}

	initGui();
}

void StateEditor::draw(const float dt)
{
	this->imageEditor->window.setView(this->view);

	return;
}

void StateEditor::handleInput()
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
		case sf::Event::Resized:
		{
			MainGuiWindowSize = ImVec2(float(event.size.width+2), float(event.size.height));
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

void StateEditor::initGui()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			//ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			//ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::SetNextWindowPos(ImVec2(-1, 17));
	ImGui::SetNextWindowSize(MainGuiWindowSize);
	if (ImGui::Begin(u8"ТЕСТ", NULL, 1 | 1 << 1 | 1 << 3 | 32))
	{
		// Рразбивка Главного Окна на Колонки Таблицы
		{
			ImGui::Columns(3, "mixed");

			static float initial_spacing = 250.f;
			if (initial_spacing) ImGui::SetColumnWidth(0, initial_spacing), initial_spacing = 0;

			ImGui::Text("Hello");
			ImGui::Button("Banana");
			ImGui::NextColumn();

			ImGui::Text("----GIF----");
			//ImGui::Image(this->imageManager->getTextureByNumber(this->imageManager->nextFrame()));
			ImGui::Image(this->imageManager->getTextureByCurFrame());
			ImGui::NextColumn();

			ImGui::Text("Sailor");
			static float bar = 1.0f;
			ImGui::InputFloat("blue", &bar, 0.05f, 0, "%.3f");
			ImGui::SliderFloat(u8"Длина Кадра", &this->imageManager->animationDeley, 0.0f, 0.5f);
			ImGui::InputFloat(u8"Прошло с пред обновления", &this->elapsedAfterFrame, 10, 0);
			if (ImGui::Button(u8"PLAY", ImVec2(46, 46)))
			{
				this->playAnimation = true;
			}
			ImGui::SameLine();
			if (ImGui::Button(u8"||###Pause", ImVec2(46, 46)))
			{
				this->playAnimation = false;
			}
			ImGui::NextColumn();
		}
	}
	ImGui::End();
	
}
