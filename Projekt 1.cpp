#include <iostream>

#include "projekt1.h"

#include <algorithm>    // std::sort
#include <chrono>       // std::chrono::high_resolution_clock

#include <thread>
#include <future>


// funkcja wywołująca testy czasów na obu algorytmach i zapisująca wyniki do pliku
void testy(const char* nazwa_pliku, int ilosc_testow);

// algorytm - realizacja naiwna
std::vector<int> znajdz_powtorzenia_a(const std::vector<std::vector<int>>::const_iterator& data_first, const std::vector<std::vector<int>>::const_iterator& data_last);

// algorytm - realizacja sprytniejsza
std::vector<int> znajdz_powtorzenia_b(const std::vector<std::vector<int>>::const_iterator& data_first, const std::vector<std::vector<int>>::const_iterator& data_last);

std::vector<int> znajdz_powtorzenia_multithread_a(const std::vector<std::vector<int>>& data, int thread_count);

std::vector<int> znajdz_powtorzenia_multithread_b(const std::vector<std::vector<int>>& data, int thread_count);


int main()
{

// inicjalizacja biblioteki pomocniczej
pro::init();

/*
std::vector<std::vector<int>> dane;

int ilosc_ciagow = pro::losowa_liczba(3, 8);
for (int i = 0; i < ilosc_ciagow; i++)
    dane.push_back(pro::generuj_losowy_ciag(0, 9, pro::losowa_liczba(8, 15)));

pro::wypisz_ciag(dane, 1);
std::cout << "\n";

std::vector<std::vector<int>> dane2;

try
{
    pro::zapisz_ciag_2d_do_pliku("test/ciag_2d_1", dane);

    dane2 = pro::odczytaj_ciag_2d_z_pliku("test/ciag_2d_1");
}
catch (std::string& e)
{
    std::cerr << e << "\n";
}

pro::wypisz_ciag(dane2, 1);
*/

testy("test", 10);

/*

auto powtorzenia = znajdz_powtorzenia_a(dane);

std::cout << "\n\n";
std::sort(powtorzenia.begin(), powtorzenia.end());
pro::wypisz_ciag(powtorzenia, 1);

*/
return 0;
}

// funkcja wywołująca testy czasów na obu algorytmach i zapisująca wyniki do pliku
void testy(const char* nazwa_pliku, int ilosc_testow)
{
    std::chrono::high_resolution_clock::time_point start, stop;
    std::chrono::duration<double> timediff;

    auto data = pro::generuj_losowy_ciag_2d(0, 9, 20000, 1000);
    //pro::zapisz_ciag_2d_do_pliku("test/ciag_2d_1.txt", data);

    const int ilosc_watkow = 8;

    std::vector<int> wynik;

    //pro::wypisz_ciag(data, 2);

    std::cout << "Start A:\n";
    start = std::chrono::high_resolution_clock::now();
    wynik = znajdz_powtorzenia_multithread_a(data, ilosc_watkow);
    stop = std::chrono::high_resolution_clock::now();

    timediff = stop - start;
    std::cout << "Czas wykonania algorytmu A asynchronicznie: " << timediff.count() << "\n";
    std::cout << "Wyniki( " << wynik.size() << "): \n";
    //pro::wypisz_ciag(wynik, 2);

    std::cout << "Start B:\n";
    start = std::chrono::high_resolution_clock::now();
    wynik = znajdz_powtorzenia_multithread_b(data, ilosc_watkow);
    stop = std::chrono::high_resolution_clock::now();

    timediff = stop - start;
    std::cout << "Czas wykonania algorytmu B asynchronicznie: " << timediff.count() << "\n";
    std::cout << "Wyniki( " << wynik.size() << "): \n";
    //pro::wypisz_ciag(wynik, 2);
    std::cout << "\n";

    /*
    std::cout << "Start A:\n";
    start = std::chrono::high_resolution_clock::now();
    wynik = znajdz_powtorzenia_a(data);
    stop = std::chrono::high_resolution_clock::now();

    timediff = stop - start;
    std::cout << "Czas wykonania algorytmu A: " << timediff.count() << "\n";
    std::cout << "Wyniki( " << wynik.size() << "): \n";
    //pro::wypisz_ciag(wynik, 1);
    std::cout << "\n";


    std::cout << "Start B:\n";
    start = std::chrono::high_resolution_clock::now();
    wynik = znajdz_powtorzenia_b(data_kopia);
    stop = std::chrono::high_resolution_clock::now();

    timediff = stop - start;
    std::cout << "Czas wykonania algorytmu B: " << timediff.count() << "\n";
    std::cout << "Wyniki( " << wynik.size() << "): \n";
    //pro::wypisz_ciag(wynik, 1);
    std::cout << "\n";

    */

}

