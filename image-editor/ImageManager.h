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
	// * true - Все Ок, false - Ошибка загрузки
	bool loadAnimationImage(const char* filePath);

	bool saveAnitaionToFile(const char* filePath, int delay);

	// ПЕРЕНЕСТИ
	// Количество фреймов (картинок) в Полученном Изображении
	UINT32 numberOfFrames;
	// Задержка перед Обновлением Анимации
	float animationDeley; 
	
	// Обновление номера Текущего фрейма 
	float nextFrame();
	// Обновление номера Текущего фрейма по номеру
	float nextFrame(UINT32 number);

	// Возвращает текстуру соответсвующую введенному номеру
	sf::Texture& getTextureByNumber(int number);
	// Возвращает текстуру в порядке очереди
	// nextFrame() - Чтобы продвинуть очередь вперед
	// prevFrame() - Чтобы подвинуть очередь назад
	sf::Texture& getTextureByCurFrame();

	// Своп текустур texN1 texN2 в Массиве текстур
	void swapTextures(int texN1, int texN2);
	// Удаление текстуры по ее номеру texN
	void eraseTexture(int texN);

private:
	// Массив картинок из файла
	std::vector <sf::Image*> images;
	// Массив текстур из массива картинок
	std::vector <sf::Texture*> textures;

	// Освобожнеие памяти массива картинок
	bool freeImages();

	// Номер текущего фрейма для вывода на экран
	float currentFrame;

	// Текстура картинки-РЕЗУЛЬТАТА
	sf::Texture imageTexture;
};

