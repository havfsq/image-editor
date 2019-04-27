#include <SFML/Graphics.hpp>

#include "imageEditor.h"
#include "ImageEditorStateMainMenu.h"

int main()
{
	ImageEditor imageEditor;

	imageEditor.pushState(new ImageEditorStateMainMenu(&imageEditor));
	imageEditor.mainLoop();

	return 0;
}