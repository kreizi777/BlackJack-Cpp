#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;


int rozdaj(int karta1, int karta2, int kartaK1, int kartaK2, double &stawka, double &saldo, int wart1, int wart2, int wartK1, int wartK2);
int wartoscKarty(int karta);
string nazwaKarty(int karta);
double sprawdzWynik( char dobranie, int kartaK1, int kartaK2, int sumaGracza, int sumaKrupiera, double &saldo, double &stawka, int wart1, int wart2, int wartK1, int wartK2);
double sprawdzSaldo(double &saldo, double &stawka, char &opcja);




int main() {

    srand(time(0));
    char opcja;
    double saldo, stawka = 0;
    int sumaGracza = 0;
    int sumaKrupiera = 0;
    char dobranie;
    int wynik = 0;

    // DEPOZYT PIENIEDZY

    cout << " Gra sie rozpoczela!!! Ile pieniedzy chcesz wplacic na start? " << endl;
    cin >> saldo;
    cout << " Gratulacje! wplaciles " << saldo << "$" << endl;

    // PETLA DZIEKI KTOREJ GRA SIE NIE KONCZY PO 1 RUNDZIE

    do {

        cout << string(50, '\n');
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
return 0;
}

int rozdaj(int karta1, int karta2, int kartaK1, int kartaK2, double &stawka, double &saldo , int wart1, int wart2, int wartK1, int wartK2) {

    // GRA SIE SKONCZY JAK STRACISZ CALE SALDO

    if (saldo <= 0) {
        cout << " [-------------------------------] " << endl;
        cout << "    PRZEGRALES CALE SALDO!!! \n     !!! WYJDZ Z GRY !!!" << endl;
        cout << " [-------------------------------] " << endl << endl;
        return '0';
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


// FUNKCJA USTALA JAKA WARTOSC MA KARTA

int wartoscKarty(int karta) {
    if (karta >= 2 && karta <= 10) return karta;
    if (karta >= 11 && karta <= 13) return 10;
    if (karta == 1) return 11; // lub 1 – zależy od sytuacji
    return 0;
}


// FUNKCJA USTALA JAKA KARTE WYLOSOWALES

string nazwaKarty(int karta) {
    switch (karta) {
        case 1: return "As";
        case 11: return "Walet";
        case 12: return "Dama";
        case 13: return "Krol";
        default: return to_string(karta);
    }
}

double sprawdzWynik( char dobranie , int kartaK1, int kartaK2, int sumaGracza, int sumaKrupiera, double &saldo, double &stawka, int wart1, int wart2, int wartK1, int wartK2) {
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
                return saldo;
            }
            if (sumaGracza == 21) {
                cout << "BlackJack!" << endl;
                stawka *= 2.5;
                saldo += stawka;
                dobranie = 'd';
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
                return saldo;
            }
            else if (sumaKrupiera == sumaGracza) {
                cout << "Remis!" << endl;
                stawka *= 1;
                saldo += stawka;
                return saldo;
            }
            else if (sumaGracza < sumaKrupiera)  {
                cout << "Przegrales! Krupier ma wiecej" << endl;
                stawka = 0;
                saldo += stawka;
                return saldo;
            }
            else if (sumaGracza > sumaKrupiera) {
                cout << "Wygrales! Masz wiecej od krupiera!" << endl;
                stawka *= 2.0;
                saldo += stawka;
                return saldo;
            }

            return saldo;
        }
    }while (dobranie != 'd' && dobranie != 'D');


}

double sprawdzSaldo(double &saldo, double &stawka, char &opcja) {


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

return 0;



}