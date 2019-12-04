#ifndef NOT_IMDB_DB_H
#define NOT_IMDB_DB_H

#include "FileIO.h"
#include "HashTable.h"
#include "list.h"
#include "pair.h"
#include "Movie.h"
#include "stack.h"
#include "BST_pair.h"
#include "CustomException.h"
#include "NotFoundException.h"
#include <chrono>

class NotIMDB_Database
{
private:
	HashTable<Movie*>*										__movieDB;
	Stack<Movie*>*											__deletedMovies;
	HashTable<BinarySearchTree<std::string, Movie*>*>*		__searchEngineBST;
	// ------------------------------------------
	// Internal Helper Method Section
	// ------------------------------------------

	void				__loadMovies(List<Movie*>* movies);
	/* tokenizes movie attributes ie movie name */
	void				__buildBSTSearchEngine(List<Movie*>* movies);
	/* to be called during updates to a specific movie where either the year or
	the name of the movie is changed
	update the search engine bst when edits are made to movies via removal
	op == 1 : editted title
	op == 2 : editted year  */
	Movie				__updateSearchEngineBST(const std::string edittedAttribute, Movie* movieToEdit, int op);
	/* function for generating a list of movie titles weighted by their number of occurences within 
	a keyword-node
	
	*/
	List<Movie*>*		__getKeywordWeightedMovies(const std::string& searchEntry) const;
	/* Internal function for processing a search entry.
	First strips the search entry string of whitespaces from the left and right.
	Then, replaces any remaining whitespaces with an underscore: "_"
	@param any search entry of either digits or alphabet characters
	@return a processed string of the form == "example3232_processed!_str" */
	void				__searchEngineDeletionHandler(Movie * movieToDelete);

public:
	void				testKeywordWeightedSearch(const std::string& searchEntry) const;
	std::string			processSearchEntry(const std::string& searchEntry) const;
	// ------------------------------------------
	// Constructor & Destructor Section
	// ------------------------------------------
	NotIMDB_Database() {
		__deletedMovies = new Stack<Movie*>();
		__searchEngineBST = new HashTable<BinarySearchTree<std::string, Movie*>*>(1000);
	}
	virtual ~NotIMDB_Database();
	// ------------------------------------------
	// Create/FileIO Section
	// ------------------------------------------
	/* This is the main function for handling database creation from a file.
	The function handles memory allocated for creation of objects read from file. 
	@return true if successfully opened and created */
	bool  				loadFromFile(std::string path);
	// save to a default path or a custom path/name
	void  				saveToFile(string path = "data//output.tsv");
	bool				createMovie(const Movie& newMovie) { return __movieDB->add(newMovie.getTitle(), new Movie(newMovie)); }

	// ------------------------------------------
	// Delete Section
	// ------------------------------------------
	// add the deleted movie to the stack
	bool				deleteMovie(std::string key);
	// undoes the most recent delete using a stack
	bool				undoMostRecentDelete();
	void				showMostRecentDelete() const;
	// ------------------------------------------
	// Update Section
	// ------------------------------------------
	// find movie by oldName, hold a copy of the movie delete movie of old name, update copy to newName, finally
	// add back into table
	bool				updateMovieName(std::string oldMovieName, std::string newMovieName);
	bool				updateMovieYear(std::string key, std::string newYearReleased);
	bool				updateMovieID(std::string key, std::string newID);
	bool				updateMovieRuntime(std::string key, std::string newRuntime);
	// op 0 appends to the genre string, op 1 sets the genre to newGenreName
	bool				updateMovieGenre(std::string key, std::string newGenreName, int op);
	bool 				updateMovieRating(std::string key, std::string newKey);

	// ------------------------------------------
	// Search Section
	// ------------------------------------------
	bool				foundMovie(std::string key) const;
	/* verify using actorDB */
	//bool  				foundActor(std::string actorName) const;

	// ------------------------------------------
	// Read Section
	// ------------------------------------------
	void				displayMovieTableStats() const;
	/* Function handles string cleaning to and processing with 
	the keyword search engine. Returned is a list of movies 
	in order of relevance to the userEntry */
	List<Movie>* 		readMovies(std::string key, bool& exactMatch) const;
	/* Use to directly display a movie by a known key of the format: title_name_year */
	bool				readAMovie(std::string key) const;
	void				displaySearchEngineState() const;
	void				unitTest();
};
#endif // !NOT_IMDB_DB_H
