#include <iostream>
#include "GUI.h"
#include "Movie.h"
#include "List.h"
#include "menu.h"
#include "menu_dialog.h"

using namespace std;

int main()
{
	NotIMDB_Database db;
	GUI::UI_run_application(db);
	//db.unitTest();
	system("pause");
	return 0;
}