#include <windows.h>
#include <time.h>

// Hauptfunktion
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Konsolenfenster verstecken, falls es erscheint
    FreeConsole();

    // Bildschirmabmessungen abrufen
    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);

    // Gerätekontext für den gesamten Bildschirm holen
    HDC hdc_screen = GetDC(NULL);

    // Zufallsgenerator initialisieren
    srand(time(0));

    // Endlosschleife, um Chaos zu erzeugen
    while (true) {
        // --- Zufällige Bälle zeichnen ---
        int x = rand() % screen_width;
        int y = rand() % screen_height;
        int size = rand() % 120 + 20; // Ballgröße zwischen 20 und 140
        COLORREF color = RGB(rand() % 256, rand() % 256, rand() % 256);

        HBRUSH brush = CreateSolidBrush(color);
        SelectObject(hdc_screen, brush);

        // Ellipse (Ball) zeichnen
        Ellipse(hdc_screen, x, y, x + size, y + size);

        DeleteObject(brush); // Pinselobjekt freigeben, um Speicherlecks zu vermeiden

        // --- Seltsame Effekte hinzufügen ---

        // Effekt 1: Invertiert die Farben eines zufälligen Rechtecks auf dem Bildschirm
        if (rand() % 10 == 0) { // Passiert mit einer Wahrscheinlichkeit von 1 zu 10
            int rx = rand() % screen_width;
            int ry = rand() % screen_height;
            int rwidth = rand() % 400 + 50;
            int rheight = rand() % 400 + 50;
            BitBlt(hdc_screen, rx, ry, rwidth, rheight, hdc_screen, rx, ry, DSTINVERT);
        }

        // Effekt 2: "Schmelzender" Bildschirm-Effekt (kopiert eine Spalte leicht versetzt)
        if (rand() % 20 == 0) { // Passiert mit einer Wahrscheinlichkeit von 1 zu 20
            int melt_x = rand() % screen_width;
            int melt_y = rand() % 20;
            int melt_width = rand() % 3 + 1;
            StretchBlt(hdc_screen, melt_x, melt_y, melt_width, screen_height, hdc_screen, melt_x, 0, melt_width, screen_height, SRCCOPY);
        }
        
        // Eine winzige Pause, um die CPU-Auslastung nicht auf 100% zu treiben
        Sleep(1);
    }

    // Dieser Code wird nie erreicht, ist aber gute Praxis
    ReleaseDC(NULL, hdc_screen);
    return 0;
}
