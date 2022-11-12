#include <iostream>

#include "projekt1.h"

#include <algorithm>    // std::sort

// algorytm - realizacja naiwna
std::vector<int> znajdz_powtorzenia_a(const std::vector<std::vector<int>>& data);

// algorytm - realizacja sprytniejsza
std::vector<int> znajdz_powtorzenia_b(std::vector<std::vector<int>> data);


int main()
{
    // inicjalizacja biblioteki pomocniczej
    pro::init();

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

    /*

    auto powtorzenia = znajdz_powtorzenia_a(dane);

    std::cout << "\n\n";
    std::sort(powtorzenia.begin(), powtorzenia.end());
    pro::wypisz_ciag(powtorzenia, 1);

    */
    return 0;
}

// algorytm - realizacja naiwna
std::vector<int> znajdz_powtorzenia_a(const std::vector<std::vector<int>> &data)
{
    if (!data.size() || !data[0].size()) return std::vector<int>();

    std::vector<int> powtorzenia = data[0];
    std::vector<int> bufor;

    std::vector<int>::iterator it;

    for (auto arr_i = data.begin() + 1; arr_i != data.end(); arr_i++)
    {

        for (const auto& el : *arr_i) 
        {
            if ((it = pro::linear_search_iterator(powtorzenia, el)) != powtorzenia.end())
            {
                bufor.push_back(el);
                powtorzenia.erase(it);
            }
            
        }

        powtorzenia = bufor;
        bufor.clear();
    }

    return powtorzenia;
}


// algorytm - realizacja sprytniejsza
std::vector<int> znajdz_powtorzenia_b(std::vector<std::vector<int>> data)
{
    if (!data.size() || !data[0].size()) return std::vector<int>();

    std::vector<int> powtorzenia = data[0];

    std::vector<int> bufor;

    std::vector<int>::iterator it;

    for (auto arr_i = data.begin() + 1; arr_i != data.end(); arr_i++)
    {
        std::sort(powtorzenia.begin(), powtorzenia.end());

        for (const int& el : *arr_i)
        {
            if ((it = pro::binary_search_iterator(powtorzenia, el)) != powtorzenia.end())
            {
                bufor.push_back(*it);
                powtorzenia.erase(it);
            }
        }

        powtorzenia = bufor;
        bufor.clear();
    }

    return powtorzenia;
}