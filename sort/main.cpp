#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <set>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

int main()
{
	ifstream fin("in.txt");
	string word;
	unordered_map<string, size_t> words;
	set<size_t> count;

	// input
	size_t start_time = clock();
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
	cout << "input - " << clock() - start_time << endl;

	// search max
	start_time = clock();
	for (auto it = words.begin(); it != words.end(); ++it)
	{
		count.insert(it->second);
	}
	cout << "search max - " << clock() - start_time << endl;

	// sort
	start_time = clock();
	vector<pair<const string*, const size_t*>> elems;
	for (auto it = words.begin(); it != words.end(); ++it)
	{
		elems.push_back(make_pair(&it->first, &it->second));
	}
	sort(elems.begin(), elems.end(), [](auto left, auto right)
	{
		return *(left.first) < *(right.first);
	});
	cout << "sort - " << clock() - start_time << endl;

	// output
	start_time = clock();
	ofstream fout("out.txt");
	if (!fout.is_open()) return 1;
	for (auto itc = count.rbegin(); itc != count.rend(); ++itc)
	{
		for (auto ite = elems.begin(); ite != elems.end(); ++ite)
		{
			if (*(ite->second) == *itc) fout << *(ite->first) << " : " << *(ite->second) << endl;
		}
	}
	fout.close();
	cout << "output - " << clock() - start_time << endl;
	return 0;
}

