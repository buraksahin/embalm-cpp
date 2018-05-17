//
//  main.cpp
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LinkedList.h"
#include "FileReadWrite.h"
#include "Movie.h"
#include "Questions.h"

using namespace std;

//
// Declerations
//
void makeQuiz(int n);
void addMovie();
void removeMovie(string movieName);
void searchMovie(string movieName);
void editMovie(string movieName);
LinkedList<Movie> getMovies();
void printMovies(LinkedList<Movie> movies);
Questions prepareQuestion();
int findCharPosition(string s, char c);
void showTotalMovie();

//
//  Variables
//
string filePath = "movies.txt";
string questionFilePath = "questions.txt";

//
// Main Method
//
int main(int argc, const char * argv[]) {
    //
    //  Variables
    //
    int gameLoopChoose = 0;

    //
    //  Main Game Loop
    //
    while(gameLoopChoose<8 && gameLoopChoose>=0){
        cout<<"\n==================================\n\tWELCOME TO MOVIE QUIZ\n==================================\n"<<endl;
        cout<<"1 > Make a quiz\n2 > Add a new movie\n3 > Remove a movie\n4 > Search a movie by name\n5 > Show total number of movies in movie data file\n6 > Print Movies\n7 > Exit\n\n=================================="<<endl;
        cout<<"Enter a choose: ";
        cin>>gameLoopChoose;
        cin.clear();
        cin.ignore();
        // Make a quiz
        if(gameLoopChoose == 1){
			int quizQuestion = 10;
			cout<<"How many questions are there?"<<endl;
			cin>>quizQuestion;
			cin.ignore();
			cin.clear();
			if(quizQuestion<10){
            	makeQuiz(10);
			}
			else{
				makeQuiz(quizQuestion);
			}
        }
        // Add a new movies
        else if(gameLoopChoose == 2){
            addMovie();
        }
        // Remove a movie
        else if(gameLoopChoose == 3){
            cout<<"Enter movie name: ";
            string movieName;
            getline(cin>>ws, movieName);
            removeMovie(movieName);
        }
        // Search a movie by name
        else if(gameLoopChoose == 4){
            cout<<"Enter movie name: ";
            string movieName;
            getline(cin>>ws, movieName);
            searchMovie(movieName);
        }
        // Show total movie in movie data file
        else if(gameLoopChoose == 5){
			showTotalMovie();
        }
        // Print Movies
        else if(gameLoopChoose == 6){
            printMovies(getMovies());
        }
        // Exit
        else if(gameLoopChoose == 7){
            break;
        }
    }
    // Ignore incorrect inputs
    system(EXIT_SUCCESS);
    return 0;
}

//
//  Make a quiz
//
void makeQuiz(int n){
  // Create LinkedList
  LinkedList<Questions> questionList;	// List of the questions
  int quizQuestionNumber = n;			// Quiz question number
  int userChoose[quizQuestionNumber];	// Keep user choose

  // Create questions and prepare quiz
  // If number of the movie is less than 10 it can be a problem for randomization
  for(int i=0; i<quizQuestionNumber; i++){
      questionList.insert(prepareQuestion());
  }

	// Ask questions and fill userChoose
  for(int q=0; q<quizQuestionNumber; q++){
    cout<<"===================="<<" #"<<q+1<<" QUESTION "<<"===================="<<endl;
    Questions tempQuestion = questionList[q];
    cout<<tempQuestion.question<<endl;
    cout<<"1: "<<tempQuestion.options[0]<<"  2: "<<tempQuestion.options[1]<<"  3: "<<tempQuestion.options[2]<<"  4: "<<tempQuestion.options[3]<<endl;
    int choose = 0;
    cin>>choose;
    cin.ignore();
    cin.clear();
		userChoose[q] =  choose-1;
  }

	// Set right answer count
  int rightAnswerCount = 0;

	// Print head line
  cout<<"====================== Resutls ======================"<<endl;

  // Compare and calculate right answers
  for(int x=0; x<quizQuestionNumber; x++){
	   // Print head line and question count
     cout<<"===================== "<<x+1<<" Question ===================="<<endl;

	    // Create a temp question
      Questions tempQuestion = questionList[x];

      if(tempQuestion.rightChoose == userChoose[x]){
          rightAnswerCount++;
          cout<<"Answer is right"<<endl;
          cout<<tempQuestion.question<<" Answer: "<<tempQuestion.options[tempQuestion.rightChoose]<<endl;
      }
      else{
          cout<<"Answer is not right"<<endl;
          cout<<tempQuestion.question<<" answer:"<<tempQuestion.options[tempQuestion.rightChoose]<<endl;
          cout<<"Your answer was: "<<tempQuestion.options[userChoose[x]]<<endl;
      }
      cout<<"====================================================="<<endl;
    }
    cout<<"Your correct answer count is "<<rightAnswerCount<<endl;
}

