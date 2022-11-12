#include <iostream>

#include "projekt1.h"




int main()
{
    // inicjalizacja biblioteki pomocniczej
    pro::init();

    auto c1 = pro::generuj_losowy_ciag(10, 100, 20);

    pro::wypisz_ciag(c1, 3);

    try
    {
        pro::zapisz_ciag_do_pliku("test\\c1.txt", c1);
    }
    catch (std::string &e)
    {
        std::cout << e << "\n";
    }

    
    return 0;
}

