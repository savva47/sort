#include "bohr_vrtx.h"

bohr_vrtx::bohr_vrtx()
{
	bohr.push_back(make_bohr_vrtx());
}

void bohr_vrtx::check_string_in_bohr_else_add(const string& s)
{
	int num = 0;
	for (int i = 0; i < s.length(); i++)
	{
		char ch = s[i] - 'a';
		if (bohr[num].next_vrtx[ch] == -1)
		{
			bohr.push_back(make_bohr_vrtx());
			bohr[num].next_vrtx[ch] = bohr.size() - 1;
		}
		num = bohr[num].next_vrtx[ch];
	}
	if (bohr[num].flag)
	{
		++bohr[num].pattern_count[bohr[num].pat_num].second;
	}
	else
	{
		bohr[num].flag = true;
		pattern_count.push_back(make_pair(s, 1u));
		bohr[num].pat_num = pattern_count.size() - 1;
	}
}

bohr_vrtx bohr_vrtx::make_bohr_vrtx()
{
	bohr_vrtx v;
	memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
	v.flag = false;
	return v;
}