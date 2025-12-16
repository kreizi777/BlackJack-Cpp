🃏 BlackJack C++ – Gra Karciana 🎲
Cześć! 👋 Oto moja wersja klasycznego Blackjacka (Oczka) napisanego w C++. Projekt powstał, żeby poćwiczyć programowanie obiektowe, ale przede wszystkim – żeby można było pograć w karty w konsoli! 🖥️

Autor: Kacper Wesołowski 👨‍💻

🧐 O co chodzi?
Symulujemy tutaj wizytę w kasynie 🎰. Grasz przeciwko Krupierowi (komputerowi). Masz swoje wirtualne pieniądze, obstawiasz zakłady i próbujesz ograć system.

Gra jest sprytna – zapamiętuje Twój stan konta, więc jak zbankrutujesz, to musisz "wpłacić" nowe środki! 💸

🌟 Co potrafi ta gra?
👤 Twój Profil: Gra pamięta Twoje imię (login).

💰 Portfel: Stan konta zapisuje się w pliku – nie tracisz kasy po wyłączeniu gry.

🧠 Mądry Krupier: Komputer gra według prawdziwych zasad kasynowych (dobiera karty do 17 punktów).

🃏 Sprytne Asy: As liczy się jako 11 albo 1, żebyś nie przegrał za szybko.

📜 Historia: Wszystkie Twoje wyniki (wygrane i wtopy) lądują w pliku statystyki.txt.

🛠️ W czym to napisane?
🔵 Język: C++

📚 Biblioteki: Standardowe (nie musisz nic doinstalowywać!). Użyłem vector do trzymania kart i fstream do zapisywania wyników.

🚀 Jak odpalić grę?
Masz kompilator C++? To jedziemy! 🏎️

Pobierz kod:

Bash

git clone https://github.com/twoj-nick/blackjack-cpp.git
Skompiluj:

Bash

g++ main.cpp -o blackjack
Graj!

Windows: blackjack.exe

Linux/Mac: ./blackjack

🎯 Zasady (Szybki poradnik)
Twoim celem jest mieć 21 punktów (lub mniej), ale więcej niż Krupier.

Dostajesz 2 karty. Krupier też, ale jedną ukrywa 🙈.

Decydujesz:

[H]it (Dobierz) ➕ – bierzesz kolejną kartę.

[S]tand (Pas) ✋ – zostajesz z tym, co masz.

⚠️ Uważaj! Jak przekroczysz 21 punktów – PRZEGRYWASZ (Fura).

Jeśli wygrasz, zgarniasz kasę (2x stawka). Jak trafisz Blackjacka (21 w dwóch kartach), dostajesz bonus! 🤑

📂 Co robią te pliki?
Gra tworzy sobie kilka plików tekstowych, żeby pamiętać, co się działo:

profil.txt 👤 – tu siedzi Twój nick.

saldo.txt 💳 – tu zapisana jest Twoja aktualna kasa.

statystyki.txt 📝 – tu jest cała historia Twoich gier (data, ile wygrałeś, jaki był wynik).
