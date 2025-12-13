#include <iostream>
#include <string>
#include <map>

#include "funkcijos.h"

using std::cout;
using std::string;
using std::map;
using std::endl;
using std::cin;


int main(){
    
    string failo_pavadinimas;
    
    cout << "Iveskite failo pavadinima: "; cin >> failo_pavadinimas;
    vector<string> eilutes = txt_skaitymas(failo_pavadinimas);
    
    map<string, Zodziai> zodziu_duomenys = zodziu_skaiciavimas(eilutes);
    
    for (const auto& [zodis, duomenys] : zodziu_duomenys) {
            if (duomenys.count > 1) {
                cout << zodis << " kartų: " << duomenys.count << ", eilutės: ";
                for (int nr : duomenys.eilutes_nr) {
                    cout << nr << " ";
                }
                cout << endl;
            }
        }

        return 0;
}
