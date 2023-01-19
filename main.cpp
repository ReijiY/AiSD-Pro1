#include <Windows.h>
#include <iostream>



#include "projekt1.h"


#include <chrono>

#include <thread>
#include <future>

#include <math.h>


// funkcja wywołująca testy czasów na obu algorytmach
std::vector<std::vector<double>> testy(int ilosc_testow, int start_w, int start_h, int multiplier, int ilosc_watkow);

// algorytm - realizacja naiwna
std::vector<int> znajdz_powtorzenia_a(const std::vector<std::vector<int>>::const_iterator& data_first, const std::vector<std::vector<int>>::const_iterator& data_last);

// algorytm - realizacja sprytniejsza
std::vector<int> znajdz_powtorzenia_b(const std::vector<std::vector<int>>::const_iterator& data_first, const std::vector<std::vector<int>>::const_iterator& data_last);

template<class T>
std::vector<int> znajdz_powtorzenia_multithread(const std::vector<std::vector<int>>& data, int thread_count, T sorting_algorithm, bool silent = true);


int main()
{
    pro::init();

    // 11 release
    // 8 debug
    auto wyniki = testy(8, 800, 80, 2, 1);

    try
    {
        std::string filename = "test/Testy.txt";
        pro::zapisz_ciag_2d_do_pliku(filename.c_str(), wyniki);
        std::cout << "Wyniki zapisane w pliku " << filename << "\n";
    }
    catch (std::string& e)
    {
        std::cout << "Error: " << e << "\n";
    }

    return 0;
}

std::vector<std::vector<double>> testy(int ilosc_testow, int start_w, int start_h, int multiplier, int ilosc_watkow)
// funkcja wywołująca testy czasów na obu algorytmach
{
    std::chrono::high_resolution_clock::time_point start, stop;
    std::chrono::duration<double> timediff;

    std::vector<std::vector<double>> wyniki;

    std::vector<int> wynik_obliczen;

    int width, height;

    for (int nr_testu = 0; nr_testu < ilosc_testow; nr_testu++)
    {

        width = std::round((double)start_w * std::pow(std::sqrt(multiplier), nr_testu));
        height = std::round((double)start_h * std::pow(std::sqrt(multiplier), nr_testu));

        std::vector<double> zebrane_dane;

        zebrane_dane.push_back(width*height);

        std::cout << "Test nr: " << nr_testu + 1 << "\n";
        std::cout << "Generowanie tablicy o wymiarach " << width << " na " << height << "\n";

        auto data = pro::generuj_losowy_ciag_2d(0, 9, width, height);

        std::cout << "Tablica wejsciowa: ";
        pro::opisz_ciag(data);

        std::cout << "Start A [" << ilosc_watkow << " thread(s)]:\n";
        start = std::chrono::high_resolution_clock::now();
        wynik_obliczen = znajdz_powtorzenia_multithread(data, ilosc_watkow, &znajdz_powtorzenia_a);
        stop = std::chrono::high_resolution_clock::now();

        timediff = stop - start;

        zebrane_dane.push_back(timediff.count());
        std::cout << "Czas wykonania algorytmu A: " << timediff.count() << "\n";
        std::cout << "Ilosc wynikow: " << wynik_obliczen.size() << "\n";

        std::cout << "Start B [" << ilosc_watkow << " thread(s)]:\n";
        start = std::chrono::high_resolution_clock::now();
        wynik_obliczen = znajdz_powtorzenia_multithread(data, ilosc_watkow, &znajdz_powtorzenia_b);
        stop = std::chrono::high_resolution_clock::now();

        timediff = stop - start;

        zebrane_dane.push_back(timediff.count());
        std::cout << "Czas wykonania algorytmu B: " << timediff.count() << "\n";
        std::cout << "Ilosc wynikow: " << wynik_obliczen.size() << "\n";

        std::cout << "<int>";
        pro::opisz_ciag(wynik_obliczen);
        std::cout << "\n";


        wyniki.push_back(zebrane_dane);

    }

    return wyniki;
}

