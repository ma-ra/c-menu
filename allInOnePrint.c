#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ncurses.h>

#include "allInOnePrint.h"

#define DISPLAY_SIZE 16
#define DISPLAY_BUFFER DISPLAY_SIZE+1 //dla wyświtlacza 16 znakowego potrzebujemy 1 znak więcej na obsługę znaku \0
#define INTERNAL_BUFFER 70 

extern WINDOW *lcdWindow;
extern WINDOW *debugWindow;
int lcdShift=0;

void allInOnePrint(int row, const char* format, ... ) { //... - wiele argumentów dla funkcji vsnprintf (ekwiwalent snprintf)
    char buffer[INTERNAL_BUFFER+DISPLAY_BUFFER]; //do otrzymanego tekstu dodajemy powtórzenie poczatku tekstu,
                                                 //aby przewijanie ładnie działało, dlatego potrzebujemy większy buffor
    size_t bufferSize = sizeof(buffer) / sizeof(buffer[0]); //rozmiar tablicy dzielimy przez rozmiar elementu; np. int ma rozmiar 2 bajtów
    size_t bufferLen=0;
    char displayBuffer[DISPLAY_BUFFER]; 
    size_t displayBufferSize = sizeof(displayBuffer) / sizeof(displayBuffer[0]); //rozmiar tablicy dzielimy przez rozmiar elementu; np. int ma rozmiar 2 bajtów
    size_t displayBufferLen=0;
    size_t displayBufferRightPadding=0;
    va_list args; //lista otrzymanych argumentów

    va_start(args, format); //start makra, które po wybranym słowie "format" (ostatni jawny argument) wstawi argumenty
      vsnprintf(buffer,INTERNAL_BUFFER,format, args); //snprintf zostawia sobie jedno miejsce na znak \0
    va_end(args); //koniec makra
    
    bufferLen=strlen(buffer);
    if (bufferLen < DISPLAY_BUFFER) { //jeżeli takst się zmieści, to wyświetlaj bez obsługi przewijania
      strncpy(displayBuffer, buffer, DISPLAY_BUFFER);
    } else { //obsługa automatycznego przewijania tekstu na ekranie
      memcpy(buffer+bufferLen, " ", 1); //dodajemy spacje na koniec tekstu do wyświetlenia
      memcpy(buffer+bufferLen+1, buffer, DISPLAY_SIZE); //dodajemy na koniec tekstu powtórzenie poczatkowych znaków aby ładnie zapętlić wyświetlanie
      memcpy(displayBuffer, buffer+lcdShift, DISPLAY_SIZE); //kopiujemy do bufora wyświetlacza za każdym razem zaczynając 1 znak dalej; 
                                                            //kopiując zostawiamy 1 znak na \0
      displayBuffer[DISPLAY_BUFFER-1]=0; //dla porządku koczymy tekst znakiem \0; bez tego nie działa np. strlen()
      if (lcdShift < bufferLen) lcdShift++; else lcdShift=0; //inkrementacja przesunięcia wyświetlanego tekstu
    }

    displayBufferLen=strlen(displayBuffer);
    displayBufferRightPadding=displayBufferSize-displayBufferLen;
    memset(displayBuffer+displayBufferLen, ' ', displayBufferRightPadding); //za nowym tekstem wstawiamy spacje 
                                                                            //które nadpiszą poprzedni tekst na wyświetlaczu
    displayBuffer[displayBufferSize-1]=0; //dla porządku koczymy tekst znakiema \0; bez tego nie działa np. strlen()

    /* Wyświetlanie na różnych urzadzeniach wyjściowych, np.
       - wyświetlacz LCD,
       - konsola,
       - konsola UART,
       - konsola z wykorzystaniem ncurses
       - telnet
       - http
    */
    
    /* ncurses */
    mvwprintw(lcdWindow, row, 1, "%s", displayBuffer); //y,x
    werase(debugWindow);  box(debugWindow, 0, 0);
    buffer[bufferLen]=0;
    mvwprintw(debugWindow, 4, 1, "allInOnePrint debug: %d - (%s)", bufferLen, buffer); //y,x

    /* inne */
    //printf("\"%s\"\n",displayBuffer);
    //lcd.set(0,row)
    //lcd.print(displayBuffer);
    //serial.print(displayBuffer);
    //serial.print("\n");
}
