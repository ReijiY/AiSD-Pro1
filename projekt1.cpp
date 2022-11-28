#include "projekt1.h"


void pro::init()
{
	// podanie warto�ci czasu do generatora liczb losowych
	srand(time(NULL));
}

inline int pro::losowa_liczba(int min, int max)
{
	// zwr�cenie losowej liczby z przedzia�u [min, max]
	return rand() % ((max + 1) - min) + min;
}

std::vector<int> pro::generuj_losowy_ciag(int min, int max, int width)
{
	// weryfikacja kolejno�ci argument�w w podanym zakresie
	if (min > max) std::swap(min, max);

	// utworzenie n-elementowego kontenera na losowy ciag
	std::vector<int> res(width);

	// generator losuj�cy warto�ci z przedzia�u [min, max]
	auto gen = [&min, &max]() {
		return losowa_liczba(min, max);
	};

	// wype�nienie losowego ci�gu warto�ciami losowanymi przez generator
	std::generate(res.begin(), res.end(), gen);

	//zwr�cenie utworzonej tablicy
	return res;
}

std::vector<std::vector<int>> pro::generuj_losowy_ciag_2d(int min, int max, int width, int height)
{
	// utworzenie kontenera na losowe ci�gi
	std::vector<std::vector<int>> res;
	
	// zmiana rozmiaru kontenera na h-elementowy
	res.resize(height);

	// generator losuj�cy warto�ci z przedzia�u [min, max]
	auto gen = [&min, &max]() {
		return losowa_liczba(min, max);
	};

	// dla ka�dego elementu kontenera
	for (auto &el : res)
	{
		// wpisanie pustego ci�gu o rozmiarze w
		el = std::vector<int>(width);
		
		// wype�nienie losowego ci�gu warto�ciami losowanymi przez generator
		std::generate(el.begin(), el.end(), gen);
	}

	//zwr�cenie utworzonej tablicy
	return res;
}

std::vector<int> pro::generuj_ciag_z_zakresu(int start, int end, int step)
{
	// weryfikacja kolejno�ci argument�w w podanym zakresie
	if (start > end) std::swap(start, end);

	// krok nie mo�e by� r�wny 0
	if (step == 0) step = 1;

	// utworzenie kontenera na ciag
	std::vector<int> res;

	// przewidziany rozmiar koncowy kontenera
	int rozmiar_kontenera = (end - start) / step + 1;

	// zmiana rozmiaru kontenera na ko�cow� ilo�� element�w
	res.resize(rozmiar_kontenera);

	// indeks nast�pnego elementu tablicy
	int i = 0;

	// dla iteratora opisanego argumentami funkcji
	for (int iterator = start; iterator <= end; iterator += step)
	{
		// wpisanie warto�ci iteratora do tablicy
		res[i++] = iterator;
	}


	// zwracanie utworzonej tablicy
	return res;
}

std::vector<int>::iterator pro::quicksort_iterator_partition(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
	// zabezpieczenie przed wywo�aniem na niew�a�ciwym zakresie
	if (std::distance(start, end) <= 0) return end;

	// wybranie warto�ci pierwszego elementu zakresu jako elementu �rodkowego
	int pivot = *start;

	// wyznaczenie pozycji elementu dziel�cego poprzez policzenie element�w o mniejszej lub tej samej warto�ci
	int count = 0;
	// dla iteratora przechodz�cego od drugiego elementu do ko�ca przedzia�u
	for (std::vector<int>::iterator it = start + 1; it != end; it++) {
		// je�eli warto�� wskazywana przez iterator jest mniejsza lub r�wna warto�ci pivot
		if (*it <= pivot)
		{
			// zwi�ksz licznik
			count++;
		}
	}

	// stworzenie iteratora na wyliczonej pozycji
	std::vector<int>::iterator pivot_index = start + count;
	// zamienienie warto�ci pierwszego elementu i elementu na wyznaczonym iteratorze
	std::swap(*pivot_index, *start);

	// stworzenie iterator�w wskazuj�cych na pierwszy i ostatni element ci�gu
	std::vector<int>::iterator it_1 = start, it_2 = end - 1;

	// dop�ki oba iteratory nie przekroczy�y indeksu warto�ci pivot
	while (it_1 < pivot_index && it_2 > pivot_index) {

		// dop�ki warto�� pierwszego iteratora jest mniejsza lub r�wna warto�ci pivot
		while (*it_1 <= pivot) {
			// zwi�ksz pierwszy iterator
			++it_1;
		}

		// dop�ki warto�� drugiego iteratora jest wi�ksza od warto�ci pivot
		while (*it_2 > pivot) {
			// zmniejsz drugi iterator
			--it_2;
		}

		// je�eli pierwszy iterator jest mniejszy od indeksu pivota i drugi iterator jest od niego wi�kszy
		if (it_1 < pivot_index && it_2 > pivot_index) {
			// zamie� ze sob� warto�ci wskazywane przez iteratory
			std::swap(*it_1++, *it_2--);
		}
	}

	// zwr�� iterator wskazuj�cy na warto�� pivota
	return pivot_index;
}

