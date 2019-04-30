#include "ImageManager.h"

ImageManager::ImageManager()
{
	//TO DO МЕХАНИЗМ ЗАРУГЗКИ КАРТИНКИ Из МЕНЮ...
	this->imageSource.loadFromFile("C:\\Users\\havfsq\\Desktop\\test.jpg");
	this->imageResult = this->imageSource;
	this->imageTexture.loadFromImage(imageResult);
}

ImageManager::~ImageManager()
{
}

sf::Image & ImageManager::getImage()
{
	return this->imageResult;
}

sf::Texture & ImageManager::getImageTexture()
{
	return this->imageTexture;
}
