//
//  Movie.h
//

#ifndef MOVIE_hpp
#define MOVIE_hpp

#include <string>
using namespace std;

class Movie{
public:
    string movieName;       // Movie Name
    string movieYear;       // Movie Year
    string movieDirector;   // Movie Director

    //
    //  Movie Constructor
    //
    Movie(){}
    Movie(string mN, string mY, string mD){
        movieName = mN;
        movieYear = mY;
        movieDirector = mD;
    }
    ~Movie(){};
};
#endif
