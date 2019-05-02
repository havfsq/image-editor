#include "StateEditor.h"

// Файловый браузер
#include "filedialog/FileDialog.h"

StateEditor::StateEditor(ImageEditor* imageEditor)
{
	this->imageEditor = imageEditor;

	sf::Vector2f pos = sf::Vector2f(this->imageEditor->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	// Установка размеров окна редактора
	MainGuiWindowSize = ImVec2(
		this->imageEditor->window.getSize().x+2, 
		this->imageEditor->window.getSize().y);

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
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu(u8"Экспорт"))
		{
			if (ImGui::MenuItem(u8"Открыть Картинку"))
			{
				this->window_fileIO_visible = true;
			}
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

			// Размер кнопок
			ImVec2 button_sz(46, 46);

			// Ширина первой колонки таблицы
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
			static int test = 0;
			ImGui::InputInt(u8"test", &test, 10, 0);
			if (ImGui::Button(u8"PLAY", button_sz))
			{
				this->playAnimation = true;
			}
			ImGui::SameLine();
			if (ImGui::Button(u8"||###Pause", button_sz))
			{
				this->playAnimation = false;
			}

			// Выводим список Кадров, с возможностью их Выбора
			ImGui::Text(u8"Кадры:");
			ImGuiStyle& style = ImGui::GetStyle();
			int buttons_count = this->imageManager->numberOfFrames;
			float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
			for (int n = 0; n < buttons_count; n++)
			{
				ImGui::PushID(n);
				// Рамка вокург кнопки с текущим кадром
				bool isBordered = false;
				if (n == this->imageManager->nextFrame(-1))
				{
					ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 5.f);
					isBordered = true;
				}
				if (ImGui::Button("Box", button_sz))
				{
					//test = n;
					this->imageManager->nextFrame(n);
				}
				if (isBordered) ImGui::PopStyleVar();
				float last_button_x2 = ImGui::GetItemRectMax().x;
				// Перенос Кнопок на новую сроку, если "не вмещается"
				float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x;
				if (n + 1 < buttons_count && next_button_x2 < window_visible_x2)
					ImGui::SameLine();
				ImGui::PopID();
			}

			ImGui::NextColumn();
		}
	}
	ImGui::End();

	// ТЕСТ
	static std::vector<std::string> window_recent_files;
	// Файловый менеджер
	if (this->window_fileIO_visible)
	{
		std::string open_file;
		if (fileIOWindow(open_file, window_recent_files, "Open", { "*.usr", "*.*" }, true))
		{
			this->window_fileIO_visible = false;
			if (!open_file.empty())
			{
				window_recent_files.push_back(open_file);
				//readStuffFromFile(open_file);
			}
		}
	}
	
}
