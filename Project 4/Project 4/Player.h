#ifndef PLAYER
#define PLAYER

#include <string>
#include <vector>

class Game;
const int P_NUM_BUCK = 99973;

class Player
{
public:
	Player(const std::vector<std::string> &words);
	std::string generateProbeWord();
	void learn(std::string probe, int nInRightPlace, int nInWrongPlace);
	~Player();
private:
	//prevent people from copying Player objects
	Player(const Player&);
	Player& operator=(const Player&);
	std::string pWord;
	int guesses;
	std::string wTotal;
	Game* g;

	class HashTable
	{
	public:
		HashTable()
			:wList(100000)
		{ }
		void add(const std::string word);
		std::string find(const std::string word, int guess);
	private:
		unsigned long hash(const char *str) const;
		unsigned long hashFunc(const std::string word) const;
		/*struct vocab
		{
			vocab(std::string vocab)
			{
				checked = false;
			}
			std::string word;
			bool checked;
		};*/
		std::vector< std::vector<std::string> >	wList;
	};

	HashTable list;
};

#endif // !PLAYER