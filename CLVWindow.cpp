/*
 * Copyright 2023, Cafeina <cafeina@haiku-os>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "CLVApp.h"
#include "CLVWindow.h"
#include <ctime>
#include <Window.h>
#include <Alert.h>
#include <Button.h>
#include <LayoutBuilder.h>
#include <TranslationUtils.h>
#include <ColumnListView.h>
#include <ColumnTypes.h>

CLVWindow::CLVWindow() : 
	BWindow(BRect(50, 50, 1156, 600), "ColumnListView example",
		B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{
	/* Creamos el BColumnListView */
	clview = new BColumnListView(/* titulo */ NULL, /* flags */ B_FRAME_EVENTS | B_WILL_DRAW,
				/* borde */ B_FANCY_BORDER, /* mostrar bar. horiz. */ true);

	/* Le creamos columnas */
	clview->AddColumn(new BIntegerColumn("Id.", 50.0, 40.0, 60.0, B_ALIGN_RIGHT), ID_INT); /* Columna de numero entero */
	clview->AddColumn(new BBitmapColumn("Logo", 150.0, 100.0, 250.0, B_ALIGN_CENTER), ID_BMP); /* Columna de cadena de texto */
	clview->AddColumn(new BStringColumn("Nombre", 150.0, 100.0, 250.0, 5, B_ALIGN_LEFT), ID_TEXT); /* Columna de cadena de texto */
	clview->AddColumn(new BDateColumn("Fecha", 200, 100, 230, B_ALIGN_LEFT), ID_DATE); /* Columna de fecha*/

	/* Configuramos el BColumnListView */
	clview->SetSortingEnabled(true); 		/* Si es posible (true) o no (false) ordenar las filas */
	clview->SetColumnFlags(B_ALLOW_COLUMN_RESIZE); 	/* Comportamiento de las columnas */
	
	/* Construimos el resto de los objetos de la interfaz */
	addBtn = new BButton("Añadir", new BMessage(M_ADD));
	remBtn = new BButton("Quitar", new BMessage(M_REMOVE));
	aboutBtn = new BButton("Acerca de" B_UTF8_ELLIPSIS, new BMessage(B_ABOUT_REQUESTED));
	exitBtn = new BButton("Salir", new BMessage(B_QUIT_REQUESTED));
	
	/* Diseñamos la interfaz con el LayoutKit */
	BLayoutBuilder::Group<>(this, B_HORIZONTAL)
		.SetInsets(B_USE_ITEM_SPACING)
		.Add(clview)
		.AddGroup(B_VERTICAL)
			.Add(addBtn)
			.Add(remBtn)
			.AddGlue()
			.Add(aboutBtn)
			.Add(exitBtn)
		.End()
	.End();
	
	/* Retoques finales */
	AddShortcut ('a', B_COMMAND_KEY, new BMessage (M_ADD)); /* Atajo del teclado: Comando+A para insertar fila */
	AddShortcut ('r', B_COMMAND_KEY, new BMessage (M_REMOVE)); /* Atajo del teclado: Comando+R para remover fila seleccionada */
	remBtn->SetEnabled(false); /* El boton de eliminar inicialmente esta deshabilitado. Se activa al elegir una fila */
	clview->SetSelectionMessage(new BMessage(M_SELECTED)); /* Al seleccionar una fila, envia este mensaje. 
														Esto nos permitirá trabajar con la fila seleccionada */
}

CLVWindow::~CLVWindow ()
{
}

void CLVWindow::MessageReceived(BMessage* msg)
{
	switch (msg->what)
	{
		case M_ADD: /* Añadir fila */
			InsertItem(elementos++, "Ejemplo");
			break;
		case M_REMOVE: /* Quitar fila */
			{
				BRow* fila = clview->CurrentSelection();/* determinamos eliminar la fila selecc. */
				if (fila) {
					clview->RemoveRow(fila); /* eliminamos la fila */
					delete fila; /* y liberamos la memoria que ocupaba */
				} else {
					BAlert* alert = new BAlert(NULL, "Error: debe elegir una fila para poder eliminarla.", 
						"Aceptar", NULL, NULL, B_WIDTH_AS_USUAL, B_STOP_ALERT);
					alert->Go();
				}
			}
			break;
		case M_SELECTED: /* Para activar o desactivar el boton de Eliminar si hay o no fila selecc. */
			if (clview->CountRows() > 0 && clview->CurrentSelection())
				remBtn->SetEnabled(true);
			else
				remBtn->SetEnabled(false);
			break;
		case B_ABOUT_REQUESTED: /* Dialogo "Acerca de" */
			{
				BAlert* alert = new BAlert("Acerca de ColumnListViewExample", 
					"ColumnListViewExample.\n2023. Creado por cafeina", "Aceptar");
				alert->Go();
			}
			break;
		case B_QUIT_REQUESTED: /* Salir */
			QuitRequested();
			break;
		default:
			BWindow::MessageReceived(msg);
			break;
	}
}

bool CLVWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}

void CLVWindow::InsertItem(int id, const char* text)
{
	int rowIndex = clview->CountRows(); /* Averiguamos cuantas filas hay, colocamos solo al final */ 
	BBitmap* bmp = BTranslationUtils::GetBitmap("splash_icons_color.png"); /* Imagen de ejemplo */
	std::time_t fecha = std::time(nullptr); /* Obtenemos fecha actual */
	
	/* Nueva instancia de fila */
	BRow* fila = new BRow();
	
	/* Creamos cuatro celdas acorde con el tipo de columna */
	BIntegerField* idfield = new BIntegerField(id > rowIndex ? id : rowIndex); /* entero: el > entre el num. filas y el maximo id */
	BBitmapField* bmpfield = new BBitmapField(bmp); /* mapa de bits: imagen de ejemplo */
	BStringField* strfield = new BStringField(text); /* cadena de texto: obtenida del parametro */
	BDateField* datefield = new BDateField(&fecha); /* fecha: ahora */

	/* Asignamos las celdas creadas a la fila */
	fila->SetField(idfield, ID_INT);
	fila->SetField(bmpfield, ID_BMP);
	fila->SetField(strfield, ID_TEXT);
	fila->SetField(datefield, ID_DATE);
	
	/* Agregamos la fila al final de la tabla */
	clview->AddRow(fila, rowIndex++);
}

