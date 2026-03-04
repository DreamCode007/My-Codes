#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>



typedef struct {
    int x;
    float y;
    float speed;
    int trailLen;
} Drop;

void terminalSize(int* width, int* height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void makeDrop(Drop* drops, int cols) {
    for (int i = 0; i < cols; i++) {
        drops[i].x = i + 1;
        drops[i].y = 1;
        drops[i].speed = 0.5f + (float)(rand() % 100) / 100.0f;
        drops[i].trailLen = 5 + rand() % 10;
    }
}

char makeChar() {
    return (char)(33 + rand() % 94); //to only get char to ascii code 33 tp 126
}

void printchar(int y, int x, int r, int g, int b, char c) {
    if (y < 1) return;
    std::cout << "\033[" << y << ";" << x << "H"
              << "\033[38;2;" << r << ";" << g << ";" << b << "m"
              << c;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Enable ANSI escape sequences on Windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (hOut == INVALID_HANDLE_VALUE || !GetConsoleMode(hOut, &dwMode)) {
        std::cerr << "Failed to get console mode\n";
        return 1;
    }
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    int width = 0, height = 0;
    terminalSize(&width, &height);

    srand((unsigned)time(NULL));

    Drop* drops = (Drop*)malloc(width * sizeof(Drop));
    makeDrop(drops, width);

    system("CLS");
    std::cout << "\033[2J\033[?25l";

    int newWidth = width, newHeight = height;

    while (1) {
        terminalSize(&newWidth, &newHeight);
        if (newWidth != width || newHeight != height) {
            width = newWidth;
            height = newHeight;
            drops = (Drop*)realloc(drops, width * sizeof(Drop));
            makeDrop(drops, width);
            // system("CLS");
            std::cout << "\033[2J"; 
        }

        for (int i = 0; i < width; i++) {
            int y = (int)drops[i].y;
            if (y >= 1 && y <= height) {
                printchar(y, drops[i].x, 150, 255, 150, makeChar());
            }
            for (int j = 1; j <= drops[i].trailLen; j++) {
                int taily = y - j;
                if (taily < 1 || taily > height) continue;
                float ratio = 1.0f - (float)j / (float)drops[i].trailLen;
                printchar(taily, drops[i].x, 0, (int)(255 * ratio), 0, makeChar());
            }

            drops[i].y += drops[i].speed;

            if (drops[i].y - drops[i].trailLen > height) {
                drops[i].y = 1; 
                drops[i].speed = 0.5f + (float)(rand() % 100) / 100.0f;
            }
        }

        Sleep(25);
    }
    std::cout << "\033[?25h";
    free(drops);
    return 0;
}