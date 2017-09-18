#include <iostream>
#include "Player.h"
using namespace std;

Player::Player(const vector<string> &words)
{
	for (int i = 0; i < words.size(); i++)
	{
		list.add(words[i]);
	}
	pWord = "";
	guesses = 0;
	wTotal = "";
}
string Player:: generateProbeWord()
{
	guesses++;
	pWord = "";
	if (guesses < 27)
		for (int i = 0; i < 21; i++)
			pWord += guesses - 1 + 'a';
	else
		pWord = list.find(wTotal, guesses - 27);
	return pWord;
}
void Player::learn(string probe, int nInRightPlace, int nInWrongPlace)
{
	if (guesses < 27)
		for (int i = 0; i < nInRightPlace; i++)
			wTotal += guesses - 1 + 'a';
}
Player::~Player()
{

}

Player::Player(const Player&)
{

}
Player& Player::operator=(const Player&)
{
	return *this;
}

void Player::HashTable::add(const string word)
{
	int w[26] = { 0 };
	for (int j = 0; j < word.size(); j++)
	{
		int i = word[j] - 'a';
		w[i]++;
	}
	string s;
	for (int i = 0; i < 26; i++)
	{
		if (w[i] != 0)
		{
			while (w[i] != 0)
			{
				s += i + 'a';
				w[i]--;
			}
		}
	}
	int bucket = hashFunc(s);
	wList[bucket].push_back(word);
}

string Player::HashTable::find(const string word, int guess)
{
	int bucket = hashFunc(word);
	for (int i = 0; i < wList[bucket].size(); i++)
	{
		cout << wList[bucket][i] << endl;
	}
	return wList[bucket][guess];
}

unsigned long Player::HashTable::hash(const char *str) const 
//http://stackoverflow.com/questions/19892609/djb2-by-dan-bernstein-for-c
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = hash * 33 + c;

	return hash;
}

unsigned long Player::HashTable::hashFunc( const string word) const
{
	int i = 0;
	unsigned long total = 0;
	for (i = 0; i < word.length(); i++)
		total += hash(&word[i]);
	total = total % P_NUM_BUCK;
	return total;
}
