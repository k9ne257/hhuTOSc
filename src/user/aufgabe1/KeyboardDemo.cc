#include "kernel/Globals.h"
#include "devices/Keyboard.h"
#include "user/aufgabe1/KeyboardDemo.h"


void keyboard_demo() {
	Keyboard keyboard;
    CGA cga;

    // Schleife für Tastatureingaben
    while (true) {
        Key key = keyboard.key_hit();  // Hole den nächsten Tastendruck

        if (key.valid()) {  // Überprüfe, ob der Key gültig ist
            char ascii = key.ascii();  // Holen des ASCII-Codes der Taste
            if (ascii != 0) {  // Nur wenn ein ASCII-Code vorhanden ist
                cga.print(&ascii, 1, cga.attribute(CGA::WHITE, CGA::BLACK, false));  // Zeige den ASCII-Code auf dem Bildschirm an
            }
        }
    }
}
