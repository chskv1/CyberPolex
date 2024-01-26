#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

void checkExpLevel(int& exp, int& level) {
    if (exp >= 100) {
        level++;
        exp -= 100;
    }
}


void shop(int &money, int &rasa, int &hp, int &hydro){
    char shopChoice;
    std::cout<<"Witaj w centrum handlowym wybierz do którego sklepu chcesz wejść\n1. Żabka (sklep z alkoholem oraz papierosami i co ważne hotdogami)\n2. Liromeriln.. Leromarlę... nie wiem ta zielona castorama (kupisz tu ulepszenia broni)\n3.Smyk (tutaj kupisz ulepszenia bardzo słabe ale za to drogie)\n4.lumpeks(kupisz tu ulepszenia zbroi)\n99. wyjście z centrum handlowego\n";
    std::cin>>shopChoice;
    switch (shopChoice) {
        case '1':
            char zabkaChoice;
            while (zabkaChoice != 99) {
                if (rasa == 5) {
                    std::cout
                            << "w tym sklepie możesz tylko kupic hot doga. Kasjerka myśli, że jesteś dzieckiem przez to że jesteś krasnoludem\n1.Hotdog - 10zł (10 zdrowia)\n99. Wyjście ze sklepu\n";
                    std::cin >> zabkaChoice;
                    switch (zabkaChoice) {
                        case '1':
                            if (money >= 10) {
                                hp += 10;
                                std::cout << "dziekujemy za zakup w naszym sklepie\n";
                            } else {
                                std::cout << "masz zbyt mało pieniedzy\n";
                            }
                            break;
                        default:
                            continue;

                    }
                } else {
                    std::cout
                            << "witaj w Żabce!\n1. małpka - 7zł (setka 40% napoju, regeneruje 10pkt napojenia\n2. tanie papieroski - 15zł (normalnie palenie raczej jest nie zdrowe ale tutaj regeneruje nam 20pkt zdrowia)\n3. drogie papieroski - 21zł (wyśmienity smak tytoniu pozwala na regeneracje 30pkt zdrowia)\n4.OFERTA SPECJALNA \"Śniadanie robotnika\" - 25zł (magiczny zestaw w którym znajduje się małpka, tanie papierosy i hot dog regeneruje 10 napojenia oraz 40 pkt zdrowia)\n99. Wyjście ze sklepu";
                    std::cin >> zabkaChoice;
                    switch (zabkaChoice) {
                        case '1':
                            if (money >= 7) {
                                hydro += 10;
                                money -=7;
                                std::cout << "dziekujemy za zakup w naszym sklepie\n";
                            } else {
                                std::cout << "masz zbyt mało pieniedzy\n";
                            }
                            break;
                        case '2':
                            if (money >=15){
                                hp+=20;
                                money -=15;
                                std::cout << "dziekujemy za zakup w naszym sklepie\n";
                            } else {
                                std::cout << "masz zbyt mało pieniedzy\n";
                            }
                            break;
                        case '3':
                            if (money >= 21) {
                                money-=21;
                                hp+=30;
                                std::cout << "dziekujemy za zakup w naszym sklepie\n";
                            } else {
                                std::cout << "masz zbyt mało pieniedzy\n";

                            }
                            break;
                        case '4':
                            if (money>=25){
                                money-=25;
                                hydro+=10;
                                hp+=40;
                                std::cout << "dziekujemy za zakup w naszym sklepie\n";
                            } else {
                                std::cout << "masz zbyt mało pieniedzy\n";
                            }
                            break;
                        default:
                            continue;
                    }
                }
                break;
               
            }
            break;
        case '2':
            char leuraChoice;
            while (leuraChoice != 99){
                std::cout<<"witaj w zielonej castoramie!!\nULEPSZENIA ATAKU\n1. 1dmg - 10zł\n2. 5dmg - 40zł\n3.10dmg - 70zł\nULEPSZENIA PANCERZA\n11. 1 armor - 20zł\n 5 armor - 90zł";
            }

            break;
            
    }   

}




