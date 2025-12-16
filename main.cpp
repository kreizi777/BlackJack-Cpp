/*
* Projekt: Gra BlackJack
* Autor: [Kacper Wesołowski]
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm> // Uzywamy z niej funkcji shuffle
#include <random> // Biblioteka do profesjonalnego generowania liczb losowych

using namespace std;


// --- DEFINICJE POMOCNICZE ---

enum Kolor { KIER, KARO, TREFL, PIK }; // Wartosci od 0 - 3 odpowiadaja odpowiedniemu typu karty.

class Karta {
    private:
        int wartosc;
        string figura; // "2", "10", "Krol", "As"
        Kolor kolor;
        string symbolKoloru;

    public:
        Karta(int ranga, Kolor k);
        int getWartosc() const { return wartosc; }
        string getPelnaNazwa() const { return figura + " " + symbolKoloru; }
};

class Talia {
    private:
        vector<Karta> karty;
        int obecnyIndeks;    // Którą karte teraz rozdajemy

    public:
        Talia() {
            obecnyIndeks = 0;
            resetuj();
        }

        void resetuj() {
            karty.clear();
            obecnyIndeks = 0;

            for (int k = 0; k < 4; k++) {
                // Rangi od 2 do 14 (11=Walet, 12=Dama, 13=Krol, 14=As)
                for (int r = 2; r <= 14; r++) {
                    karty.push_back(Karta(r, static_cast<Kolor>(k)));
                }
            }
        }

        void tasuj() { // Odpowiada za losowość
            random_device rd;
            mt19937 g(rd());
            shuffle(karty.begin(), karty.end(), g);
            obecnyIndeks = 0; // Po przetasowaniu rozdajemy od nowa
        }

        Karta wezKarte() {
            if (obecnyIndeks >= karty.size()) {
                resetuj(); // Jeśli karty się skończą, tworzymy nową talię
                tasuj();
            }
            return karty[obecnyIndeks++];
        }
};

class BlackJack {
private:
    double saldo;
    double stawka;
    char opcja;
    Talia taliaGry;
    vector <Karta> rekaGracza;
    vector <Karta> rekaKrupiera;
    string login;

public:
    BlackJack();
    void menu();

private:
    void start(); // Główna pętla gry
    void profil(string &login);
    void pokazStatystyki();
    double wczytajSaldo();
    void zapiszSaldo(double saldo);
    void zapiszWynik(double saldo, double stawka, int sumaGracza, int sumaKrupiera, string wynik);
    double sprawdzSaldo(double &saldo, double &stawka, char &opcja);

    // Logika gry
    int obliczPunkty(const vector<Karta>& reka);
};

// --- MAIN ---

int main() {
    BlackJack gra;
    gra.menu();
    return 0;
}

// --- IMPLEMENTACJA METOD ---

Karta::Karta(int ranga, Kolor k) {
    kolor = k;

    switch (k) {
        case KIER: symbolKoloru = " Kier (♥)"; break;
        case KARO: symbolKoloru = " Karo (♦)"; break;
        case PIK: symbolKoloru = " Pik (♠)"; break;
        case TREFL: symbolKoloru = " Trefl (♣)"; break;
    }

    if (ranga <= 10) {
        figura = to_string(ranga);
        wartosc = ranga;
    } else if (ranga == 11) {
        figura = "Walet"; wartosc = 10;
    } else if (ranga == 12) {
        figura = "Dama"; wartosc = 10;
    } else if (ranga == 13) {
        figura = "Krol"; wartosc = 10;
    } else if (ranga == 14) {
        figura = "As"; wartosc = 11;
    }
}

BlackJack::BlackJack() {
    saldo = 0;
    stawka = 0;
    opcja = ' ';
}

void BlackJack::menu() {
    int wybor;
    do {
        cout << "\n===== BLACKJACK =====\n";
        cout << "1 - Zacznij gre\n";
        cout << "2 - Statystyki\n";
        cout << "3 - Wyjscie\n";
        cout << "Twoj wybór: ";
        cin >> wybor;

        // Zabezpieczenie przed wpisaniem litery zamiast liczby
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "To nie jest liczba!\n";
            continue;
        }

        switch (wybor) {
            case 1:
                saldo = wczytajSaldo();
                cout << "Wczytano saldo: " << saldo << "$" << endl;
                start();
                zapiszSaldo(saldo);
                break;
            case 2:
                pokazStatystyki();
                break;
            case 3:
                cout << "Dzieki za gre! Do zobaczenia!\n";
                break;
            default:
                cout << "Nieprawidlowy wybor! Sprobuj ponownie.\n";
        }
    } while (wybor != 3);
}

void BlackJack::start() {
    // Logowanie / Profil
    profil(login);

    if (saldo <= 0) {
        cout << "Brak srodkow na koncie. Ile pieniedzy chcesz wplacic? " << endl;
        cin >> saldo;
        if (saldo <= 0) {
             cout << "Nie mozna wplacic 0 lub mniej!\n";
             return;
        }
        cout << "Gratulacje! Wplaciles " << saldo << "$" << endl;
    }

    // Pętla rozgrywki (kolejne rozdania)
    do {
        // 1. Przygotowanie stołu
        rekaGracza.clear();
        rekaKrupiera.clear();
        taliaGry.tasuj();

        cout << "\n----------------------------------\n";
        cout << "--- NOWE ROZDANIE ---\n";
        cout << "----------------------------------\n";

        if (saldo <= 0) {
            cout << "Masz 0$! Koniec gry. Wplac wiecej w menu.\n";
            break;
        }

        // 2. Pobieranie stawki
        cout << "Obecne saldo: " << saldo << "$" << endl;
        cout << "Ile chcesz obstawic? ";
        cin >> stawka;

        if (cin.fail() || stawka <= 0) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Nieprawidlowa stawka!\n";
            continue;
        }
        if (stawka > saldo) {
            cout << "Za malo srodkow!\n";
            continue;
        }
        saldo -= stawka;

        // 3. Rozdawanie początkowe
        rekaGracza.push_back(taliaGry.wezKarte());
        rekaKrupiera.push_back(taliaGry.wezKarte());
        rekaGracza.push_back(taliaGry.wezKarte());
        rekaKrupiera.push_back(taliaGry.wezKarte());

        // 4. Wyświetlanie początkowe
        cout << "\nTwoje karty: \n";
        for (const auto& k : rekaGracza) cout << " - " << k.getPelnaNazwa() << endl;
        cout << "SUMA PUNKTOW: " << obliczPunkty(rekaGracza) << endl << endl;

        cout << "Karty krupiera: \n - " << rekaKrupiera[0].getPelnaNazwa() << endl;
        cout << " - [KARTA UKRYTA]" << endl;

        // 5. Tura Gracza›
        char decyzja;
        bool koniecTuryGracza = false;
        string wynikRozdania = "";

        // Sprawdzenie Blackjacka od razu (21 w 2 kartach)
        if (obliczPunkty(rekaGracza) == 21) {
             cout << "\n*** BLACKJACK! ***\n";
             koniecTuryGracza = true;
        }

        while (!koniecTuryGracza) {
            cout << "\n[H]it (dobierz) czy [S]tand (pas)? ";
            cin >> decyzja;

            if (decyzja == 'h' || decyzja == 'H') {
                Karta nowa = taliaGry.wezKarte();
                rekaGracza.push_back(nowa);
                cout << "Dobrales: " << nowa.getPelnaNazwa() << endl;
                cout << "Nowa suma: " << obliczPunkty(rekaGracza) << endl;

                if (obliczPunkty(rekaGracza) > 21) {
                    cout << "PRZEGRALES! Przekroczyles 21.\n";
                    wynikRozdania = "Przegrana (Fura)";
                    koniecTuryGracza = true;
                }
            } else if (decyzja == 's' || decyzja == 'S') {
                koniecTuryGracza = true;
            } else {
                cout << "Nieznana opcja.\n";
            }
        }

        int pktGracza = obliczPunkty(rekaGracza);
        int pktKrupiera = obliczPunkty(rekaKrupiera); // Początkowe punkty krupiera

        // 6. Tura Krupiera (tylko jeśli gracz nie przegrał już furą)
        if (pktGracza <= 21) {
            cout << "\n--- TURA KRUPIERA ---\n";
            cout << "Odkryta karta krupiera: " << rekaKrupiera[1].getPelnaNazwa() << endl;

            while (obliczPunkty(rekaKrupiera) < 17) {
                Karta k = taliaGry.wezKarte();
                rekaKrupiera.push_back(k);
                cout << "Krupier dobiera: " << k.getPelnaNazwa() << endl;
            }

            pktKrupiera = obliczPunkty(rekaKrupiera);
            cout << "Suma krupiera: " << pktKrupiera << endl;

            // 7. Porównanie wyników
            cout << "\n[----------------------- WYNIK ------------------------]\n";
            if (pktGracza == 21 && pktKrupiera != 21) {
                cout << "BLACKJACK!\n";
                saldo += (stawka * 2.5);
                wynikRozdania = "Wygrana! BlackJack!";
            }else if (pktKrupiera == 21 && pktGracza != 21) {
                cout << "Krupier - BlackJack!\n";
                wynikRozdania = "Przegrana! Krupier mial BlackJack!";
            }

            else if(pktKrupiera > 21) {
                cout << "Krupier przekroczyl 21! WYGRYWASZ!\n";
                saldo += (stawka * 2);
                wynikRozdania = "Wygrana (Krupier Fura)";
            } else if (pktGracza > pktKrupiera) {
                cout << "Masz wiecej punktow! WYGRYWASZ!\n";
                saldo += (stawka * 2);
                 wynikRozdania = "Wygrana";
            } else if (pktGracza == pktKrupiera) {
                cout << "REMIS! Odzyskujesz stawke.\n";
                saldo += stawka;
                wynikRozdania = "Remis";
            } else {
                cout << "Krupier ma wiecej punktow. PRZEGRYWASZ.\n";
                 wynikRozdania = "Przegrana";
            }
        } else {
            // Gracz miał furę > 21
             wynikRozdania = "Przegrana (Fura)";
        }

        zapiszWynik(saldo, stawka, pktGracza, pktKrupiera, wynikRozdania);

        // Menu po grze
        sprawdzSaldo(saldo, stawka, opcja);

    } while (opcja != 'q' && opcja != 'Q');
}

int BlackJack::obliczPunkty(const vector<Karta>& reka) {
    int suma = 0;
    int liczbaAsow = 0;

    for (const auto& k : reka) {
        suma += k.getWartosc();
        if (k.getWartosc() == 11) {
            liczbaAsow++;
        }
    }
    // Jeśli suma > 21, zamień asy z 11 na 1
    while (suma > 21 && liczbaAsow > 0) {
        suma -= 10;
        liczbaAsow--;
    }
    return suma;
}

void BlackJack::zapiszWynik(double saldo, double stawka, int sumaGracza, int sumaKrupiera, string wynik) {
    ofstream plik("statystyki.txt", ios::app);
    if (plik.is_open()) {
        time_t teraz = time(0);
        string czas = ctime(&teraz);
        if(!czas.empty()) czas.pop_back(); // Usuwa znak nowej linii z daty

        plik << "------------------------------------------\n";
        plik << "Data: " << czas << endl;
        plik << "Gracz: " << login << endl;
        plik << "Saldo po grze: " << saldo << "$" << endl;
        plik << "Stawka: " << stawka << "$\n";
        plik << "Punkty gracza: " << sumaGracza << "\n";
        plik << "Punkty krupiera: " << sumaKrupiera << "\n";
        plik << "Wynik: " << wynik << endl;
        plik.close();
    } else {
        cout << "Blad zapisu do pliku!\n";
    }
}


void BlackJack::profil(string &login) {
    // Proste logowanie - jeśli plik istnieje, wczytaj ostatni login, jeśli nie - zapytaj
    if (login.empty()) {
        ifstream wczytaj("profil.txt");
        if (wczytaj.is_open()) {
            wczytaj >> login;
            wczytaj.close();
        }

        if (login.empty()) {
            cout << "Podaj swoj login: ";
            cin >> login;
            ofstream zapisz("profil.txt");
            if (zapisz.is_open()) {
                zapisz << login;
                zapisz.close();
            }
        } else {
            cout << "Witaj ponownie, " << login << "!\n";
        }
    }
}

void BlackJack::pokazStatystyki() {
    ifstream plik("statystyki.txt");
    if (plik.is_open()) {
        string linia;
        cout << "\n===== HISTORIA GIER =====\n";
        while (getline(plik, linia)) {
            cout << linia << endl;
        }
        plik.close();
    } else {
        cout << "Brak zapisanych statystyk!\n";
    }
}

void BlackJack::zapiszSaldo(double saldo) {
    ofstream plik("saldo.txt");
    if (plik.is_open()) {
        plik << saldo;
        plik.close();
    }
}

double BlackJack::wczytajSaldo() {
    ifstream plik("saldo.txt");
    double wczytane = 0;
    if (plik.is_open()) {
        plik >> wczytane;
        plik.close();
    }
    return wczytane;
}

double BlackJack::sprawdzSaldo(double &saldo, double &stawka, char &opcja) {
    while (true) {
        cout << "\n[1] Sprawdz saldo | [2] Graj dalej | [Q] Wyjscie\nWybor: ";
        cin >> opcja;

        if (opcja == '1') {
            cout << "--- Twoje saldo: " << saldo << "$ ---\n";
        } else if (opcja == '2') {
            return saldo;
        } else if (opcja == 'q' || opcja == 'Q') {
            return saldo;
        } else {
            cout << "Nieprawidlowy wybor!\n";
        }
    }
}
