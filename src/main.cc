#include "kernel/Globals.h"
#include "user/aufgabe1/TextDemo.h"
#include "user/aufgabe1/KeyboardDemo.h"

void aufgabe01(CGA& cga) {
    // Bildschirmausgabe testen
    text_demo(cga);

    // Tastatur testen
    keyboard_demo();
}

int main() {
    CGA cga; // Erstelle ein CGA-Objekt

    // Bildschirm löschen.
    cga.clear();

    // Startmeldung ausgeben
    cga.print("Startmeldung: Das System startet...", 30, cga.attribute(CGA::BLACK, CGA::WHITE, false));

    aufgabe01(cga);

    while (1); // Endlosschleife, um das Programm am Laufen zu halten
    return 0;
}