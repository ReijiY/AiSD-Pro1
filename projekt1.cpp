#include "projekt1.h"


void pro::init()
{
	// podanie wartoœci czasu do generatora liczb losowych
	srand(time(NULL));
}

inline int pro::losowa_liczba(int min, int max)
{
	// zwrócenie losowej liczby z przedzia³u [min, max]
	return rand() % ((max + 1) - min) + min;
}

std::vector<int> pro::generuj_losowy_ciag(int min, int max, int width)
{
	// weryfikacja kolejnoœci argumentów w podanym zakresie
	if (min > max) std::swap(min, max);

	// utworzenie n-elementowego kontenera na losowy ciag
	std::vector<int> res(width);

	// generator losuj¹cy wartoœci z przedzia³u [min, max]
	auto gen = [&min, &max]() {
		return losowa_liczba(min, max);
	};

	// wype³nienie losowego ci¹gu wartoœciami losowanymi przez generator
	std::generate(res.begin(), res.end(), gen);

	//zwrócenie utworzonej tablicy
	return res;
}

std::vector<std::vector<int>> pro::generuj_losowy_ciag_2d(int min, int max, int width, int height)
{
	// utworzenie kontenera na losowe ci¹gi
	std::vector<std::vector<int>> res;
	
	// zmiana rozmiaru kontenera na h-elementowy
	res.resize(height);

	// generator losuj¹cy wartoœci z przedzia³u [min, max]
	auto gen = [&min, &max]() {
		return losowa_liczba(min, max);
	};

	// dla ka¿dego elementu kontenera
	for (auto &el : res)
	{
		// wpisanie pustego ci¹gu o rozmiarze w
		el = std::vector<int>(width);
		
		// wype³nienie losowego ci¹gu wartoœciami losowanymi przez generator
		std::generate(el.begin(), el.end(), gen);
	}

	//zwrócenie utworzonej tablicy
	return res;
}

std::vector<int> pro::generuj_ciag_z_zakresu(int start, int end, int step)
{
	// weryfikacja kolejnoœci argumentów w podanym zakresie
	if (start > end) std::swap(start, end);

	// krok nie mo¿e byæ równy 0
	if (step == 0) step = 1;

	// utworzenie kontenera na ciag
	std::vector<int> res;

	// przewidziany rozmiar koncowy kontenera
	int rozmiar_kontenera = (end - start) / step + 1;

	// zmiana rozmiaru kontenera na koñcow¹ iloœæ elementów
	res.resize(rozmiar_kontenera);

	// indeks nastêpnego elementu tablicy
	int i = 0;

	// dla iteratora opisanego argumentami funkcji
	for (int iterator = start; iterator <= end; iterator += step)
	{
		// wpisanie wartoœci iteratora do tablicy
		res[i++] = iterator;
	}


	// zwracanie utworzonej tablicy
	return res;
}

std::vector<int>::iterator pro::quicksort_iterator_partition(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
	// zabezpieczenie przed wywo³aniem na niew³aœciwym zakresie
	if (std::distance(start, end) <= 0) return end;

	// wybranie wartoœci pierwszego elementu zakresu jako elementu œrodkowego
	int pivot = *start;

	// wyznaczenie pozycji elementu dziel¹cego poprzez policzenie elementów o mniejszej lub tej samej wartoœci
	int count = 0;
	// dla iteratora przechodz¹cego od drugiego elementu do koñca przedzia³u
	for (std::vector<int>::iterator it = start + 1; it != end; it++) {
		// je¿eli wartoœæ wskazywana przez iterator jest mniejsza lub równa wartoœci pivot
		if (*it <= pivot)
		{
			// zwiêksz licznik
			count++;
		}
	}

	// stworzenie iteratora na wyliczonej pozycji
	std::vector<int>::iterator pivot_index = start + count;
	// zamienienie wartoœci pierwszego elementu i elementu na wyznaczonym iteratorze
	std::swap(*pivot_index, *start);

	// stworzenie iteratorów wskazuj¹cych na pierwszy i ostatni element ci¹gu
	std::vector<int>::iterator it_1 = start, it_2 = end - 1;

	// dopóki oba iteratory nie przekroczy³y indeksu wartoœci pivot
	while (it_1 < pivot_index && it_2 > pivot_index) {

		// dopóki wartoœæ pierwszego iteratora jest mniejsza lub równa wartoœci pivot
		while (*it_1 <= pivot) {
			// zwiêksz pierwszy iterator
			++it_1;
		}

		// dopóki wartoœæ drugiego iteratora jest wiêksza od wartoœci pivot
		while (*it_2 > pivot) {
			// zmniejsz drugi iterator
			--it_2;
		}

		// je¿eli pierwszy iterator jest mniejszy od indeksu pivota i drugi iterator jest od niego wiêkszy
		if (it_1 < pivot_index && it_2 > pivot_index) {
			// zamieñ ze sob¹ wartoœci wskazywane przez iteratory
			std::swap(*it_1++, *it_2--);
		}
	}

	// zwróæ iterator wskazuj¹cy na wartoœæ pivota
	return pivot_index;
}

