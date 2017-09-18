#ifndef PLAYER
#define PLAYER

#include <string>
#include <vector>

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
	int update;
	int random;
	int curVec;
	std::string ch;
	char curChar;

	class HashTable
	{
	public:
		HashTable()
			:wList(100000)
		{ }
		void add(const std::string word, int g, char c);
		std::string find(int vec, int spot);
		void print(int i, int j)
		{
			std::cout << wList[i][j] << std::endl;
		}
		int size(int buck)
		{
			return wList[buck].size();
		}
	private:
		std::vector< std::vector<std::string> >	wList;
	};

	HashTable list;
};

#endif // !PLAYER