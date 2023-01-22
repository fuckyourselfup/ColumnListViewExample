/*
 * Copyright 2023, Cafeina <cafeina@haiku-os>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef __CLVWINDOW_H
#define __CLVWINDOW_H

#include <SupportDefs.h>
#include <Window.h>
#include <ColumnListView.h>

enum {
	ID_INT,
	ID_BMP,
	ID_TEXT,
	ID_DATE
};

class CLVWindow : public BWindow 
{
public:
	CLVWindow();
	~CLVWindow();
	void MessageReceived(BMessage* msg);
	bool QuitRequested();
	void InsertItem(int id, const char* text);
	void DeleteItem ();	
private:
	BColumnListView* clview;
	BButton* addBtn;
	BButton* remBtn;
	BButton* aboutBtn;
	BButton* exitBtn;
	
	int elementos = 0; /* identificador unico */
};


#endif // __CLVWINDOW_H
