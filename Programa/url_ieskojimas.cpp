#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <locale>
#include <cwctype>
#include <iomanip>
#include <regex>
#include <fstream>

#include "url_ieskojimas.h"

using std::wcout;
using std::cout;
using std::wofstream;
using std::wifstream;
using std::wstring;
using std::string;
using std::vector;
using std::set;
using std::wstringstream;
using std::locale;
using std::setw;
using std::left;
using std::endl;
using std::wregex;
using std::wsregex_iterator;


wstring mazosios_raides(const wstring& zodis) {
    wstring rezultatas;
    for (wchar_t c : zodis) {
        rezultatas += towlower(c);
    }
    return rezultatas;
}


set<wstring> nuskaityti_tlds(const string& failo_pavadinimas) {
    wifstream in(failo_pavadinimas);
    in.imbue(locale("lt_LT.UTF-8")); // Nustatome UTF-8 koduotę

    if (!in.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failo_pavadinimas << ". " << "URL adresų suradimas bus netikslus." << endl;
        return {};
    }
    
    // Asociatyvus konteineris
    
    // Saugo unikalias reikšmes
    set<wstring> url;
    wstring eilute;

    while (getline(in, eilute)) {
        if (!eilute.empty()) {
            url.insert(mazosios_raides(eilute));
        }
    }

    if (url.empty()) {
        cout << "Failas " << failo_pavadinimas << " yra tuščias. URL adresų suradimas bus netikslus. " << endl;
    }

    in.close();
    return url;
}

wstring sutvarkyti_url(const wstring& url) {
    wstring rezultatas = url;

    // Pašaliname pradinius simbolius, kurie nėra raidė ar skaičius
    while (!rezultatas.empty() && !iswalnum(rezultatas.front())) {
        rezultatas.erase(rezultatas.begin());
    }

    // Pašaliname galinius simbolius, kurie nėra raidė ar skaičius
    while (!rezultatas.empty() && !iswalnum(rezultatas.back())) {
        rezultatas.pop_back();
    }
    
    rezultatas = mazosios_raides(rezultatas);

    return rezultatas;
}

bool ar_tld(const wstring& zodis, const set<wstring>& tlds) {
    wstring lower = mazosios_raides(zodis);

    size_t pos = lower.rfind(L'.');

    if (pos == wstring::npos) {
        return tlds.find(lower) != tlds.end();
    }

    if (pos == 0 || pos == lower.size() - 1)
        return false;

    wstring ending = lower.substr(pos + 1);
    return tlds.find(ending) != tlds.end();
}




set<wstring> surasti_url(const vector<wstring>& eilutes, const set<wstring>& tlds) {
    set<wstring> urls;

    wregex url_regex(
        L"(https?://[\\w\\-\\.]+)|"
        L"(www\\.[\\w\\-\\.]+)|"
        L"([\\w\\-]+(\\.[\\w\\-]+)+)|"
        L"(xn--[\\w\\-]+(\\.[\\w\\-]+)*)"
    );
    

    for (const auto& eilute : eilutes) {
        for (auto it = wsregex_iterator(eilute.begin(), eilute.end(), url_regex);
             it != wsregex_iterator(); ++it) {

            wstring valytas = sutvarkyti_url(it->str());

            if (ar_tld(valytas, tlds)) {
                urls.insert(valytas);
            }
        }
    }

    return urls;
}




void url_terminalas(const set<wstring>& urls) {
    wcout << L"----- Surasti URL -----\n\n";
    wcout << left << setw(5) << L"Nr." << L"| " << setw(40) << L"URL" << endl;
    wcout << L"--------------------------------------------------------\n";

    int nr = 1;
    for (const auto& url : urls) {
        wstring nr_str = std::to_wstring(nr) + L".";
        wcout << left << setw(5) << nr_str << L"| "
              << setw(40) << url << L"\n";
        nr++;
    }
}


void url_failas(const set<wstring>& urls, const string& failo_pavadinimas) {
    wofstream out(failo_pavadinimas);
    out.imbue(locale("lt_LT.UTF-8"));

    if (!out.is_open()) {
        cout << "Nepavyko sukurti failo: " << failo_pavadinimas << endl;
        return;
    }

    out << L"----- Surasti URL -----\n\n";
    out << left << setw(5) << L"Nr." << L"| " << setw(40) << L"URL" << endl;
    out << L"--------------------------------------------------------\n";

    int nr = 1;
    for (const auto& url : urls) {
        wstring nr_str = std::to_wstring(nr) + L".";
        out << left << setw(5) << nr_str << L"| " << setw(40) << url << L"\n";
        nr++;
    }

    out.close();
    cout << "URL lentelė išsaugota faile: " << failo_pavadinimas << endl;
}