//
//  Add a new movie
//
void addMovie(){
    int choose = 0;
    string movieName;
    string movieYear = "";
    string movieDirector = "";

    cout<<"Please enter movie name: ";
    getline(cin>>ws, movieName);
    cout<<"Please enter movie year: ";
    cin>>movieYear;
    cout<<"Please enter movie director: ";
    getline(cin>>ws, movieDirector);
    cout<<"Do you want to save this > '" + movieName + " " + movieYear + " " + movieDirector + "' movie to database? \n1 > YES | 0 > NO :";
    cin>>choose;
    if(choose==1){
        FileReadWrite *fRW = new FileReadWrite(filePath);
        fRW->writeToFile(movieName + "#" + movieYear + "#" + movieDirector, 1);
    }
}// end of the addMovie

//
//  Remove a movie
//
void removeMovie(string movieName){
    LinkedList<Movie> movies = getMovies();
    FileReadWrite *fRW = new FileReadWrite(filePath);

    Movie movieInformations = fRW->getMovieFromFile(movieName);
    if(movieInformations.movieName == movieName){
        int getIsSure = 0;
        cout<<"Are you sure?\n1 > YES | 0 > NO :"<<endl;
        cin>>getIsSure;
        if(getIsSure == 1){

            for(int i=0; i<movies.getSize(); i++){
                Movie tempMovie = movies[i];
                if(tempMovie.movieName!=movieName){
                    if(i==0){
                        fRW->writeToFile(movies[i].movieName + "#" + movies[i].movieYear + "#" + movies[i].movieDirector, 0);
                    }
                    else{
                        fRW->writeToFile(movies[i].movieName + "#" + movies[i].movieYear + "#" + movies[i].movieDirector, 1);
                    }
                }
            }// end of the for loop
        }// end of the user checking if
    }// end of the if
    else{
        cout<<"Movie doesn't exist or name input is not correct.\nYou can check movie names from main menu."<<endl;
    }
}

//
//  Search a movie by name
//
void searchMovie(string movieName){
    FileReadWrite *fRW = new FileReadWrite(filePath);
    Movie movieInformations = fRW->getMovieFromFile(movieName);
    cout<<"Movie name: " + movieInformations.movieName + "\nMovie year: " + movieInformations.movieYear + "\nMovie director: " + movieInformations.movieDirector<<endl;
}

//
//  Get movies as Linked List
//
LinkedList<Movie> getMovies(){
    LinkedList<Movie> moviesLinkedList;
    FileReadWrite *fRW = new FileReadWrite(filePath);
    moviesLinkedList = fRW->getMovieFromFile();
    return moviesLinkedList;
}

//
//  Print Linked List
//
void printMovies(LinkedList<Movie> movies){
    for(int i=0; i<movies.getSize(); i++){
        Movie tempMovie = movies[i];
        cout<<tempMovie.movieName + " " + tempMovie.movieYear + " " + tempMovie.movieDirector<<endl;
    }
}

