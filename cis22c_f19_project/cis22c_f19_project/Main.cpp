#include <iostream>
#include "GUI.h"
//#include "Movie.h"
#include "List.h"
#include "menu.h"
#include "menu_dialog.h"

using namespace std;

int main() {
	//string str1 = "ThanksGiving";
	//List<string> g1;
	//g1.append("Horror");
	//g1.append("Comedey");
	//List<string> c1;
	//g1.append("Jon Doe");
	//g1.append("Herry Styles");
	//cout << c1;
	//Movie m(str1, 2019, 8.0, &g1, &c1);
	////cout << m.getGenre() << endl;
	////cout << m << endl;

	std::cout << "Welcome to NotNetfix!" << std::endl;

	bool end = true;
	while (end) {
		int choice = menu_prompt("What would you like to do?", menu_operations, 5);
		switch (choice) {
			case 1: {
				UI_search(/*const database& database*/);
				break;
			}
			case 2: {
				UI_add(/*const database& database*/);
				break;
			}
			case 3: {
				UI_remove(/*const database& database*/);
				break;
			}
			case 4: {
				UI_edit();
				break;
			}
			case 5: {
				end = false;
				break;
			}
		}
	}
	return 0;
}