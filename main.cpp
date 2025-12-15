#include <iostream>
#include <string>
#include <map>
#include <locale>

#include "funkcijos.h"

using std::wcout;
using std::string;
using std::map;
using std::locale;

int main() {
    locale::global(locale("lt_LT.UTF-8"));
    wcout.imbue(locale("lt_LT.UTF-8"));
    
    string failas = "tekstas.txt";

    vector<wstring> eilutes = failo_skaitymas(failas);

    map<wstring, int> zodziu_skaicius;
    map<wstring, vector<int>> zodziu_eilutes;
    
    analizuoti_teksta(eilutes, zodziu_skaicius, zodziu_eilutes);

    cross_reference_terminalas(zodziu_skaicius, zodziu_eilutes);
    cross_reference_i_faila(zodziu_skaicius, zodziu_eilutes, "rezultatai.txt");

    return 0;
}
