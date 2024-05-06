#include"lowpoly-engine.h"

int main()
{
	lowpoly_engine application;

	application.setGUI(false);

	while (true)
	{
		application.clear();
		application.processInput();

		// Draw

		application.render();
	}
	
	return 0;
}