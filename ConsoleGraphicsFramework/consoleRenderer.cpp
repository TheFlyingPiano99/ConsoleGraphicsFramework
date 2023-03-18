#include "consoleRenderer.h"

#ifdef WINDOWS_PLATFORM

void ConsoleRenderer::setColor(Color color)
{
    SetConsoleTextAttribute(hSTD_IO, (WORD)color);
}

void ConsoleRenderer::reset()
{
    SetConsoleTextAttribute(hSTD_IO, (WORD)Color::backgroundBLACK);
    SetConsoleTextAttribute(hSTD_IO, (WORD)Color::foregroundBRIGHT_WHITE);
    setCursorPosition(0, 0);
}

void ConsoleRenderer::initRenderer(IVec2 _sizeInChars)
{
    sizeInChar = _sizeInChars;
    hSTD_IO = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hSTD_IO, &dwMode);
    dwMode |= ENABLE_EXTENDED_FLAGS;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hSTD_IO, dwMode);

    //Set console code page to UTF-8 so console known how to interpret string data
    SetConsoleOutputCP(CP_UTF8);

    // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
    // Causes error!!!
    //setvbuf(stdout, nullptr, _IOFBF, 1000);

    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hSTD_IO, 0, &fontex);
    fontex.FontWeight = 600;
    IVec2 fontSize(20, 20);
    fontex.dwFontSize.X = (short)fontSize.x;
    fontex.dwFontSize.Y = (short)fontSize.y;
    SetCurrentConsoleFontEx(hSTD_IO, NULL, &fontex);

    HWND hwnd = GetConsoleWindow();

    ShowScrollBar(hwnd, SB_BOTH, FALSE);
    DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;           // Window Extended Style
    DWORD dwStyle = (WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

    IVec2 offset(50, 50);
    constexpr const int scrollBarSize = 20;
    RECT rect = { offset.x, offset.y, offset.x + (int)(fontSize.x * 0.5f * sizeInChar.x) + scrollBarSize, offset.y + fontSize.y * sizeInChar.y };
    AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);   // To hide scroll-bar

    MoveWindow(hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);

}

#endif // WINDOWS_PLATFORM

#ifdef LINUX_PLATFORM
    //TODO

#endif // LINUX_PLATFORM

