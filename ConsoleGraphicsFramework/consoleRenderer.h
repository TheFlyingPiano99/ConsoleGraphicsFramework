#pragma once

/*
* Define platform WINDOWS_PLATFORM or LINUX_PLATFORM
*/
#define WINDOWS_PLATFORM


/*
* Source code is from https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
* Access time: 30. 11. 2022. 23:00
*/

#include <fcntl.h>
#include <io.h>
#include <iostream>

#include "vectorAlgebra.h"
using namespace VectorAlgebra;

#ifdef WINDOWS_PLATFORM
#include <Windows.h>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN


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
enum class Color {
    foregroundBlack = 0x0000,
    foregroundBlue = 0x0001,
    foregroundGreen = 0x0002,
    foregroundAQUA = 0x0003,
    foregroundRED = 0x0004,
    foregroundPURPLE = 0x0005,
    foregroundYELLOW = 0x0006,
    foregroundWHITE = 0x0007,

    foregroundGRAY = 0x0008,
    foregroundLIGHT_BLUE = 0x0009,
    foregroundLIGHT_GREEN = 0x000A,
    foregroundLIGHT_AQUA = 0x000B,
    foregroundLIGHT_RED = 0x000C,
    foregroundLIGHT_PURPLE = 0x000D,
    foregroundLIGHT_YELLOW = 0x000E,
    foregroundBRIGHT_WHITE = 0x000F,

    backgroundBLACK = 0x0000,
    backgroundBLUE = 0x0010,
    backgroundGREEN = 0x0020,
    backgroundAQUA = 0x0030,
    backgroundRED = 0x0040,
    backgroundPURPLE = 0x0050,
    backgroundYELLOW = 0x0060,
    backgroundWHITE = 0x0070,

    backgroundGRAY = 0x0080,
    backgroundLIGHT_BLUE = 0x0090,
    backgroundLIGHT_GREEN = 0x00A0,
    backgroundLIGHT_AQUA = 0x00B0,
    backgroundLIGHT_RED = 0x00C0,
    backgroundLIGHT_PURPLE = 0x00D0,
    backgroundLIGHT_YELLOW = 0x00E0,
    backgroundBRIGHT_WHITE = 0x00F0
};

class ConsoleRenderer {
    HANDLE hSTD_IO = nullptr;    // STDIO handle
    IVec2 sizeInChar;
    IVec2 cursorPos;

public:

    IVec2 getSizeInChars() const {
        return sizeInChar;
    }


    void setColor(Color color);

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
#endif

#ifdef LINUX_PLATFORM
enum class Color {
    foregroundBlack = 0x0000;
};

class ConsoleRenderer {
public:
    //TODO


private:

};

#endif
