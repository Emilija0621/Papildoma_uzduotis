#include <iostream>
#include <string>
#include <map>

#include "funkcijos.h"

using std::cout;
using std::string;
using std::map;
using std::endl;
using std::cin;
using std::invalid_argument;


int main() {
    while (true) {
        string failo_pavadinimas;
        vector<string> eilutes;
        
        while (true) {
            cout << "Įveskite failo pavadinimą: ";
            cin >> failo_pavadinimas;
            
            eilutes = failo_skaitymas(failo_pavadinimas);
            if (!eilutes.empty()) break;
            cout << "Bandykite dar kartą." << endl;
        }
        
        map<string, Zodziai> zodziai = zodziu_skaiciavimas(eilutes);
        
        int pasirinkimas = 0;
        while (true) {
            cout << "Kaip norite gauti rezultatus?" << endl;
            cout << "1 - į konsolę" << endl;
            cout << "2 - į failą" << endl;
            
            string ivestis;
            cin >> ivestis;
            
            try {
                pasirinkimas = stoi(ivestis);
                if (pasirinkimas < 1 || pasirinkimas > 2) {
                    cout << "Neteisingas pasirinkimas. Įveskite skaičių nuo 1 iki 2." << endl;
                    continue;
                }
                break;
            } catch (const invalid_argument&) {
                cout << "Įvesta netinkama reikšmė. Įveskite skaičių nuo 1 iki 2." << endl;
            }
        }
        
        if (pasirinkimas == 1) {
            cross_reference_terminalas(zodziai);
        } else if (pasirinkimas == 2) {
            string failo_isvestis;
            cout << "Įveskite išvesties failo pavadinimą: ";
            cin >> failo_isvestis;
            cross_reference_i_faila(zodziai, failo_isvestis);
            cout << "Lentelė išsaugota faile: " << failo_isvestis << endl;
        }
    }
    return 0;
}
