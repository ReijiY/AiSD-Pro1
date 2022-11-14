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

	// utworzenie kontenera na losowy ciag
	std::vector<int> res;

	// zmiana rozmiaru kontenera na n-elementowy
	res.resize(n);

	// dla ka�dego elementu kontenera
	for (auto el = res.begin(); el != res.end(); el++)
	{
		// wpisanie losowej liczby z przedzia�u od min do max (w��cznie)
		*el = losowa_liczba(min, max);
	}

	//zwr�cenie utworzonej tablicy
	return res;
}

std::vector<std::vector<int>> pro::generuj_losowy_ciag_2d(int min, int max, int w, int h)
{
	// utworzenie kontenera na losowe ci�gi
	std::vector<std::vector<int>> res;
	
	// zmiana rozmiaru kontenera na h-elementowy
	res.resize(h);

	// dla ka�dego elementu kontenera
	for (auto el = res.begin(); el != res.end(); el++)
	{
		// wpisanie losowo wygenerowanego ci�gu o rozmiarze w i warto�ciach w przedziale min do max
		*el = generuj_losowy_ciag(min, max, w);
	}

	//zwr�cenie utworzonej tablicy
	return res;
}

// generuje ciag z zakresu start do end z krokiem step (2, 7, 2) -> [2, 4, 6]
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

std::vector<int>::iterator pro::linear_search_iterator(std::vector<int>& arr, int val)
{
	return std::find(arr.begin(), arr.end(), val);
}

std::deque<int>::iterator pro::binary_search_iterator(std::deque<int>& arr, int val)
{
	std::deque<int>::iterator it = std::lower_bound(arr.begin(), arr.end(), val);
	if (it == arr.end() || *it != val) return arr.end();
	return it;
}

// wypisuje tablice na ekranie
void pro::wypisz_ciag(const std::vector<int>& arr, unsigned spacing)
{
	std::cout << "[";

	if (spacing == 0)
	{
		// dla ka�dego elementu tablicy
		for (auto el = arr.begin(); el != arr.end(); el++)
		{
			// wypisanie warto�ci elementu
			std::cout << *el;
			if (el != arr.end() - 1) std::cout << ",";
		}
	}
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
	for (auto const& arr : data)
	{
		wypisz_ciag(arr, spacing);
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
