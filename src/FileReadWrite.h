//
// FileReadWrite.h
//

#ifndef FILERW_h
#define FILERW_h

#include <string>
#include <fstream>
#include "Movie.h"
#include "LinkedList.h"
#include "Questions.h"

using namespace std;

class FileReadWrite{
public:
    string filePath = "path";
    FileReadWrite(){}
    FileReadWrite(string path){
        filePath = path;
    }
    ~FileReadWrite(){}

    //
    // Read as Movie Object
    //
    Movie getMovieFromFile(string name){
        // String variables for keep movie information
        string movieName = "";
        string movieYear = "";
        string movieDirector = "";
        string movieLine = "";

        ifstream readFile;          // File reader
        readFile.open(filePath);    // Open file
        string s;                   // String for keep movie information lines which is read from movie data file

        // If file is exist and opened read line from text file
        if (readFile.is_open()){
            while(getline(readFile, s)){
                // Get movie line and splite it as delimiters '#'
                // Find first sharp character in the string
                int movieNamePos = findCharPosition(s);
                // Get movie line and splite it as delimiters '#'
                // Find sharp character in the line and set substring of the movie
                int movieYearPos = findCharPosition(s.substr(movieNamePos + 1, s.size()));
                // Set strings
                movieName = s.substr(0, movieNamePos);
                movieYear = s.substr(movieNamePos + 1, movieYearPos);
                movieDirector = s.substr(movieNamePos + movieYearPos + 2, s.size());

                // If found movie break
                if (movieName == name) {
                    break; // Stop
                }
            }// end of the while loop
            readFile.close(); // Close file
        }
        if(movieName == name){
            Movie *tempMovie = new Movie(movieName, movieYear, movieDirector);
            return *tempMovie;
        }
        else{
            Movie *tempMovie = new Movie("not exist", "not exist", "not exist");
            return *tempMovie;
        }
    }// end of the read movie

    //
    // Read as Movie Object
    //
    LinkedList<Movie> getMovieFromFile(){
        // String variables for keep movie information
        string movieName = "";
        string movieYear = "";
        string movieDirector = "";
        string movieLine = "";

        ifstream readFile;              // File reader
        readFile.open(filePath);        // Open file
        string s;                       // String for keep movie information lines which is read from movie data file
        LinkedList<Movie> listOfMovies; // Create movie linked list to keep movies

        // If file is exist and opened
        if (readFile.is_open()){
            while(getline(readFile, s)){
                // Get movie line and splite it as delimiters '#'
                // Find first sharp character in the string
                int movieNamePos = findCharPosition(s);
                // Get movie line and splite it as delimiters '#'
                // Find sharp character in the line and set substring of the movie
                int movieYearPos = findCharPosition(s.substr(movieNamePos + 1, s.size()));
                // Set strings
                movieName = s.substr(0, movieNamePos);
                movieYear = s.substr(movieNamePos + 1, movieYearPos);
                movieDirector = s.substr(movieNamePos + movieYearPos + 2, s.size());

                // Create new movie object to keep movie informations
                Movie * tempMovie = new Movie(movieName, movieYear, movieDirector);
                // Insert new movie to linked list
                listOfMovies.insert(*tempMovie);
            }
            readFile.close(); // Close file
        }
        return listOfMovies; // Return list of the movies
    }// end of the read movies as object

    //
    // Write to File
    //
    void writeToFile(string d, int mode){
        ofstream writeFile;

        // Open write file
        if(mode == 0){
            writeFile.open(filePath);
        } else{
            writeFile.open(filePath, ios::app);
        }

        // Write to file
        writeFile<<d<<endl;

        // Close file
        writeFile.close();
    }

    //
    //  Read Question
    //
    LinkedList<string> readQuestions(){
        string question = "";
        LinkedList<string> *questions = new LinkedList<string>();

        // File reader
        ifstream readFile;
        // Open file
        readFile.open(filePath);
        string s;

        if(readFile.is_open()){
            while(getline(readFile, s)){
                questions->insert(s);
            }
            readFile.close(); // Close file
        }
        return *questions;
    }

    //
    // We keep movies in a txt file in 'movie_name#year#director' format
    // To split informations we have to find sharp('#') character positions
    // This function will return positon of the sharp as integer
    //
    int findCharPosition(string s){
        int result = 0; // Initial position
        for(int p=0; p<s.size(); p++){
            result=p;
            if (s.at(p)== '#'){
                break;
            }
        }
        return result; // Position of the sharp
    }

    void changeMovieName(string name, string newName);
    void changeMovieDate(string name, string year);
    void changeMovieDirector(string name, string directorName);
    void removeFromFile(string name);
};
#endif
