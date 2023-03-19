#include "consoleRenderer.h"

#ifdef WINDOWS_PLATFORM

IVec2 ConsoleRenderer::getSizeInChars() const {
    return sizeInChar;
}

void ConsoleRenderer::setColor(Color color)
{
    SetConsoleTextAttribute(hSTD_IO, (WORD)color);
}

void ConsoleRenderer::reset()
{
    SetConsoleTextAttribute(hSTD_IO, (WORD)Color::backgroundBlack);
    SetConsoleTextAttribute(hSTD_IO, (WORD)Color::foregroundBrightWhite);
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
    clearScreen();
}

void ConsoleRenderer::clearScreen()
{
    system("CLS");
}

/*
* x is the column, y is the row.The origin(0, 0) is top - left.
* Returns true if the position is inside the window
*/

bool ConsoleRenderer::setCursorPosition(int x, int y)
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

IVec2 ConsoleRenderer::getCursorPosition() const {
    return cursorPos;
}

void ConsoleRenderer::drawSprite(Vec2 pos, char* sprite[], unsigned int width, unsigned int height)
{
    for (int y = 0; y < height; y++) {
        setCursorPosition(pos.x - width / 2, pos.y - height / 2 + y);
        std::cout << sprite[y];
}
    }

void ConsoleRenderer::draw(float x, float y, std::string_view str) {
    if (setCursorPosition(x, y)) {
        std::cout << str;
    }
}

void ConsoleRenderer::draw(float x, float y, std::wstring_view str) {
    if (setCursorPosition(x, y)) {
        std::cout << utf8_encode(str);
    }
}

void ConsoleRenderer::draw(Vec2 pos, std::string_view str) {
    if (setCursorPosition(pos.x, pos.y)) {
        std::cout << str;
    }
}

void ConsoleRenderer::draw(Vec2 pos, std::wstring_view str) {
    if (setCursorPosition(pos.x, pos.y)) {
        std::cout << utf8_encode(str);
    }
}

void ConsoleRenderer::draw(std::string_view str) const {
    std::cout << str;
}

void ConsoleRenderer::draw(std::wstring_view str) const {
    std::cout << utf8_encode(str);
}

/*
* Source code from: https://stackoverflow.com/questions/215963/how-do-you-properly-use-widechartomultibyte
* Accessed: 2023-03-18
*/
// Convert a wide Unicode string to an UTF8 string

std::string ConsoleRenderer::utf8_encode(std::wstring_view wstr) const
{
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

// Convert an UTF8 string to a wide Unicode String

std::wstring ConsoleRenderer::utf8_decode(std::string_view str) const
{
    if (str.empty()) return std::wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
    }

#endif // WINDOWS_PLATFORM

#ifdef LINUX_PLATFORM
    //TODO

#endif // LINUX_PLATFORM

