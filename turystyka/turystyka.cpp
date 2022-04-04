#include <iostream>
#include <vector>

using namespace std;

int main()
{
	//wczytuje: m - liczba miast, d - liczba drog
	int m, d;
	cin >> m;
	cin >> d;

	//wczytuje: c1,c2 - numery miast, p - max liczba pasazerow
	//tablice c1, c2, p - twoarza zbior s zawierajacy krawedzie grafu
	int* c1 = new int[d];
	int* c2 = new int[d];
	int* p = new int[d];
	for (int i = 0; i < d; i++) {
		cin >> c1[i];
		cin >> c2[i];
		cin >> p[i];
	}

	//wczytuje przypadki testowe
	//s - poczatek trasy, e - koniec trasy, t - liczba pasazerow
	int s, e, t;
	cin >> s;
	cin >> e;
	while (s || e) {
		cin >> t;

		//tworzy poczatkowy las l
		vector <vector<int>> l(m);
		for (int i = 0; i < m; i++)
			l[i].push_back(i+1);

		while (true) {

		}


		l.clear();
	}


	delete[] c1;
	delete[] c2;
	delete[] p;
}