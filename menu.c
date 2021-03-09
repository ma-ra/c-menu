/*  gcc -o menu menu.c allInOnePrint.c -lncurses */

#include <ncurses.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h> //sleep
#include "allInOnePrint.h"

#define MENU_SIZE 6
#define STRING_SIZE 70
#define GET 0
#define SET 1

/**************/
/* Deklaracje */
/**************/
int key;
time_t rawTime;
struct tm * localTime;

WINDOW *lcdWindow, *debugWindow;  // Okna programu

typedef struct {
  char item[STRING_SIZE];
  char itemValue[STRING_SIZE];
  const char* itemValueFormat;
  int values[16];
  char valuesCount;
  void (*updateMenuBuffer)();
} menuStruct;
menuStruct menu[MENU_SIZE];

typedef struct {
  char action;
  char value;
} menuStatusStruct;
menuStatusStruct menuStatus = {GET, 0}; 

void updateMenuBuffer(int i) {
  /* Wyświetlanie aktualnego czasu */
  rawTime=time(NULL);
  localTime=localtime(&rawTime);
  strftime(menu[0].item,STRING_SIZE,"%m-%d %T",localTime);

  /* Wyświetlanie aktualnych wartości na bazie zadeklarowanego formatu */
  if (menu[i].itemValueFormat != NULL) {
    if (menu[i].valuesCount == 1) { //przypadek gdy mamy do wyświetlenia 1 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0]);
    } else if (menu[i].valuesCount == 2) { //przypadek gdy mamy do wyświetlenia 2 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1]);
    } else if (menu[i].valuesCount == 3) { //przypadek gdy mamy do wyświetlenia 3 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2]);
    } else if (menu[i].valuesCount == 4) { //przypadek gdy mamy do wyświetlenia 4 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3]);
    } else if (menu[i].valuesCount == 5) { //przypadek gdy mamy do wyświetlenia 5 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3], menu[i].values[4]);
    } else if (menu[i].valuesCount == 6) { //przypadek gdy mamy do wyświetlenia 6 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3], menu[i].values[4], menu[i].values[5]);
    } else if (menu[i].valuesCount == 7) { //przypadek gdy mamy do wyświetlenia 7 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3], menu[i].values[4], menu[i].values[5], menu[i].values[6]);
    } else if (menu[i].valuesCount == 8) { //przypadek gdy mamy do wyświetlenia 8 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3], menu[i].values[4], menu[i].values[5], menu[i].values[6], menu[i].values[7]);
    } else if (menu[i].valuesCount == 9) { //przypadek gdy mamy do wyświetlenia 9 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3], menu[i].values[4], menu[i].values[5], menu[i].values[6], menu[i].values[7], menu[i].values[8]);
    } else if (menu[i].valuesCount == 10) { //przypadek gdy mamy do wyświetlenia 10 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3], menu[i].values[4], menu[i].values[5], menu[i].values[6], menu[i].values[7], menu[i].values[8], menu[i].values[9]);
    } else if (menu[i].valuesCount == 11) { //przypadek gdy mamy do wyświetlenia 11 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3], menu[i].values[4], menu[i].values[5], menu[i].values[6], menu[i].values[7], menu[i].values[8], menu[i].values[9], menu[i].values[10]);
    } else if (menu[i].valuesCount == 12) { //przypadek gdy mamy do wyświetlenia 12 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3], menu[i].values[4], menu[i].values[5], menu[i].values[6], menu[i].values[7], menu[i].values[8], menu[i].values[9], menu[i].values[10], menu[i].values[11]);
    } else if (menu[i].valuesCount == 13) { //przypadek gdy mamy do wyświetlenia 13 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3], menu[i].values[4], menu[i].values[5], menu[i].values[6], menu[i].values[7], menu[i].values[8], menu[i].values[9], menu[i].values[10], menu[i].values[11], menu[i].values[12]);
    } else if (menu[i].valuesCount == 14) { //przypadek gdy mamy do wyświetlenia 14 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3], menu[i].values[4], menu[i].values[5], menu[i].values[6], menu[i].values[7], menu[i].values[8], menu[i].values[9], menu[i].values[10], menu[i].values[11], menu[i].values[12], menu[i].values[13]);
    } else if (menu[i].valuesCount == 15) { //przypadek gdy mamy do wyświetlenia 15 wartość
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3], menu[i].values[4], menu[i].values[5], menu[i].values[6], menu[i].values[7], menu[i].values[8], menu[i].values[9], menu[i].values[10], menu[i].values[11], menu[i].values[12], menu[i].values[13], menu[i].values[14]);
    } else if (menu[i].valuesCount == 16) { //przypadek gdy mamy do wyświetlenia 16 wartości
      snprintf(menu[i].itemValue, STRING_SIZE, menu[i].itemValueFormat, menu[i].values[0], menu[i].values[1], menu[i].values[2], menu[i].values[3], menu[i].values[4], menu[i].values[5], menu[i].values[6], menu[i].values[7], menu[i].values[8], menu[i].values[9], menu[i].values[10], menu[i].values[11], menu[i].values[12], menu[i].values[13], menu[i].values[14], menu[i].values[15]);
      /* Dotychczas 16 wartości używa tylko jedna pozycja w menu. 
         Dlatego w brzydki sposób tutaj umieściłem specyficzną obsługe tej pozycji. */
      if (menuStatus.action==SET && menuStatus.value >= 0 && menuStatus.value <= 3) {
        memmove(menu[i].itemValue,menu[i].itemValue+7,16);
        menu[i].itemValue[12]=0;
      } else if (menuStatus.action==SET && menuStatus.value >= 4 && menuStatus.value <= 7) {
        memmove(menu[i].itemValue,menu[i].itemValue+20,16);
        menu[i].itemValue[12]=0;
      } else if (menuStatus.action==SET && menuStatus.value >= 8 && menuStatus.value <= 11) {
        memmove(menu[i].itemValue,menu[i].itemValue+33,16);
        menu[i].itemValue[12]=0;
      } else if (menuStatus.action==SET && menuStatus.value >= 12 && menuStatus.value <= 16) {
        memmove(menu[i].itemValue,menu[i].itemValue+46,16);
        menu[i].itemValue[12]=0;
      }
    }
  }
}

