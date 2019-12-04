#include "NotIMDB_Database.h"
#include "GUI.h"

void NotIMDB_Database::__loadMovies(List<Movie>* movies)
{
	Movie newMovie;
	int MSIZE;
	MSIZE = movies->getLength();
	for (int i = 0; i < MSIZE; i++)
	{
		newMovie = movies->getEntry(i);
		// preprocess the key
		std::string key = newMovie.getTitle();
		key = StringUtil::lowercase(StringUtil::strip(key));	// remove whitespace and turn into lowercase
		key = StringUtil::replace(key, " ", "_");
		// add to the table
		__movieDB.add(key, newMovie);
	}
	//delete movies;

}

/* create the map of bsts such that the first character of each tokenized word
signifies a key in the dictionary */
void NotIMDB_Database::__buildMovieBST(List<Movie>* movies)
{
	int SIZE = movies->getLength();
	Movie newMovie;
	List<std::string>* keywords;
	std::string keyword, keywords_preprocess;
	BinarySearchTree<std::string, Movie> found;

	std::string firstCharOfKeyword;

	for (int i = 0; i < SIZE; i++) {
		newMovie = movies->getEntry(i);
		/*  homogenize characters in the string */
		// strip then turn into lowercase
		keywords_preprocess = StringUtil::lowercase(StringUtil::strip(newMovie.getTitle() + " " + newMovie.getYearReleased())); 
		keywords_preprocess = StringUtil::replace(keywords_preprocess, " ", "_");
		// create a list of keywords from movie title and year
		keywords = StringUtil::split(keywords_preprocess, "_");	
		// create trees and populate accordingly such that 
		// the first letter of a keyword from the keyword list signifies a key in the
		// table of BSTS
		for (int j = 0; j < keywords->getLength(); j++)
		{
			keyword = keywords->getEntry(j);
			firstCharOfKeyword = std::string(1, keyword[0]);
			try {
				// check in the dictionary
				found = __searchEngineBST[firstCharOfKeyword];
				std::string keywordFound = found.getKey(keyword);
				// simply add if keywordFound else the exception caught will signify to add the new keyword
				__searchEngineBST[firstCharOfKeyword].addValue(keyword, newMovie);
				//found.printBreadthFirst();	// DBEUG

			}
			// first character of a keyword was not found to denote a key in the table
			catch (const CustomException& e)
			{
				// create a new bst such that the first character of the keyword denotes 
				// a key to a tree in the table of bst 
				__searchEngineBST.add(firstCharOfKeyword, 
					BinarySearchTree<std::string, Movie>(keywords->getEntry(j)));
				__searchEngineBST[firstCharOfKeyword].addKey(keyword);
				__searchEngineBST[firstCharOfKeyword].addValue(keyword,newMovie);
				//found.printBreadthFirst();	// DBEUG

			}
			catch (const NotFoundException& e)
			{
				// create the new node holdsing the keyword
				found.addKey(keyword);	
				// append to the list of values in the newly created keyword-node
				found.addValue(keyword, newMovie);
				//found.printBreadthFirst();	// DBEUG
			}

		}
		// memory clean
		delete keywords;
	}

}

<<<<<<< Updated upstream
std::string NotIMDB_Database::__processSearchEntry(const std::string & searchEntry)
{

	std::string processedKey = StringUtil::lowercase(StringUtil::strip(searchEntry));
	processedKey = StringUtil::replace(processedKey, " ", "_");
	return processedKey;
}

/* to be called during updates to a specific movie where either the year or
	the name of the movie is changed
	update the search engine bst when edits are made to movies via removal
	op == 1 : editted title
	op == 2 : editted year  */
void NotIMDB_Database::__updateSearchEngineBST(const std::string edittedAttribute, const Movie& movieToEdit, int op)
=======
/* Internal function for maintaining the keyword search engine
	be called during updates to a specific movie where either the year or
	the name of the movie is change update the search engine bst when edits
	are made to movies via removal
	toggle between various operations:
	1 by movieID
	2 by rating
	3 by year
	4 by title
	5 by runtime
*/
Movie NotIMDB_Database::__updateSearchEngineBST(const std::string newAttribute, const Movie& movieToEdit, int op)
>>>>>>> Stashed changes
{
	BinarySearchTree<std::string, Movie> found;
	List<std::string>* keywords;
	std::string keyword, keywords_preprocess, firstCharOfKeyword;
	// create copy of the movie
	Movie edittedMovie(movieToEdit);
	keywords_preprocess = StringUtil::lowercase(StringUtil::strip(movieToEdit.getTitle() + " " + movieToEdit.getYearReleased()));
	keywords_preprocess = StringUtil::replace(keywords_preprocess, " ", "_");
	if (op < 1)
		throw CustomException("Error: Invalid Update Operation Value");
	if (op == 1)
	{
		// 
		edittedMovie.setTitle(edittedAttribute);
		keywords = StringUtil::split(keywords_preprocess, "|");
		// remove all matched keyword and movie pairs from the search engine
		for (int j = 0; j < keywords->getLength(); j++)
		{
			keyword = keywords->getEntry(j);
			firstCharOfKeyword = std::string(1, keyword[0]);
			try {
				// check in the dictionary
				found = __searchEngineBST[firstCharOfKeyword];
				__searchEngineBST[firstCharOfKeyword].remove(keyword, movieToEdit);
			}
			// first character of a keyword was not found to denote a key in the table
			catch (const CustomException& e)
			{
				// create a new bst such that the first character of the keyword denotes 
				// a key to a tree in the table of bst 
				__searchEngineBST.add(std::string(1, keywords->getEntry(j)[0]),
					BinarySearchTree<std::string, Movie>(keywords->getEntry(j)));

			}

		}

	}
}

