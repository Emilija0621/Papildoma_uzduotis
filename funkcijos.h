#include <istream>
#include <vector>
#include <string>
#include <map>


using std::string;
using std::vector;
using std::map;
using std::wstring;


wstring sutvarkyti_zodziai(const wstring& zodis);
vector<wstring> failo_skaitymas(const string& failo_pavadinimas);
void cross_reference_terminalas(const map<wstring, int>& zodziu_skaicius, const map<wstring, vector<int>>& zodziu_eilutes);
void cross_reference_i_faila(const map<wstring, int>& zodziu_skaicius, const map<wstring, vector<int>>& zodziu_eilutes, const string& failo_vardas);
void analizuoti_teksta(const vector<wstring>& eilutes, map<wstring, int>& zodziu_skaicius, map<wstring, vector<int>>& zodziu_eilutes);