/*********/
/* Main */
/********/
int main() {
  for (int i=0; i<MENU_SIZE; i++) {
    menu[i].itemValueFormat=NULL; //poźniej sprawdzamy czy NULL i jezeli tak to nic nie robimy
    menu[i].valuesCount=1; //na poczatek przyjmujemy, że każda pozycja będzie miała 1 wartosć
    menu[i].updateMenuBuffer=updateMenuBuffer; //podpięcie funkcji pod wskaźnik
  }

  /******************/
  /* Struktura menu */
  /******************/
  strncpy(menu[0].item, "XX-XX XX:XX:XX", STRING_SIZE); //później funkcja updateMenuBuffer wstawi tutaj czas
  menu[0].valuesCount=2; //zmieniamy domyślne 1 na 2
  menu[0].values[0] = 65.10; //podajemy wartości do wyświetlenia
  menu[0].values[1] = 22.12;
  menu[0].itemValueFormat="P:%d B:%d"; //format w jaki wyświetlać
  menu[0].updateMenuBuffer(0); //zapisz w buforze treść do wyświetlenia zawierającą aktualne wartości

  strncpy(menu[1].item, "1. Boiler status", STRING_SIZE);
  menu[1].values[0] = 180;
  menu[1].itemValueFormat="On: %d min";
  menu[1].updateMenuBuffer(1);

  strncpy(menu[2].item, "2 Boiler harm.", STRING_SIZE);
  menu[2].valuesCount=16;
  menu[2].values[0] = 6;
  menu[2].values[1] = 0;
  menu[2].values[2] = 7;
  menu[2].values[3] = 0;
  menu[2].values[4] = 13;
  menu[2].values[5] = 10;
  menu[2].values[6] = 14;
  menu[2].values[7] = 50;
  menu[2].values[8] = 22;
  menu[2].values[9] = 0;
  menu[2].values[10] = 23;
  menu[2].values[11] = 0;
  menu[2].values[12] = 0;
  menu[2].values[13] = 0;
  menu[2].values[14] = 0;
  menu[2].values[15] = 0;
  menu[2].itemValueFormat="PN-ND, %02d:%02d-%02d:%02d, %02d:%02d-%02d:%02d, %02d:%02d-%02d:%02d, %02d:%02d-%02d:%02d";
  menu[2].updateMenuBuffer(2);
  
  strncpy(menu[3].item, "3. Boiler timer", STRING_SIZE);
  menu[3].values[0] = 13;
  menu[3].itemValueFormat="%d min";
  menu[3].updateMenuBuffer(3);

  strncpy(menu[4].item, "4. Aktual. czas", STRING_SIZE);
  strncpy(menu[4].itemValue, "-", STRING_SIZE);

  strncpy(menu[5].item, "5. Jasnosc", STRING_SIZE);
  menu[5].values[0] = 90;
  menu[5].itemValueFormat="%d%%";
  menu[5].updateMenuBuffer(5);

  /*************************/
  /* Emulacja wyświetlacza */
  /*************************/
  initscr(); //inicjalizacja ekranu dla ncurses
  cbreak(); //nie czekaj na enter przy odczycie klawiszy
  keypad(stdscr, TRUE); //włączy tryb Keypad dla okna głównego; m.in obsługa strzałek na klawiaturze
  noecho(); //nie wyświetlaj wciskanych klawiszy
  curs_set(0); //nie wyświetlaj kursora
  timeout(0); //getch nie wstrzymuje pętli; warto dodać usleep(100000) w pętli aby nie obciążać procesora

  mvprintw(0,1,"LCD"); //wyświetl napisy w ustalonych pozycjach
  mvprintw(6,1,"Debug"); 
  refresh(); //przenieś bufor na ekran

  lcdWindow = newwin(4, 18, 1, 0); //nowe okno; linie, kolumny, y, x
  box(lcdWindow, 0, 0);     //standardowe ramki dla okna
  allInOnePrint(1, "%s", menu[0].item); //obsługa wyświetlania w zewnętrznej bibliotece
  allInOnePrint(2, "%s", menu[0].itemValue);
  wrefresh(lcdWindow); //przenieś bufor okienka na ekran

  debugWindow = newwin(10, 120, 7, 0);
  box(debugWindow, 0, 0);
  wrefresh(debugWindow);

  /****************/
  /* Obsługa menu */
  /****************/
  int i=0; //iterator po menu
  while (key != 'q') {
    menu[0].updateMenuBuffer(0); //wyświetlanie czasu
    key=getch();

    /* Ustawianie menuStatus do odpowiednich wartości*/
    if (key == ' ' && menu[i].valuesCount > 1 && menuStatus.action == SET) { //zmian z SET na SET dla pozycji o większej liczbie parametrów niż 1
      menuStatus.value++; //inkrementuj znacznik indetyfikujący argument którego dotyczy SET
      if (menuStatus.value >=menu[i].valuesCount) { //maksymalna ilość argumentów, czyli przejsć z SET na SET
        menuStatus.value=0; //ustawiono wszystkie wartości
        menuStatus.action=GET; //wracamy do akcji GET
      }
    } else if (key == ' ' && menuStatus.action == GET) { //zmiana z GET na pierwsze SET
      menuStatus.action=SET; 
    } else if (key == ' ' && menuStatus.value==0 && menuStatus.action == SET) { //zmiana z SET na GET
      menuStatus.action=GET;
    }

    /* Przeglądanie menu*/
    if (menuStatus.action == GET) {
      if (key == KEY_UP) {
          if (i>0) i--; else i=MENU_SIZE-1;
      } else if (key == KEY_DOWN) {
          if (i<MENU_SIZE-1) i++; else i=0;
      }
    /* Zmiana wartości paremetrów w menu*/
    } else if (menuStatus.action == SET) {
      if (key == KEY_UP) {
        menu[i].values[menuStatus.value]++; //inkrementuj parametr wskazywany przez menuStatus.value
      } else if (key == KEY_DOWN) {
        menu[i].values[menuStatus.value]--; //dekrementuj
      }
    }
    menu[i].updateMenuBuffer(i); //odśwież bufor z treściami do wyświetlenia 

    

    allInOnePrint(1, "%s", menu[i].item);  //wyświetl aktualne dane z bufora
    allInOnePrint(2, "%s", menu[i].itemValue);
    mvwprintw(debugWindow, 1, 1, "menuStatus.action: %d %010s",menuStatus.action," "); //dane do kontroli działania manu
    mvwprintw(debugWindow, 2, 1, "menuStatus.value: %d %010s",menuStatus.value," ");
    wrefresh(lcdWindow); //odśwież okienko
    wrefresh(debugWindow); //odświez okienko
    refresh(); //odśwież dane na ekranie
    usleep(100000); //aby pętla while nie zjadała za dużo procesora
  }
  endwin(); //była inicjalizacja ekranu ncurses, to trzeba zwolnić ekran; 
            //np. przywraca kursor, obsługę przejścia do nowej linii itp.

  return 0;
}

/* TO DO
- blokada zmiany niektórych parametrów, tzw. readonly
- przenieść obsługę ustawiania harmonogramu w inne miejsce
*/
