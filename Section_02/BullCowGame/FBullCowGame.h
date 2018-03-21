/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind*/

#pragma once
#include <string>

//to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

//All values initialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EResetStatus
{
	No_Hidden_word,
	OK
};
class FBullCowGame {
public:
	FBullCowGame(); // Constructor 

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EWordStatus CheckGuessValidity(FString) const;

	void Reset();

	// counts bulls & cows and increases turn number assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	//See constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};