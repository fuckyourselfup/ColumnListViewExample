/*
 * Copyright 2023, Cafeina <cafeina@haiku-os>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef __CLVAPP_H
#define __CLVAPP_H

enum {
	M_ADD,
	M_REMOVE, 
	M_EDIT,
	M_SELECTED
};

#include <SupportDefs.h>
#include <Application.h>

class CLVApp : public BApplication
{
public:
	CLVApp();
	~CLVApp();
private:

};


#endif // __CLVAPP_H