void fight(int &hp, int &money, int &exp, int lvl, int &armor, int &mana, int &dmg, char &mob) {
    std::cout << "Rozpoczęła się walka z " << mob << "\n";
    char fightmenu;
    int random;
    int hpmob;
    int dmgmob;
    bool escp = false;

    dmgmob = 2 + 2 * lvl - armor;
    hpmob = 20 + 3 * lvl;
    while (hpmob > 0 && hp > 0 && !escp) {
        std::cout << "Twoje życie: " << hp << "\nTwoja mana: " << mana << "\nŻycie przeciwnika: " << hpmob << std::endl;
        std::cout << "1. Atak\n2. Czary\n3. Ucieczka\n";
        std::cin >> fightmenu;
        switch (fightmenu) {
            case '1':
                random = rand() % 10 + 1;
                if (random >= 5) {
                    hpmob -= dmg;
                    hp -= dmgmob;
                } else {
                    hp -= dmgmob;
                }
                break;
            case '2':

                break;
            case '3':
               random = rand() % 10 + 1;
                if (random > 8) {
                    std::cout << "Udało się uciec!!" << std::endl;
                    escp = true;
                } else {
                    std::cout << "Nie udało się uciec" << std::endl;
                    escp = false;
                }
                break;
            default:
                std::cout << "Niepoprawny wybór!" << std::endl;
                continue;
        }
    }
    money += dmgmob;
    exp += hpmob;
    checkExpLevel(exp, lvl);
}


void createSaveFile(int hp, int armor, int dmg, int money, int hydro, int lvl, int exp, int hpmax, int hydromax, char rasa, char klasa, const std::string& fileName) {
    std::string currentFilePath = __FILE__;
    std::string currentDirectory = currentFilePath.substr(0, currentFilePath.find_last_of("/\\"));
    std::string saveFilePath = currentDirectory + fileName + ".txt";

    std::ofstream saveFile(saveFilePath);

    if (saveFile.is_open()) {
        saveFile << "Name: " << fileName << "\n";
        saveFile << "HP: " << hp << "\n";
        saveFile << "Armor: " << armor << "\n";
        saveFile << "Damage: " << dmg << "\n";
        saveFile << "Money: " << money << "\n";
        saveFile << "Hydro: " << hydro << "\n";
        saveFile << "Level: " << lvl << "\n";
        saveFile << "Experience: " << exp << "\n";
        saveFile << "Max HP: " << hpmax << "\n";
        saveFile << "Max Hydro: " << hydromax << "\n";
        saveFile << "Rasa: " << rasa << "\n";
        saveFile << "Klasa: " << klasa << "\n";
        saveFile.close();
        std::cout << "Postać została zapisana w pliku " << fileName << ".txt" << std::endl;
    } else {
        std::cerr << "bład stworzenia pliku " << fileName << ".txt" << std::endl;
    }
}

void displayFileListAndLoadData() {
    std::vector<std::string> txtFiles;
    int fileNum = 1;

    for (const auto & entry : std::filesystem::directory_iterator(".")) {
        if (entry.path().extension() == ".txt") {
            std::cout << fileNum << ". " << entry.path().filename() << std::endl;
            txtFiles.push_back(entry.path().filename().string());
            fileNum++;
        }
    }

    int chosenFileNum;
    std::cout << "wybierz save do grania: ";
    std::cin >> chosenFileNum;

    if (chosenFileNum > 0 && chosenFileNum <= txtFiles.size()) {
        std::string chosenFileName = txtFiles[chosenFileNum - 1];
        std::ifstream chosenFile(chosenFileName);
        if (chosenFile.is_open()) {
            std::string line;
            std::string name;
            int hp, armor, damage, money, hydro, level, experience, maxHP, maxHydro;
            std::string race, playerClass;

            while (std::getline(chosenFile, line)) {
                if (line.find("Name: ") != std::string::npos) {
                    name = line.substr(6);
                } else if (line.find("HP: ") != std::string::npos) {
                    hp = std::stoi(line.substr(4));
                } else if (line.find("Armor: ") != std::string::npos) {
                    armor = std::stoi(line.substr(7));
                } else if (line.find("Damage: ") != std::string::npos) {
                    damage = std::stoi(line.substr(8));
                } else if (line.find("Money: ") != std::string::npos) {
                    money = std::stoi(line.substr(7));
                } else if (line.find("Hydro: ") != std::string::npos) {
                    hydro = std::stoi(line.substr(7));
                } else if (line.find("Level: ") != std::string::npos) {
                    level = std::stoi(line.substr(7));
                } else if (line.find("Experience: ") != std::string::npos) {
                    experience = std::stoi(line.substr(12));
                } else if (line.find("Max HP: ") != std::string::npos) {
                    maxHP = std::stoi(line.substr(8));
                } else if (line.find("Max Hydro: ") != std::string::npos) {
                    maxHydro = std::stoi(line.substr(11));
                } else if (line.find("Rasa: ") != std::string::npos) {
                    race = line.substr(6);
                } else if (line.find("Klasa: ") != std::string::npos) {
                    playerClass = line.substr(7);
                }
            }
            chosenFile.close();

            std::cout << "Wczytywanie postaci..." << std::endl;
        } else {
            std::cerr << "Error: brak możliwości otwarcia pliku" << std::endl;
        }
    } else {
        std::cerr << "Error: zły numer pliku" << std::endl;
    }
}

