#include "ImageManager.h"
#include "gifproc/gif.h"

ImageManager::ImageManager()
{
	//TO DO МЕХАНИЗМ ЗАРУГЗКИ КАРТИНКИ Из МЕНЮ...
	this->currentFrame = 0;
}

ImageManager::~ImageManager()
{
}

// Загрузка Картинки с Анимацией (GIF/APNG/...)
bool ImageManager::loadAnimationImage(const char * filePath)
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
		return false;

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
	
	// Освобожнеие памяти массива картинок
	this->freeImages();

	return true;
}

bool ImageManager::saveAnitaionToFile(const char * filePath, int delay)
{
	if (delay < 6)
		return false;

	int width = this->textures[0]->getSize().x;
	int height = this->textures[0]->getSize().y;

	// Объявление Обработчика Для созданиния Анимации
	GifWriter g;
	GifBegin(&g, filePath, width, height, delay);

	// Заполняем массив изображений "из" массива текстур
	for (int i = 0; i < this->textures.size(); i++)
	{
		//this->images.push_back(new sf::Image(this->textures[i]->copyToImage()));

		// Временное хранилище для изображения текущего фрейма
		sf::Image image = this->textures[i]->copyToImage();
		// Указатель на массив пикселей изображения
		uint8_t* imgPtr = (uint8_t*)image.getPixelsPtr();

		GifWriteFrame(&g, imgPtr, width, height, delay);
	}

	// Освобожнеие памяти Обработчика Для созданиния Анимации
	GifEnd(&g);

	// Освобожнеие памяти массива картинок
	this->freeImages();

	return true;
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

float ImageManager::nextFrame(UINT32 number)
{
	// Если введено корректный номер
	if (number < this->numberOfFrames && number >= 0)
	{
		// Изменяем текущий фрейм, на фрейм по номеру
		this->currentFrame = number;
		return this->currentFrame;
	}
	// Иначе ничего не меняем
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

void ImageManager::swapTextures(int texN1, int texN2)
{
	std::swap(this->textures[texN1], this->textures[texN2]);
}

bool ImageManager::freeImages()
{
	if (this->images.size() > 0)
	{
		for (int i = 0; i < this->images.size(); i++)
		{
			delete this->images[i];
		}
		this->images.clear();
	}

	return true;
}