//
//  Prepare Random Question
//
Questions prepareQuestion(){
    // Read questions
    FileReadWrite *fRW = new FileReadWrite(questionFilePath);
    LinkedList<string> listOfQuestions = fRW->readQuestions();
    delete fRW;
    // Get movies
    LinkedList<Movie> listOfMovies = getMovies();
    int sizeOfTheMovies = listOfMovies.getSize();

    // Select random movie
    srand(time(NULL)*rand()); // Seed random number
    int randomChoose = rand()%sizeOfTheMovies;
    Movie movie = listOfMovies.get(randomChoose);
    // Select random question
    int sizeOfTheQuestions = listOfQuestions.getSize();
    randomChoose = rand()%sizeOfTheQuestions;
    string questionString = listOfQuestions[randomChoose];

    // Set tag positions
    int firstS = findCharPosition(questionString, '#');
    int secondS = findCharPosition(questionString.substr(firstS+1, questionString.size()), '#');
    int firstA = findCharPosition(questionString, '@');

    // Split question string
    string withoutAtTag = questionString.substr(0, firstA);
    string qQuestionType = withoutAtTag.substr(firstS+1, secondS);

    // Question string
    string qS;

    // Set question string as tag
    if(qQuestionType == "MOVIENAME"){
      qS = withoutAtTag.substr(0, firstS) + " " + movie.movieName + " " + withoutAtTag.substr(firstS + secondS + 2, withoutAtTag.size());
    }
    else if(qQuestionType == "YEAR"){
        qS = withoutAtTag.substr(0, firstS) + " " + movie.movieYear + " " + withoutAtTag.substr(firstS + secondS + 2, withoutAtTag.size());
    }
    else if(qQuestionType == "DIRECTOR"){
      qS = withoutAtTag.substr(0, firstS) + " " + movie.movieDirector + " " + withoutAtTag.substr(firstS + secondS + 2, withoutAtTag.size());
    }
    // Question object
    Questions question;
    question.question = qS;

    // Parse answer type from question string
    string qOptionType = questionString.substr(firstA+1,questionString.size());
    int totalDatabaseMovie = sizeOfTheMovies; // Set size of movies
    if(qOptionType == "MOVIENAME"){
  	// Movie name
  	if(totalDatabaseMovie < 4){
        cout<<"Not enough movie for create quiz!";
    	}
    else{
  		int randomFill = rand()%4;  		// Select random option
  		question.rightChoose = randomFill;	// Set the right option number
  		for(int i=0; i<4; i++){
          if(i!=randomFill){
  				int p = totalDatabaseMovie;
  				// Try to find a movie from list
  				while(p>0){
  					int selectRandomMovie = rand()%totalDatabaseMovie;	// Select random movie index for choose a movie in the listOfMovies linked list
  					if(listOfMovies[selectRandomMovie].movieName != movie.movieName){
  						int existMovie = 0;
  						for(int z=0; z<4; z++){
  							if(listOfMovies[selectRandomMovie].movieName == question.options[z]){
  								existMovie = 1;
  							}
  						}
              if(existMovie==0){
  							question.options[i] = listOfMovies[selectRandomMovie].movieName;
  							break; // If success break loop
  						}
  					}
  					p--; // Decrease counter
  				 }
  	      }
	        else{
            question.options[i] = movie.movieName; // Set right option
          }
        }
      }
    }
    else if(qOptionType == "YEAR"){
      // Year
      int randomFill = rand()%4;  		// Select random option
      question.rightChoose = randomFill;	// Set the right option number
      for(int i=0; i<4; i++){
        if(i!=randomFill){
            int tempYear = std::stoi(movie.movieYear);
            tempYear = tempYear + 1 + i;
            string tempOptionStr = to_string(tempYear);
            question.options[i] = tempOptionStr;	// Create random options
        }
        else{
          question.options[i] = movie.movieYear;		// Set right option
        }
      }
    }
    else{
      // Director
      if(totalDatabaseMovie < 4){
        cout<<"Not enough movie for create quiz!";
      }
      else{
          int randomFill = rand()%4;  		// Select random option
          question.rightChoose = randomFill;	// Set the right option number
  		for(int i=0; i<4; i++){
          if(i!=randomFill){
            int p = totalDatabaseMovie;
            // Try to find a movie from list
            while(p>0){
              int selectRandomMovie = rand()%totalDatabaseMovie;	// Select random movie index for choose a movie in the listOfMovies linked list
              if(listOfMovies[selectRandomMovie].movieDirector != movie.movieDirector){
                int existMovie = 0;
                for(int z=0; z<4; z++){
                  if(listOfMovies[selectRandomMovie].movieDirector == question.options[z]){
                    existMovie = 1;
                  }
                }
                if(existMovie==0){
                  question.options[i] = listOfMovies[selectRandomMovie].movieDirector;
                  break; // If success break loop
                }
              }
              p--; // Decrease counter
            }
          }
          else{
            question.options[i] = movie.movieDirector; // Set right option
          }
        }
      }
    }
    // Return question
    return question;
}

//
// Get questions in a txt file in 'question...#MOVIENAME#...question@YEAR@' format
// Behind the sharps we will set a movie name and answer will be a year.
// This function will return positon of the characters as integer
//
int findCharPosition(string s, char c){
    int result = 0; // Initial position
    for(int p=0; p<s.size(); p++){
        result = p;
        if(s.at(p) == c){
            break;
        }
    }
    return result;  // Position of the sharp
}

//
//	Show total of movie
//
void showTotalMovie(){
    LinkedList<Movie> moviesLinkedList;
    FileReadWrite *fRW = new FileReadWrite(filePath);
    moviesLinkedList = fRW->getMovieFromFile();
	cout<<"==================================\nThere are "<<moviesLinkedList.getSize()<<" movies in the database.\n=================================="<<endl;
}
