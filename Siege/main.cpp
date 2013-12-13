#include "stdafx.h"
#include "sys.h"

int main(int argv, char* argc[]) {
	
	Window.Init("Siege");
	Window.SetGameManager(NULL);
	Window.Start();

	return 42;
}