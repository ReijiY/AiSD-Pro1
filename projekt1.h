/**
 * \file   projekt1.h
 * \brief
 *
 * \author Dariusz Strojny
 * \date   November 2022
*/

#ifndef __PROJEKT_1_AISD__
#define __PROJEKT_1_AISD__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <algorithm>

#include <time.h>

#include <vector>
#include <chrono>

#include <deque>

#define PRO_FILE_VALUE_DELIMITER ','
#define PRO_FILE_ARRAY_DELIMITER '\n'

namespace pro
{
	/* ---===---   FUNCTION DECLARATIONS   ---===--- */

	/**
	 * @brief Inicjalizuje bibliotek� pomocnicz�.
	 */
	void init();

	/**
	 * @brief Generuje losow� liczb� z przedzia�u [min, max].
	 * 
	 * @param min Minimalna warto�� liczby
	 * @param max Maksymalna wartos� liczby
	 * 
	 * @return wygenerowana liczba
	 */
	inline int losowa_liczba(int min, int max);

	// 
	/**
	 * @brief Generuje losowy ciag o podanej d�ugo�ci z warto�ciami z podanego przedzia�u.
	 * 
	 * @param min Minimalna warto�� elementu w ci�gu
	 * @param max Maksymalna wartos� elementu w ci�gu
	 * @param width Ilo�� element�w w ci�gu
	 * 
	 * @return wygenerowany ci�g
	 */
	std::vector<int> generuj_losowy_ciag(int min, int max, int width);

	/**
	 * @brief Generuje losowy dwuwymiarowy ciag o podanych wymiarach z warto�ciami z podanego przedzia�u.
	 * 
	 * @param min Minimalna warto�� elementu w ci�gu
	 * @param max Maksymalna wartos� elementu w ci�gu
	 * @param width Ilo�� kolumn w ci�gu
	 * @param height Ilo�� wierszy ci�gu
	 * 
	 * @return wygenerowany ci�g
	 */
	std::vector<std::vector<int>> generuj_losowy_ciag_2d(int min, int max, int width, int height);

	/**
	 * @brief Zwraca ciag z zakresu start do end z krokiem step.
	 * 
	 * @code
	 * np. f(2, 6, 2) -> [2, 4, 6]
	 * @endcode
	 * 
	 * @param start Pocz�tkowa warto�� iteratora
	 * @param end Maksymalna warto�� iteratora (w��cznie)
	 * @param step Krok o jaki zwi�kszany jest iterator
	 */
	std::vector<int> generuj_ciag_z_zakresu(int start, int end, int step = 1);

	/**
	 * @brief Funkcja pomocnicza sortowania quicksort.
	 * 
	 * Dzieli ci�g danych na dwie cz�ci przenosz�c elementy mniejsze lub r�wne pierwszej warto�ci na jej lew� stron� a pozosta�e na jej praw� stron�.
	 * 
	 * @param begin 
	 * @param end 
	 * 
	 * @return Iterator wskazuj�cy na warto�� oddzielaj�c� oba ci�gi
	*/
	std::vector<int>::iterator quicksort_iterator_partition(std::vector<int>::iterator begin, std::vector<int>::iterator end);
	
	/**
	 * @brief Sortowanie metod� quicksort na podanym przedziale.
	 * 
	 * @param begin Iterator wskazuj�cy na pocz�tek przedzia�u
	 * @param end Iterator wskazuj�cy na koniec przedzia�u
	*/
	void quicksort_iterator(std::vector<int>::iterator begin, std::vector<int>::iterator end);
	
	/**
	 * @brief Przeprowadza wyszukiwanie liniowe w warto�ciach tablicy.
	 * 
	 * @param arr Tablica, na kt�rej wykonywane jest wyszukiwanie
	 * @param val Warto�� szukana w tablicy
	 * 
	 * @return Iterator wskazuj�cy na znaleziony element lub na koniec przedzia�u
	*/
	std::vector<int>::iterator linear_search_iterator(std::vector<int>& arr, int val);

	// wyszukuje wsp�lne elementy tablic arr1 i arr2 poprzez intersekcje oraz przepisuje je do tablicy res
	// zwraca iterator tablicy res wskazuj�cy na ostatni przypisany element
	
	/**
	 * @brief Wyszukuje wsp�lne elementy dw�ch tablic.
	 * 
	 * Funkcja wykonuje wyszukiwanie wsp�lnych element�w poprzez skrzy�owanie ze sob� dw�ch tablic.
	 * Tablice wej�ciowe musz� by� posortowane rosn�co.
	 * 
	 * @param arr1 Pierwsza tablica
	 * @param arr2 Druga tablica
	 * @param res Iterator wskazuj�cy na pierwszy element tablicy o rozmiarze przynajmniej min(rozmiar arr1, rozmiar arr2)
	 * 
	 * @return Iterator wskazuj�cy na element za ostatnim wpisanym elementem
	*/
	std::vector<int>::iterator set_intersection(const std::vector<int>& arr1, const std::vector<int>& arr2, std::vector<int>::iterator res);

	/**
	 * @brief Wypisuje w konsoli wymiary tablicy.
	 * 
	 * @param arr opisywana tablica
	*/
	void opisz_ciag(const std::vector<int>& arr);

	/**
	 * @brief Wypisuje w konsoli wymiary tablicy.
	 * 
	 * @param arr opisywana tablica
	*/
	void opisz_ciag(const std::vector<std::vector<int>>& arr);

	/**
	 * @brief Odczytuje ci�g z pliku wej�ciowego.
	 * 
	 * @param nazwa_pliku �cie�ka do pliku
	 * @param delimiter Znak oddzielaj�cy warto�ci w pliku
	 * 
	 * @return Ci�g odczytany z pliku
	*/
	std::vector<int> odczytaj_ciag_z_pliku(const char* nazwa_pliku, char delimiter = PRO_FILE_VALUE_DELIMITER);