void pro::quicksort_iterator(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	// zabezpieczenie przed wywo�aniem na niew�a�ciwym zakresie oraz warunek ko�cz�cy prac� funckji rekurencyjnej
	if (std::distance(begin, end) <= 0) return;

	// podzia� ci�gu na dwie cz�ci z warto�ciami odpowiednio mniejszymi i wi�kszymi od pierwszego elementu
	std::vector<int>::iterator p = pro::quicksort_iterator_partition(begin, end);

	// wykonanie sortowania na pierwszej po�owie podzielonego ci�gu
	pro::quicksort_iterator(begin, p);

	// wykonanie sortowania na drugiej po�owie podzielonego ci�gu
	pro::quicksort_iterator(p + 1, end);
}

std::vector<int>::iterator pro::linear_search_iterator(std::vector<int>& arr, int val)
{
	// zwr�� wynik wyszukiwania liniowego zaimplementowanego w standardzie C++
	return std::find(arr.begin(), arr.end(), val);
}

std::vector<int>::iterator pro::set_intersection(const std::vector<int>& arr1, const std::vector<int>& arr2, std::vector<int>::iterator res)
{
	// wyw�aszczenie iterator�w pocz�tk�w i ko�c�w tablic
	std::vector<int>::const_iterator first1 = arr1.begin(), last1 = arr1.end(), first2 = arr2.begin(), last2 = arr2.end();

	// dop�ki iterator �adnej z tablicy nie dotar� do jej ko�ca
	while (first1 != last1 && first2 != last2) 
	{
		// je�eli warto�� wskazywana przez pierwszy iterator jest mniejsza ni� warto�� wskazywana przez drugi iterator
		if (*first1 < *first2) 
		{
			// zwi�ksz pierwszy iterator
			++first1;
		}
		// w przeciwnym wypadku, je�eli warto�� wskazywana przez drugi iterator jest mniejsza od warto�ci wskazywanej przez pierwszy iterator
		else if (*first2 < *first1)
		{
			// zwi�ksz drugi operator
			++first2;
		}
		// w przeciwnych wypadkach
		else 
		{
			// w tym momencie wiemy, �e pierwszy i drugi iterator wskazuj� na tak� sam� warto��
			// wpisz warto�� wskazywan� przez pierwszy iterator do pami�ci wskazywanej przez iterator tablicy z wynikami
			*res = *first1;
			
			// zwi�ksz iterator tablicy z wynikami oraz pierwszej i drugiej tablicy
			++res;
			++first1;
			++first2;
		}
	}
	// zwr�� iterator tablicy z wynikami
	return res;
}

void pro::opisz_ciag(const std::vector<int>& arr)
{
	// wypisanie rozmiaru ci�gu
	std::cout << "[" << arr.size() << "]\n";
}

void pro::opisz_ciag(const std::vector<std::vector<int>>& arr)
{
	// je�eli tablica posiada wiersze
	if (arr.size() > 0)
	{
		// sprawdzenie czy wiersze s� tej samej d�ugo�ci

		int i, j, size = 0;

		// dla ka�dego wiersza
		for (i = 0; i < arr.size(); i++)
		{
			// przypisanie warto�ci tego wiersza do zmiennej
			size = arr[i].size();

			// dla ka�dego nast�pnego wiersza
			for (j = i + 1; j < arr.size(); j++)
			{
				// je�eli d�ugo�� wiersza jest inna ni� warto�� zapisanej zmiennej
				if (arr[j].size() != size)
				{
					// przerwij p�tl�
					break;
				}
			}

			// je�eli p�tla zosta�a przerwana
			if (j < arr.size())
			{
				// przerwij szukanie r�nych wierszy
				break;
			}
		}

		// je�eli p�tla zosta�a przerwana
		if (i < arr.size())
		{
			// wypisz nieznan� szeroko��
			std::cout << "[?x" << arr.size() << "]\n";

			// zako�cz wykonywanie funkcji
			return;
		}

		// je�eli nie znaleziono r�nych d�ugo�ci wierszy
		// wypisz wymiary ostatniego sprawdzonego wiersza na ilo�� wierszy
		std::cout << "[" << size << "x" << arr.size() << "]\n";
	}

	// wypisz brak element�w
	std::cout << "[0x" << 0 << "]\n";
}