int main() {
                                                                                       // Zmienne statystyk gracza
    int hp, armor, dmg, money, hydro, lvl, exp, hpmax, hydromax, randomValue, police;

    char rasa, klasa, advmenu, mob, workChoice, ksChoice, msChoice, pieCHoice;
    while (true) {

        // Menu gry
        std::cout << " _____       _              ______     _           \n";
        std::cout << "/  __ \\     | |             | ___ \\   | |          \n";
        std::cout << "| /  \\/_   _| |__   ___ _ __| |_/ /__ | | _____  __\n";
        std::cout << "| |   | | | | '_ \\ / _ \\ '__|  __/ _ \\| |/ _ \\ \\/ /\n";
        std::cout << "| \\__/\\ |_| | |_) |  __/ |  | | | (_) | |  __/>  < \n";
        std::cout << " \\____/\\__, |_|\\__/ \\___|_|  \\_|  \\___/|_|\\___/_/\\_\\\n";
        std::cout << "        __/ |                                      \n";
        std::cout << "       |___/                                       \n";
        std::cout << "------------------------------------------------------\n";
        std::cout << "                        MENU\n";
        std::cout << "------------------------------------------------------\n";
        std::cout << "1. nowa gra\n";
        std::cout << "2. wczytaj grę\n";
        std::cout << "3. ustawienia\n";
        std::cout << "99. wyjście\n";
        char menu;
        std::cin >> menu;
        switch (menu) {
            case '1':
                // Rozpoczęcie nowej gry
                char savename[100];
                std::cout << "Podaj swoje imię: "; // Nazwa save
                std::cin >> savename;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                // Wybór rasy
                std::cout << "Wybierz rasę\n";
                std::cout
                        << "1. POLAK- Wygląda jak człowiek i jest nim.\n Myśli że jest wyjątkowy a nie wyróżnia się niczym specjalnym.\n Nienawidzi innych ludzi i boi się diabłów.\n";
                std::cout
                        << "2. ARAB- Nie mówi za dobrze po polsku za to robi wyśmienite kebaby,\n dzięki czemu jest w stanie złagodzić przeciwnika.\n Jego higiena zostawia wiele do życzenia.\n ";
                std::cout
                        << "3. UCHODŹCA WOJENNY- Zna polski ale mówi z wyjątkowym akcentem.\n Gdy dochodzi do tarcia z stróżami prawa zapomina języka polskiego\n wymawiając zaklęcie \"ja nie chcioł ja nie wiedzioł\"\n";
                std::cout
                        << "4. DIABEŁ- Zna wszystkie języki.\n Ludzie na jego widok uciekają może przebrać się i udawać człowieka.\n Posiada przenośne wrota piekieł.\n W piekle od roku 2020 nie wolno palić papierosów, często udaje się na ziemię żeby zapalić.\n";
                std::cout
                        << "5. KRASNOLUD- W zasadzie to po prostu karzeł, ale żeby było zabawnie twórca stwierdził że będzie to krasnolud.\n Często zostaje nie zauważony przez innych ludzi.\n Niestety ma duży problem z przedmiotami oraz ubraniami, dlatego wszystkie przedmioty kupuje w sklepie z zabawkami.\n";
                std::cin >> rasa;
                std::cout << "Wybrałeś rasę: " << rasa << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                // Wybór klasy
                std::cout << "Wybierz klasę\n";
                std::cout
                        << "1. WOJOWNIK ULICY- Można powiedzieć, że to typowa klasa wojownika.\n Może zarabiać na okradaniu przechodniów,\n może również handlować dobrami nielegalnymi i kradzionymi radiami samochodowymi.\n";
                std::cout
                        << "2. KSIĄDZ- Dostaje do bonusy do walki z siłami nieczystymi.\n Ma słabość do ministrantów.\n Może rzucać zaklęciami. Główne źródło utrzymania\n to taca, ale czasem trafi się ślub lub kolęda, gdzie obywatele dają co łaska nie mniej niż 300zł.\n";
                std::cout
                        << "3. FACHOWIEC- Główne motto to: u siebie rób jak u siebie, a u obcego na od.....\n Zarabia na pracach remontowych. \n";
                std::cout
                        << "4. EGZORCYSTA- Posługuje się bronią palną, jednak bardzo nie celnie.\n Głównie utrzymuje się ze zleceń na powstrzymywaniu sił nieczystych (200zł a jak z fakturą to jeszcze drożej, czyli się nie opłaca).\n";
                std::cout
                        << "5. DEBIL- W zasadzie ta klasa nic nie robi.\n Ale dzięki swojej ukrytej umiejętności przeciwnicy nie zwracają na niego uwagi, dzięki czemu ucieczka staje się łatwiejsza.\n";
                std::cin >> klasa;

                hp = 100;
                hydro = 100;
                dmg = 1;
                armor = 0;
                money = 0;
                lvl = 0;
                exp = 0;

                switch (klasa) {
                    case '1':
                        hp = hp + 10;
                        hpmax = hp;
                        hydro = hydro - 70;
                        hydromax = hydro;
                        dmg = dmg + 5;
                        armor = armor + 5;
                        break;
                    case '2':
                        hp = hp - 50;
                        hydro = hydro + 20;
                        dmg = 0;
                        hpmax = hp;
                        hydromax = hydro;
                        break;
                    case '3':
                        armor = 15;
                        dmg = 3;
                        hydro = 60;
                        hpmax = hp;
                        hydromax = hydro;
                        break;
                    case '4':
                        hp = 110;
                        dmg = 20;
                        hpmax = hp;
                        hydromax = hydro;
                        break;
                    default:
                        break;
                }

                // Stworzenie save i rozpoczęcie gry
                std::string saveName;
                std::cout << "Podaj nazwę save: ";
                std::cin >> saveName;
                createSaveFile(hp, armor, dmg, money, hydro, lvl, exp, hpmax, hydromax, rasa, klasa, saveName);

                break;
            case '2':
                // Wczytanie zapisu gry
                displayFileListAndLoadData();

                break;
           case '3':
                // Ustawienia - W sumie chuj wie co tu dać
                break;
           case '99':
                return 0;
           default:
                continue;
        }
        // Rozgrywka
        // Ekran ładowania ale już działą
        int i;
        for (i = 0; i < 15; i++) {
            std::cout << "=";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        checkExpLevel(exp, lvl);
        std::cout << std::endl;
        std::cout << "____________________Statystyki________________________________\n";
        std::cout << "Życie: " << hp <<"/"<< hpmax << " Najpojenie: " << hydro <<"/"<< hydromax << " Pieniądze: " << money << "\n Siła ataku: " << dmg
                  << " Pancerz: " << armor << " Poziom: " << lvl << " Doświadczenie: " << exp << std::endl;
        std::cout << "1. przygoda\n";
        std::cout << "2. praca\n";
        std::cout << "3. ustawienia\n";
        std::cout << "4. zapisz gre\n";
        std::cout << "98. wróć do menu\n";
        char menugame;
        std::cin >> menugame;
        switch (menugame) {
            case '1':
                std::cout << "Wyruszasz w przygodę pełną niespodzianek rzuć kościa by doweidzieć sie co sie wydarzy\n";
                std::cout << "wpisz w terminal liczbę 1 aby rzucić kością\n";
                char userInput;
                std::cin >> userInput;

                if (userInput == '1') {
                    // Losowanie liczby od 1 do 10
                    randomValue = rand() % 10 + 1;

                    std::cout << "Wylosowano liczbę: " << randomValue << std::endl;
                } else {
                    std::cout << "Niepoprawne wejście. Wpisz '1' aby losować liczbę.\n";
                }
                switch (userInput) {
                    case '1':

                        std::cout<< "Trafiasz na MENELA który prosi ciebie o 5 zł na piwo. Wydaje się być bardzo sympatyczny. \n na razie nie musisz sie o nic obawiać. jednak co się stanie gdy nie dasz mu 5zł tego nikt nie wie.....";
                        mob = 'MENEL';
                        std::cout << "1.daj 5ZŁ.\n2.nie dwaj\n";
                        char choice;
                        std::cin >> choice;
                        switch (choice) {
                            case '1':
                                if (money >= 5) {
                                    money -= 5;
                                } else {
                                    std::cout << "Nie masz tyle pieniedzy";
                                    fight(hp, money, exp, lvl, armor, hydro, dmg, mob);
                                }
                                break;
                            case '2':
                                std::cout << "i to był twój błąd";
                                fight(hp, money, exp, lvl, armor, hydro, dmg, mob);
                                break;
                            default:
                                continue;
                        }

                        fight(hp, money, exp, lvl, armor, hydro, dmg, mob);

                        break;
                    case '2':
                        std::cout
                                << "napotykasz farmę na której słyszysz dziwne dzwięki.\n Podchodzisz bliżej by zobaczyć o co chodzi i tu nagle ni z gruchy ni z pietruchy\n wyskakuje ANTYCHRYSTOZAUR\n";
                        fight(hp, money, exp, lvl, armor, hydro, dmg, mob);
                        break;
                    case '3':
                        std::cout
                                << "ahhh któy mamy rok? w sumie to nie wiem. Nie ważne,\n ważne że jesteś w wielkiej metropoli zwaną polską przechadzasz sie ulicami\n wszędzie pełno demonów i tego podopbnego dziadostwa\n w sumie to wiecej jest tego dziwactwa niż ludzi\n zamyśliłeś się człowieku i prawie wszedłęś na koncert Ajronwejder ale na szczęśćie ochroniarz ciebie zatrzymał\n teraz z nim walczysz jest to NEBULIZATOR\n ";
                        fight(hp, money, exp, lvl, armor, hydro, dmg, mob);
                        break;
                    case '4':
                        std::cout
                                << "napotykasz pełną paczke papierosów. Myślisz sobie kto mogł to zgubić\n ja też nie wiem.\n";
                        fight(hp, money, exp, lvl, armor, hydro, dmg, mob);
                        break;
                    case '5':
                        std::cout
                                << "po długiej podróży która trwała całe 5min zatrzymujesz sie\n by zapalić swoje ulubione papieroski.\n obok ciebie przechodzi stara baba okazuje sie być SZEPTUCHĄ \n coś tam sobie mamrocze pod nosem nie wiesz o co chodzi\n i w ty momencie ona sie odwraca i ciebie atakuje wraz z przyzwanymi demonami\n";
                        fight(hp, money, exp, lvl, armor, hydro, dmg, mob);
                        break;
                    case '6':
                        std::cout
                                << "Przechadzając się ulicami miasta, nagle zauważasz podejrzaną postać w czarnym płaszczu.\n Gdy zbliżasz się, okazuje się, że to EGZORCYSTA , gotowy do walki z siłami ciemności.";
                        fight(hp, money, exp, lvl, armor, hydro, dmg, mob);
                        break;
                    case '7':
                        std::cout
                                << "Podczas spaceru natrafiasz na tajemniczy obiekt zakryty płachtą. Gdy podnosisz ją, zauważasz, że to DEMON-WERKELING, który grozi zniszczeniem miasta. Czas na walkę!";
                        fight(hp, money, exp, lvl, armor, hydro, dmg, mob);
                        break;
                    case '8':
                        std::cout
                                << "Wchodzisz do opuszczonego budynku, gdzie czujesz niepokojącą obecność. Nagle z ciemności wyłania się ZJAWA nawiedzająca mieszkańców miasta. Musisz ją powstrzymać!";
                        fight(hp, money, exp, lvl, armor, hydro, dmg, mob);
                        break;
                    case '9':
                        std::cout
                                << "Podczas spaceru po parku dostrzegasz tajemniczy rytuał odprawiany przez grupę kultystów. Nagle z krzaków wyrasta upiorny DEMON-KULTYSTA, gotowy do konfrontacji!\n";
                        fight(hp, money, exp, lvl, armor, hydro, dmg, mob);
                        break;
                    case '10':
                        std::cout
                                << "W lesie napotykasz starożytny grobowiec, z którego wydobywa się złowieszczy szmer. Niespodziewanie z ciemności wyskakuje ZMUMIFIKOWANY WAMPIR, gotowy do krwawej uczty. Czas na walkę o przetrwanie!\n";
                        fight(hp, money, exp, lvl, armor, hydro, dmg, mob);
                        break;
                    default:
                        continue;
                }

                break;
            case '2':

                std::cout
                        << "wybierz od kogo chcesz wykonać zlecenie:\n 1. ksiądz proboszcz\n 2.mieszkańcy\n3. wyprawa do piekła(wymaga przenośnych wrot piekieł)\n99. Powrót\n";
                std::cin >> workChoice;
                switch (workChoice) {
                    case '1':

                            if (klasa == 2) {
                                std::cout
                                        << "1.zbieranie na tace(-20 napojenia, +20-100zł)\n2.rozgrzeszanie wiernych(-10 napojenia +35zł)\n3.udzielanie ślubu(-80 napojenia +100-500zł\n";
                                std::cin >> ksChoice;
                                switch (ksChoice) {
                                    case '1':
                                        money += rand() % 81 + 20;
                                        hydro -= 20;
                                        break;
                                    case '2':
                                        money += 35;
                                        hydro -= 10;
                                        break;
                                    case '3':
                                        money += rand() % 401 + 100;
                                        hydro -= 80;
                                        break;
                                    default:
                                        std::cout << "wybrano złą opcję";
                                        continue;
                                }

                            }
                            if (klasa == 3) {
                                std::cout
                                        << "1.renowacja ławek w kościele(-50 hydro + 60zł)\n2.remont zachrysti(-90 hydro +150zł) \n";
                                std::cin >> ksChoice;
                                switch (ksChoice) {
                                    case '1':
                                        hydro -= 50;
                                        money += 60;
                                        break;
                                    case '2':
                                        hydro -= 90;
                                        money += 150;
                                        break;
                                    default:
                                        std::cout << "zły wybór z menu\n";
                                }
                            }
                            if (klasa == 5) {
                                std::cout
                                        << "1.posprzątaj w kościele(-60 hydro +20zł)\n2.wynieś smieci (-1 hydro +10zł)\n";
                                std::cin >> ksChoice;
                                switch (ksChoice) {
                                    case '1':
                                        hydro -= 60;
                                        money += 20;
                                        break;
                                    case '2':
                                        hydro -= 1;
                                        money += 10;
                                        break;
                                    default:
                                        break;
                                }
                            } else {
                                std::cout
                                        << "1. pozbądz sie sił nieczytych(-20 hydro +50zł)\n2. umyj Maybacha ksiedza wikarego (-30 hydro +80zł)\n ";
                                std::cin >> ksChoice;
                                switch (ksChoice) {
                                    case '1':
                                        hydro -= 20;
                                        money += 50;
                                        break;
                                    case '2':
                                        hydro -= 30;
                                        money += 80;
                                        break;
                                    default:
                                        continue;
                                }
                            }
                            break;

                    case '2':
                        if (klasa == 1) {
                            std::cout
                                    << "1. okradaj przechodniów(-20 hydro +0-40zł)\n2.wykonaj zlecenie na pobicie i odzyskanie długu(-60 hydro +100zł)\n3. handluj nielegalnymi towarami(-80 hydro +50-500zł) (ryzyko złapania przez policję)\n";
                            std::cin >> msChoice;
                            switch (msChoice) {
                                case '1':
                                    hydro -= 20;
                                    money += rand() % 40;
                                    break;
                                case '2':
                                    hydro -= 60;
                                    money += 100;
                                    break;
                                case '3':
                                    police = rand() % 100 + 1;
                                    hydro -= 80;
                                    if (police <= 30) {
                                        std::cout
                                                << "Zostałeś złapany przez policję zabierają ci wszystkie pieniądze i na dodatek pobili ciebie zostaje ci 1 pkt zdrowia!!\n";
                                        money = 0;
                                        hp = 1;
                                    } else {
                                        money += rand() % 450 + 51;
                                    }
                                    break;
                                default:
                                    break;
                            }
                        }
                        if (klasa == 3) { // fachowiec

                        }
                        break;
                    case '3':
                        break;
                    case '99':
                        break;
                    default:
                        continue;
                }
                break;
            default:
                continue;
        }
    }
}