void pro::quicksort_iterator(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	// zabezpieczenie przed wywo³aniem na niew³aœciwym zakresie oraz warunek koñcz¹cy pracê funckji rekurencyjnej
	if (std::distance(begin, end) <= 0) return;

	// podzia³ ci¹gu na dwie czêœci z wartoœciami odpowiednio mniejszymi i wiêkszymi od pierwszego elementu
	std::vector<int>::iterator p = pro::quicksort_iterator_partition(begin, end);

	// wykonanie sortowania na pierwszej po³owie podzielonego ci¹gu
	pro::quicksort_iterator(begin, p);

	// wykonanie sortowania na drugiej po³owie podzielonego ci¹gu
	pro::quicksort_iterator(p + 1, end);
}

std::vector<int>::iterator pro::linear_search_iterator(std::vector<int>& arr, int val)
{
	// zwróæ wynik wyszukiwania liniowego zaimplementowanego w standardzie C++
	return std::find(arr.begin(), arr.end(), val);
}

std::vector<int>::iterator pro::set_intersection(const std::vector<int>& arr1, const std::vector<int>& arr2, std::vector<int>::iterator res)
{
	// wyw³aszczenie iteratorów pocz¹tków i koñców tablic
	std::vector<int>::const_iterator first1 = arr1.begin(), last1 = arr1.end(), first2 = arr2.begin(), last2 = arr2.end();

	// dopóki iterator ¿adnej z tablicy nie dotar³ do jej koñca
	while (first1 != last1 && first2 != last2) 
	{
		// je¿eli wartoœæ wskazywana przez pierwszy iterator jest mniejsza ni¿ wartoœæ wskazywana przez drugi iterator
		if (*first1 < *first2) 
		{
			// zwiêksz pierwszy iterator
			++first1;
		}
		// w przeciwnym wypadku, je¿eli wartoœæ wskazywana przez drugi iterator jest mniejsza od wartoœci wskazywanej przez pierwszy iterator
		else if (*first2 < *first1)
		{
			// zwiêksz drugi operator
			++first2;
		}
		// w przeciwnych wypadkach
		else 
		{
			// w tym momencie wiemy, ¿e pierwszy i drugi iterator wskazuj¹ na tak¹ sam¹ wartoœæ
			// wpisz wartoœæ wskazywan¹ przez pierwszy iterator do pamiêci wskazywanej przez iterator tablicy z wynikami
			*res = *first1;
			
			// zwiêksz iterator tablicy z wynikami oraz pierwszej i drugiej tablicy
			++res;
			++first1;
			++first2;
		}
	}
	// zwróæ iterator tablicy z wynikami
	return res;
}

void pro::opisz_ciag(const std::vector<int>& arr)
{
	// wypisanie rozmiaru ci¹gu
	std::cout << "[" << arr.size() << "]\n";
}

void pro::opisz_ciag(const std::vector<std::vector<int>>& arr)
{
	// je¿eli tablica posiada wiersze
	if (arr.size() > 0)
	{
		// sprawdzenie czy wiersze s¹ tej samej d³ugoœci

		int i, j, size = 0;

		// dla ka¿dego wiersza
		for (i = 0; i < arr.size(); i++)
		{
			// przypisanie wartoœci tego wiersza do zmiennej
			size = arr[i].size();

			// dla ka¿dego nastêpnego wiersza
			for (j = i + 1; j < arr.size(); j++)
			{
				// je¿eli d³ugoœæ wiersza jest inna ni¿ wartoœæ zapisanej zmiennej
				if (arr[j].size() != size)
				{
					// przerwij pêtlê
					break;
				}
			}

			// je¿eli pêtla zosta³a przerwana
			if (j < arr.size())
			{
				// przerwij szukanie ró¿nych wierszy
				break;
			}
		}

		// je¿eli pêtla zosta³a przerwana
		if (i < arr.size())
		{
			// wypisz nieznan¹ szerokoœæ
			std::cout << "[?x" << arr.size() << "]\n";

			// zakoñcz wykonywanie funkcji
			return;
		}

		// je¿eli nie znaleziono ró¿nych d³ugoœci wierszy
		// wypisz wymiary ostatniego sprawdzonego wiersza na iloœæ wierszy
		std::cout << "[" << size << "x" << arr.size() << "]\n";
	}

	// wypisz brak elementów
	std::cout << "[0x" << 0 << "]\n";
}

