#include <iostream>
#include "Game.h"
using namespace std;

Game::Game(const vector<string> &words)
{
	for (int i = 0; i < words.size(); i++)
	{
		list.insert(words[i]);
	}
	secretWord = "";
}
bool Game::setSecretWord(const string &sw)
{
	secretWord = sw;
	return list.search(sw);
}
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

	for (int i = 0; i < length; i++)
	{
		if (probeWord[i] == secretWord[i])
			nInRightPlace++;
	}

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

	int common = 0;
	for (int n = 0; n < 26; n++)
	{
		if (s[n] != 0 && p[n] != 0)
			common += s[n];
	}

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

void Game::HashTable::insert(const string word)
{
	int bucket = hashFunc(word);
	wList[bucket].push_back(word);
}

bool Game::HashTable::search(const string word)
{
	int bucket = hashFunc(word);

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

int Game::HashTable::hashFunc(const string word) const
{
	int i, total = 0;
	for (i = 0; i < word.length(); i++)
		total = total + (i + 1)*word[i];
	total = total % GNUM_BUCK;
	return total;
}

//int main()
//{
//	vector<string> words;
//	words.push_back("apocalypse");
//	Game g(words);
//	g.setSecretWord("apocalypse");
//	cout << g.secretWordLenth() << endl;
//	int bull = 0;
//	int cow = 0;
//	g.probe("apapda", bull, cow);
//	cout << bull << " " << cow;
//}