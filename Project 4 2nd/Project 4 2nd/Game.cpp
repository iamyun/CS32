#include <iostream>
#include "Game.h"
using namespace std;

//insert all words in word list to hashtable
Game::Game(const vector<string> &words)
{
	for (int i = 0; i < words.size(); i++)
	{
		list.insert(words[i]);
	}
	secretWord = "";
}
//set secretWord and check if it's in the wordList
bool Game::setSecretWord(const string &sw)
{
	secretWord = sw;
	return list.search(sw);
}
//get secretWord's word length
int Game::secretWordLength() const
{
	return secretWord.size();
}
void Game::probe(const string &probeWord, int &nInRightPlace, int &nInWrongPlace)
{
	nInRightPlace = 0;
	nInWrongPlace = 0;

	
	int length = 0;
	if (probeWord.size() > secretWord.size())
		length = secretWord.size();
	else length = probeWord.size();

	//stop searching for bulls when reach end of one of the string
	for (int i = 0; i < length; i++)
	{
		if (probeWord[i] == secretWord[i])
			nInRightPlace++;
	}

	//this gets all the characters that are in both string
	int p[26] = { 0 };
	int s[26] = { 0 };
	for (int j = 0; j < probeWord.size(); j++)
	{
		int i = probeWord[j] - 'a';
		p[i]++;
	}
	for (int k = 0; k < secretWord.size(); k++)
	{
		int i = secretWord[k] - 'a';
		s[i]++;
	}

	//common gets the total common characters probeWord has in secretWord
	int common = 0;
	for (int n = 0; n < 26; n++)
	{
		if (s[n] != 0 && p[n] != 0)
		{
			if (s[n] < p[n])
				common += s[n];
			else common += p[n];
		}
	}

	//subtract total common characters by bulls will give cows
	nInWrongPlace = common - nInRightPlace;
}
Game::~Game()
{

}

Game::Game(const Game&)
{

}
Game& Game::operator=(const Game&)
{
	return *this;
}

//just push back to the vector to insert new word
void Game::HashTable::insert(const string word)
{
	int bucket = hashFunc(word);
	wList[bucket].push_back(word);
}

//search word in wordlist, check if it's in it
bool Game::HashTable::search(const string word)
{
	int bucket = hashFunc(word);

	//stop searching after going through all words
	for (int tries = 0; tries < GNUM_BUCK; tries++)
	{
		vector<string>::iterator wordPtr;
		for (wordPtr = wList[bucket].begin(); wordPtr != wList[bucket].end(); wordPtr++)
		{
			if (*wordPtr == word)
				return true;
		}
	}
	return false;
}

//convert string to int
unsigned long Game::HashTable::hash(const char *str) const
//http://stackoverflow.com/questions/19892609/djb2-by-dan-bernstein-for-c
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = hash * 33 + c;

	return hash;
}

unsigned long Game::HashTable::hashFunc(const string word) const
{
	int i = 0;
	unsigned long total = 0;
	for (i = 0; i < word.length(); i++)
		total += hash(&word[i]);
	total = total % GNUM_BUCK;
	return total;
}
