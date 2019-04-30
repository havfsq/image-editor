#include "ImageManager.h"

ImageManager::ImageManager()
{
	//TO DO МЕХАНИЗМ ЗАРУГЗКИ КАРТИНКИ Из МЕНЮ...
	//this->imageSource.loadFromFile("C:\\Users\\havfsq\\Desktop\\test.jpg");
	//this->imageResult = this->imageSource;
	//this->imageTexture.loadFromImage(imageResult);
	this->currentFrame = 0;
}

ImageManager::~ImageManager()
{
}

// Загрузка Картинки с Анимацией (GIF/APNG/...)
int ImageManager::loadAnimationImage(const char* filePath)
{
	til::TIL_Init();

	// TO DO: ДОБАВИТЬ ЗАГРУЗКУ ИЗ ВВЕДЕННОГО ПУТИ	!!№!"№!"№!"№
	til::ImageGIF* gif = (til::ImageGIF*)til::TIL_Load(
		"media\\af.gif", 
		TIL_FILE_ADDWORKINGDIR | TIL_DEPTH_A8B8G8R8);

	// Количество фреймов (картинок) в полученной изображении
	this->numberOfFrames = gif->GetFrameCount();
	this->animationDeley = gif->GetDelay();
	// Подгоняет на галозок ***
	this->animationDeley *= 9.0f;

	// Ширина и высота изображения
	UINT32 width = gif->GetPitchX(1);
	UINT32 height = gif->GetPitchY(1);

	if (this->numberOfFrames == 0)
		return -1;

	// Загрузка фреймов из изображения в массив фреймов
	for (UINT32 i = 0; i < numberOfFrames; i++)
	{
		UINT8* pixels = (UINT8*)gif->GetPixels(i);
		this->images.push_back(new sf::Image());
		this->images[i]->create(width, height, pixels);
	}
	// Преобразование полученных фреймов в Текстуры
	for (UINT32 i = 0; i < images.size(); i++)
	{
		this->textures.push_back(new sf::Texture());
		this->textures[i]->loadFromImage(*this->images[i]);
	}

	til::TIL_ShutDown();
	
	return 0;
}

sf::Image & ImageManager::getImage()
{
	return this->imageResult;
}

sf::Texture & ImageManager::getImageTexture()
{
	return this->imageTexture;
}

float ImageManager::nextFrame()
{
	if (this->currentFrame == this->numberOfFrames - 1)
	{
		this->currentFrame = 0;
		return this->currentFrame;
	}
	this->currentFrame++;
	return this->currentFrame;
}

sf::Texture & ImageManager::getTextureByNumber(int number)
{
	// Если номер "Корректный", возвращаем нужную текстуру
	if (number > 0 && number < this->numberOfFrames)
	{
		return *this->textures[number];
	}
	// Иначе возвращаем самую первую тестуру ***
	else
		return *this->textures[0];

}

sf::Texture & ImageManager::getTextureByCurFrame()
{
	// Добавить проверку на провильность номера, есил понадобится
	return *this->textures[this->currentFrame];
}
