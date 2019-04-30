#pragma once

#include <SFML/Graphics.hpp>

#include "gifproc/gifdec.h"

// Управление Картинками для Редактора
class ImageManager
{
public:
	ImageManager();
	~ImageManager();

	sf::Image& getImage();
	sf::Texture& getImageTexture();

private:
	// Хранилище для Гифки
	gd_GIF *gif; 

	// Картинка полсе приминения фильтров (Результат)
	sf::Image imageResult;
	// Картинка до приминения фильтров (Оригинальная)
	sf::Image imageSource;

	// Текстура картинки-РЕЗУЛЬТАТА
	sf::Texture imageTexture;
};

