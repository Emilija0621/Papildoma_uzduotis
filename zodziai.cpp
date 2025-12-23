#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include <locale>
#include <cwctype>

#include "zodziai.h"

using std::wcout;
using std::cout;
using std::wofstream;
using std::wifstream;
using std::wstring;
using std::string;
using std::vector;
using std::map;
using std::wstringstream;
using std::setw;
using std::left;
using std::locale;
using std::endl;


vector<wstring> sutvarkyti_zodziai(const wstring& zodis) {
    vector<wstring> rezultatas;
    wstring laikinas;

    for (wchar_t c : zodis) {
        if (iswalpha(c)) {
            laikinas += towlower(c);
        } else {
            if (!laikinas.empty()) {
                rezultatas.push_back(laikinas);
                laikinas.clear();
            }
        }
    }

    if (!laikinas.empty()) rezultatas.push_back(laikinas);

    return rezultatas;
}


vector<wstring> failo_skaitymas(const string& failo_pavadinimas){
    wifstream in(failo_pavadinimas);
    in.imbue(locale("lt_LT.UTF-8")); // Nustatome UTF-8 koduotę

    if (!in.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failo_pavadinimas << endl;
        return {};
    }

    vector<wstring> eilutes;
    wstring eilute;
    
    while (getline(in, eilute)) {
        eilutes.push_back(eilute);
    }
    
    if (eilutes.empty()) {
        cout << "Failas " << failo_pavadinimas << " yra tuščias" << endl;
    }

    in.close();
    return eilutes;
}

void analizuoti_teksta(const vector<wstring>& eilutes, map<wstring, int>& zodziu_skaicius, map<wstring, vector<int>>& zodziu_eilutes) {
    int eilutes_nr = 0;

    for (const auto& eilute : eilutes) {
        eilutes_nr++;
        wstringstream ss(eilute);
        wstring zodis;
        
        while (ss >> zodis) {
            vector<wstring> sutvarkyti = sutvarkyti_zodziai(zodis);
            
            for (const auto& s : sutvarkyti) {
                if (!s.empty()) {
                    zodziu_skaicius[s]++;
                    auto& eil = zodziu_eilutes[s];
                    if (eil.empty() || eil.back() != eilutes_nr)
                        eil.push_back(eilutes_nr);
                }
            }
        }
    }
}



void cross_reference_terminalas(const map<wstring, int>& zodziu_skaicius, const map<wstring, vector<int>>& zodziu_eilutes) {
    wcout << L"----- Cross reference lentele -----\n\n";
    wcout << left << setw(5)  << L"Nr." << L"| " << setw(15) << L"Žodis" << L"| " << setw(7)  << L"Kartai" << L"| " << L"Eilučių nr." << endl;

    wcout << L"-------------------------------------------------------------\n";

    int nr = 1;
    for (const auto& [zodis, kiekis] : zodziu_skaicius) {
        if (kiekis > 1) {
            auto it = zodziu_eilutes.find(zodis);
            if (it != zodziu_eilutes.end()) {
                const auto& eilutes_vec = it->second;

                wstring nr_str = std::to_wstring(nr) + L".";
                wcout << left << setw(5) << nr_str << L"| " << setw(15) << zodis << L"| " << setw(7)  << kiekis << L"| ";

                for (int e : eilutes_vec) {
                    wcout << e << L" ";
                }
                wcout << L"\n";
                nr++;
            }
        }
    }
}


void cross_reference_i_faila(const map<wstring, int>& zodziu_skaicius, const map<wstring, vector<int>>& zodziu_eilutes, const string& failo_pavadinimas) {
    
    wofstream out(failo_pavadinimas);
    out.imbue(locale("lt_LT.UTF-8")); // UTF-8 koduotė

    if (!out.is_open()) {
        cout << "Nepavyko sukurti failo" << endl;
        return;
    }

    out << L"----- Cross reference lentele -----\n\n";
    out << left << setw(5)  << L"Nr." << L"| " << setw(15) << L"Žodis" << L"| " << setw(7)  << L"Kartai" << L"| " << L"Eilučių nr." << endl;

    out << L"-------------------------------------------------------------\n";

    int nr = 1;
    for (const auto& [zodis, kiekis] : zodziu_skaicius) {
        if (kiekis > 1) {
            auto it = zodziu_eilutes.find(zodis);
            if (it != zodziu_eilutes.end()) {
                const auto& eilutes_vec = it->second;

                wstring nr_str = std::to_wstring(nr) + L".";
                out << left << setw(5) << nr_str << L"| " << setw(15) << zodis << L"| " << setw(7)  << kiekis << L"| ";

                for (int e : eilutes_vec) {
                    out << e << L" ";
                }
                out << L"\n";
                nr++;
            }
        }
    }

    out.close();
}

