# Egzamino išankstinė užduotis

## Aprašymas

Ši programa skirta analizuoti tekstą iš failo (pavadinimas.txt) ir atlikti du pagrindinius veiksmus:

#### Pasikartojančių žodžių analizė: <br>
- Suskaičiuoja, kiek kartų kiekvienas žodis (tekste esantis daugiau nei 1 kartą) pasikartoja tekste.
- Generuoja cross-reference lentelę, kurioje nurodoma, kiek kartų bei kuriose teksto eilutėse pasikartojantys žodžiai buvo paminėti.

#### URL paieška tekste:
- Išskiria visus URL adresus tekste. Formatai: <br>
Pilni: `https://www.vu.lt/` <br>
Su http: `http://www.vu.lt/` <br>
Sutrumpinti: `www.vu.lt`, `vu.lt` <br>
- Patikrina, ar URL baigiasi galiojančiais domenais (TLD), nurodytais URL.txt faile.
- Rezultatus galima peržiūrėti ekrane arba išsaugoti faile.

## Programos veikimo principas:

- Vartotojas gali pasirinkti, kokį veiksmą nori atlikti: <br>

<img width="313" height="86" alt="image" src="https://github.com/user-attachments/assets/2be225c9-a48f-463a-a445-04da575d716d" /> <br>


- Pasirinkus 1 (tekste rasti pasikartojančius žodžius) vartotojui reikia įvesti failo pavadinimą, kuriame nori rasti pasikartojančius žodžius: <br>

<img width="263" height="35" alt="image" src="https://github.com/user-attachments/assets/7fc7cda3-542d-4062-be48-8d2e1f61347a" /> <br>

Taip pat vartotojo paprašo pasirinkti, kur nori išvesti rezultatus. Jei pasirenka 2 (į failą), paprašo įvesti norimą failo pavadinimą:<br>

<img width="228" height="69" alt="image" src="https://github.com/user-attachments/assets/ef18c54a-f1cb-42d8-b090-0f033399ebff" /> <br>
<img width="275" height="35" alt="image" src="https://github.com/user-attachments/assets/80df0487-4147-4338-b5c4-bdf4aaf7e37d" /> <br>

- Pasirinkus 2 (tekste rasti URL) vartotojui reikia įvesti failo pavadinimą, kuriame nori rasti URL: <br>

<img width="261" height="35" alt="image" src="https://github.com/user-attachments/assets/0540a231-ddb9-40ab-9bc1-99929fc6c53f" /> <br>

Taip pat vartotojo paprašo pasirinkti, kur nori išvesti rezultatus. Jei pasirenka 2 (į failą), paprašo įvesti norimą failo pavadinimą:<br>

<img width="228" height="69" alt="image" src="https://github.com/user-attachments/assets/ef18c54a-f1cb-42d8-b090-0f033399ebff" /> <br>
<img width="275" height="35" alt="image" src="https://github.com/user-attachments/assets/80df0487-4147-4338-b5c4-bdf4aaf7e37d" /> <br>

## Reikalavimai:

- C++ kompiliatorius (Apple Clang 17+ su C++20 palaikymu)
- CMake (3.10+)
- make (Unix/macOS įrankis)

## Paleidimo žingsniai:

#### Projekto struktūra:
Projekto aplankas pavadintas egzaminas. Jame turi būti šie failai: <br>
- main.cpp, zodziai.h ir zodziai.cpp, url_ieskojimas.h ir url_ieskojimas.cpp <br>
- URL.txt, tekstas.txt <br>
- CMakeLists.txt, runme.sh 

#### 1. Naudojant runme.sh:

- Atidaryti terminalą ir pereiti į projekto aplanką: <br>
`cd ~/Desktop/egzaminas`
- Užtikrinti, kad runme.sh yra vykdomas: <br>
`chmod +x runme.sh`
- Paleisti programą: <br>
`./runme.sh`

#### 2. Naudojant cmake:
- Atidaryti terminalą ir pereiti į projekto aplanką: <br>
`cd ~/Desktop/egzaminas`
- Sukurti build aplanką ir sukompiliuoti projektą: <br>
`mkdir build` <br>
`cd build `  <br>
`cmake .. `  <br>
`make ` <br>
- Paleisti programą: <br>
`./egzaminas`



