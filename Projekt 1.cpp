#include <iostream>

#include "projekt1.h"

#include <algorithm>    // std::sort
#include <chrono>       // std::chrono::high_resolution_clock

#include <thread>
#include <future>


// funkcja wywołująca testy czasów na obu algorytmach i zapisująca wyniki do pliku
std::vector<std::vector<double>> testy(int ilosc_testow, int max_w, int max_h, int ilosc_watkow);

// algorytm - realizacja naiwna
std::vector<int> znajdz_powtorzenia_a(const std::vector<std::vector<int>>::const_iterator& data_first, const std::vector<std::vector<int>>::const_iterator& data_last);

// algorytm - realizacja sprytniejsza
std::vector<int> znajdz_powtorzenia_b(const std::vector<std::vector<int>>::const_iterator& data_first, const std::vector<std::vector<int>>::const_iterator& data_last);

std::vector<int> znajdz_powtorzenia_multithread_a(const std::vector<std::vector<int>>& data, int thread_count, bool silent = true);

std::vector<int> znajdz_powtorzenia_multithread_b(const std::vector<std::vector<int>>& data, int thread_count, bool silent = true);


int main()
{
    pro::init();
 
    auto wyniki = testy(40, 100000, 500, 12);

    try
    {
        pro::zapisz_ciag_2d_do_pliku("test/Testy2.txt", wyniki);
    }
    catch (std::string &e)
    {
        std::cout << e << "\n";
    }
    
    return 0;
}

// funkcja wywołująca testy czasów na obu algorytmach
std::vector<std::vector<double>> testy(int ilosc_testow, int max_w, int max_h, int ilosc_watkow)
{
    std::chrono::high_resolution_clock::time_point start, stop;
    std::chrono::duration<double> timediff;

    std::vector<std::vector<double>> wyniki;

    std::vector<int> wynik_obliczen;

    for (int nr_testu = 0; nr_testu < ilosc_testow; nr_testu++)
    {
        std::vector<double> zebrane_dane;

        int width =     (double)(nr_testu + 1.0) / (double)ilosc_testow * max_w;
        int height =    (double)(nr_testu + 1.0) / (double)ilosc_testow * max_h;

        zebrane_dane.push_back(width);
        zebrane_dane.push_back(height);

        std::cout << "Generowanie tablicy o wymiarach " << width << " na " << height << "\n";

        auto data = pro::generuj_losowy_ciag_2d(0, 9, width, height);

        std::cout << "Ciag wejsciowy: ";
        pro::opisz_ciag(data);

        std::cout << "Start A:\n";
        start = std::chrono::high_resolution_clock::now();
        wynik_obliczen = znajdz_powtorzenia_multithread_a(data, ilosc_watkow);
        stop = std::chrono::high_resolution_clock::now();

        timediff = stop - start;

        zebrane_dane.push_back(timediff.count());
        std::cout << "Czas wykonania algorytmu A: " << timediff.count() << "\n";
        std::cout << "Ilosc wynikow: " << wynik_obliczen.size() << "\n";

        pro::opisz_ciag(wynik_obliczen);
        std::cout << "\n";

        std::cout << "Start B:\n";
        start = std::chrono::high_resolution_clock::now();
        wynik_obliczen = znajdz_powtorzenia_multithread_b(data, ilosc_watkow);
        stop = std::chrono::high_resolution_clock::now();

        timediff = stop - start;

        zebrane_dane.push_back(timediff.count());
        std::cout << "Czas wykonania algorytmu B: " << timediff.count() << "\n";
        std::cout << "Ilosc wynikow: " << wynik_obliczen.size() << "\n";

        pro::opisz_ciag(wynik_obliczen);
        std::cout << "\n";


        wyniki.push_back(zebrane_dane);
    }

    return wyniki;
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
                *it = empty_marker;
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

std::vector<int> znajdz_powtorzenia_multithread_a(const std::vector<std::vector<int>>& data, int thread_count, bool silent)
{
    std::vector<std::future<std::vector<int>>> threads;

    if(!silent) std::cout << "Uruchamianie watkow: \n";

    for (int i = 0; i < thread_count; i++)
    {
        auto bound = pro::thread_bounds(data, thread_count, i);
        if (std::distance(bound.first, bound.second) == 0) continue;

        if (!silent) std::cout << i << ":[" << std::distance(data.begin(), bound.first) << ", " << std::distance(data.begin(), bound.second) << "] ";

        threads.push_back(std::async(&znajdz_powtorzenia_a, bound.first, bound.second));
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

    return znajdz_powtorzenia_a(res.begin(), res.end());
}

std::vector<int> znajdz_powtorzenia_multithread_b(const std::vector<std::vector<int>>& data, int thread_count, bool silent)
{
    std::vector<std::future<std::vector<int>>> threads;

    if (!silent) std::cout << "Uruchamianie watkow: \n";

    for (int i = 0; i < thread_count; i++)
    {
        auto bound = pro::thread_bounds(data, thread_count, i);
        if (std::distance(bound.first, bound.second) == 0) continue;

        if (!silent) std::cout << i << ":[" << std::distance(data.begin(), bound.first) << ", " << std::distance(data.begin(), bound.second) << "] ";

        threads.push_back(std::async(&znajdz_powtorzenia_b, bound.first, bound.second));
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

    return znajdz_powtorzenia_b(res.begin(), res.end());
}