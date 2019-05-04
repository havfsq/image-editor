#include "StateEditor.h"
// Файловый браузер
#include "filedialog/FileDialog.h"
#include "filebrowser/filebrowser.h"

StateEditor::StateEditor(ImageEditor* imageEditor, const char* imageFilePath)
{
	this->imageEditor = imageEditor;

	//this->imageFilePath = "C:\\Users\\havfsq\\Desktop\\image-editor\\Debug\\media\\af2.gif";
	this->imageFilePath = imageFilePath;

	sf::Vector2f pos = sf::Vector2f(this->imageEditor->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	// Установка размеров окна редактора
	MainGuiWindowSize = ImVec2(
		this->imageEditor->window.getSize().x+2, 
		this->imageEditor->window.getSize().y);

	this->imageManager = new ImageManager();
	this->imageManager->loadAnimationImage(this->imageFilePath.c_str());

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
		if (ImGui::BeginMenu(u8"Импорт"))
		{
			if (ImGui::MenuItem(u8"Открыть Картинку"))
			{
				this->window_fileIO_visible = true;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu(u8"Экспорт"))
		{
			if (ImGui::MenuItem(u8"Сохранить gif"))
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
			static float initial_spacingx1 = 260.f; 
			if (initial_spacingx1) ImGui::SetColumnWidth(0, initial_spacingx1), initial_spacingx1 = 0;
			static float initial_spacingx2 = ImGui::GetWindowHeight();
			if (initial_spacingx2) ImGui::SetColumnWidth(1, initial_spacingx2), initial_spacingx2 = 0;

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
			
			// Кропки Запуска/Остановки Анимации
			if (ImGui::Button(u8"PLAY", button_sz))
			{
				this->playAnimation = true;
			}ImGui::SameLine();
			if (ImGui::Button(u8"||###Pause", button_sz))
			{
				this->playAnimation = false;
			}
			// Кнопки Удилание/Добавления Текстуры
			if (ImGui::Button(u8"X", button_sz))
			{
				this->imageManager->eraseTexture(this->imageManager->nextFrame(-1));
			}ImGui::SameLine();
			if (ImGui::Button(u8"+", button_sz))
			{
				this->imageManager->eraseTexture(this->imageManager->nextFrame(-1));
			}

			// Выводим список Кадров, с возможностью их Выбора
			ImGui::Text(u8"Кадры:");
			ImGuiStyle& style = ImGui::GetStyle();
			int buttons_count = this->imageManager->numberOfFrames;
			float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 1.f));
			window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
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
				if (ImGui::ImageButton(this->imageManager->getTextureByNumber(n),
					button_sz,
					4,
					sf::Color::Transparent,
					sf::Color::White))
				{
					this->imageManager->nextFrame(n);
				}

				if (isBordered) ImGui::PopStyleVar();
				// Our buttons are both drag sources and drag targets here!
				if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
				{
					// Контейнер для информации о перемещаемой кнопке
					ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));        
					ImGui::Image(this->imageManager->getTextureByNumber(n), button_sz);

					ImGui::EndDragDropSource();
				}
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
					{
						IM_ASSERT(payload->DataSize == sizeof(int));
						int payload_n = *(const int*)payload->Data;
						// Свапаем кнопка
						this->imageManager->swapTextures(n, payload_n);
					}
					ImGui::EndDragDropTarget();
				}
				float last_button_x2 = ImGui::GetItemRectMax().x;
				// Перенос Кнопок на новую сроку, если "не вмещается"
				float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x;
				if (n + 1 < buttons_count && next_button_x2 < window_visible_x2)
					ImGui::SameLine();
				ImGui::PopID();
			}
			ImGui::PopStyleColor(); // Обновляем стиль кнопок


			ImGui::NextColumn();
		}

		ImGui::TextColored(ImVec4(0.8f, 1.0f, 0.4f, 1.0f), u8"инф:");
		ImGui::Text(u8"Прошло с пред обновления = %f", this->elapsedAfterFrame);
		if (ImGui::ImageButton(this->imageManager->getTextureByCurFrame(), ImVec2(100, 100)))
		{
			this->imageManager->saveAnitaionToFile("bwgif.gif", 100);
		}
	}
	ImGui::End();

	// Файловый менеджер
	static imgui_ext::file_browser_modal fileBrowser(u8"Загрузка изображения");
	if (fileBrowser.render(this->window_fileIO_visible, browserPath))
	{
		imageFilePath = browserPath;
		this->imageManager->loadAnimationImage(this->imageFilePath.c_str());
		//this->imageManager->loadAnimationImage("C:\\Users\\havfsq\\Desktop\\image-editor\\Debug\\media\\af2.gif");
	}
}
