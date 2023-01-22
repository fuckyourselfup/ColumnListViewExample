/*
 * Copyright 2023, Cafeina <cafeina@haiku-os>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "CLVApp.h"
#include <Application.h>

int main (int argc, char *argv[])
{
	CLVApp* app = new CLVApp();	/* Creo nueva instancia de la aplicacion */
	app->Run();					/* La ejecuto */
	delete app;					/* Al terminar, libera la memoria ocupada */
	return B_OK;
}
