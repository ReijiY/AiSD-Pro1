#include "projekt1.h"


// inicjalizuje bibliotekê pomocnicz¹
void pro::init()
{
	// podanie wartoœci czasu do generatora liczb losowych
	srand(time(NULL));
}

// generuje losow¹ liczbê z przedzia³u od min do max
inline int pro::losowa_liczba(int min, int max)
{
	return rand() % ((max + 1) - min) + min;
}

// Generuje losowy ciag n wartosci z przedzialu od min do max
std::vector<int> pro::generuj_losowy_ciag(int min, int max, int n)
{
	// weryfikacja kolejnoœci argumentów w podanym zakresie
	if (min > max) std::swap(min, max);

	// utworzenie n-elementowego kontenera na losowy ciag
	std::vector<int> res(n);

	// generator losuj¹cy wartoœci z przedzia³u [min, max]
	auto gen = [&min, &max]() {
		return losowa_liczba(min, max);
	};

	// wype³nienie losowego ci¹gu wartoœciami losowanymi przez generator
	std::generate(res.begin(), res.end(), gen);

	//zwrócenie utworzonej tablicy
	return res;
}

std::vector<std::vector<int>> pro::generuj_losowy_ciag_2d(int min, int max, int w, int h)
{
	// utworzenie kontenera na losowe ci¹gi
	std::vector<std::vector<int>> res;
	
	// zmiana rozmiaru kontenera na h-elementowy
	res.resize(h);

	// generator losuj¹cy wartoœci z przedzia³u [min, max]
	auto gen = [&min, &max]() {
		return losowa_liczba(min, max);
	};

	// dla ka¿dego elementu kontenera
	for (auto &el : res)
	{
		// wpisanie pustego ci¹gu o rozmiarze w
		el = std::vector<int>(w);
		
		// wype³nienie losowego ci¹gu wartoœciami losowanymi przez generator
		std::generate(el.begin(), el.end(), gen);
	}

	//zwrócenie utworzonej tablicy
	return res;
}

// generuje ciag z zakresu start do end z krokiem step, np. (2, 7, 2) -> [2, 4, 6]
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

// przeprowadza wyszukiwanie liniowe w wartoœciach tablicy zwracaj¹c iterator na znaleziony element lub iterator koñca tablicy
std::vector<int>::iterator pro::linear_search_iterator(std::vector<int>& arr, int val)
{
	// zwróæ wynik wyszukiwania liniowego zaimplementowanego w standardzie C++
	return std::find(arr.begin(), arr.end(), val);
}

// wyszukuje wspólne elementy tablic arr1 i arr2 poprzez intersekcje oraz przepisuje je do tablicy res
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

// wypisuje tablice na ekranie
void pro::wypisz_ciag(const std::vector<int>& arr, unsigned spacing)
{
	std::cout << "[";

	// je¿eli przekazana zosta³a domyœlna d³ugoœæ dope³nienia
	if (spacing == 0)
	{
		// dla ka¿dego elementu tablicy
		for (auto el = arr.begin(); el != arr.end(); el++)
		{
			// wypisanie wartoœci elementu
			std::cout << *el;
			// dla wartoœci innych ni¿ ostatnia wypisz znak ','
			if (el != arr.end() - 1) std::cout << ",";
		}
	}
	// w przeciwnym wypadku
	else
	{
		// zabezpieczenie przed przypadkowym przepe³nieniem w dó³ (unsigned -1 = 4294967295)
		if (spacing > 50) spacing = 50;


		// utworzenie tablicy znaków dla formatu dope³nienia wartoœci
		char* mod = new char[12];
		// wpisanie formatu do tablicy znaków (np. "%3d, ")
		sprintf_s(mod, 12, "%%%dd", spacing);

		// dla ka¿dego elementu tablicy
		for (auto el = arr.begin(); el != arr.end(); el++)
		{
			// wypisanie wartoœci elementu przy u¿yciu utworzonego wczeœniej formatu
			printf(mod, *el);
			if (el != arr.end() - 1) std::cout << ",";
		}

		// zwolnienie pamiêci tablicy formatu
		delete[] mod;
	}

	std::cout << "]\n";
}

void pro::wypisz_ciag(const std::vector<std::vector<int>>& data, unsigned spacing)
{
	// dla ka¿dego elementu tablicy 2-wymiarowej
	for (auto const& arr : data)
	{
		// wypisz wartoœci ci¹gu 1-wymiarowego wykorzystuj¹c istniaj¹c¹ funkcjê wypisz_ci¹g
		pro::wypisz_ciag(arr, spacing);
	}
}

// zapisuje tablice do pliku wyjsciowego z opcjonaln¹ specyfikacj¹ znaku oddzielaj¹cego waroœci
void pro::zapisz_ciag_do_pliku(const char* nazwa_pliku, const std::vector<int>& arr, char delimiter)
{	
	// otwarcie pliku do zapisu
	std::fstream ofs(nazwa_pliku, std::ios::out);

	// weryfikacja otwarcia pliku
	if (!ofs.good())
		// b³¹d przy próbie otwarcia pliku
		throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do zapisu!";

	// dla ka¿dego elementu tablicy
	for (const auto &el : arr) 
		// wpisane wartoœci do pliku razem ze znakiem koñca wartoœci
		ofs << el << delimiter;
}

// zapisuje tablice dwuwymiarow¹ do pliku wyjsciowego z opcjonaln¹ specyfikacj¹ znaku oddzielaj¹cego waroœci i tablice
void pro::zapisz_ciag_2d_do_pliku(const char* nazwa_pliku, const std::vector<std::vector<int>>& data, char delimiter_val, char delimiter_array)
{
	// otwarcie pliku do zapisu
	std::fstream ofs(nazwa_pliku, std::ios::out);

	// weryfikacja otwarcia pliku
	if (!ofs.good())
		// b³¹d przy próbie otwarcia pliku
		throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do zapisu!";

	// dla ka¿dego podci¹gu
	for (const auto& arr : data)
	{
		//dla ka¿dego elementu tablicy
		for (const auto& el : arr)
		{
			// wpisane wartoœci do pliku razem ze znakiem koñca wartoœci
			ofs << el << delimiter_val;
		}

		// wpisane znaku koñca tabeli
		ofs << delimiter_array;
	}
		
}

// odczytuje tablice z pliku wejsciowego z opcjonaln¹ specyfikacj¹ znaku oddzielaj¹cego waroœci
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

// odczytuje tablice dwuwymiarow¹ z pliku wejsciowego z opcjonaln¹ specyfikacj¹ znaku oddzielaj¹cego waroœci i tablice
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

// zwraca parê iteratorów, na której wykonywane maj¹ byæ operacje dla tablicy 2-wymiarowej dla n-tego w¹tku przy zdefiniowanej ³¹cznej liczbie wykoszystanych w¹tków
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