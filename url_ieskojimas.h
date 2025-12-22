#pragma once

#include <istream>
#include <vector>
#include <string>
#include <set>

using std::string;
using std::vector;
using std::wstring;
using std::set;

wstring mazosios_raides(const wstring& zodis);
set<wstring> nuskaityti_tlds(const string& failo_pavadinimas);
wstring sutvarkyti_url(const wstring& url);
bool ar_tld(const wstring& zodis, const set<wstring>& tlds);
set<wstring> surasti_url(const vector<wstring>& eilutes, const set<wstring>& tlds);
void url_terminalas(const set<wstring>& urls);
void url_failas(const set<wstring>& urls, const string& failo_pavadinimas);
