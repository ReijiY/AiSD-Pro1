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

	// inicjalizuje bibliotekê pomocnicz¹
	void init();

	// generuje losow¹ liczbê z przedzia³u od min do max
	inline int losowa_liczba(int min, int max);

	// generuje losowy ciag n wartosci z przedzialu od min do max
	std::vector<int> generuj_losowy_ciag(int min, int max, int n);

	// generuje losowy ciag 2d wartosci z przedzialu od min do max o wymiarach w x h
	std::vector<std::vector<int>> generuj_losowy_ciag_2d(int min, int max, int w, int h);

	// generuje ciag z zakresu start do end z krokiem step (2, 7, 2) -> [2, 4, 6]
	std::vector<int> generuj_ciag_z_zakresu(int start, int end, int step = 1);

	// przeprowadza wyszukiwanie liniowe w wartoœciach tablicy zwracaj¹c iterator na znaleziony element lub iterator koñca tablicy
	std::vector<int>::iterator linear_search_iterator(std::vector<int>& arr, int val);

	// wyszukuje wspólne elementy tablic arr1 i arr2 poprzez intersekcje oraz przepisuje je do tablicy res
	std::vector<int>::iterator set_intersection(const std::vector<int>& arr1, const std::vector<int>& arr2, std::vector<int>::iterator res);

	void opisz_ciag(const std::vector<int>& arr);
	void opisz_ciag(const std::vector<std::vector<int>>& arr);

	// wypisuje tablice na ekranie z opcjonalnym dope³nianiem bia³ymi znakami do podanej iloœci znaków (max 50)
	void wypisz_ciag(const std::vector<int> &arr, unsigned spacing = 0);
	void wypisz_ciag(const std::vector<std::vector<int>>& data, unsigned spacing = 0);

	// odczytuje tablice z pliku wejsciowego z opcjonaln¹ specyfikacj¹ znaku oddzielaj¹cego waroœci
	std::vector<int> odczytaj_ciag_z_pliku(const char* nazwa_pliku, char delimiter = PRO_FILE_VALUE_DELIMITER);

	// odczytuje tablice dwuwymiarow¹ z pliku wejsciowego z opcjonaln¹ specyfikacj¹ znaku oddzielaj¹cego waroœci i tablice
	std::vector<std::vector<int>> odczytaj_ciag_2d_z_pliku(const char* nazwa_pliku, char delimiter_val = PRO_FILE_VALUE_DELIMITER, char delimiter_array = PRO_FILE_ARRAY_DELIMITER);

	// zwraca parê iteratorów, na której wykonywane maj¹ byæ operacje dla tablicy 2-wymiarowej dla n-tego w¹tku przy zdefiniowanej ³¹cznej liczbie wykoszystanych w¹tków
	std::pair<std::vector<std::vector<int>>::const_iterator, std::vector<std::vector<int>>::const_iterator> thread_bounds(const std::vector<std::vector<int>>& data, int thread_count, int thread_id);



	// zapisuje tablice do pliku wyjsciowego z opcjonaln¹ specyfikacj¹ znaku oddzielaj¹cego waroœci
	template<class T>
	void zapisz_ciag_do_pliku(const char* nazwa_pliku, const std::vector<T>& arr, char delimiter = PRO_FILE_VALUE_DELIMITER)
	{
		// otwarcie pliku do zapisu
		std::fstream ofs(nazwa_pliku, std::ios::out);

		// weryfikacja otwarcia pliku
		if (!ofs.good())
			// b³¹d przy próbie otwarcia pliku
			throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do zapisu!";

		// dla ka¿dego elementu tablicy
		for (const auto& el : arr)
			// wpisane wartoœci do pliku razem ze znakiem koñca wartoœci
			ofs << el << delimiter;
	}

	// zapisuje tablice dwuwymiarow¹ do pliku wyjsciowego z opcjonaln¹ specyfikacj¹ znaku oddzielaj¹cego waroœci i tablice
	template<class T>
	void zapisz_ciag_2d_do_pliku(const char* nazwa_pliku, const std::vector<std::vector<T>>& data, char delimiter_val = PRO_FILE_VALUE_DELIMITER, char delimiter_array = PRO_FILE_ARRAY_DELIMITER)
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