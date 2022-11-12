#ifndef __PROJEKT_1_AISD__
#define __PROJEKT_1_AISD__

#include <iostream>
#include <fstream>
#include <string>

#include <time.h>

#include <vector>
#include <chrono>

#define PRO_FILE_VALUE_DELIMITER ','

namespace pro
{

	// inicjalizuje bibliotekê pomocnicz¹
	// z³o¿onoœæ O(1)
	void init();

	// Generuje losowy ciag n wartosci z przedzialu od min do max
	// z³o¿onoœæ O(n)
	std::vector<int> generuj_losowy_ciag(int min, int max, int n);

	// Wypisuje tablice na ekranie z opcjonalnym dope³nianiem bia³ymi znakami do podanej iloœci znaków (max 50)
	// z³o¿onoœæ O(n)
	void wypisz_ciag(std::vector<int> arr, unsigned spacing = 0);

	// Zapisuje tablice do pliku wyjsciowego z opcjonaln¹ specyfikacj¹ znaku oddzielaj¹cego waroœci
	// z³o¿onoœæ O(n)
	void zapisz_ciag_do_pliku(const char* nazwa_pliku, std::vector<int> arr, char delimiter = PRO_FILE_VALUE_DELIMITER);

	// Odczytuje tablice z pliku wejsciowego z opcjonaln¹ specyfikacj¹ znaku oddzielaj¹cego waroœci
	// z³o¿onoœæ O(n)
	std::vector<int> odczytaj_ciag_z_pliku(const char* nazwa_pliku, char delimiter = PRO_FILE_VALUE_DELIMITER);


}





#endif