// algorytm - realizacja naiwna
std::vector<int> znajdz_powtorzenia_a(const std::vector<std::vector<int>>::const_iterator& data_first, const std::vector<std::vector<int>>::const_iterator& data_last)
{
    //if (!data.size() || !data[0].size()) return std::vector<int>();
    if (std::distance(data_first, data_last) <= 0 || !data_first->size()) return std::vector<int>();

    auto data = std::vector<std::vector<int>>(data_first, data_last);

    std::vector<int> powtorzenia(data[0]);
    std::vector<int> bufor;

    std::vector<int>::iterator it;

    int empty_marker = -1;
    while (std::find(powtorzenia.begin(), powtorzenia.end(), empty_marker) != powtorzenia.end()) empty_marker--;

    for (auto arr_i = data.begin() + 1; arr_i != data.end(); arr_i++)
    {
        for (auto el = arr_i->begin(); el != arr_i->end(); el++)
        {
            if ((it = pro::linear_search_iterator(powtorzenia, *el)) != powtorzenia.end())
            {
                bufor.push_back(*it);
                *it = empty_marker;//powtorzenia.erase(it);
            }

        }
        if (bufor.size() == 0) return std::vector<int>();
        powtorzenia = bufor;
        bufor.clear();

    }

    return powtorzenia;
}



// algorytm - realizacja sprytniejsza
std::vector<int> znajdz_powtorzenia_b(const std::vector<std::vector<int>>::const_iterator& data_first, const std::vector<std::vector<int>>::const_iterator& data_last)
{
    //if (!data_origin.size() || !data_origin[0].size()) return std::vector<int>();
    if (std::distance(data_first, data_last) <= 0 || !data_first->size()) return std::vector<int>();

    auto data = std::vector<std::vector<int>>(data_first, data_last);

    std::vector<int> powtorzenia(data[0]);

    std::vector<int> bufor;
    bufor.resize(powtorzenia.size());

    std::vector<int>::iterator it;

    for (auto arr_i = data.begin() + 1; arr_i != data.end(); arr_i++)
    {
        std::sort(powtorzenia.begin(), powtorzenia.end());
        std::sort(arr_i->begin(), arr_i->end());

        it = pro::set_intersection(powtorzenia, *arr_i, bufor.begin());

        bufor.resize(std::distance(bufor.begin(), it));

        if (bufor.size() == 0) return std::vector<int>();
        powtorzenia = bufor;
        bufor.resize(powtorzenia.size());
    }

    return powtorzenia;
}

std::vector<int> znajdz_powtorzenia_multithread_a(const std::vector<std::vector<int>>& data, int thread_count)
{
    std::vector<std::future<std::vector<int>>> threads;

    for (int i = 0; i < thread_count; i++)
    {
        auto bound = pro::thread_bounds(data, thread_count, i);
        if (std::distance(bound.first, bound.second) == 0) continue;

        std::cout << "starting thread " << i << " in range [" << std::distance(data.begin(), bound.first) << ", " << std::distance(data.begin(), bound.second) << "]\n";

        threads.push_back(std::async(&znajdz_powtorzenia_b, bound.first, bound.second));
    }
    std::cout << "\n";

    std::vector<std::vector<int>> res;

    for (int i = 0; i < threads.size(); i++)
    {
        std::cout << "retrieving data from thread " << i << "\n";
        res.push_back(threads[i].get());
    }

    return znajdz_powtorzenia_a(res.begin(), res.end());
}

std::vector<int> znajdz_powtorzenia_multithread_b(const std::vector<std::vector<int>>& data, int thread_count)
{
    std::vector<std::future<std::vector<int>>> threads;

    for (int i = 0; i < thread_count; i++)
    {
        auto bound = pro::thread_bounds(data, thread_count, i);
        if (std::distance(bound.first, bound.second) == 0) continue;

        std::cout << "starting thread " << i << " in range [" << std::distance(data.begin(), bound.first) << ", " << std::distance(data.begin(), bound.second) << "]\n";

        threads.push_back(std::async(&znajdz_powtorzenia_b, bound.first, bound.second));
    }
    std::cout << "\n";

    std::vector<std::vector<int>> res;

    for (int i = 0; i < threads.size(); i++)
    {
        std::cout << "retrieving data from thread " << i << "\n";
        res.push_back(threads[i].get());
    }

    return znajdz_powtorzenia_b(res.begin(), res.end());
}