// algorytm - realizacja naiwna
std::vector<int> znajdz_powtorzenia_a(const std::vector<std::vector<int>>::const_iterator& data_first, const std::vector<std::vector<int>>::const_iterator& data_last)
{
    // Zwrócenie pustej tablicy jeżeli ilość elementów w podanym zakresie jest niedodatnia lub pierwsza tablica z podanego zakresu jest pusta
    if (std::distance(data_first, data_last) <= 0 || !data_first->size()) return std::vector<int>();

    // wykonanie kopii podanego zakresu do nowej tablicy dwuwymiarowej
    auto data = std::vector<std::vector<int>>(data_first, data_last);

    // deklaracja tablicy do wyszukiwania powtórzeń i skopiowanie do niej zawartości pierwszego ciągu
    std::vector<int> powtorzenia(data[0]);
    // deklaracja tablicy, do której wpiswane będą wyniki porównań w trakcie jednej iteracji
    std::vector<int> bufor;

    // deklaracja iteratora przechowującego wynik wyszukiwania liniowego w tablicy powtórzeń
    std::vector<int>::iterator it;

    // deklaracja wartości, którą oznaczane będą wartości już znalezione w tablicy z początkową wartością pierwszego elementu tablicy powtórzeń
    int empty_marker = powtorzenia[0];
    // przypisanie do pustego znacznika najmniejszej wartości z tablicy powtórzeń
    for (it = powtorzenia.begin(); it != powtorzenia.end(); it++)
        if (*it < empty_marker) empty_marker = *it;

    // w przypadku gdy najmniejszy element w tablicy jest minimalną wartością możliwą do zapisania w zmiennej typu int
    if (empty_marker == INT_MIN)
        // zmniejszanie wartości pustego markera dopóki element z taką samą wartością znajduje się w tablicy powtórzeń
        while (pro::linear_search_iterator(powtorzenia, empty_marker) != powtorzenia.end()) empty_marker--;
    // w przeciwnym wypadku zmniejszenie wartości pustego znacznika
    else empty_marker--;

    // dla każdej poza pierwszą podtablicy w tablicy wejściowej
    for (auto arr_i = data.begin() + 1; arr_i != data.end(); arr_i++)
    {
        // dla każdego elementu w podtablicy
        for (auto el = arr_i->begin(); el != arr_i->end(); el++)
        {
            // jeżeli szukany element znajduje się w tablicy powtórzeń
            if (*el != empty_marker && (it = pro::linear_search_iterator(powtorzenia, *el)) != powtorzenia.end())
            {
                // wpisanie znalezionego elementu do tablicy bufor
                bufor.push_back(*it);
                // zamiana wartości znalezionego elementu na pusty znacznik
                *it = empty_marker;
            }

        }
        // jeżeli rozmiar tablicy bufor jest równy 0 zwraca pustą tablicę (brak powtórzeń)
        if (bufor.size() == 0) return std::vector<int>();
        // przypisanie zawartości tablicy bufor to tablicy powtórzeń
        powtorzenia = bufor;
        // wyczyszczenie zawartości tablicy bufor
        bufor.clear();
    }

    // zwrócenie tablicy powtórzeń
    return powtorzenia;
}



// algorytm - realizacja sprytniejsza
std::vector<int> znajdz_powtorzenia_b(const std::vector<std::vector<int>>::const_iterator& data_first, const std::vector<std::vector<int>>::const_iterator& data_last)
{
    //if (!data_origin.size() || !data_origin[0].size()) return std::vector<int>();
    if (std::distance(data_first, data_last) <= 0 || !data_first->size()) return std::vector<int>();

    // wykonanie kopii podanego zakresu do nowej tablicy dwuwymiarowej
    auto data = std::vector<std::vector<int>>(data_first, data_last);

    // deklaracja tablicy do wyszukiwania powtórzeń i skopiowanie do niej zawartości pierwszego ciągu
    std::vector<int> powtorzenia(data[0]);

    // deklaracja tablicy, do której wpiswane będą wyniki porównań w trakcie jednej iteracji
    std::vector<int> bufor;
    // ustawienie rozmiaru tablicy bufor na równy ilości elementów w tablicy powtórzenia
    bufor.resize(powtorzenia.size());

    // deklaracja iteratora przechowującego wynik skrzyżowania wartości dwóch tablic
    std::vector<int>::iterator it;

    // posortowanie tablicy powtórzeń przy użyciu algorytmu quicksort z usprawnieniem dla często powtarzających się elementów
    // (Dutch national flag problem)
    pro::quicksort_three_way_iterator(powtorzenia.begin(), powtorzenia.end());

    // dla każdej poza pierwszą podtablicy w tablicy wejściowej
    for (auto arr_i = data.begin() + 1; arr_i != data.end(); arr_i++)
    {
        // posortowanie tablicy przy użyciu algorytmu quicksort z usprawnieniem dla często powtarzających się elementów
        // (Dutch national flag problem)
        pro::quicksort_three_way_iterator(arr_i->begin(), arr_i->end());

        // skrzyżowanie wartości tablicy powtórzeń i podtablicy wejściowej, wpisanie wyników do tablicy bufor i iteratora końcowego do it
        it = pro::set_intersection(powtorzenia, *arr_i, bufor.begin());

        // jeżeli funkcja krzyżująca zwróciła 0 elementów, zwróć pustą tablicę
        if(bufor.begin() == it) return std::vector<int>();

        // zmiana rozmiaru tablicy bufor na ilość elementów zwróconych z funkcji krzyżującej
        bufor.resize(std::distance(bufor.begin(), it));

        // przypisanie zawartości tablicy bufor to tablicy powtórzeń
        powtorzenia = bufor;
    }

    // zwrócenie tablicy powtórzeń
    return powtorzenia;
}

template<class T>
std::vector<int> znajdz_powtorzenia_multithread(const std::vector<std::vector<int>>& data, int thread_count, T sorting_algorithm, bool silent)
{
    if(thread_count <= 0) return sorting_algorithm(data.begin(), data.end());
    std::vector<std::future<std::vector<int>>> threads;

    if (!silent) std::cout << "Uruchamianie watkow: \n";

    for (int i = 0; i < thread_count; i++)
    {
        auto bound = pro::thread_bounds(data, thread_count, i);
        if (std::distance(bound.first, bound.second) == 0) continue;

        if (!silent) std::cout << i << ":[" << std::distance(data.begin(), bound.first) << ", " << std::distance(data.begin(), bound.second) << "] ";

        threads.push_back(std::async(sorting_algorithm, bound.first, bound.second));
    }
    if (!silent) std::cout << "\n";

    std::vector<std::vector<int>> res;

    if (!silent) std::cout << "Odczytywanie wynikow z watkow: \n";

    for (int i = 0; i < threads.size(); i++)
    {
        if (!silent) std::cout << i << " ";
        res.push_back(threads[i].get());
    }
    if (!silent) std::cout << "\nScalanie wynikow\n";

    return sorting_algorithm(res.begin(), res.end());
}
