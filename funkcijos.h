#include <istream>
#include <vector>
#include <string>
#include <map>

#include "zodziai.h"

using std::string;
using std::vector;
using std::map;

string sutvarkyti_zodziai(const string& zodis);
vector<string> failo_skaitymas(const string& failo_pavadinimas);
map<string, Zodziai> zodziu_skaiciavimas(const vector<string>& eilutes);
void cross_reference_terminalas(const map<string, Zodziai>& zodziai);
void cross_reference_i_faila(const map<string, Zodziai>& zodziai, const string& failo_vardas);



