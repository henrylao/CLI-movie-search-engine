#include <string>

#ifndef MENU_DIALOG_H
#define MENU_DIALOG_H

namespace GUI {
	const std::string menu_try_again[] = {
		"Try again",
		"Exit to main menu"
	};
	const std::string menu_try_again_or_exit_prog[] = {
		"Try again",
		"Exit program"
	};

	const std::string menu_continue_operation[] = {
		"Yes, Continue the operation",
		"No, Exit"
	};

	const std::string menu_yes_no[] = {
		"Yes",
		"No"
	};

	const std::string menu_continue_program[] = {
		"Yes",
		"No, exit the program"
	};

	const std::string divider = "--------------------------------------";

	const std::string menu_operations[] = {
		"Search for a movie",
		"Add a new movie",
		"Remove a movie",
		"Edit a movie",
		"Exit program"
	};

	const std::string menu_remove[] = {
		"Remove a person by full name",
		"Remove a person by birthdate",
		"Return to main menu"
	};

	const std::string menu_search[] = {
		"Search for a movie by title",
		"Search for a movie by release year",
		"Search for a movie by ratings",
		"Search for a movie by genre",
		"Return to main menu"
	};

	const std::string menu_attributes[] = {
		"Title",
		"Release year",
		"ID",
		"Runtime",
		"Genre",
		"Ratings"
	};

	const std::string menu_continue_edit[] = {
		"Continue editting",
		"Return to main menu"
	};

	const std::string menu_continue_search[] = {
		"Continue searching",
		"Return to main menu"
	};
	const std::string menu_continue_remove[] = {
		"Continue removeing",
		"Return to main menu"
	};

	//const std::string menu_display[] = {
	//	"Display movies by title",
	//	"Display movies by release year",
	//	"Display movies by ratings",
	//	"Display movies by genre",
	//	"Display movies by cast",
	//	"Return to main menu"
	//};

	//const std::string menu_continue_display[] = {
	//	"Continue viewing the database",
	//	"Return to main menu"
	//};


}
#endif
