#include <iostream>
#include <string>
#include <map>
#include <locale>
#include <set>
#include <fstream>

#include "zodziai.h"
#include "url_ieskojimas.h"

using std::wcout;
using std::string;
using std::map;
using std::locale;
using std::cout;
using std::cin;
using std::endl;
using std::set;


int main() {
    // Nustatome globalią lokalę į lietuvišką UTF-8
    locale::global(locale("lt_LT.UTF-8"));
    // Nustatome wcout, kad galėtume spausdinti lietuviškas raides
    wcout.imbue(locale("lt_LT.UTF-8"));
    
    while (true) {
        int pasirinkimas = 0;

        while (true) {
            cout << "Pasirinkite veiksmą: " << endl;
            cout << "1 - Tekste rasti pasikartojančius žodžius" << endl;
            cout << "2 - Tekste rasti URL" << endl;
            cout << "Pasirinkimas: ";

            string ivestis;
            cin >> ivestis;

            try {
                pasirinkimas = stoi(ivestis);
                if (pasirinkimas == 1 || pasirinkimas == 2) break;
            } catch (...) {}

            cout << "Neteisingas pasirinkimas. Bandykite dar kartą." << endl;
        }
        string failas;
        vector<wstring> eilutes;

        while (true) {
            cout << "Įveskite failo pavadinimą: ";
            cin >> failas;

            eilutes = failo_skaitymas(failas);
            if (!eilutes.empty()) break;

            cout << "Bandykite dar kartą." << endl;
        }
        
        if (pasirinkimas == 1) {
            
            // Asociatyvūs konteineriai
            
            // Žodis, kiek kartų pasikartojo
            map<wstring, int> zodziu_skaicius;
            
            // Žodis, eilutėse numeriai
            map<wstring, vector<int>> zodziu_eilutes;
            
            analizuoti_teksta(eilutes, zodziu_skaicius, zodziu_eilutes);
            
            int pasirinkimas1 = 0;
            while (true) {
                cout << "Kaip norite gauti rezultatus?" << endl;
                cout << "1 - į konsolę" << endl;
                cout << "2 - į failą" << endl;
                cout << "Pasirinkimas: ";

                string ivestis;
                cin >> ivestis;

                try {
                    pasirinkimas1 = stoi(ivestis);
                    if (pasirinkimas1 == 1 || pasirinkimas1 == 2) break;
                } catch (...) {}

                cout << "Neteisingas pasirinkimas. Bandykite dar kartą." << endl;
            }

            if (pasirinkimas1 == 1) {
                cross_reference_terminalas(zodziu_skaicius, zodziu_eilutes);
            } else {
                string isvesties_failas;
                cout << "Įveskite išvesties failo pavadinimą: ";
                cin >> isvesties_failas;

                cross_reference_i_faila(zodziu_skaicius, zodziu_eilutes, isvesties_failas);

                cout << "Lentelė išsaugota faile: " << isvesties_failas << endl;
            }
        } else {
            set<wstring> tlds = nuskaityti_tlds("URL.txt");
            set<wstring> urlai = surasti_url(eilutes, tlds);

            int isv = 0;
            while (true) {
                cout << "Kaip norite gauti rezultatus?" << endl;
                cout << "1 - į konsolę" << endl;
                cout << "2 - į failą" << endl;
                cout << "Pasirinkimas: ";
                
                string ivestis;
                cin >> ivestis;
                try {
                    isv = stoi(ivestis);
                    if (isv == 1 || isv == 2) break;
                } catch (...) {}
                cout << "Neteisingas pasirinkimas. Bandykite dar kartą." << endl;
            }

            if (isv == 1) {
                url_terminalas(urlai);
            } else {
                string isv_failas;
                cout << "Įveskite išvesties failo pavadinimą: ";
                cin >> isv_failas;
                url_failas(urlai, isv_failas);
            }
        }
 
    }
    return 0;
}


