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
#include <iostream>

#include "vectorAlgebra.h"
using namespace VectorAlgebra;

#ifdef WINDOWS_PLATFORM
#include <Windows.h>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

namespace cgf {

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
        foregroundAqua = 0x0003,
        foregroundRed = 0x0004,
        foregroundPurple = 0x0005,
        foregroundYellow = 0x0006,
        foregroundWhite = 0x0007,

        foregroundGray = 0x0008,
        foregroundLightBlue = 0x0009,
        foregroundLightGreen = 0x000A,
        foregroundLightAqua = 0x000B,
        foregroundLightRed = 0x000C,
        foregroundLightPurple = 0x000D,
        foregroundLightYellow = 0x000E,
        foreground_bright_white = 0x000F,

        backgroundBlack = 0x0000,
        backgroundBlue = 0x0010,
        backgroundGreen = 0x0020,
        backgroundAqua = 0x0030,
        backgroundRed = 0x0040,
        backgroundPurple = 0x0050,
        backgroundYellow = 0x0060,
        backgroundWhite = 0x0070,

        backgroundGray = 0x0080,
        backgroundLightBlue = 0x0090,
        backgroundLightGreen = 0x00A0,
        backgroundLightAqua = 0x00B0,
        backgroundLightRed = 0x00C0,
        backgroundLightPurple = 0x00D0,
        backgroundLightYellow = 0x00E0,
        backgroundBrightWhite = 0x00F0
    };

    class ConsoleRenderer {
    public:

        IVec2 getSizeInChars() const;

        void setColor(Color color);

        void reset();

        void initRenderer(IVec2 _sizeInChars);

        void clearScreen();

        /*
        * x is the column, y is the row.The origin(0, 0) is top - left.
        * Returns true if the position is inside the window
        */
        bool setCursorPosition(int x, int y);

        IVec2 getCursorPosition() const;

        void drawSprite(Vec2 pos, char* sprite[], unsigned int width, unsigned int height);

        void draw(float x, float y, std::string_view str);

        void draw(float x, float y, std::wstring_view str);

        void draw(Vec2 pos, std::string_view str);

        void draw(Vec2 pos, std::wstring_view str);

        void draw(std::string_view str) const;

        void draw(std::wstring_view str) const;

    private:

        /*
        * Source code from: https://stackoverflow.com/questions/215963/how-do-you-properly-use-widechartomultibyte
        * Accessed: 2023-03-18
        * Convert a wide Unicode string to an UTF8 string
        */
        std::string utf8_encode(std::wstring_view wstr) const;

        /*
        * Source code from: https://stackoverflow.com/questions/215963/how-do-you-properly-use-widechartomultibyte
        * Accessed: 2023-03-18
        * Convert an UTF8 string to a wide Unicode String
        */
        std::wstring utf8_decode(std::string_view str) const;

        HANDLE hSTD_IO = nullptr;    // STDIO handle
        IVec2 sizeInChar;
        IVec2 cursorPos;
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

}
