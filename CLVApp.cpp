/*
 * Copyright 2023, Cafeina <cafeina@haiku-os>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "CLVApp.h"
#include "CLVWindow.h"
#include <Application.h>
#include <Window.h>

CLVApp::CLVApp() : 
	BApplication("application/x-vnd.Haiku.Example-ColumnListView")
{
	CLVWindow* window = new CLVWindow();
	window->Show();
}

CLVApp::~CLVApp()
{
}

