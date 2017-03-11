#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
	ifstream fin("in.txt");
	string word;
	unordered_map<string, size_t> unordered_words;
	unordered_map<size_t, bool> unordered_count;

	// ввод
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
		++unordered_words[word];
	}
	fin.close();

	// поиск максимума
	for (auto it = unordered_words.begin(); it != unordered_words.end(); ++it)
	{
		unordered_count[(*it).second] = true;
	}

	// сортировка
	map<string, size_t> words(unordered_words.begin(), unordered_words.end());
	map<size_t, bool> count(unordered_count.begin(), unordered_count.end());

	// вывод
	ofstream fout("out.txt");
	if (!fout.is_open()) return 1;
	for (auto itc = --count.end(); itc != --count.begin(); --itc)
	{
		if ((*itc).second)
		{
			for (auto it = words.begin(); it != words.end(); ++it)
			{
				if ((*it).second == (*itc).first) fout << (*it).first << " : " << (*it).second << endl;
			}
		}
	}
	fout.close();

	return 0;
}

