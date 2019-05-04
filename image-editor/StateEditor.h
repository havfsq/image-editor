#pragma once

#include <string>
#include <string>

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#include "State.h"
#include "ImageManager.h"

class StateEditor
	: public State
{
public:
	StateEditor(ImageEditor* imageEditor, const char* imageFilePath);
	~StateEditor();

	virtual void update(const float dt);
	virtual void draw(const float dt);
	virtual void handleInput();

private:
	sf::View view;
	ImVec2 MainGuiWindowSize;

	// Пусть к изображению
	std::string imageFilePath;
	// Путь из файлового менеджера
	std::string browserPath;

	// Работа над выводом изображения:
	// Класс контроля изображений
	ImageManager* imageManager;
	float elapsedAfterFrame;
	bool playAnimation;

	// Открыть/Зарктыть Файловый браузер
	bool window_fileIO_visible = false;
	// Определение Интерфейса пользователя
	void initGui();
};

