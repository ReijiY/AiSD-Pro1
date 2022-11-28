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
	 * @brief Inicjalizuje bibliotekê pomocnicz¹.
	 */
	void init();

	/**
	 * @brief Generuje losow¹ liczbê z przedzia³u [min, max].
	 * 
	 * @param min Minimalna wartoœæ liczby
	 * @param max Maksymalna wartosæ liczby
	 * 
	 * @return wygenerowana liczba
	 */
	inline int losowa_liczba(int min, int max);

	// 
	/**
	 * @brief Generuje losowy ciag o podanej d³ugoœci z wartoœciami z podanego przedzia³u.
	 * 
	 * @param min Minimalna wartoœæ elementu w ci¹gu
	 * @param max Maksymalna wartosæ elementu w ci¹gu
	 * @param width Iloœæ elementów w ci¹gu
	 * 
	 * @return wygenerowany ci¹g
	 */
	std::vector<int> generuj_losowy_ciag(int min, int max, int width);

	/**
	 * @brief Generuje losowy dwuwymiarowy ciag o podanych wymiarach z wartoœciami z podanego przedzia³u.
	 * 
	 * @param min Minimalna wartoœæ elementu w ci¹gu
	 * @param max Maksymalna wartosæ elementu w ci¹gu
	 * @param width Iloœæ kolumn w ci¹gu
	 * @param height Iloœæ wierszy ci¹gu
	 * 
	 * @return wygenerowany ci¹g
	 */
	std::vector<std::vector<int>> generuj_losowy_ciag_2d(int min, int max, int width, int height);

	/**
	 * @brief Zwraca ciag z zakresu start do end z krokiem step.
	 * 
	 * @code
	 * np. f(2, 6, 2) -> [2, 4, 6]
	 * @endcode
	 * 
	 * @param start Pocz¹tkowa wartoœæ iteratora
	 * @param end Maksymalna wartoœæ iteratora (w³¹cznie)
	 * @param step Krok o jaki zwiêkszany jest iterator
	 */
	std::vector<int> generuj_ciag_z_zakresu(int start, int end, int step = 1);

	/**
	 * @brief Funkcja pomocnicza sortowania quicksort.
	 * 
	 * Dzieli ci¹g danych na dwie czêœci przenosz¹c elementy mniejsze lub równe pierwszej wartoœci na jej lew¹ stronê a pozosta³e na jej praw¹ stronê.
	 * 
	 * @param begin 
	 * @param end 
	 * 
	 * @return Iterator wskazuj¹cy na wartoœæ oddzielaj¹c¹ oba ci¹gi
	*/
	std::vector<int>::iterator quicksort_iterator_partition(std::vector<int>::iterator begin, std::vector<int>::iterator end);
	
	/**
	 * @brief Sortowanie metod¹ quicksort na podanym przedziale.
	 * 
	 * @param begin Iterator wskazuj¹cy na pocz¹tek przedzia³u
	 * @param end Iterator wskazuj¹cy na koniec przedzia³u
	*/
	void quicksort_iterator(std::vector<int>::iterator begin, std::vector<int>::iterator end);
	
	/**
	 * @brief Przeprowadza wyszukiwanie liniowe w wartoœciach tablicy.
	 * 
	 * @param arr Tablica, na której wykonywane jest wyszukiwanie
	 * @param val Wartoœæ szukana w tablicy
	 * 
	 * @return Iterator wskazuj¹cy na znaleziony element lub na koniec przedzia³u
	*/
	std::vector<int>::iterator linear_search_iterator(std::vector<int>& arr, int val);

	// wyszukuje wspólne elementy tablic arr1 i arr2 poprzez intersekcje oraz przepisuje je do tablicy res
	// zwraca iterator tablicy res wskazuj¹cy na ostatni przypisany element
	
	/**
	 * @brief Wyszukuje wspólne elementy dwóch tablic.
	 * 
	 * Funkcja wykonuje wyszukiwanie wspólnych elementów poprzez skrzy¿owanie ze sob¹ dwóch tablic.
	 * Tablice wejœciowe musz¹ byæ posortowane rosn¹co.
	 * 
	 * @param arr1 Pierwsza tablica
	 * @param arr2 Druga tablica
	 * @param res Iterator wskazuj¹cy na pierwszy element tablicy o rozmiarze przynajmniej min(rozmiar arr1, rozmiar arr2)
	 * 
	 * @return Iterator wskazuj¹cy na element za ostatnim wpisanym elementem
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
	 * @brief Odczytuje ci¹g z pliku wejœciowego.
	 * 
	 * @param nazwa_pliku Œcie¿ka do pliku
	 * @param delimiter Znak oddzielaj¹cy wartoœci w pliku
	 * 
	 * @return Ci¹g odczytany z pliku
	*/
	std::vector<int> odczytaj_ciag_z_pliku(const char* nazwa_pliku, char delimiter = PRO_FILE_VALUE_DELIMITER);

	/**
	 * @brief Odczytuje dwuwymiarow¹ tablicê z pliku wejœciowego.
	 * 
	 * @param nazwa_pliku Œcie¿ka do pliku
	 * @param delimiter_val Znak oddzielaj¹cy wartoœci wiersza w pliku
	 * @param delimiter_array Znak oddzielaj¹cy kolumny w pliku
	 * 
	 * @return Dwuwymiarowa tablica odczytany z pliku
	*/
	std::vector<std::vector<int>> odczytaj_ciag_2d_z_pliku(const char* nazwa_pliku, char delimiter_val = PRO_FILE_VALUE_DELIMITER, char delimiter_array = PRO_FILE_ARRAY_DELIMITER);

	/**
	 * @brief Oblicza zakres danych, na których maj¹ byæ wykonane operacje dla podanego w¹tku.
	 * 
	 * @param data Dane do podzielenia
	 * @param thread_count £¹czna iloœæ w¹tków
	 * @param thread_id Numer w¹tku, dla którego obliczany jest zakres
	 * 
	 * @return Para iteratorów wskazuj¹cych na pocz¹tek i koniec wyznaczonego zakresu danych
	*/
	std::pair<std::vector<std::vector<int>>::const_iterator, std::vector<std::vector<int>>::const_iterator> 
		thread_bounds(const std::vector<std::vector<int>>& data, int thread_count, int thread_id);


	/* ---===---   TEMPLATE FUNCTION DECLARATIONS   ---===--- */

	/**
	 * @brief Wypisuje zawartoœæ tablicy na ekranie.
	 * 
	 * @tparam T Rodzaj danych przechowywanych w tablicy
	 * @param arr Tablica do wyœwietlenia
	 * @param spacing Dope³nienie ka¿dej komórki danych znakami bia³ymi do podanej iloœci znaków
	*/
	template<class T>
	void wypisz_ciag(const std::vector<T>& arr, unsigned spacing = 0);

	/**
	 * @brief Wypisuje zawartoœæ tablicy dwuwymiarowej na ekranie.
	 * 
	 * @tparam T Rodzaj danych przechowywanych w tablicy
	 * @param data Tablica do wyœwietlenia
	 * @param spacing Dope³nienie ka¿dej komórki danych znakami bia³ymi do podanej iloœci znaków
	*/
	template<class T>
	void wypisz_ciag(const std::vector<std::vector<T>>& data, unsigned spacing = 0);

	/**
	 * @brief Zapisuje ci¹g do pliku wyjœciowego.
	 * 
	 * @tparam T Rodzaj danych przechowywanych w ci¹gu
	 * @param nazwa_pliku Œcie¿ka do pliku
	 * @param data Ci¹g do zapisania
	 * @param delimiter Znak oddzielaj¹cy wartoœci w pliku
	*/
	template<class T>
	void zapisz_ciag_do_pliku(const char* nazwa_pliku, const std::vector<T>& data, char delimiter = PRO_FILE_VALUE_DELIMITER);

	/**
	 * @brief Zapisuje tablilcê dwuwymiarow¹ do pliku wyjœciowego.
	 * 
	 * @tparam T Rodzaj danych przechowywanych w tablicy
	 * @param nazwa_pliku Œcie¿ka do pliku
	 * @param data Tablica do zapisania
	 * @param delimiter_val Znak oddzielaj¹cy wartoœci wiersza w pliku
	 * @param delimiter_array Znak oddzielaj¹cy kolumny w pliku
	*/
	template<class T>
	void zapisz_ciag_2d_do_pliku(const char* nazwa_pliku, const std::vector<std::vector<T>>& data, char delimiter_val = PRO_FILE_VALUE_DELIMITER, char delimiter_array = PRO_FILE_ARRAY_DELIMITER);


	/* ---===---   TEMPLATE FUNCTION DEFINITIONS   ---===--- */

	// wypisuje tablice na ekranie
	template<class T>
	void wypisz_ciag(const std::vector<T>& arr, unsigned spacing)
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

	template<class T>
	void wypisz_ciag(const std::vector<std::vector<T>>& data, unsigned spacing)
	{
		// dla ka¿dego elementu tablicy 2-wymiarowej
		for (auto const& arr : data)
		{
			// wypisz wartoœci ci¹gu 1-wymiarowego wykorzystuj¹c istniaj¹c¹ funkcjê wypisz_ci¹g
			pro::wypisz_ciag(arr, spacing);
		}
	}

	// zapisuje tablice do pliku wyjsciowego z opcjonaln¹ specyfikacj¹ znaku oddzielaj¹cego waroœci
	template<class T>
	void zapisz_ciag_do_pliku(const char* nazwa_pliku, const std::vector<T>& data, char delimiter)
	{
		// otwarcie pliku do zapisu
		std::fstream ofs(nazwa_pliku, std::ios::out);

		// weryfikacja otwarcia pliku
		if (!ofs.good())
			// b³¹d przy próbie otwarcia pliku
			throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do zapisu!";

		// dla ka¿dego elementu tablicy
		for (const auto& el : data)
			// wpisane wartoœci do pliku razem ze znakiem koñca wartoœci
			ofs << el << delimiter;
	}

	// zapisuje tablice dwuwymiarow¹ do pliku wyjsciowego z opcjonaln¹ specyfikacj¹ znaku oddzielaj¹cego waroœci i tablice
	template<class T>
	void zapisz_ciag_2d_do_pliku(const char* nazwa_pliku, const std::vector<std::vector<T>>& data, char delimiter_val, char delimiter_array)
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
}

#endif