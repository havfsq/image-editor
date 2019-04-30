#include "StateEditor.h"

StateEditor::StateEditor(ImageEditor* imageEditor)
{
	this->imageEditor = imageEditor;

	sf::Vector2f pos = sf::Vector2f(this->imageEditor->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	MainGuiWindowSize = ImVec2(1280, 720);

	imageManager = new ImageManager();
}


StateEditor::~StateEditor()
{
}

void StateEditor::update(const float dt)
{
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
			MainGuiWindowSize = ImVec2(float(event.size.width), float(event.size.height));
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

void StateEditor::gifTestProc()
{
	char fpath[255] = "C:\\Users\\havfsq\\Desktop\\bald potato.gif";
	//this->gif = gd_open_gif(fpath);
}

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

	ImGui::SetNextWindowPos(ImVec2(0, 20));
	ImGui::SetNextWindowSize(MainGuiWindowSize);
	if (ImGui::Begin(u8"ТЕСТ", NULL, 1 | 1 << 1 | 1 << 3 | 32))
	{
		// Рразбивка Главного Окна на Колонки Таблицы
		{
			ImGui::Columns(3, "mixed");

			ImGui::Text("Hello");
			ImGui::Button("Banana");
			ImGui::NextColumn();

			ImGui::Text("ImGui");
			ImGui::Image(this->imageManager->getImageTexture());
			ImGui::NextColumn();

			ImGui::Text("Sailor");
			static float bar = 1.0f;
			ImGui::InputFloat("blue", &bar, 0.05f, 0, "%.3f");
			static int gifdelay = 100;
			ImGui::InputInt(u8"Длинна Кадра", &gifdelay, 10, 0);
			if (ImGui::Button(u8"PALY", ImVec2(60, 60)))
			{
				//
			}
			ImGui::SameLine();
			if (ImGui::Button(u8"PAUSE", ImVec2(60, 60)))
			{
				//
			}
			ImGui::NextColumn();

			ImGui::Columns(1);
		}
	}
	ImGui::End();
	
}