<<<<<<< Updated upstream
=======
List<Movie> NotIMDB_Database::__getKeywordWeightedMovies(const std::string & searchEntry) const
{
	// process search entry
	std::string processSearchEntry = __processSearchEntry(searchEntry);
	// mnovie titles will be associated with an integer value
	HashTable<int> weightedMovieTitles;
	// tokenize the processed search entry
	List<std::string>* keywords = StringUtil::split(processSearchEntry, "_");

	// variables for accessing table of BSTs
	std::string keyword;
	int SIZE = keywords->getLength();
	List<Movie> moviesByKeyword;
	std::string firstCharOfKeyword;

	// for each keyword get the bst associated with the first character of the keyword
	for (int i = 0; i < SIZE; i++)
	{
		// c
		keyword = keywords->getEntry(i);
		firstCharOfKeyword = std::string(1, keyword[0]);
		// get movies of the asociated keyword-key from the BST
		//moviesByKeyword = __searchEngineBST[firstCharOfKeyword].getValues(keyword);
		std::cout << __searchEngineBST.get(firstCharOfKeyword).getValues(keyword) << std::endl;
		int MBK_SIZE = moviesByKeyword.getLength();
		// loop through the list of values from 
		for (int j = 0; i < MBK_SIZE; i++)
		{
			// create the processedMovieName
			std::string processedMovieName = moviesByKeyword.getEntry(i).getTitle() + " " + moviesByKeyword.getEntry(i).getYearReleased();
			try {
				processedMovieName = __processSearchEntry(processedMovieName);
				// if an associated weight exists for the movie increment by 1
				int found = weightedMovieTitles[processedMovieName];
				weightedMovieTitles[processedMovieName] += 1;
			}
			// processed movie title does not exist in the table of weighted movies
			catch (const CustomException& e)
			{
				weightedMovieTitles.add(processedMovieName, 1);
			}
		}
	}
	return List<Movie>();
}


std::string NotIMDB_Database::__processSearchEntry(const std::string & query) const
{
	std::string processedKey = StringUtil::lowercase(StringUtil::strip(query));
	processedKey = StringUtil::replace(processedKey, " ", "_");
	return processedKey;
}

void NotIMDB_Database::testKeywordWeightedSearch(const std::string & searchEntry) const
{
	List<Movie> weightedMovies = __getKeywordWeightedMovies(searchEntry);
}

>>>>>>> Stashed changes
bool NotIMDB_Database::foundMovie(std::string key)
{
	Movie found;
	try {
		found = __movieDB[key];
		return true;
	}
	catch (const CustomException& e)
	{
		return false;
	}
	return false;

}


void NotIMDB_Database::displayMovieTableStats() const
{
	__movieDB.showStats();
}
bool NotIMDB_Database::readMovie(std::string key) const
{
	try {
<<<<<<< Updated upstream
		Movie found = __movieDB.get(key);
		std::cout << found << std::endl;
=======
		// 1st match found
		std::cout << __movieDB[processedKey] << std::endl;
		// display keyword-weighted movie using the search engine
>>>>>>> Stashed changes
		return true;
	}
	catch (const CustomException& e)
	{
		return false;
	}
	return false;
}

void NotIMDB_Database::unitTest()
{
	std::string divider = "--------------------------------";
	NotIMDB_Database db;
	db.loadFromFile();
	db.readMovie("Miss Jerry");
	db.saveToFile("output.tsv");

	std::cout << divider << std::endl;
	std::cout << "Pre-delete:" << std::endl;
	db.displayMovieTableStats();
	std::cout << divider << std::endl;

	std::cout << "Post-delete:" << std::endl;
	db.displayMovieTableStats();
	std::cout << divider << std::endl;

	db.showMostRecentDelete();
	db.undoMostRecentDelete();
	std::cout << divider << std::endl;
	db.readMovie("Miss Jerry");
	std::string path = "data\\full\\title_basics_cleaned_final_trimmed2.tsv";
	List<Movie>* movies = FileIO::buildMovieList(path);
	db.createMovie(movies->getEntry(5));
	db.displayMovieTableStats();
<<<<<<< Updated upstream
=======
	db.displaySearchEngineState();
	db.updateMovieName("Miss Jerry 1894", "Mister Jerry");

	//db.displaySearchEngineState();	// BUGGED
	db.testKeywordWeightedSearch("Miss Jerry");
	system("pause");
>>>>>>> Stashed changes
}


