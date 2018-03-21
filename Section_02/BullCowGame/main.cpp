#pragma once
/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#include <iostream>
#include <string>
#include "FBullCowGame.h"


//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//Prototypes initialization
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; //instantiate a new game

// The entry point of our Application
int main() 
{
	bool bPlayAgain = false;
	do
	{
		BCGame.Reset();
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays a game to completion
void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is NOT won
	//and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 
				
		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	return;
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done you've won! " << std::endl;
	}
	else 
	{
		std::cout << "Better luck next time! " << std::endl;
	}
	std::cout << std::endl;

	return;
}
//loop continually until the user gives a valid Guess
FText GetValidGuess()
{	
	EWordStatus Status = EWordStatus::Invalid_Status;
	FText Guess = "";

	do {
		//get player guess
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		getline(std::cin, Guess);

		//check status and give some feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter your guess all in lowercase.\n\n";
			break;
		default:
			//assume guess is valid
			break;
		}
	} while (Status != EWordStatus::OK); //Keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word? (y/n) ";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
