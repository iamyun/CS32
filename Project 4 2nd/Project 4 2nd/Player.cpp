#include <iostream>
#include "Player.h"
using namespace std;

//insert all words into data structure
Player::Player(const vector<string> &words)
{
	for (int i = 0; i < words.size(); i++)
	{
		list.add(words[i], 0, 'a');
	}
	pWord = "";
	guesses = 0;
	update = 0;
	random = 0;
	curVec = 0;
	ch = "a";
	curChar = 'a';
}

//guess a word from the list
string Player::generateProbeWord()
{
	if (guesses == 0)
	{
		pWord = 'I';
		guesses++;
	}
	if (guesses == 1)
		for (int i = 0; i < 21; i++)
			pWord += 'a';
	//if all 26 characters are tested, have to guess from whatever is in the vector
	if (curChar == 0)
	{
		int total = 0;
		int repeat = 1;
		//gets the spot of the vector in current updated list
		for (int i = ch.size()-1; i >= 0; i--)
		{
			if (ch.size() == 1)
				total += (ch[i] - 'a') * 21 + 1;
			else if (ch[i] == ch[i - 1])
				repeat++;
			else
			{
				total += (ch[i] - 'a') * 21 + repeat;
				break;
			}
		}
		//guess word from the list one by one
		if (random < list.size(update*550 + total))
		{
			pWord = list.find(update*550 + total, random);
			random++;
		}
	}
	guesses++;
	return pWord;
}

//update data structure base on what's returned from game
void Player::learn(string probe, int nInRightPlace, int nInWrongPlace)
{
	char w = probe[0];
	string s = "";
	for (int i = 0; i < 21; i++)	//a string will all same characters
		s += w;

	if (s == probe && nInRightPlace > 0)	
	//if the probeWord is just all same characters, and bulls is not 0
	//then go to the vector that stores the words that has bulls many "s"
	//and reorganize those words and add them to the end of the current hashtable
	{
		//vec is where the vector after elimination is at
		//basically my hash function. Multiplies 550 because everytime it
		//updates, assumes it takes up 550 slots since 21*26 = 546
		int spot = (w - 'a') * 21 + nInRightPlace;
		int vec = update * 550 + spot;
		curVec = vec;

		int record = nInRightPlace;
		while (record != 0)
		{
			ch += w;
			record--;
		}

		//if the vector that it supposed to be in is empty, it's not in the word list
		if (list.size(vec) == 0)
		{
			pWord = "not in word list";
			return;
		}

		//if there are only one word left in the wordlist, that should be the secretWord, so just probe that
		if (list.size(vec) < 10)
		{
			pWord = list.find(vec, random);
			random++;
			return;
		}

		//otherwise, update wordlist. 
		//Get the vector that has words with exact numbers of 
		//characters that are checked so far, reorganized them base on
		//numbers of the smallest character in it that is greater than probe[0]
		for (int i = 0; i < list.size(vec); i++)
		{
			string word = list.find(vec, i);	
			list.add(word, update+1, w+1);
		}
		update++;	//increase update, so when we start looking for words next time
					//start at the next 550 slot of hashtable

		//finds out what character to check next but finding 
		//among the words, what is the smallest character they have that is 
		//greater than probe[0]
		for (int i = update * 550 + 1; i < (update + 1) * 550 + 1; i++)
		{
			if (list.size(i) != 0)	
			//the first vector that's not empty has the character that I am looking for
			{
				string word = list.find(i, 0);
				int freq[26] = { 0 };
				for (int j = 0; j < word.size(); j++)
				{
					int n = word[j] - 'a';
					freq[n]++;
				}
				char c = w+1;
				for (int k = 0; k < 26; k++)
				{
					if (freq[k] != 0 && (k + 'a') > w)
					{
						c = k + 'a';
						break;
					}
				}	

				curChar = c;	//gets what's the current character that we are checking

				//get the character and make the probe word become a string of length 21 only with that character
				pWord = "";
				for (int j = 0; j < 21; j++)
					pWord += c;
				return;
			}
		}
	}
	else if (s == probe && nInRightPlace == 0)		
	//if the word does not contain the character that we just checked
	//check the character that is just greater than it
	{
		w = guesses + 'a';
		if (curChar == 'z')
			curChar = 0;
		else
			curChar = w;
		pWord = "";
		for (int i = 0; i < 21; i++)
			pWord += w;
	}
	//if haven't checked all characters yet, but the vector has less than 10 words left in it
	//just guess from the vector
	else if (s != probe && curChar != 0)
	{
		pWord = list.find(curVec, random);
		random++;
		return;
	}

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

//add word to the hashtable
//organize by the first character in the word that is greater than or equal to 
//the character we passed in.
void Player::HashTable::add(const string word, int g, char c)
{
	int w[26] = { 0 };
	for (int j = 0; j < word.size(); j++)
	{
		int i = word[j] - 'a';
		w[i]++;
	}
	int bucket = 0;
	for (int i = 0; i < 26; i++)
	{
		if (w[i] != 0 && i+'a' >= c)
		{
			bucket = i * 21 + w[i];
			break;
		}
		if (i == 25 && g > 0)
		{
			bucket = (c - 'a' - 1) * 21 + w[c - 'a' - 1];
		}
	}
	wList[g*550 + bucket].push_back(word);
}

//find the word from the hashtable
string Player::HashTable::find(int vec, int spot)
{
	if (vec < wList.size() && spot < wList[vec].size())
		return wList[vec][spot];
	else
		return "not in word list";
}
