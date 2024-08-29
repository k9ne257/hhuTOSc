#include "devices/CGA.h"
#include "kernel/IOport.h"


void CGA::setpos (int x, int y) {
    IOport ctrl_port(0x3D4); // Control port
    IOport data_port(0x3D5); // Data port

    // Setze die Cursor-Position auf (x, y)
    // Wir haben 80 Spalten und 25 Zeilen im CGA-Modus
    // Offset im Video-Speicher für die Cursor-Position
    unsigned short pos = y * 80 + x;

    ctrl_port.outb(0x0E); // Set the register index to 0x0E (High Byte)
    data_port.outb(pos >> 8); // Write the high byte of the position

    ctrl_port.outb(0x0F); // Set the register index to 0x0F (Low Byte)
    data_port.outb(pos & 0xFF); // Write the low byte of the position

}

void CGA::getpos (int &x, int &y) {

    IOport ctrl_port(0x3D4); // Control port
    IOport data_port(0x3D5); // Data port

    ctrl_port.outb(0x0E); // Set the register index to 0x0E (High Byte)
    unsigned short pos = data_port.inb() << 8; // Read the high byte

    ctrl_port.outb(0x0F); // Set the register index to 0x0F (Low Byte)
    pos |= data_port.inb(); // Read the low byte

    y = pos / 80;
    x = pos % 80;

}


/*****************************************************************************
 * Parameter:                                                                *
 *      x,y         Position des Zeichens                                    *
 *      character   Das auszugebende Zeichen                                 *
 *      attrib      Attributbyte fuer das Zeichen                            *
 *****************************************************************************/
void CGA::show (int x, int y, char character, unsigned char attrib) {
    
    /* Hier muess Code eingefuegt werden */
    unsigned char* video_memory = (unsigned char*)0xb8000;
    int offset = (y * 80 + x) * 2; // Berechne den Offset im Video-Speicher

    video_memory[offset] = character; // Setze das Zeichen
    video_memory[offset + 1] = attrib; // Setze das Attribut (Farbe)
    
}

void CGA::scrollup () {
    
    /* Hier muess Code eingefuegt werden */

    unsigned char* video_memory = (unsigned char*)0xb8000;
    for (int i = 0; i < 24 * 80 * 2; ++i) {
        video_memory[i] = video_memory[i + 80 * 2]; // Verschiebe alle Zeilen nach oben
    }
    // Leere die letzte Zeile
    for (int i = 24 * 80 * 2; i < 25 * 80 * 2; ++i) {
        video_memory[i] = ' '; // Setze Leerzeichen
        video_memory[i + 1] = 0x07; // Setze die Standardfarbe
    }
    
}


/*****************************************************************************
 * Parameter:                                                                *
 *      string      Auszugebende Zeichenkette                                *
 *      n           Laenger der Zeichenkette                                 *
 *      attrib      Attributbyte fuer alle Zeichen der Zeichenkette          *
 *****************************************************************************/
void CGA::print (char* string, int n, unsigned char attrib) {
    for (int i = 0; i < n; ++i) {
        if (string[i] == '\n') {
            int x, y;
            // Zeilenumbruch: Setze den Cursor auf den Anfang der nächsten Zeile
            getpos(x, y);
            if (y >= 24) {
                scrollup(); // Wenn wir am Ende des Bildschirms angekommen sind, nach oben scrollen
                y = 24; // Setze y auf die letzte Zeile
            }
            setpos(0, y + 1); // Setze den Cursor auf die nächste Zeile
        } else {
            int x, y;
            show(x, y, string[i], attrib); // Zeige das Zeichen an
            getpos(x, y);
            setpos(x + 1, y); // Gehe zur nächsten Spalte
        }
    }

}

/*****************************************************************************
 * Methode:         CGA::clear                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Lösche den Textbildschirm.                               *
 *****************************************************************************/
void CGA::clear () {
    
    /* Hier muess Code eingefuegt werden */
    unsigned char* video_memory = (unsigned char*)0xb8000;
    for (int i = 0; i < 80 * 25 * 2; ++i) {
        video_memory[i] = ' '; // Setze Leerzeichen
        video_memory[i + 1] = 0x07; // Setze die Standardfarbe
    }
    setpos(0, 0); // Setze den Cursor auf den Anfang des Bildschirms
    
}


/*****************************************************************************
 * Methode:         CGA::attribute                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Hilfsfunktion zur Erzeugung eines Attribut-Bytes aus     *
 *                  Hintergrund- und Vordergrundfarbe und der Angabe, ob das *
 *                  Zeichen blinkend darzustellen ist.                       *
 *                                                                           *
 * Parameter:                                                                *
 *      bg          Background color                                         *
 *      fg          Foreground color                                         *
 *      blink       ywa/no                                                   *
 *****************************************************************************/
unsigned char CGA::attribute (CGA::color bg, CGA::color fg, bool blink) {
    
    /* Hier muess Code eingefuegt werden */

    return (bg << 4) | (fg & 0x0F) | (blink ? 0x80 : 0x00);
    
}
