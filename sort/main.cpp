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
	
	map<size_t, bool> count;
	size_t max = 0;

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
		count[(*it).second] = true;
		if ((*it).second > max)
		{
			max = (*it).second;
		}
	}

	// сортировка
	map<string, size_t> words(unordered_words.begin(), unordered_words.end());

	// вывод
	ofstream fout("out.txt");
	if (!fout.is_open()) return 1;
	while (max != 0)
	{
		if (count[max])
		{
			for (auto it = words.begin(); it != words.end(); ++it)
			{
				if ((*it).second == max) fout << (*it).first << " : " << (*it).second << endl;
			}
		}
	--max;
	}
	fout.close();

	return 0;
}

