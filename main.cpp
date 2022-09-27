#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> take_out(vector <int> things, int cur, int wdiff, int vdiff, int w, int v, int *weight, int *value)
{
	vector <int> nw;
	if (w > wdiff || v > vdiff || cur >= things.size() - 1)
		return nw;
	if (w + weight[things[cur]] == wdiff && v + value[things[cur]] == vdiff)
	{
		nw.push_back(things[cur]);
		return nw;
	}
	nw = take_out(things, cur + 1, wdiff, vdiff, w, v, weight, value);
	if (nw.empty())
	{
		w += weight[things[cur]];
		v += value[things[cur]];
		nw = take_out(things, cur + 1, wdiff, vdiff, w, v, weight, value);
		nw.push_back(things[cur]);
	}
	cout << things[cur] << endl;
	return nw;
}

vector <int> put_thing(vector <int> things, int i, int j, int *weight, int maxweight, int *value, int vdiff)
{
	int k, f, mx = 0, w = 0, v = 0, wdiff, x = 0, thing = i;
	vector <int> th; //things we took out
	if (things.size() > 0)
	{
		if (things[things.size() - 1] != thing)
			things.push_back(thing);
		else
			return things;
	}
	else
		things.push_back(thing);
	for (k = 0; k < things.size(); k++)
		w = w + weight[things[k]];
	
	wdiff = j - weight[i];
	cout << wdiff << " " << vdiff << endl;
	if (w > maxweight)
	{
		th = take_out(things, 0, wdiff, vdiff, 0, 0, weight, value);
		for (k = 0; k < th.size(); k++)
			for (f = 0; f < things.size(); f++)
				if (things[f] == th[k])
				{
					things[f] = things[things.size() - 1];
					things.pop_back();	
				}
	}
	return things;
}

vector <int> find(vector <vector <int>> things, int *weight, int maxweight)
{
	int i, j, cur;
	vector <int> th;
	cur = maxweight;
	for (i = things.size() - 1; i >= 0; i--)
	{
		for (j = things[i].size() - 1; j >= 0; j--)
		{
			if (things[i][j] == cur)
			{
				th.push_back(i);
				cur = cur - weight[i + 1];
				break;
			}
		}
	}
	return th;
}

void solving(int n, int maxweight, int *value, int *weight)
{
	int *maxvalue1, *maxvalue2, *x, i, j, k;
//	vector <int> things;
	vector <vector <int>> things;
	vector <int> th;
	maxvalue1 = new int[maxweight + 1];
	maxvalue2 = new int[maxweight + 1];
	maxvalue1[0] = 0;
	maxvalue2[0] = 0;
	for (i = 0; i < maxweight + 1; i++)
		maxvalue1[i] = 0;
	for (i = 1; i < n + 1; i++)
	{
		for (j = 1; j < maxweight + 1; j++)
			if (j >= weight[i])
			{
				maxvalue2[j] = max(maxvalue1[j], maxvalue1[j - weight[i]] + value[i]);
				if (maxvalue1[j] != maxvalue2[j])
				{
					th.push_back(j);
				}
			}
			else
				maxvalue2[j] = maxvalue1[j];
		x = maxvalue2;
		maxvalue2 = maxvalue1;
		maxvalue1 = x;
		things.push_back(th);
		th.clear();
	}

	th = find(things, weight, maxweight);
	for (i = 0; i < th.size(); i++)
		cout << th[i] << " ";
	cout << endl;
	delete(maxvalue2);
	delete(maxvalue1);
}

int main()
{
	int *value, *weight, n, maxweight, i;
	cin >> n;
	cin >> maxweight;
	value = new int[n + 1];
	weight = new int[n + 1];
	for (i = 1; i < n + 1; i ++)
	{
		cin >> value[i];
		cin >> weight[i];
	}
	solving(n, maxweight, value, weight);
	delete(value);
	delete(weight);
	return 0;
}
