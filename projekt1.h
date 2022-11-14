#ifndef __PROJEKT_1_AISD__
#define __PROJEKT_1_AISD__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <time.h>

#include <vector>
#include <chrono>

#include <deque>

#define PRO_FILE_VALUE_DELIMITER ','
#define PRO_FILE_ARRAY_DELIMITER '\n'

namespace pro
{

	// inicjalizuje bibliotek� pomocnicz�
	void init();

	// generuje losow� liczb� z przedzia�u od min do max
	inline int losowa_liczba(int min, int max);

	// generuje losowy ciag n wartosci z przedzialu od min do max
	std::vector<int> generuj_losowy_ciag(int min, int max, int n);

	// generuje losowy ciag 2d wartosci z przedzialu od min do max o wymiarach w x h
	std::vector<std::vector<int>> generuj_losowy_ciag_2d(int min, int max, int w, int h);

	// generuje ciag z zakresu start do end z krokiem step (2, 7, 2) -> [2, 4, 6]
	std::vector<int> generuj_ciag_z_zakresu(int start, int end, int step = 1);


	std::vector<int>::iterator linear_search_iterator(std::vector<int>& arr, int val);

	std::deque<int>::iterator binary_search_iterator(std::deque<int>& arr, int val);

	// wypisuje tablice na ekranie z opcjonalnym dope�nianiem bia�ymi znakami do podanej ilo�ci znak�w (max 50)
	void wypisz_ciag(const std::vector<int> &arr, unsigned spacing = 0);
	void wypisz_ciag(const std::vector<std::vector<int>>& data, unsigned spacing = 0);

	// zapisuje tablice do pliku wyjsciowego z opcjonaln� specyfikacj� znaku oddzielaj�cego waro�ci
	void zapisz_ciag_do_pliku(const char* nazwa_pliku, const std::vector<int> &arr, char delimiter = PRO_FILE_VALUE_DELIMITER);

	// zapisuje tablice dwuwymiarow� do pliku wyjsciowego z opcjonaln� specyfikacj� znaku oddzielaj�cego waro�ci i tablice
	void zapisz_ciag_2d_do_pliku(const char* nazwa_pliku, const std::vector<std::vector<int>>& data, char delimiter_val = PRO_FILE_VALUE_DELIMITER, char delimiter_array = PRO_FILE_ARRAY_DELIMITER);

	// odczytuje tablice z pliku wejsciowego z opcjonaln� specyfikacj� znaku oddzielaj�cego waro�ci
	std::vector<int> odczytaj_ciag_z_pliku(const char* nazwa_pliku, char delimiter = PRO_FILE_VALUE_DELIMITER);

	// odczytuje tablice dwuwymiarow� z pliku wejsciowego z opcjonaln� specyfikacj� znaku oddzielaj�cego waro�ci i tablice
	std::vector<std::vector<int>> odczytaj_ciag_2d_z_pliku(const char* nazwa_pliku, char delimiter_val = PRO_FILE_VALUE_DELIMITER, char delimiter_array = PRO_FILE_ARRAY_DELIMITER);


}





#endif