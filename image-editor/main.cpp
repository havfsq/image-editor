#include <SFML/Graphics.hpp>

#include "imageEditor.h"
#include "StateMainMenu.h"

int main()
{
	ImageEditor imageEditor;

	imageEditor.pushState(new StateMainMenu(&imageEditor));
	imageEditor.mainLoop();

	return 0;
}