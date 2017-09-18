#ifndef GAME
#define GAME

#include <string>
#include <vector>
#include <list>

const int GNUM_BUCK = 99973;

class Game
{
public:
	Game(const std::vector<std::string> &words);
	bool setSecretWord(const std::string &sw);
	int secretWordLength() const;
	void probe(const std::string &probeWord, int &nInRightPlace, int &nInWrongPlace);
	~Game();
private:
	Game(const Game&);
	Game& operator=(const Game&);
	std::string secretWord;

	class HashTable
	{
	public:
		HashTable()
			:wList(100000)
		{ }
		void insert(const std::string word);
		bool search(const std::string word);
	private:
		unsigned long hash(const char *str) const;
		unsigned long hashFunc(const std::string word) const;
		std::vector< std::vector<std::string> >	wList;
	};

	HashTable list;
};

#endif // !GAME