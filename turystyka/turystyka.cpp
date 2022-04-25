#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

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

	//zwraca wartosc argumentu p
	int get_p() {
		return p;
	}

	//zamienia wartosci argumetnow: c1 i c2
	void swap_c() {
		int ancillary = c1;
		c1 = c2;
		c2 = ancillary;
	}
};

//wczytuje do tablicy roads: c1,c2 - numery miast, p - max liczba pasazerow
void set_roads(vector <Road> &roads, int d) {
	for (int i = 0; i < d; i++) {
		int c1, c2, p;
		cin >> c1 >> c2 >> p;
		roads[i].set(c1, c2, p);
	}
}

//znajduje sasiada miasta 'c'
int neighbour(vector <int> forest, int c) {
	int current_value = forest[c - 1];

	if (current_value != c)
		return neighbour(forest, current_value);
	else
		return c;	
}

//po wykonaniu w tablicy roads zostaja drogi nalezace do MST
void mst(vector <Road>& roads, int m, int d) {

	//zamienia wagi 'p' drogi na przeciwne aby algorytm mogl zadzialac
	for (int i = 0; i < d; i++)
		roads[i].opposite_p();
	//sortuje tablice roads rosnaco wzgledem atrybutu 'p'
	sort(roads.begin(), roads.end());

	//tworzy poczatkowy las 'forest' z wierzcholkow oryginalnego grafu
	vector <int> forest(m);
	for (int i = 0; i < m; i++)
		forest[i] = i+1;
	

	//zrobic warunek przerwania petli kiedy utworzymy mst, nie zapomniec o zamianie 2<1


	for (int i = 0; roads.size() != m - 1; i++) {
		//dla wszystkich drog wartosci c1 musza byc zawsze mniejsze albo zawsze wieksze od wartosci c2, aby algorytm dzialal poprawnie
		if (roads[i].get_c1() > roads[i].get_c2())
			roads[i].swap_c();

		//sprawdza czy dwa miasta sa juz polaczone (czy naleza do tego samego drzewa)
		if (neighbour(forest, roads[i].get_c1()) == neighbour(forest, roads[i].get_c2())) {
			roads.erase(roads.begin() + i);
			i--;
		}
		else
			forest[neighbour(forest, roads[i].get_c1()) - 1] = neighbour(forest, roads[i].get_c2());
		
	}

	//zamienia wagi 'p' jeszcze raz na przeciwne
	for (int i = 0; i < m-1; i++)
		roads[i].opposite_p();

	forest.clear();
}

//tworzy tablice sasiedztwa dla miast
void neighbours_set(vector <vector<int>>& neighbours, vector <Road> roads) {
	//zmienne do przechowywania aktualnej wartosci c1 i c2
	int c1, c2;
	for (size_t i = 0; i < roads.size(); i++) {
		c1 = roads[i].get_c1();
		c2 = roads[i].get_c2();
		neighbours[c1 - 1].push_back(c2);
		neighbours[c2 - 1].push_back(c1);
	}
}

//funckja znajdujaca droge z miasta 's' do 'e'
void find_connection(vector <vector<int>> neighbours, vector <bool>& visited, int s, int e, bool& check, vector <int>& connection) {
	//ustawia miasto jako odwiedzone
	visited[s - 1] = true;

	//przeszukuje sasiadow miasta
	for (size_t i = 0; i < neighbours[s - 1].size(); i++) {
		int next_city = neighbours[s - 1][i];
		if (next_city == e)
			check = true;
		else if (!visited[next_city - 1])
			find_connection(neighbours, visited, next_city, e, check, connection);
		if (check) {
			connection.push_back(s);
			break;
		}
	}
}

//funkcja zwraca najwieksza ilosc pasazerow mozliwa do przewiezienia bez kierowcy
int maximum_passengers(vector <Road> roads, vector <int> connection) {
	//zmienne do przechowywania aktualnej wartosci c1 i c2
	int c1, c2, min;
	//tablica przechowuje mozaliwa do przewiezenia ilolsc pasazerow
	vector <int> passengers;
	for (size_t i = 0; i < connection.size() - 1; i++) {
		for (size_t j = 0; j < roads.size(); j++) {
			c1 = roads[j].get_c1();
			c2 = roads[j].get_c2();
			if ((c1 == connection[i] && c2 == connection[i + 1]) || (c2 == connection[i] && c1 == connection[i + 1])) {
				passengers.push_back(roads[j].get_p());
				break;
			}
				
		}
	}
	min = *min_element(passengers.begin(), passengers.end());
	passengers.clear();
	return min;
}

int main()
{
	//wczytuje: m - liczba miast, d - liczba drog
	int m, d;
	cin >> m >> d;

	//tworzy tablice obiektow zawiarajacych informacje o drogach
	vector <Road> roads(d);

	//wczytuje informacje o drogach do tablicy roads
	set_roads(roads, d);

	//wczytuje przypadki testowe
	//s - poczatek trasy, e - koniec trasy, t - liczba pasazerow
	int s, e, t;
	cin >> s >> e;

	//tworzy MST z podanych drog
	mst(roads, m, d);

	//wypisuje mst
	/*cout << '\n';
	for (int i = 0; i < m - 1; i++) {
		cout << roads[i].get_c1() << ' ' << roads[i].get_c2() << ' ' << roads[i].get_p()<<'\n';
	}*/

	//tablica przechowujaca sasiadow danego miasta
	vector <vector<int>> neighbours(m);
	neighbours_set(neighbours, roads);

	//tablica przechowujaca informacje czy dane miasto zostalo juz odwiedzone
	vector <bool> visited(neighbours.size());

	while (s || e) {
		cin >> t;
		//zmienna 'check' przechowuje informacje czy znaleziono juz miasto docelowe
		bool check=false;
		//ustawia wszystkie miasta jako nieodwiedzone
		fill(visited.begin(), visited.end(), false);
		//tablica w ktorej znajdzie sie polaczenie miedzy miastami
		vector <int> connection;
		//pierwszym elementem tablicy zawsze bedzie miasto docelowe
		connection.push_back(e);
		
		find_connection(neighbours, visited, s, e, check, connection);

		//wypisuje minimalna liczbe kursow
		cout << ceil((float)t / (maximum_passengers(roads, connection) - 1));
		
		connection.clear();
		cin >> s >> e;
		if (s || e)
			cout << '\n';
	}

	//zwalnianie pamieci
	roads.clear();
	for (size_t i = 0; i < neighbours.size(); i++)
		neighbours[i].clear();
	neighbours.clear();
	visited.clear();

}