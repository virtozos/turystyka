#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//klasa zawierajaca informacje o drogach
class Road {
private:
	//c1,c2 - numery miast, p - max liczba pasazerow
	int c1, c2, p;

public:
	void set(int c1_in, int c2_in, int p_in) {
		c1 = c1_in;
		c2 = c2_in;
		p = p_in;
	}

	//przeciazenie operatora < aby dzialala funjkcja sortujaca
	bool operator< (Road r) {
		return this->p < r.p;
	}

	//zamienia wartosc atrybutu p na przeciwna
	void opposite_p() {
		p *= -1;
	}

	//zwraca wartosc argumentu c1
	int get_c1() {
		return c1;
	}
	
	//zwraca wartosc argumentu c2
	int get_c2() {
		return c2;
	}
};

//wczytuje: c1,c2 - numery miast, p - max liczba pasazerow do tablicy roads
void set_roads(vector <Road> &roads, int d) {
	for (int i = 0; i < d; i++) {
		int c1, c2, p;
		cin >> c1 >> c2 >> p;
		roads[i].set(c1, c2, p);
	}
}

//znajduje sasiada miasta 'c'
int find(vector <int> forest, int c) {

}

//po wykonaniu w tablicy roads zostaja drogi nalezace do MST
void mst(vector <Road> &roads, int m, int d) {

	//zamienia wagi 'p' drogi na przeciwne aby algorytm mogl zadzialac
	for (int i = 0; i < d; i++)
		roads[i].opposite_p();
	//sortuje tablice roads rosnaco wzgledem atrybutu 'p'
	sort(roads.begin(),roads.end());

	//tworzy poczatkowy las 'forest' z wierzcholkow oryginalnego grafu
	vector <int> forest(m);
	for (int i = 0; i < m; i++)
		forest[i] = i+1;
	
	while (roads.size() != m - 1) {

	}
	//sprawdza czy dwa miasta sa juz polaczone (czy naleza do tego samego drzewa)
	if (find(forest, roads[i].get_c1()) != find(forest, roads[i].get_c2()) {
		
	}

	forest.clear();
}

int main()
{
	//wczytuje: m - liczba miast, d - liczba drog
	int m, d;
	cin >> m >> d;

	//tworzy tablice obiektow zawiarajacych informacje o drogach
	//Road* roads = new Road[d];
	vector <Road> roads(d);

	//wczytuje informacje o drogach do tablicy roads
	set_roads(roads, d);

	//wczytuje przypadki testowe
	//s - poczatek trasy, e - koniec trasy, t - liczba pasazerow
	int s, e, t;
	cin >> s >> e;

	//tworzy MST z podanych drog
	mst(roads, m, d);

	while (s || e) {
		cin >> t;

		//tworzy poczatkowy las l
		vector <vector<int>> l(m);
		for (int i = 0; i < m; i++)
			l[i].push_back(i+1);

		while (true) {

		}


		roads.clear();
		cin >> s >> e;
	}

}