NotIMDB_Database::~NotIMDB_Database()
{
}

bool NotIMDB_Database::loadFromFile(std::string path)
{
	List<Movie>* movies = nullptr;

	//std::thread t1( FileIO::loadActorsIntoList, actorFilePath, actors);
	movies = FileIO::buildMovieList(path);
	__loadMovies(movies);
	__buildMovieBST(movies);
	List<std::string> keys = __searchEngineBST.keys();
	int SIZE = keys.getLength();

	/* DEBUG Keyword Search Engine*/
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << GUI::divider << std::endl;
		std::cout << "BST in table at keyword char: " << keys.getEntry(i) << std::endl;
		std::cout << "Depth-first: " << std::endl;
		__searchEngineBST[keys.getEntry(i)].printBreadthFirst();
	}
	// call internal loading functions
	std::cout << __searchEngineBST.size() << std::endl;	// DEBUG
	return true;
}

void NotIMDB_Database::saveToFile(string path)
{
	std::ofstream outfile;
	outfile.open(path, std::ios::out);

	std::string out;
	size_t MSIZE = __movieDB.size();
	Movie temp;
	for (size_t i = 0; i < MSIZE; i++)
	{
		temp = (__movieDB[__movieDB.keys().getEntry(i)]);
		out = temp.getID() + " | " + temp.getTitle() + " | " +
			temp.getYearReleased() + " | " + temp.getRuntime()
			+ " | " + temp.getGenres() + "\n";
		outfile << out;
	}
	outfile.close();

}

bool NotIMDB_Database::deleteMovie(std::string key)
{
	std::string processedKey = __processSearchEntry(key);
	try{
		Movie temp;
		temp = __movieDB[processedKey];
		__deletedMovies.push(temp);

	}
	catch (const CustomException& e)
	{
		return false;
	}
	// push onto the stack
	__movieDB.remove(processedKey);	// movie removed from table
	return true;
}

bool NotIMDB_Database::undoMostRecentDelete()
{
	Movie movieDeleted;
	if (__deletedMovies.size() > 0)
	{
		movieDeleted = __deletedMovies.peek();
		__deletedMovies.pop();
	}
	__movieDB.add(movieDeleted.getTitle(), movieDeleted);
	return false;
}

void NotIMDB_Database::showMostRecentDelete() const
{
	if (__deletedMovies.size() > 0)
		std::cout << __deletedMovies.peek() << std::endl;
<<<<<<< Updated upstream
	else
=======
}

bool NotIMDB_Database::updateMovieName(std::string oldMovieName, std::string newMovieName)
{
	// check for existence
	if (!foundMovie(oldMovieName))
		return false;
	Movie edittedMovie = __updateSearchEngineBST(newMovieName, __movieDB[oldMovieName], 1);
	__movieDB[newMovieName] = edittedMovie;
	return true;
}

bool NotIMDB_Database::updateMovieYear(std::string key, std::string newYearReleased)
{
	try {
		std::string processedKey = __processSearchEntry(key);
		Movie newMovie = __updateSearchEngineBST(newYearReleased, __movieDB[processedKey], 2);
		__movieDB[processedKey] = newMovie;
		return true;
	}
	catch (CustomException e)
	{
		std::cout << e.getMessage() << std::endl;
	}
	return false;
}

bool NotIMDB_Database::updateMovieID(std::string key, std::string newID)
{
	try {
		std::string processedKey = __processSearchEntry(key);
		Movie newMovie = __updateSearchEngineBST(newID, __movieDB[processedKey], 3);
		__movieDB[processedKey] = newMovie;
		return true;
	}
	catch (CustomException e)
	{
		std::cout << e.getMessage() << std::endl;
	}
	return false;
}

bool NotIMDB_Database::updateMovieRuntime(std::string key, std::string newRuntime)
{
	try {
		std::string processedKey = __processSearchEntry(key);
		Movie newMovie = __updateSearchEngineBST(newRuntime, __movieDB[processedKey], 4);
		__movieDB[processedKey] = newMovie;
		return true;
	}
	catch (CustomException e)
	{
		std::cout << e.getMessage() << std::endl;
	}
	return false;
}

bool NotIMDB_Database::updateMovieGenre(std::string key, std::string newGenreName, int op)
{
	try {
		std::string processedKey = __processSearchEntry(key);
		std::string genres;
		if (op)
			genres = newGenreName;
		else
			genres = __movieDB[processedKey].getGenres().append(newGenreName);
		Movie newMovie = __updateSearchEngineBST(genres, __movieDB[processedKey], 5);
		__movieDB[processedKey] = newMovie;
		return true;
	}
	catch (CustomException e)
>>>>>>> Stashed changes
	{
		std::cout << "There are no movies that have been deleted\n";
	}
}
