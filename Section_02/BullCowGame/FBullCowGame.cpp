#pragma once
#include "FBullCowGame.h"
#include <map>

#define TMap std::map
//to make syntax Unreal friendly
using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planets"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHword = 0; MHword < WordLength; MHword++)
	{
		//compare letters against the guess
		for (int32 GHWord = 0; GHWord < WordLength; GHWord++)
		{
			//if they match then
			if (MyHiddenWord[MHword] == Guess[GHWord])
			{
				if (MHword == GHWord)	//increment bulls if they're in the same place
				{
					BullCowCount.Bulls++;
				}
				else //increment cows if not
				{
					BullCowCount.Cows++;
				}
			}
				
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	
	//Treat 0 and 1 letter words as isograms
	if (Word.length() <= 2) { return true; }
	//Declare alphabet map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)	//For all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { return false; } // we do NOT have an isogram
		else { LetterSeen[Letter] = true; } // store letter
	}

	
	return true;
}
EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//If the guess is not an isogram 
	{
		return EWordStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess))//if the guess is not all lowercase 
	{
		return EWordStatus::Not_Lowercase; 
	}
	else if (GetHiddenWordLength() != Guess.length())//if the guess length is wrong
	{
		return EWordStatus::Wrong_Length;
	}
	else
	{
		return EWordStatus::OK;
	}
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))// if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}