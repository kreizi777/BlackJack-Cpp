#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;


class Karta {
    private:
        int numer;
        string nazwa;
        int wartosc;

    public:
        Karta(int n);
    int getWartosc() const;
    string getNazwa() const;

};

class BlackJack {
private:
    double saldo;
    double stawka;
    char opcja;
    int sumaGracza;
    int sumaKrupiera;

public:
    BlackJack();
    void start();
    void menu();

private:
    void zapiszWynik(double saldo, double stawka, int sumaGracza, int sumKrupiera, string wynik);
    int wartoscKarty(int karta);
    string nazwaKarty(int karta);
    double sprawdzWynik( char dobranie, int kartaK1, int kartaK2, int sumaGracza, int sumaKrupiera, double &saldo, double &stawka, int wart1, int wart2, int wartK1, int wartK2);
    double sprawdzSaldo(double &saldo, double &stawka, char &opcja);
    int rozdaj(int karta1, int karta2, int kartaK1, int kartaK2, double &stawka, double &saldo, int wart1, int wart2, int wartK1, int wartK2);
    void pokazStatystyki();
    double wczytajSaldo();
    void zapiszSaldo(double saldo);
};



    int main() {
        srand(time(0));
        BlackJack gra;
        gra.menu();
        return 0;
    }





    Karta::Karta(int n) {
        numer = n;

        switch (n) {
            case 1: nazwa = "As"; wartosc = 11; break;
            case 11: nazwa = "Walet"; wartosc = 10; break;
            case 12: nazwa = "Dama"; wartosc = 10; break;
            case 13: nazwa = "Krol"; wartosc = 10; break;
            default: nazwa = to_string(n); wartosc = n; break;

        }
    }
    int Karta::getWartosc() const { return wartosc; }
    string Karta::getNazwa() const { return nazwa; }

    BlackJack::BlackJack() {
        saldo = 0;
        stawka = 0;
        opcja = ' ';
        sumaGracza = 0;
        sumaKrupiera = 0;
        srand(time(0));
    }

    void BlackJack::menu() {
        int wybor;
        do{
            cout << "\n===== BLACKJACK =====\n";
            cout << "1 - Zacznij gre\n";
            cout << "2 - Statystyki\n";
            cout << "3 - Wyjscie\n";
            cout << "Twoj wybór: ";
            cin >> wybor;

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
        }while (wybor != 3);
    }
    void BlackJack::start() {
        // DEPOZYT PIENIEDZY
        if (saldo == 0) {
            cout <<  "Ile pieniedzy chcesz wplacic" << endl;
            cin >> saldo;
            cout << " Gratulacje! wplaciles " << saldo << "$" << endl;

            // PETLA DZIEKI KTOREJ GRA SIE NIE KONCZY PO 1 RUNDZIE
        }
        do {
            
            opcja = ' ';
            int karta1 = rand() % 13 + 1;
            int karta2 = rand() % 13 + 1;

            int wart1 = wartoscKarty(karta1);
            int wart2 = wartoscKarty(karta2);

            if (wart1 + wart2 > 21) {
                if (wart1 == 11) wart1 = 1;
                else if (wart2 == 11) wart2 = 1;
            }

            sumaGracza = wart1 + wart2;

            int kartaK1 = rand() % 13 + 1;
            int kartaK2 = rand() % 13 + 1;

            int wartK1 = wartoscKarty(kartaK1);
            int wartK2 = wartoscKarty(kartaK2);

            if (wartK1 + wartK2 > 21) {
                if (wartK1 == 11) wartK1 = 1;
                else if (wartK2 == 11) wartK2 = 1;
            }

            sumaKrupiera = wartK1 + wartK2;

            rozdaj(karta1, karta2, kartaK1, kartaK2, stawka, saldo, wart1, wart2, wartK1, wartK2);
            sprawdzSaldo(saldo, stawka, opcja);


        }while (opcja != 'q' && opcja != 'Q');

        cout << string(50, '\n');
        cout << "Dzieki za zagranie w mojego BlackJacka!!!" << endl;
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
        double saldo = 100; // domyślne saldo
        if (plik.is_open()) {
            plik >> saldo;
            plik.close();
        }
        return saldo;
    }

    int BlackJack::wartoscKarty(int karta) {
        if (karta >= 2 && karta <= 10) return karta;
        if (karta >= 11 && karta <= 13) return 10;
        if (karta == 1) return 11; // lub 1 – zależy od sytuacji
        return 0;
    }
    string BlackJack::nazwaKarty(int karta) {
        Karta k(karta);
        return k.getNazwa();
    }

    int BlackJack::rozdaj(int karta1, int karta2, int kartaK1, int kartaK2, double &stawka, double &saldo , int wart1, int wart2, int wartK1, int wartK2) {

        // GRA SIE SKONCZY JAK STRACISZ CALE SALDO

        if (saldo <= 0) {
            cout << " [-------------------------------] " << endl;
            cout << "    PRZEGRALES CALE SALDO!!!  \n !!!WYJDZ Z GRY !!! " << endl;
            cout << " [-------------------------------] " << endl << endl;
            return 0;
        }

        // GRA PRZYJMUJE WARTOSCI JAKIMI CHCESZ GRAC I ZACZYNA ROZDANIE

        cout << "Ile pieniedzy chcesz obstawic? " << endl;
        cin  >> stawka;
        if (stawka > saldo) {
            cout << "Nie masz tyle pieniedzy!" << endl;
            return 0;
        }
        saldo -= stawka;

        cout << " [ ----------------------- GRACZ --------------------- ] " << endl << endl;
        cout << "Twoje rozdanie to: " << nazwaKarty(karta1) << " i " << nazwaKarty(karta2) << endl;
        cout << "Wartosc twoich kart to: " << wart1 + wart2 << endl << endl;

        cout << " [ ---------------------- KRUPIER --------------------- ] " << endl << endl;
        cout << "Rozdanie krupiera to: " << nazwaKarty(kartaK1) << " i " << "Ukryta " << endl << endl;

        char dobranie;

        sprawdzWynik(dobranie, kartaK1, kartaK2, wartoscKarty(karta1) + wartoscKarty(karta2), wartoscKarty(kartaK1) + wartoscKarty(kartaK2) , saldo , stawka, wart1, wart2, wartK1, wartK2  );

        return 0;

    }
    double BlackJack::sprawdzWynik( char dobranie , int kartaK1, int kartaK2, int sumaGracza, int sumaKrupiera, double &saldo, double &stawka, int wart1, int wart2, int wartK1, int wartK2) {
        int dobrana = rand() % 13 + 1;
        int dobranaK1 = 0;


        // PETLA DZIEKI KTOREJ MOZESZ DOBIERAC ILE CHCESZ

        do {
            cout << "Czy chcesz dobrac karte? Jesli tak wpisz h, jesli nie d." << endl;
            cin >> dobranie;


            if (dobranie == 'h' || dobranie == 'H') {
                dobrana = rand() % 13 + 1;
                sumaGracza += wartoscKarty(dobrana);

                if (wartoscKarty(dobrana) == 11 && sumaGracza > 21) {
                    sumaGracza -= 10;
                }

                cout << "Twoja dobrana liczba to: " << wartoscKarty(dobrana) << endl << endl;
                cout << "Twoja suma wynosi teraz: " << sumaGracza << endl << endl;



                if (sumaGracza > 21) {
                    cout << "Przegrales! Przekroczyles 21!" << endl;
                    stawka = 0;
                    saldo += stawka;
                    zapiszWynik(saldo, stawka, sumaGracza, sumaKrupiera, "Przegrana");
                    return saldo;
                }
                if (sumaGracza == 21) {
                    cout << "BlackJack!" << endl;
                    stawka *= 2.5;
                    saldo += stawka;
                    dobranie = 'd';
                    zapiszWynik(saldo, stawka, sumaGracza, sumaKrupiera, "BlackJack");
                    return saldo;
                }
            }
            if (dobranie == 'd' || dobranie == 'D') {
                cout << "Suma krupiera to: " << sumaKrupiera << endl << endl;



                //  DOBIERANIE KRUPIERA

                while (sumaKrupiera < 17) {
                    dobranaK1 = rand() % 13 + 1;
                    sumaKrupiera += wartoscKarty(dobranaK1);

                    if (wartoscKarty(dobranaK1) == 11 && sumaKrupiera > 21) {
                        sumaKrupiera -= 10;
                    }

                    cout << "Krupier dobral karte: " << nazwaKarty(dobranaK1) << endl;
                    cout << "Suma krupiera to: " << sumaKrupiera << endl << endl;
                }


                // POKAZYWANIE WYNIKU

                cout << endl << " [----------------------- WYNIK ------------------------] " << endl << endl;
                cout << "Twoja finalna suma to: " << sumaGracza << endl;
                cout << "Finalna suma krupiera: " << sumaKrupiera << endl << endl;


                // DECYZJA CZY WYGRALES CZY PRZEGRALES

                if (sumaKrupiera > 21) {
                    cout << "Krupier przekroczyl 21! Wygrales!" << endl;
                    stawka *= 2.0;
                    saldo += stawka;
                    zapiszWynik(saldo, stawka, sumaGracza, sumaKrupiera, "Wygrana");
                    return saldo;
                }
                else if (sumaKrupiera == sumaGracza) {
                    cout << "Remis!" << endl;
                    stawka *= 1;
                    saldo += stawka;
                    zapiszWynik(saldo, stawka, sumaGracza, sumaKrupiera, "Remis");
                    return saldo;
                }
                else if (sumaGracza < sumaKrupiera)  {
                    cout << "Przegrales! Krupier ma wiecej" << endl;
                    stawka = 0;
                    saldo += stawka;
                    zapiszWynik(saldo, stawka, sumaGracza, sumaKrupiera, "Przegrana");
                    return saldo;
                }
                else if (sumaGracza > sumaKrupiera) {
                    cout << "Wygrales! Masz wiecej od krupiera!" << endl;
                    stawka *= 2.0;
                    saldo += stawka;
                    zapiszWynik(saldo, stawka, sumaGracza, sumaKrupiera, "Wygrana");
                    return saldo;
                }

                return saldo;
            }
        }while (dobranie != 'd' && dobranie != 'D');


    }
    double BlackJack::sprawdzSaldo(double &saldo, double &stawka, char &opcja) {
        // PETLA KTORA DZIALA DOPOKI NIE WYBIERZESZ ZE CHCESZ ZACZAC NASTEPNA RUNDE ALBO WYJSC

        while (opcja != 'q' && opcja != 'Q' && opcja != '2') {
            cout << endl <<"[----------------------------------------------------------]" << endl << endl;
            cout << endl << "Wybierz 1 jeśli chcesz sprawdzic saldo! " << endl;
            cout << endl << "Wybierz 2 jeśli chcesz zaczac nastepna runde! " << endl << endl;
            cout << endl << "Wybierz q jeśli chcesz wyjsc i sie poddac :c ! " << endl << endl;

            cin >> opcja;


            // POKAZYWANIE SALDA

            switch (opcja) {
                case '1': cout << "----------------[ Twoje saldo wynosi: " << saldo << "$ ]------------------" << endl; break;
                case '2': break;
                case 'q': return 'q';
                default: cout << "Wprowadz poprawny wybor! \n";
            }

        }
        return saldo;
    }
    void BlackJack::zapiszWynik(double saldo, double stawka, int sumaGracza, int sumaKrupiera, string wynik) {
        ofstream plik("statystyki.txt", ios::app);
        if (plik.is_open()) {
            time_t teraz = time(0);
            string czas = ctime(&teraz);
            czas.pop_back();

            plik << "------------------------------------------\n";
            plik << "Data: " << czas << endl;
            plik << "Saldo: " << saldo << "$" << endl;
            plik << "Stawka: " << stawka << "$\n";
            plik << "Suma gracza: " << sumaGracza << "\n";
            plik << "Suma krupiera: " << sumaKrupiera << "\n";
            plik << "Wynik: " << wynik << endl;
            plik.close();

            cout << "\n ✅ Wynik zapisany do pliku statystyki.txt\n";
        } else { cout << "❌ Blad zapisu do pliku!" << endl;}

        }