	/**
	 * @brief Odczytuje dwuwymiarow� tablic� z pliku wej�ciowego.
	 * 
	 * @param nazwa_pliku �cie�ka do pliku
	 * @param delimiter_val Znak oddzielaj�cy warto�ci wiersza w pliku
	 * @param delimiter_array Znak oddzielaj�cy kolumny w pliku
	 * 
	 * @return Dwuwymiarowa tablica odczytany z pliku
	*/
	std::vector<std::vector<int>> odczytaj_ciag_2d_z_pliku(const char* nazwa_pliku, char delimiter_val = PRO_FILE_VALUE_DELIMITER, char delimiter_array = PRO_FILE_ARRAY_DELIMITER);

	/**
	 * @brief Oblicza zakres danych, na kt�rych maj� by� wykonane operacje dla podanego w�tku.
	 * 
	 * @param data Dane do podzielenia
	 * @param thread_count ��czna ilo�� w�tk�w
	 * @param thread_id Numer w�tku, dla kt�rego obliczany jest zakres
	 * 
	 * @return Para iterator�w wskazuj�cych na pocz�tek i koniec wyznaczonego zakresu danych
	*/
	std::pair<std::vector<std::vector<int>>::const_iterator, std::vector<std::vector<int>>::const_iterator> 
		thread_bounds(const std::vector<std::vector<int>>& data, int thread_count, int thread_id);


	/* ---===---   TEMPLATE FUNCTION DECLARATIONS   ---===--- */

	/**
	 * @brief Wypisuje zawarto�� tablicy na ekranie.
	 * 
	 * @tparam T Rodzaj danych przechowywanych w tablicy
	 * @param arr Tablica do wy�wietlenia
	 * @param spacing Dope�nienie ka�dej kom�rki danych znakami bia�ymi do podanej ilo�ci znak�w
	*/
	template<class T>
	void wypisz_ciag(const std::vector<T>& arr, unsigned spacing = 0);

	/**
	 * @brief Wypisuje zawarto�� tablicy dwuwymiarowej na ekranie.
	 * 
	 * @tparam T Rodzaj danych przechowywanych w tablicy
	 * @param data Tablica do wy�wietlenia
	 * @param spacing Dope�nienie ka�dej kom�rki danych znakami bia�ymi do podanej ilo�ci znak�w
	*/
	template<class T>
	void wypisz_ciag(const std::vector<std::vector<T>>& data, unsigned spacing = 0);

	/**
	 * @brief Zapisuje ci�g do pliku wyj�ciowego.
	 * 
	 * @tparam T Rodzaj danych przechowywanych w ci�gu
	 * @param nazwa_pliku �cie�ka do pliku
	 * @param data Ci�g do zapisania
	 * @param delimiter Znak oddzielaj�cy warto�ci w pliku
	*/
	template<class T>
	void zapisz_ciag_do_pliku(const char* nazwa_pliku, const std::vector<T>& data, char delimiter = PRO_FILE_VALUE_DELIMITER);

	/**
	 * @brief Zapisuje tablilc� dwuwymiarow� do pliku wyj�ciowego.
	 * 
	 * @tparam T Rodzaj danych przechowywanych w tablicy
	 * @param nazwa_pliku �cie�ka do pliku
	 * @param data Tablica do zapisania
	 * @param delimiter_val Znak oddzielaj�cy warto�ci wiersza w pliku
	 * @param delimiter_array Znak oddzielaj�cy kolumny w pliku
	*/
	template<class T>
	void zapisz_ciag_2d_do_pliku(const char* nazwa_pliku, const std::vector<std::vector<T>>& data, char delimiter_val = PRO_FILE_VALUE_DELIMITER, char delimiter_array = PRO_FILE_ARRAY_DELIMITER);


	/* ---===---   TEMPLATE FUNCTION DEFINITIONS   ---===--- */

	// wypisuje tablice na ekranie
	template<class T>
	void wypisz_ciag(const std::vector<T>& arr, unsigned spacing)
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

	template<class T>
	void wypisz_ciag(const std::vector<std::vector<T>>& data, unsigned spacing)
	{
		// dla ka�dego elementu tablicy 2-wymiarowej
		for (auto const& arr : data)
		{
			// wypisz warto�ci ci�gu 1-wymiarowego wykorzystuj�c istniaj�c� funkcj� wypisz_ci�g
			pro::wypisz_ciag(arr, spacing);
		}
	}

	// zapisuje tablice do pliku wyjsciowego z opcjonaln� specyfikacj� znaku oddzielaj�cego waro�ci
	template<class T>
	void zapisz_ciag_do_pliku(const char* nazwa_pliku, const std::vector<T>& data, char delimiter)
	{
		// otwarcie pliku do zapisu
		std::fstream ofs(nazwa_pliku, std::ios::out);

		// weryfikacja otwarcia pliku
		if (!ofs.good())
			// b��d przy pr�bie otwarcia pliku
			throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do zapisu!";

		// dla ka�dego elementu tablicy
		for (const auto& el : data)
			// wpisane warto�ci do pliku razem ze znakiem ko�ca warto�ci
			ofs << el << delimiter;
	}

	// zapisuje tablice dwuwymiarow� do pliku wyjsciowego z opcjonaln� specyfikacj� znaku oddzielaj�cego waro�ci i tablice
	template<class T>
	void zapisz_ciag_2d_do_pliku(const char* nazwa_pliku, const std::vector<std::vector<T>>& data, char delimiter_val, char delimiter_array)
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
}

#endif