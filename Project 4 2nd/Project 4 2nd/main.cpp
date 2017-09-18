#include <iostream>
#include <fstream>
#include "Game.h"
#include "Player.h"
using namespace std;

const char* filename = "wordlist.txt";
// A Windows user might have the path be "C:/CS32/P4/wordlist.txt"
// A Mac user might have it be "/Users/fred/CS32/P4/wordlist.txt"

void play(Game& g, Player &p, int& min, int& max)
{
	int secretLength = g.secretWordLength();
	int nTurns = 0;
	for (;;)
	{
		int nInRightPlace, nInWrongPlace;
		string probe = p.generateProbeWord();
		g.probe(probe, nInRightPlace, nInWrongPlace);
		// repeat probes until word is guessed
		nTurns++;
		if (nInRightPlace == secretLength)
			break;
		p.learn(probe, nInRightPlace, nInWrongPlace);
	}

	cerr << "The Player probed " << nTurns << " times!" << endl;
	if (nTurns < min && nTurns > 1)
		min = nTurns;
	if (nTurns > max)
		max = nTurns;
}

int main()
{
	ifstream wordlistfile(filename);
	if (!wordlistfile)
	{
		cerr << "Cannot open " << filename << "!" << endl;
		return 1;
	}
	vector<string> words;

	string w;
	while (wordlistfile >> w)
		words.push_back(w);

	int min = 60000;
	int max = 1;
	for (int i = 0; i < words.size(); i++)
	{
		Player player(words);
		Game g(words);
		if (!g.setSecretWord(words[i]))  // Supply the secret word
		{
			cerr << "Secret word is not in word list!" << endl;
			return 1;
		}

		play(g, player, min, max);
	}

	//Player player(words);
	//Game g(words);
	//if (!g.setSecretWord("absconded"))  // Supply the secret word
	//{
	//	cerr << "Secret word is not in word list!" << endl;
	//	return 1;
	//}

	//play(g, player, min, max);

	cout << min << " " << max;
}