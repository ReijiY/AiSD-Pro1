#include "projekt1.h"


// inicjalizuje bibliotek� pomocnicz�
void pro::init()
{
	// podanie warto�ci czasu do generatora liczb losowych
	srand(time(NULL));
}

// generuje losowy ciag n wartosci z przedzialu od min do max
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
		*el = rand() % ((max + 1) - min) + min;
	}

	// zwracanie utworzonej tablicy
	return res;
}


// wypisuje tablice na ekranie
void pro::wypisz_ciag(std::vector<int> arr, unsigned spacing)
{
	if (spacing == 0)
	{
		// dla ka�dego elementu tablicy
		for (const auto &el : arr) 
			// wypisanie warto�ci elementu
			std::cout << el << ",";
	}
	else
	{
		// zabezpieczenie przed przypadkowym przepe�nieniem w d� (unsigned -1 = 4294967295)
		if (spacing > 50) spacing = 50;

		// utworzenie tablicy znak�w dla formatu dope�nienia warto�ci
		char* mod = new char[12];
		// wpisanie formatu do tablicy znak�w (np. "%3d, ")
		sprintf_s(mod, 12, "%%%dd, ", spacing);

		// dla ka�dego elementu tablicy
		for (const auto &el : arr)
			// wypisanie warto�ci elementu przy u�yciu utworzonego wcze�niej formatu
			printf(mod, el);

		// zwolnienie pami�ci tablicy formatu
		delete[] mod;
	}
}

// zapisuje tablice do pliku wyjsciowego
void pro::zapisz_ciag_do_pliku(const char* nazwa_pliku, std::vector<int> arr, char delimiter)
{	
	// otwarcie pliku do zapisu
	std::fstream ofs(nazwa_pliku, std::ios::out);

	// weryfikacja otwarcia pliku
	if (!ofs.good())
		// b��d przy pr�bie otwarcia pliku
		throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do zapisu!";

	// dla ka�dego elementu tablicy
	for (const auto& el : arr) 
		// wpisane warto�ci do pliku razem ze znakiem ko�ca warto�ci
		ofs << el << delimiter;
}

// Odczytuje tablice z pliku wejsciowego
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