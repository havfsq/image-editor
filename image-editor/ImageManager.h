#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include "TinyImageLoader.h"
#include "TILImageGIF.h"

// Управление Картинками для Редактора
class ImageManager
{
public:
	ImageManager();
	~ImageManager();

	// * Загрузка Картинки с Анимацией (GIF/APNG/...)
	// * 0 - Все Ок, -1 - Ошибка загрузки
	int loadAnimationImage(const char* filePath);

	sf::Image& getImage();
	sf::Texture& getImageTexture();

	// ПЕРЕНЕСТИ
	// Количество фреймов (картинок) в Полученном Изображении
	UINT32 numberOfFrames;
	// Задержка перед Обновлением Анимации
	float animationDeley; 
	
	// Обновление номера Текущего фрейма
	float nextFrame();

	// Возвращает текстуру соответсвующую введенному номеру
	sf::Texture& getTextureByNumber(int number);
	// Возвращает текстуру в порядке очереди
	// nextFrame() - Чтобы продвинуть очередь вперед
	// prevFrame() - Чтобы подвинуть очередь назад
	sf::Texture& getTextureByCurFrame();

private:
	// Картинка полсе приминения фильтров (Результат)
	sf::Image imageResult;
	// Картинка до приминения фильтров (Оригинальная)
	sf::Image imageSource;

	// Массив картинок из файла
	std::vector <sf::Image*> images;
	// Массив текстур из массива картинок
	std::vector <sf::Texture*> textures;

	// Номер текущего фрейма для вывода на экран
	float currentFrame;

	// Текстура картинки-РЕЗУЛЬТАТА
	sf::Texture imageTexture;
};

