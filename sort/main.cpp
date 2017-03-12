#include <string>
#include <map>
#include <fstream>
#include <set>

using namespace std;

int main()
{
	ifstream fin("in.txt");
	string word;
	map<string, size_t> words;
	set<size_t> count;

	// input
	if (!fin.is_open()) return 1;
	while (fin >> word)
	{
		for (size_t i = 0; i < word.length(); i++)
		{
			if ((word[i] < 65 || word[i] > 90) && (word[i] < 97 || word[i] > 122))
			{
				word.erase(i, 1);
				--i;
				continue;
			}
			if ((word[i] >= 65) && (word[i] <= 90)) word[i] += 32;
		}
		++words[word];
	}
	fin.close();

	// search max
	for (auto it = words.begin(); it != words.end(); ++it)
	{
		count.insert(it->second);
	}

	// output
	ofstream fout("out.txt");
	if (!fout.is_open()) return 1;
	for (auto itc = count.rbegin(); itc != count.rend(); ++itc)
	{
		for (auto it = words.begin(); it != words.end(); ++it)
		{
			if (it->second == *itc) fout << it->first << " : " << it->second << endl;
		}
	}
	fout.close();

	return 0;
}

