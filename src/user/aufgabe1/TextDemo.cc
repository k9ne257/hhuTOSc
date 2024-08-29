//#include <CGA.h>

 #include "kernel/Globals.h"
 #include "devices/CGA.h"

void text_demo(CGA &cga) {
    // Bildschirm löschen
    cga.clear();

    // Beispieltexte ausgeben
    cga.print("Textdemo gestartet...", 20, cga.attribute(CGA::BLACK, CGA::WHITE, false));
    cga.print("\nZeile 1: Dies ist eine Testzeile.", 30, cga.attribute(CGA::BLACK, CGA::WHITE, false));
    cga.print("\nZeile 2: Hier sehen Sie die Ausgabe auf dem CGA-Bildschirm.", 35,
              cga.attribute(CGA::BLACK, CGA::WHITE, false));
}