#pragma once

/*
* Source code is from https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
* Access time: 30. 11. 2022. 23:00
*/


#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>

#include "vectorAlgebra.h"

/*
0 = Black       8 = Gray
1 = Blue        9 = Light Blue
2 = Green       A = Light Green
3 = Aqua        B = Light Aqua
4 = Red         C = Light Red
5 = Purple      D = Light Purple
6 = Yellow      E = Light Yellow
7 = White       F = Bright White
*/
constexpr const int foregroundBlack = 0x0000;
constexpr const int foregroundBLUE = 0x0001;
constexpr const int foregroundGREEN = 0x0002;
constexpr const int foregroundAQUA = 0x0003;
constexpr const int foregroundRED = 0x0004;
constexpr const int foregroundPURPLE = 0x0005;
constexpr const int foregroundYELLOW = 0x0006;
constexpr const int foregroundWHITE = 0x0007;

constexpr const int foregroundGRAY = 0x0008;
constexpr const int foregroundLIGHT_BLUE = 0x0009;
constexpr const int foregroundLIGHT_GREEN = 0x000A;
constexpr const int foregroundLIGHT_AQUA = 0x000B;
constexpr const int foregroundLIGHT_RED = 0x000C;
constexpr const int foregroundLIGHT_PURPLE = 0x000D;
constexpr const int foregroundLIGHT_YELLOW = 0x000E;
constexpr const int foregroundBRIGHT_WHITE = 0x000F;

constexpr const int backgroundBLACK = 0x0000;
constexpr const int backgroundBLUE = 0x0010;
constexpr const int backgroundGREEN = 0x0020;
constexpr const int backgroundAQUA = 0x0030;
constexpr const int backgroundRED = 0x0040;
constexpr const int backgroundPURPLE = 0x0050;
constexpr const int backgroundYELLOW = 0x0060;
constexpr const int backgroundWHITE = 0x0070;

constexpr const int backgroundGRAY = 0x0080;
constexpr const int backgroundLIGHT_BLUE = 0x0090;
constexpr const int backgroundLIGHT_GREEN = 0x00A0;
constexpr const int backgroundLIGHT_AQUA = 0x00B0;
constexpr const int backgroundLIGHT_RED = 0x00C0;
constexpr const int backgroundLIGHT_PURPLE = 0x00D0;
constexpr const int backgroundLIGHT_YELLOW = 0x00E0;
constexpr const int backgroundBRIGHT_WHITE = 0x00F0;

using namespace VectorAlgebra;

class ConsoleRenderer {
    HANDLE hSTD_IO = nullptr;    // STDIO handle
    IVec2 sizeInChar;
    IVec2 cursorPos;

public:

    IVec2 getSizeInChars() const {
        return sizeInChar;
    }

    void setColor(int color);

    void reset();
    
    void initRenderer(IVec2 _sizeInChars);

    void clearScreen()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        COORD topLeft = { 0, 0 };

        // Figure out the current width and height of the console window
        if (!GetConsoleScreenBufferInfo(hSTD_IO, &csbi)) {
            abort();
        }
        DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

        DWORD written;

        // Flood-fill the console with spaces to clear it
        FillConsoleOutputCharacter(hSTD_IO, TEXT(' '), length, topLeft, &written);

        // Reset the attributes of every character to the default.
        // This clears all background colour formatting, if any.
        FillConsoleOutputAttribute(hSTD_IO, csbi.wAttributes, length, topLeft, &written);

        // Move the cursor back to the top left for the next sequence of writes
        SetConsoleCursorPosition(hSTD_IO, topLeft);
    }

    /*
    * x is the column, y is the row.The origin(0, 0) is top - left.
    * Returns true if the position is inside the window
    */
    bool setCursorPosition(int x, int y)
    {
        if (0 > x || 0 > y || x > sizeInChar.x || y > sizeInChar.y) {   // Prevent out of window positions
            return false;
        }
        COORD coord = { (SHORT)x, (SHORT)y };
        if (SetConsoleCursorPosition(hSTD_IO, coord)) {
            cursorPos = IVec2(x, y);
            return true;
        }
        return false;
    }

    IVec2 getCursorPosition() const {
        return cursorPos;
    }

    void drawSprite(Vec2 pos, char* sprite[], unsigned int width, unsigned int height)
    {
        for (int y = 0; y < height; y++) {
            setCursorPosition(pos.x - width / 2, pos.y - height / 2 + y);
            std::cout << sprite[y];
        }
    }

    void draw(float x, float y, std::string_view str) {
        if (setCursorPosition(x, y)) {
            std::cout << str;
        }
    }

    void draw(float x, float y, std::wstring_view str) {
        if (setCursorPosition(x, y)) {
            std::cout << utf8_encode(str);
        }
    }

    void draw(Vec2 pos, std::string_view str) {
        if (setCursorPosition(pos.x, pos.y)) {
            std::cout << str;
        }
    }

    void draw(Vec2 pos, std::wstring_view str) {
        if (setCursorPosition(pos.x, pos.y)) {
            std::cout << utf8_encode(str);
        }
    }

    void draw(std::string_view str) const {
        std::cout << str;
    }

    void draw(std::wstring_view str) const {
        std::cout << utf8_encode(str);
    }

    private:

    /*
    * Source code from: https://stackoverflow.com/questions/215963/how-do-you-properly-use-widechartomultibyte
    * Accessed: 2023-03-18
    */
    // Convert a wide Unicode string to an UTF8 string
    std::string utf8_encode(std::wstring_view wstr) const
    {
        if (wstr.empty()) return std::string();
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
        std::string strTo(size_needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
        return strTo;
    }

    // Convert an UTF8 string to a wide Unicode String
    std::wstring utf8_decode(std::string_view str) const
    {
        if (str.empty()) return std::wstring();
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
        std::wstring wstrTo(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
        return wstrTo;
    }
};