std::vector<int> pro::odczytaj_ciag_z_pliku(const char* nazwa_pliku, char delimiter)
{
	// otwarcie pliku do odczytu
	std::fstream ifs(nazwa_pliku, std::ios::in);

	// weryfikacja otwarcia pliku
	if (!ifs.good())
		// b��d przy pr�bie otwarcia pliku
		throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do odczytu!";

	// utworzenie tablicy na warto�ci odczytane z pliku
	std::vector<int> arr;

	// dla ka�dego �a�cucha znak�w, oddzielonego znakiem ko�ca warto�ci, odczytanego z pliku
	for (std::string el; std::getline(ifs, el, delimiter); )
		// wpisanie do tablicy warto�ci przekonwertowanej na liczb�
		arr.push_back(atoi(el.c_str()));

	// zwr�cenie tablicy z warto�ciami
	return arr;
}

std::vector<std::vector<int>> pro::odczytaj_ciag_2d_z_pliku(const char* nazwa_pliku, char delimiter_val, char delimiter_array)
{
	// otwarcie pliku do odczytu
	std::fstream ifs(nazwa_pliku, std::ios::in);

	// weryfikacja otwarcia pliku
	if (!ifs.good())
		// b��d przy pr�bie otwarcia pliku
		throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do odczytu!";

	// utworzenie tablic na warto�ci odczytane z pliku
	std::vector<std::vector<int>> data;
	std::vector<int> arr;

	// dla ka�dego �a�cucha znak�w, oddzielonego znakiem ko�ca tablicy, odczytanego z pliku
	for (std::string line_str; std::getline(ifs, line_str, delimiter_array); )
	{
		// wyczyszczenie tablicy warto�ci
		arr.clear();

		// przypisanie odczytanego �a�cucha znak�w do strumienia tekstowego
		std::stringstream line(line_str);

		// dla ka�dego �a�cucha znak�w, oddzielonego znakiem ko�ca warto�ci, ze strumienia tekstowego
		for (std::string el; std::getline(line, el, delimiter_val); )
		{
			// wpisanie do tablicy warto�ci przekonwertowanej na liczb�
			arr.push_back(atoi(el.c_str()));
		}
		
		// wpisanie do tablicy dwuwymiarowej odczytanych warto�ci w postaci tablicy
		data.push_back(arr);
	}
		

	// zwr�cenie dwuwymiarowej tablicy z warto�ciami
	return data;
}


std::pair<std::vector<std::vector<int>>::const_iterator, std::vector<std::vector<int>>::const_iterator> pro::thread_bounds(const std::vector<std::vector<int>>& data, int thread_count, int thread_id)
{
	// odczytanie ilo�ci wierszy w tablicy dla operacji
	int data_size = data.size();

	// zmienna przechowuj�ca indeks w�tku, kt�ry jako pierwszy posiada mniej element�w od w�tku o indeksie o jeden mniejszym
	int break_point = data_size % thread_count;

	// obliczenie ilo�ci wierszy, za kt�rych przetworzenie ma by� odpowiedzialny w�tek o podanym numerze
	int weight_sum = thread_id < break_point ? data_size / thread_count + 1 : data_size / thread_count;

	// oblicznenie indeksu pocz�tku danych przydzielonych dla w�tku o podanym numerze
	int data_before = break_point - 1 < thread_id ? weight_sum * thread_id + break_point : weight_sum * thread_id;

	// utworzenie iterator�w pocz�tku i ko�ca danych
	auto first = data.begin() + data_before;
	auto last = first + weight_sum;

	
	if (std::distance(first, last) < 0) {
		std::cout << "\n first > last !!! \n";
	}

	if (std::distance(data.begin(), first) < 0) {
		std::cout << "\n first < data.begin() !!! \n";
	}

	if (std::distance(last, data.end()) < 0) {
		std::cout << "\n last > data.end() !!! \n";
	}

	// zwr�cenie pary iterator�w jako wyniku oblicze�
	return std::pair<std::vector<std::vector<int>>::const_iterator, std::vector<std::vector<int>>::const_iterator>(first, last);
}