std::vector<int> pro::odczytaj_ciag_z_pliku(const char* nazwa_pliku, char delimiter)
{
	// otwarcie pliku do odczytu
	std::fstream ifs(nazwa_pliku, std::ios::in);

	// weryfikacja otwarcia pliku
	if (!ifs.good())
		// b³¹d przy próbie otwarcia pliku
		throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do odczytu!";

	// utworzenie tablicy na wartoœci odczytane z pliku
	std::vector<int> arr;

	// dla ka¿dego ³añcucha znaków, oddzielonego znakiem koñca wartoœci, odczytanego z pliku
	for (std::string el; std::getline(ifs, el, delimiter); )
		// wpisanie do tablicy wartoœci przekonwertowanej na liczbê
		arr.push_back(atoi(el.c_str()));

	// zwrócenie tablicy z wartoœciami
	return arr;
}

std::vector<std::vector<int>> pro::odczytaj_ciag_2d_z_pliku(const char* nazwa_pliku, char delimiter_val, char delimiter_array)
{
	// otwarcie pliku do odczytu
	std::fstream ifs(nazwa_pliku, std::ios::in);

	// weryfikacja otwarcia pliku
	if (!ifs.good())
		// b³¹d przy próbie otwarcia pliku
		throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do odczytu!";

	// utworzenie tablic na wartoœci odczytane z pliku
	std::vector<std::vector<int>> data;
	std::vector<int> arr;

	// dla ka¿dego ³añcucha znaków, oddzielonego znakiem koñca tablicy, odczytanego z pliku
	for (std::string line_str; std::getline(ifs, line_str, delimiter_array); )
	{
		// wyczyszczenie tablicy wartoœci
		arr.clear();

		// przypisanie odczytanego ³añcucha znaków do strumienia tekstowego
		std::stringstream line(line_str);

		// dla ka¿dego ³añcucha znaków, oddzielonego znakiem koñca wartoœci, ze strumienia tekstowego
		for (std::string el; std::getline(line, el, delimiter_val); )
		{
			// wpisanie do tablicy wartoœci przekonwertowanej na liczbê
			arr.push_back(atoi(el.c_str()));
		}
		
		// wpisanie do tablicy dwuwymiarowej odczytanych wartoœci w postaci tablicy
		data.push_back(arr);
	}
		

	// zwrócenie dwuwymiarowej tablicy z wartoœciami
	return data;
}


std::pair<std::vector<std::vector<int>>::const_iterator, std::vector<std::vector<int>>::const_iterator> pro::thread_bounds(const std::vector<std::vector<int>>& data, int thread_count, int thread_id)
{
	// odczytanie iloœci wierszy w tablicy dla operacji
	int data_size = data.size();

	// zmienna przechowuj¹ca indeks w¹tku, który jako pierwszy posiada mniej elementów od w¹tku o indeksie o jeden mniejszym
	int break_point = data_size % thread_count;

	// obliczenie iloœci wierszy, za których przetworzenie ma byæ odpowiedzialny w¹tek o podanym numerze
	int weight_sum = thread_id < break_point ? data_size / thread_count + 1 : data_size / thread_count;

	// oblicznenie indeksu pocz¹tku danych przydzielonych dla w¹tku o podanym numerze
	int data_before = break_point - 1 < thread_id ? weight_sum * thread_id + break_point : weight_sum * thread_id;

	// utworzenie iteratorów pocz¹tku i koñca danych
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

	// zwrócenie pary iteratorów jako wyniku obliczeñ
	return std::pair<std::vector<std::vector<int>>::const_iterator, std::vector<std::vector<int>>::const_iterator>(first, last);
}