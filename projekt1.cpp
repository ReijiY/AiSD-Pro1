#include "projekt1.h"


// inicjalizuje bibliotek� pomocnicz�
void pro::init()
{
	// podanie warto�ci czasu do generatora liczb losowych
	srand(time(NULL));
}

// generuje losow� liczb� z przedzia�u od min do max
inline int pro::losowa_liczba(int min, int max)
{
	return rand() % ((max + 1) - min) + min;
}

// Generuje losowy ciag n wartosci z przedzialu od min do max
std::vector<int> pro::generuj_losowy_ciag(int min, int max, int n)
{
	// weryfikacja kolejno�ci argument�w w podanym zakresie
	if (min > max) std::swap(min, max);

	// utworzenie n-elementowego kontenera na losowy ciag
	std::vector<int> res(n);

	// generator losuj�cy warto�ci z przedzia�u [min, max]
	auto gen = [&min, &max]() {
		return losowa_liczba(min, max);
	};

	// wype�nienie losowego ci�gu warto�ciami losowanymi przez generator
	std::generate(res.begin(), res.end(), gen);

	//zwr�cenie utworzonej tablicy
	return res;
}

std::vector<std::vector<int>> pro::generuj_losowy_ciag_2d(int min, int max, int w, int h)
{
	// utworzenie kontenera na losowe ci�gi
	std::vector<std::vector<int>> res;
	
	// zmiana rozmiaru kontenera na h-elementowy
	res.resize(h);

	// generator losuj�cy warto�ci z przedzia�u [min, max]
	auto gen = [&min, &max]() {
		return losowa_liczba(min, max);
	};

	// dla ka�dego elementu kontenera
	for (auto &el : res)
	{
		// wpisanie pustego ci�gu o rozmiarze w
		el = std::vector<int>(w);
		
		// wype�nienie losowego ci�gu warto�ciami losowanymi przez generator
		std::generate(el.begin(), el.end(), gen);
	}

	//zwr�cenie utworzonej tablicy
	return res;
}

// generuje ciag z zakresu start do end z krokiem step, np. (2, 7, 2) -> [2, 4, 6]
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

// przeprowadza wyszukiwanie liniowe w warto�ciach tablicy zwracaj�c iterator na znaleziony element lub iterator ko�ca tablicy
std::vector<int>::iterator pro::linear_search_iterator(std::vector<int>& arr, int val)
{
	// zwr�� wynik wyszukiwania liniowego zaimplementowanego w standardzie C++
	return std::find(arr.begin(), arr.end(), val);
}

// wyszukuje wsp�lne elementy tablic arr1 i arr2 poprzez intersekcje oraz przepisuje je do tablicy res
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

// wypisuje tablice na ekranie
void pro::wypisz_ciag(const std::vector<int>& arr, unsigned spacing)
{
	std::cout << "[";

	// je�eli przekazana zosta�a domy�lna d�ugo�� dope�nienia
	if (spacing == 0)
	{
		// dla ka�dego elementu tablicy
		for (auto el = arr.begin(); el != arr.end(); el++)
		{
			// wypisanie warto�ci elementu
			std::cout << *el;
			// dla warto�ci innych ni� ostatnia wypisz znak ','
			if (el != arr.end() - 1) std::cout << ",";
		}
	}
	// w przeciwnym wypadku
	else
	{
		// zabezpieczenie przed przypadkowym przepe�nieniem w d� (unsigned -1 = 4294967295)
		if (spacing > 50) spacing = 50;


		// utworzenie tablicy znak�w dla formatu dope�nienia warto�ci
		char* mod = new char[12];
		// wpisanie formatu do tablicy znak�w (np. "%3d, ")
		sprintf_s(mod, 12, "%%%dd", spacing);

		// dla ka�dego elementu tablicy
		for (auto el = arr.begin(); el != arr.end(); el++)
		{
			// wypisanie warto�ci elementu przy u�yciu utworzonego wcze�niej formatu
			printf(mod, *el);
			if (el != arr.end() - 1) std::cout << ",";
		}

		// zwolnienie pami�ci tablicy formatu
		delete[] mod;
	}

	std::cout << "]\n";
}

void pro::wypisz_ciag(const std::vector<std::vector<int>>& data, unsigned spacing)
{
	// dla ka�dego elementu tablicy 2-wymiarowej
	for (auto const& arr : data)
	{
		// wypisz warto�ci ci�gu 1-wymiarowego wykorzystuj�c istniaj�c� funkcj� wypisz_ci�g
		pro::wypisz_ciag(arr, spacing);
	}
}

// zapisuje tablice do pliku wyjsciowego z opcjonaln� specyfikacj� znaku oddzielaj�cego waro�ci
void pro::zapisz_ciag_do_pliku(const char* nazwa_pliku, const std::vector<int>& arr, char delimiter)
{	
	// otwarcie pliku do zapisu
	std::fstream ofs(nazwa_pliku, std::ios::out);

	// weryfikacja otwarcia pliku
	if (!ofs.good())
		// b��d przy pr�bie otwarcia pliku
		throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do zapisu!";

	// dla ka�dego elementu tablicy
	for (const auto &el : arr) 
		// wpisane warto�ci do pliku razem ze znakiem ko�ca warto�ci
		ofs << el << delimiter;
}

// zapisuje tablice dwuwymiarow� do pliku wyjsciowego z opcjonaln� specyfikacj� znaku oddzielaj�cego waro�ci i tablice
void pro::zapisz_ciag_2d_do_pliku(const char* nazwa_pliku, const std::vector<std::vector<int>>& data, char delimiter_val, char delimiter_array)
{
	// otwarcie pliku do zapisu
	std::fstream ofs(nazwa_pliku, std::ios::out);

	// weryfikacja otwarcia pliku
	if (!ofs.good())
		// b��d przy pr�bie otwarcia pliku
		throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do zapisu!";

	// dla ka�dego podci�gu
	for (const auto& arr : data)
	{
		//dla ka�dego elementu tablicy
		for (const auto& el : arr)
		{
			// wpisane warto�ci do pliku razem ze znakiem ko�ca warto�ci
			ofs << el << delimiter_val;
		}

		// wpisane znaku ko�ca tabeli
		ofs << delimiter_array;
	}
		
}

// odczytuje tablice z pliku wejsciowego z opcjonaln� specyfikacj� znaku oddzielaj�cego waro�ci
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

// odczytuje tablice dwuwymiarow� z pliku wejsciowego z opcjonaln� specyfikacj� znaku oddzielaj�cego waro�ci i tablice
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

// zwraca par� iterator�w, na kt�rej wykonywane maj� by� operacje dla tablicy 2-wymiarowej dla n-tego w�tku przy zdefiniowanej ��cznej liczbie wykoszystanych w�tk�w
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