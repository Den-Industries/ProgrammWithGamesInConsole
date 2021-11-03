#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <time.h>
#include <locale.h>

using namespace std;

bool work = true, work1 = true, wait = true;
int choosengame = -1, score[2], mode = 0, turn = 1, polekn[3][3], polemb[4][10][10], polesap[15][15], polesapsee[15][15], polelab[21][40], px, py, inseption = 0, sapqofbombs = 0;
int remainingships[2][4] = { {4, 3, 2, 1}, {4, 3, 2, 1} }, entermode = -1, whereit = -1, formes = 0, who = -1, howmanymes = 0, messtuff[5], tick = 0;
string name, parol, bik = "", datafromfile, messages, names[64], messagestext[5], trash;
string maintext;
COORD nach;
COORD need;
POINT crr;
HANDLE h;
CONSOLE_SCREEN_BUFFER_INFO ci;

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void showcursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = true;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void setcolor(int tc, int bc)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((bc << 4) | tc));
}

void beout(string out, int speed = 1)
{
    for (int i = 0; i < out.length(); i++) {
        std::cout << out[i]; if (!GetAsyncKeyState(1)) Sleep(speed);
    }
}

void cls(int ba = 0)
{
    SetConsoleCursorPosition(h, nach);
    for (int u = 0; u < ci.srWindow.Bottom - ci.srWindow.Top + 1 + ba * (ci.srWindow.Bottom - ci.srWindow.Top + 1) * 2; u++)
    {
        for (int i = 0; i < ci.srWindow.Right - ci.srWindow.Left + 1; i++) std::cout << " "; 
    }
    SetConsoleCursorPosition(h, nach);
}

void enst()
{
    beout("Нажми enter, чтобы продолжить\n");
    while (GetAsyncKeyState(13)) {}
    while (!GetAsyncKeyState(13)) {}

}

bool iscurin(int x, int x1, int y, int y1)
{
    return (crr.x > x && crr.x < x1&& crr.y > y && crr.y < y1);
}

bool click()
{
    bool out = false;
    while (GetAsyncKeyState(1)) { out = true; }
    return out;
}

bool clickp()
{
    bool out = false;
    while (GetAsyncKeyState(2)) { out = true; }
    return out;
}

int checkwinkn(int net = 0)
{
    int da = -1;
    bool iswin = true;
    for (int i = 0; i < 2; i++) if (polekn[0][i] != polekn[0][1 + i]) iswin = false;
    if (polekn[0][0] == 0) iswin = false; if (iswin) da = polekn[0][0];
    if (!iswin)
    {
        iswin = true;
        for (int i = 0; i < 2; i++) if (polekn[1][i] != polekn[1][1 + i]) iswin = false;
        if (polekn[1][0] == 0) iswin = false; if (iswin) da = polekn[1][0];
    }
    if (!iswin)
    {
        iswin = true;
        for (int i = 0; i < 2; i++) if (polekn[2][i] != polekn[2][1 + i]) iswin = false;
        if (polekn[2][0] == 0) iswin = false; if (iswin) da = polekn[2][0];
    }
    if (!iswin)
    {
        iswin = true;
        for (int i = 0; i < 2; i++) if (polekn[i][0] != polekn[1 + i][0]) iswin = false;
        if (polekn[0][0] == 0) iswin = false; if (iswin) da = polekn[0][0];
    }
    if (!iswin)
    {
        iswin = true;
        for (int i = 0; i < 2; i++) if (polekn[i][1] != polekn[1 + i][1]) iswin = false;
        if (polekn[0][1] == 0) iswin = false; if (iswin) da = polekn[0][1];
    }
    if (!iswin)
    {
        iswin = true;
        for (int i = 0; i < 2; i++) if (polekn[i][2] != polekn[1 + i][2]) iswin = false;
        if (polekn[0][2] == 0) iswin = false; if (iswin) da = polekn[0][2];
    }
    if (!iswin)
    {
        iswin = true;
        for (int i = 0; i < 2; i++) if (polekn[i][i] != polekn[1 + i][1 + i]) iswin = false;
        if (polekn[1][1] == 0) iswin = false; if (iswin) da = polekn[1][1];
    }
    if (!iswin)
    {
        iswin = true;
        for (int i = 0; i < 2; i++) if (polekn[2 - i][i] != polekn[1 - i][1 + i]) iswin = false;
        if (polekn[1][1] == 0) iswin = false; if (iswin) da = polekn[1][1];
    }
    if (net == 0)
    {
        if (iswin)
        {
            need.X = 0;
            need.Y = 3;
            SetConsoleCursorPosition(h, need);
            std::cout << "Игрок номер " << 3 - turn << " выйграл!!!"; if (entermode != 1) if (datafromfile[whereit] < 127) datafromfile[whereit]++;
            Sleep(2500); mode = -1; cls();
            //beout(maintext);
        }
        else
        {
            iswin = true;
            for (int yyy = 0; yyy < 3; yyy++)
                for (int xxx = 0; xxx < 3; xxx++)
                    if (polekn[yyy][xxx] == 0) iswin = false;
            if (iswin)
            {
                need.X = 0;
                need.Y = 3;
                SetConsoleCursorPosition(h, need);
                std::cout << "Ничья!!!";
                Sleep(2500); mode = -1; cls();
                //beout(maintext);
            }
        }
    }
    return da;
}

bool mbisnorm(int x, int y)
{
    return x >= 0 && y >= 0 && x < 10 && y < 10;
}

bool mbprov(int g, int x, int y)
{
    bool out = true;
    if (mbisnorm((x - 1), (y - 1))) if (polemb[g][y - 1][x - 1] == 1) out = false;
    if (mbisnorm((x - 1), (y + 1))) if (polemb[g][y + 1][x - 1] == 1) out = false;
    if (mbisnorm((x + 1), (y - 1))) if (polemb[g][y - 1][x + 1] == 1) out = false;
    if (mbisnorm((x + 1), (y + 1))) if (polemb[g][y + 1][x + 1] == 1) out = false;
    return out;
}

int mbstuff(int g, int x, int y)
{
    int out = 1, xx = x, yy = y; 
    if (!mbprov(g, x, y) || !mbisnorm(x, y)) out = -1;
    if (mbisnorm((x - 1), y) && polemb[g][y][x - 1] == 1)
    {
        if (out < 2)
        {
            x--;
            while (mbisnorm(x, y) && out != -1 && polemb[g][y][x] == 1) { if (polemb[g][y][x] == 1) out++; if (!mbprov(g, x, y)) out = -1; if (out > 4) out = -1; x--; }
        }
        else out = -1;
    }
    x = xx; y = yy;
    if (mbisnorm((x + 1), y) && polemb[g][y][x + 1] == 1)
    {
        if (out < 2)
        {
            x++;
            while (mbisnorm(x, y) && out != -1 && polemb[g][y][x] == 1) { if (polemb[g][y][x] == 1) out++; if (!mbprov(g, x, y)) out = -1; if (out > 4) out = -1; x++; }
        }
        else out = -1;
    }
    x = xx; y = yy;
    if (mbisnorm(x, (y - 1)) && polemb[g][y - 1][x] == 1)
    {
        if (out < 2)
        {
            y--;
            while (mbisnorm(x, y) && out != -1 && polemb[g][y][x] == 1) { if (polemb[g][y][x] == 1) out++; if (!mbprov(g, x, y)) out = -1; if (out > 4) out = -1; y--; }
        }
        else out = -1;
    }
    x = xx; y = yy;
    if (mbisnorm(x, (y + 1)) && polemb[g][y + 1][x] == 1)
    {
        if (out < 2)
        {
            y++;
            while (mbisnorm(x, y) && out != -1 && polemb[g][y][x] == 1) { if (polemb[g][y][x] == 1) out++; if (!mbprov(g, x, y)) out = -1; if (out > 4) out = -1; y++; }
        }
        else out = -1;
    }
    return out;
}

int mbstuff1(int g, int x, int y, int modddde = -1)
{

    if (mbisnorm(x, y))
    {
        if ((polemb[g][y][x] == 1 && g != (turn - 1) * 2 + 1) || polemb[g][y][x] == 3)
        {
            int out = 1;
            switch (modddde)
            {
            case -1:
                out += mbstuff1(g, x - 1, y, 0);
                out += mbstuff1(g, x + 1, y, 1);
                out += mbstuff1(g, x, y - 1, 2);
                out += mbstuff1(g, x, y + 1, 3);
                break;
            case 0:
                out += mbstuff1(g, x - 1, y, 0);
                break;
            case 1:
                out += mbstuff1(g, x + 1, y, 1);
                break;
            case 2:
                out += mbstuff1(g, x, y - 1, 2);
                break;
            case 3:
                out += mbstuff1(g, x, y + 1, 3);
                break;
                break;
            }
            return out;
        }
        else return 0;
    }
    else return 0;
}

void mbshtuka(int g, int x, int y)
{
    polemb[g][y][x] = 4;
    if (mbisnorm(x - 1, y)) if (polemb[g][y][x - 1] == 3) mbshtuka(g, x - 1, y); else if (polemb[g][y][x - 1] != 4) polemb[g][y][x - 1] = 1;
    if (mbisnorm(x + 1, y)) if (polemb[g][y][x + 1] == 3) mbshtuka(g, x + 1, y); else if (polemb[g][y][x + 1] != 4) polemb[g][y][x + 1] = 1;
    if (mbisnorm(x, y - 1)) if (polemb[g][y - 1][x] == 3) mbshtuka(g, x, y - 1); else if (polemb[g][y - 1][x] != 4) polemb[g][y - 1][x] = 1;
    if (mbisnorm(x, y + 1)) if (polemb[g][y + 1][x] == 3) mbshtuka(g, x, y + 1); else if (polemb[g][y + 1][x] != 4) polemb[g][y + 1][x] = 1;
    if (mbisnorm(x - 1, y - 1)) polemb[g][y - 1][x - 1] = 1;
    if (mbisnorm(x - 1, y + 1)) polemb[g][y + 1][x - 1] = 1;
    if (mbisnorm(x + 1, y - 1)) polemb[g][y - 1][x + 1] = 1;
    if (mbisnorm(x + 1, y + 1)) polemb[g][y + 1][x + 1] = 1;
}

void genMbmap(int g)
{
    for (int i = 3; i > 0; i--)
        while (remainingships[(turn - 1)][i] > 0)
        {

            int x = rand() % 10, y = rand() % 10, dir = rand() % 4; bool cont = true;
            if (polemb[g][y][x] == 0 && mbprov(g, x, y) && polemb[g][y][x + 1] == 0 && polemb[g][y][x - 1] == 0
                && polemb[g][y + 1][x] == 0 && polemb[g][y - 1][x] == 0)
            {
                polemb[g][y][x] = 1;
                do {
                    if (dir == 0) x--; if (dir == 1) x++; if (dir == 2) y--; if (dir == 3) y++;
                    polemb[g][y][x] = 1;
                    cont = true;
                    if (dir != 0 && polemb[g][y][x + 1] == 1) cont = false;
                    if (dir != 1 && polemb[g][y][x - 1] == 1) cont = false;
                    if (dir != 2 && polemb[g][y + 1][x] == 1) cont = false;
                    if (dir != 3 && polemb[g][y - 1][x] == 1) cont = false;
                } while (mbstuff(g, x, y) != -1 && cont && mbstuff(g, x, y) < i + 1);

                if (!(mbstuff(g, x, y) != -1 && cont && mbstuff(g, x, y) == i + 1))
                {
                    do
                    {
                        polemb[g][y][x] = 0; if (dir == 0) x++; if (dir == 1) x--; if (dir == 2) y++; if (dir == 3) y--;
                    } while (polemb[g][y][x] == 1);
                }
                else remainingships[(turn - 1)][i]--;
            }
        }
    for (int i = 0; i < remainingships[(turn - 1)][0]; i++)
    {
        int x = 0, y = 0;
        do
        {
            x = rand() % 10; y = rand() % 10;
        } while (polemb[g][y][x + 1] == 1 
            || polemb[g][y][x - 1] == 1 
            || polemb[g][y + 1][x] == 1 
            || polemb[g][y - 1][x] == 1 
            || polemb[g][y][x] == 1 
            || !mbprov(g, x, y));
        polemb[g][y][x] = 1;
    }
    remainingships[(turn - 1)][0] = 0;
}

bool sapisnorm(int x, int y)
{
    return x >= 0 && y >= 0 && x < 15 && y < 15;
}

void sapshtuka(int x, int y)
{
    if (sapisnorm(x, y) && polesapsee[y][x] == -2)
    {
        bool mogu = true;
        if (sapisnorm(x - 1, y) && polesap[y][x - 1] == -1) mogu = false;
        if (sapisnorm(x + 1, y) && polesap[y][x + 1] == -1) mogu = false;
        if (sapisnorm(x, y - 1) && polesap[y - 1][x] == -1) mogu = false;
        if (sapisnorm(x, y + 1) && polesap[y + 1][x] == -1) mogu = false;
        polesapsee[y][x] = polesap[y][x];
        if (mogu)
        {
            sapshtuka(x - 1, y); sapshtuka(x + 1, y);
            sapshtuka(x, y - 1); sapshtuka(x, y + 1);
        }
    }
}

void nigga()
{
    string out;
    for (int y = 0; y < 21; y++)
    {
        for (int x = 0; x < 40; x++)
            if (py == y && px == x) out = out + 'O'; else
            {
                if (polelab[y][x] == 0) out = out + ' ';
                if (polelab[y][x] == 1) out = out + 'X';
                if (polelab[y][x] == 2) out = out + char(134);
                if (polelab[y][x] == 3) out = out + char(127);
            }
        if (y != 20) out = out + '\n';
    }
    need.Y = 0; need.X = 0;
    SetConsoleCursorPosition(h, need);
    std::cout << out; //Sleep(125);
}
/*
void labgen()
{
    int x = 0, y = 0, xx = 0, yy = 0;
    int longvall = 3 + 2 * (rand() % 3);
    int mmode = 0;
    xx += longvall + 1; x = 0; y = yy;
    for (; x < xx - 1; x++) { polelab[y][x] = 0; } yy += 2;
    for (int i = 0; i < 40; i++)
    {
        mmode = rand() % 2;
        if (yy < 21) mode = 1;
        //mmode = 0;
        if (mmode == 0 && yy < 21)
        {
            x = 0; y = yy;
            do
            {
                longvall = (2 * (rand() % 4)) + 1;
                for (int gg = 0; gg < longvall; gg++) { if (xx - x < 2 || x == 39) { longvall = gg; } polelab[y][x] = 0; x++; nigga(); }
                int nutipo = 1;
                if (longvall > 1) nutipo = rand() % (max(longvall - 2, 1)) + 1;
                if (nutipo % 2 == 0) nutipo++;
                if (x - nutipo >= 0 && x - nutipo < 40)
                {
                    if (polelab[y - 2][x - nutipo] != 0) nutipo++;
                    polelab[y - 1][x - nutipo] = 0;
                }
                if (x + 1 < min(39, xx))
                {
                    polelab[y][x] = 3; x++;
                }
                nigga();
            } while (x < xx - 2);
            yy += 2;
        }
        if (mmode == 1 && xx < 40)
        {
            y = 0; x = xx;
            do
            {
                longvall = (2 * (rand() % 4)) + 1;
                for (int gg = 0; gg < longvall; gg++) { if (yy - y <= 2 || y == 39) { longvall = gg; } polelab[y][x] = 0; y++; nigga(); }
                int nutipo = 1;
                if (longvall > 1) nutipo = rand() % (max(longvall - 2, 1)) + 1;
                if (nutipo % 2 == 0) nutipo++;
                if (y - nutipo >= 0 && y - nutipo < 21)
                {
                    if (polelab[y - nutipo][x - 2] != 0) nutipo++;
                    polelab[y - nutipo][x - 1] = 0;
                }
                if (y + 1 < min(20, yy))
                {
                    polelab[y][x] = 3; y++;
                }
                nigga();
            } while (y < yy - 2);
            xx += 2;
        }
    }
}*/
void labgen()
{
    int x = 0, y = 0, xx = 0, yy = 0;
    int longvall = 40;
    xx += longvall + 1; x = 0; y = yy;
    for (; x < xx - 1; x++) { polelab[y][x] = 0; nigga(); } yy += 2;
    while (yy < 21)
    {
        x = 0; y = yy;
        do
        {
            longvall = (rand() % 8) + 2;
            for (int gg = 0; gg < longvall; gg++) { if (xx - x < 2 || x == 39) { longvall = gg; } polelab[y][x] = 0; x++; nigga(); }
            int nutipo = 1;
            if (longvall > 1) nutipo = rand() % (max(longvall - 2, 1)) + 1;
            //if (nutipo % 2 == 1) nutipo++;
            if (x - nutipo >= 0 && x - nutipo < 40)
            {
                if (polelab[y - 2][x - nutipo] != 0) nutipo++;
                polelab[y - 1][x - nutipo] = 0;
            }
            if (x + 1 < 39)
            {
                polelab[y][x] = 3; x++;
            }
            nigga();
        } while (x < xx - 2);
        yy += 2;
    }//Рабочий вариант
}

COORD knrazum()
{
    COORD bestcoord; int bestscore = -999;
    bestcoord.X = 0; bestcoord.Y = 0;
    int iii = rand() % 3, uuu = rand() % 3;
    for (int ii = iii; ii < 3 + iii; ii++)
        for (int uu = uuu; uu < 3 + uuu; uu++)
        {
            COORD da;
            int ssscore = 10;
            da.X = ii % 3;
            da.Y = uu % 3;
            if (polekn[da.Y][da.X] == 0)
            {
                polekn[da.Y][da.X] = turn;
                if (checkwinkn(1) == turn) {
                    ssscore += 12;
                }
                else
                    if (inseption < 3)
                    {
                        bool ha = true;
                        for (int yyy = 0; yyy < 3; yyy++)
                            for (int xxx = 0; xxx < 3; xxx++)
                                if (polekn[yyy][xxx] == 0) ha = false;
                        if (!ha)
                        {
                            inseption++;
                            turn = 3 - turn;
                            COORD net = knrazum();
                            polekn[net.Y][net.X] = turn;
                            if (checkwinkn(1) == turn) ssscore -= 3;
                            polekn[net.Y][net.X] = 0;
                            turn = 3 - turn;
                            inseption--;
                        }
                    }
                polekn[da.Y][da.X] = 0;
                if (ssscore > bestscore)
                {
                    bestcoord = da; bestscore = ssscore;
                }
            }
        }
    return bestcoord;
}

void intro()
{
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned int)time(NULL));
    if (true)
    {
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = 32;                   // Width of each character in the font
        cfi.dwFontSize.Y = 32;                  // Height
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
        COORD coord;
        SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);
        CONSOLE_CURSOR_INFO info;
        GetConsoleCursorInfo(h, &info);
        info.bVisible = FALSE;
        SetConsoleCursorInfo(h, &info);
        GetConsoleScreenBufferInfo(h, &ci);
        SetWindowPos(GetConsoleWindow(), GetConsoleWindow(), -4, 0, ci.dwSize.X, ci.dwSize.Y, SWP_NOMOVE);
    }
}

int main()
{
    //for (int i = 0; i < 256; i++) cout << char(i) << "  " << i << endl; Sleep(999999);
    //while (true) for (int i = 0; i < 256; i++) if (GetAsyncKeyState(i)) cout << i << endl;
    //std::ofstream out;
    //out.open("data.den");
    //27 esc    1 - лкм   2 - пкм        w 87 38   a 65 37   s 83 40   d 68 39
    intro();
    hidecursor();
    std::ifstream in("data.den");
    datafromfile = "";
    string line;
    while (getline(in, line)) datafromfile = datafromfile + line + "\n";
    for (int i = 0; i < datafromfile.length(); i++) datafromfile[i] = (datafromfile[i] + 1) % 256;
    in.close();
    in.open("mess.den");
    messages = "";
    while (getline(in, line)) messages = messages + line + "\n";
    for (int i = 0; i < messages.length(); i++) messages[i] = (messages[i] + 1) % 256;
    in.close(); setcolor(10, 0);
    beout("Добро пожаловать в DSOGAM!\nDenis's system of games and messages\n"); enst(); cls();
    while (true)
    {
        cls();
        setcolor(10, 0); cin.clear(); 
        beout("Регистрация\nГость\nВход");
        while (work)
        {
            GetCursorPos(&crr); hidecursor(); cin.clear();
            if (iscurin(0, 352, 23, 55))
            {
                need.Y = 0;
                SetConsoleCursorPosition(h, need);
                setcolor(11, 0);
                std::cout << "Регистрация";
                setcolor(10, 0);
                if (click())
                {
                    entermode = 0; work = false;
                }
            }
            else
            {
                need.Y = 0;
                SetConsoleCursorPosition(h, need);
                std::cout << "Регистрация";
            }
            if (iscurin(0, 160, 55, 87))
            {
                need.Y = 1;
                SetConsoleCursorPosition(h, need);
                setcolor(11, 0);
                std::cout << "Гость";
                setcolor(10, 0);
                if (click())
                {
                    entermode = 1; work = false;
                }
            }
            else
            {
                need.Y = 1;
                SetConsoleCursorPosition(h, need);
                std::cout << "Гость";
            }
            if (iscurin(0, 128, 87, 119))
            {
                need.Y = 2;
                SetConsoleCursorPosition(h, need);
                setcolor(11, 0);
                std::cout << "Вход";
                setcolor(10, 0);
                if (click())
                {
                    entermode = 2; work = false;
                }
            }
            else
            {
                need.Y = 2;
                SetConsoleCursorPosition(h, need);
                std::cout << "Вход";
            }
            if (iscurin(0, 160, 119, 151))
            {
                need.Y = 3;
                SetConsoleCursorPosition(h, need);
                setcolor(11, 0);
                std::cout << "Выход";
                setcolor(10, 0);
                if (click())
                {
                    exit(0);
                }
            }
            else
            {
                need.Y = 3;
                SetConsoleCursorPosition(h, need);
                std::cout << "Выход";
            }
        }
        work = true; cls();
        need.X = 0; need.Y = 0;
        SetConsoleCursorPosition(h, need);
        if (entermode == 0)
        {
            beout("Введи имя\n(Без пробелов, все что \nпосле пробела обрежется)\n");
            showcursor(); std::cin >> name; hidecursor();
            beout("Замечательно. \nТеперь введи свой пароль\n(Тоже без пробелов)\n");
            showcursor(); std::cin >> parol; hidecursor();
            beout("Добро пожаловать!\n");
            bool iscan = true;
            for (int i = 0; i < datafromfile.length(); i++)
                if (datafromfile[i] == '-' && (i + 1 < datafromfile.length() && datafromfile[i + 1] == '/') 
                    && (i + 2 < datafromfile.length() && datafromfile[i + 2] == '-'))
                {
                    bool isit = true;
                    for (int u = 1; i - u - 1 != '\n' && i - u - 1 >= 0; u++)
                        if (datafromfile[i - u] != name[name.length() - u]) isit = false;
                    if (isit) iscan = false;
                }
            if (iscan)
            {
                datafromfile = datafromfile + name + "-/-" + parol + char(33) + char(33) + char(33) + char(33) + char(33) + "\n";
                whereit = datafromfile.length() - 6;
                for (int i = 0; i < datafromfile.length(); i++) datafromfile[i] = (datafromfile[i] - 1) % 256;
                std::ofstream out;
                out.open("data.den");
                out << datafromfile;
                for (int i = 0; i < datafromfile.length(); i++) datafromfile[i] = (datafromfile[i] + 1) % 256;
                out.close();
            }
            else
            {
                beout("Это имя занято\n"); enst(); exit(0);
            }
            enst();
        }
        if (entermode == 1)
        {
            beout("Как тебя зовут?\n");
            showcursor(); std::cin >> name; hidecursor();
            beout("Салют, " + name + "\n", 55);
            enst();
        }
        if (entermode == 2)
        {
            beout("Введите имя\n");
            showcursor(); std::cin >> name; hidecursor();
            beout("Теперь пароль\n");
            showcursor(); std::cin >> parol; hidecursor(); 
            bool allok = false, exist = false;
            for (int i = 0; i < datafromfile.length(); i++)
                if (datafromfile[i] == '-' && (i + 1 < datafromfile.length() && datafromfile[i + 1] == '/') && (i + 2 < datafromfile.length() && datafromfile[i + 2] == '-'))
                {
                    bool isit = true;
                    for (int u = 1; i - u >= 0 && name.length() - u < 999; u++)
                    {
                        //cout << datafromfile[i - u] << " " << name[name.length() - u] << "  " << u << " " << name.length() - u << endl;
                        if (datafromfile[i - u] != name[name.length() - u]) isit = false;
                    }
                    if  (isit) 
                    {
                        exist = true;
                        for (int u = 0; i + 3 + u != char(11) && i + 3 + u < datafromfile.length() && u < parol.length(); u++)
                            if (datafromfile[i + 3 + u] != parol[u]) isit = false;
                        if (isit)
                        {
                            allok = true; whereit = i + 3 + parol.length();
                        }
                    }
                }
            if (exist)
            {
                if (allok)
                {
                    beout("С возвращением!\n"); enst();
                }
                else
                {
                    beout("Неправильный пароль\n"); enst(); exit(0);
                }
            }
            else
            {
                beout("Имени не существует\n"); enst(); exit(0);
            }
        }
        maintext = "Во что сыграем, " + name + "?\nКрестики нолики\nБыки и коровы\nМорской бой\nСапер\nЛабиринт\nОставить сообщение\nПисьма\nВыход";
        if (entermode == 1)
            maintext = "Во что сыграем, " + name + "?\nКрестики нолики\nБыки и коровы\nМорской бой\nСапер\nЛабиринт\n\n\nВыход";
        cls();
        beout(maintext);
        while (GetAsyncKeyState(1)) {}
        need.X = 0;
        while (work)
        {
            GetCursorPos(&crr); hidecursor(); cin.clear(); 
            switch (choosengame)
            {
            case -1:
                if (true)
                {
                    if (iscurin(0, 576, 55, 87))
                    {
                        need.Y = 1;
                        SetConsoleCursorPosition(h, need);
                        setcolor(11, 0);
                        std::cout << "Крестики нолики";
                        setcolor(10, 0);
                        if (click())
                        {
                            choosengame = 0;
                        }
                    }
                    else
                    {
                        need.Y = 1;
                        SetConsoleCursorPosition(h, need);
                        std::cout << "Крестики нолики";
                    }
                    if (iscurin(0, 416, 87, 119))
                    {
                        need.Y = 2;
                        SetConsoleCursorPosition(h, need);
                        setcolor(11, 0);
                        std::cout << "Быки и коровы";
                        setcolor(10, 0);
                        if (click())
                        {
                            choosengame = 1;
                        }
                    }
                    else
                    {
                        need.Y = 2;
                        SetConsoleCursorPosition(h, need);
                        std::cout << "Быки и коровы";
                    }
                    if (iscurin(0, 352, 119, 151))
                    {
                        need.Y = 3;
                        SetConsoleCursorPosition(h, need);
                        setcolor(11, 0);
                        std::cout << "Морской бой";
                        setcolor(10, 0);
                        if (click())
                        {
                            choosengame = 2;
                        }
                    }
                    else
                    {
                        need.Y = 3;
                        SetConsoleCursorPosition(h, need);
                        std::cout << "Морской бой";
                    }
                    if (iscurin(0, 160, 151, 183))
                    {
                        need.Y = 4;
                        SetConsoleCursorPosition(h, need);
                        setcolor(11, 0);
                        std::cout << "Сапер";
                        setcolor(10, 0);
                        if (click())
                        {
                            choosengame = 3;
                        }
                    }
                    else
                    {
                        need.Y = 4;
                        SetConsoleCursorPosition(h, need);
                        std::cout << "Сапер";
                    }
                    if (iscurin(0, 256, 183, 215))
                    {
                        need.Y = 5;
                        SetConsoleCursorPosition(h, need);
                        setcolor(11, 0);
                        std::cout << "Лабиринт";
                        setcolor(10, 0);
                        if (click())
                        {
                            choosengame = 4;
                        }
                    }
                    else
                    {
                        need.Y = 5;
                        SetConsoleCursorPosition(h, need);
                        std::cout << "Лабиринт";
                    }
                    if (entermode != 1)
                    {
                        if (iscurin(0, 576, 215, 247))
                        {
                            need.Y = 6;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Оставить сообщение";
                            setcolor(10, 0);
                            if (click() && datafromfile.length() > 0)
                            {
                                choosengame = 5;
                            }
                        }
                        else
                        {
                            need.Y = 6;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Оставить сообщение";
                        }
                        if (iscurin(0, 192, 247, 279))
                        {
                            need.Y = 7;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Письма";
                            setcolor(10, 0);
                            if (click())
                            {
                                choosengame = 6;
                            }
                        }
                        else
                        {
                            need.Y = 7;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Письма";
                        }
                    }
                    if (iscurin(0, 192, 279, 311))
                    {
                        need.Y = 8;
                        SetConsoleCursorPosition(h, need);
                        setcolor(11, 0);
                        std::cout << "Выход";
                        setcolor(10, 0);
                        if (click())
                        {
                            work = false;
                        }
                    }
                    else
                    {
                        need.Y = 8;
                        SetConsoleCursorPosition(h, need);
                        std::cout << "Выход";
                    }
                    if (choosengame != -1)
                    {
                        cls(); mode = -1;
                    }
                }
                break;
            case 0: //Крестики нолики mode 1 - с человеком 2 - с роботом
                if (true)
                {
                    if (mode == -1)
                    {
                        need.Y = 0;
                        SetConsoleCursorPosition(h, need);
                        for (int i = 0; i < 3; i++) for (int u = 0; u < 3; u++) polekn[i][u] = 0;
                        stringstream ss;
                        if (entermode != 1) {  ss << "Счет в игре: " << int(datafromfile[whereit]) - 33 << "\n"; }
                        beout("Играть с\nЧеловеком\nКомпьютером\nКомп против компа\nПередумал\n" + ss.str()); mode = 0; wait = false; turn = 1;
                    }
                    if (mode == 0)
                    {
                        if (iscurin(0, 350, 55, 87))
                        {
                            need.Y = 1;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Человеком";
                            setcolor(10, 0);
                            if (click())
                            {
                                mode = 1;
                            }
                        }
                        else
                        {
                            need.Y = 1;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Человеком";
                        }
                        if (iscurin(0, 420, 87, 119))
                        {
                            need.Y = 2;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Компьютером";
                            setcolor(10, 0);
                            if (click())
                            {
                                mode = 2;
                            }
                        }
                        else
                        {
                            need.Y = 2;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Компьютером";
                        }
                        if (iscurin(0, 544, 119, 151))
                        {
                            need.Y = 3;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Комп против компа";
                            setcolor(10, 0);
                            if (click())
                            {
                                mode = 3;
                            }
                        }
                        else
                        {
                            need.Y = 3;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Комп против компа";
                        }
                        if (iscurin(0, 420, 151, 193))
                        {
                            need.Y = 4;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Передумал";
                            setcolor(10, 0);
                            if (click())
                            {
                                choosengame = -1; cls();
                                beout(maintext);
                            }
                        }
                        else
                        {
                            need.Y = 4;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Передумал";
                        }
                        if (mode != 0)
                        {
                            cls();
                            for (int i = 0; i < 3; i++)
                            {
                                for (int u = 0; u < 3; u++)
                                {
                                    if (polekn[i][u] == 0) std::cout << "+";
                                    if (polekn[i][u] == 1) std::cout << "X";
                                    if (polekn[i][u] == 2) std::cout << "O";
                                }
                                std::cout << "\n";
                            }
                        }
                    }
                    if (mode == 1 || mode == 2 || mode == 3)
                    {
                        if (mode == 1 || (mode == 2 && turn == 1))
                        {
                            for (int yyy = 0; yyy < 3; yyy++)
                                for (int xxx = 0; xxx < 3; xxx++)
                                {
                                    //if (iscurin(2 + xxx * 50, , , ))
                                    if ((crr.x > 2 + xxx * 32 && crr.x < 34 + xxx * 32 && crr.y > 24 + yyy * 32 && crr.y < 56 + yyy * 32))
                                        if (click())
                                        {
                                            if (polekn[yyy][xxx] == 0)
                                            {
                                                need.X = xxx;
                                                need.Y = yyy;
                                                SetConsoleCursorPosition(h, need);
                                                polekn[need.Y][need.X] = turn;
                                                if (polekn[need.Y][need.X] == 0) std::cout << "+";
                                                if (polekn[need.Y][need.X] == 1) std::cout << "X";
                                                if (polekn[need.Y][need.X] == 2) std::cout << "O";
                                                turn = 3 - turn;
                                                Sleep(200);
                                            }
                                        }
                                }
                            checkwinkn();
                        }
                        if (mode == 3 && turn == 1)
                        {
                            COORD cc = knrazum();
                            polekn[cc.Y][cc.X] = turn;
                            SetConsoleCursorPosition(h, cc);
                            if (polekn[cc.Y][cc.X] == 0) std::cout << "+";
                            if (polekn[cc.Y][cc.X] == 1) std::cout << "X";
                            if (polekn[cc.Y][cc.X] == 2) std::cout << "O";
                            turn = 3 - turn;
                            Sleep(200);
                            checkwinkn();
                        }
                        if (mode != -1)
                            if (mode > 1 && turn == 2)
                            {
                                COORD cc = knrazum();
                                polekn[cc.Y][cc.X] = turn;
                                SetConsoleCursorPosition(h, cc);
                                if (polekn[cc.Y][cc.X] == 0) std::cout << "+";
                                if (polekn[cc.Y][cc.X] == 1) std::cout << "X";
                                if (polekn[cc.Y][cc.X] == 2) std::cout << "O";
                                turn = 3 - turn;
                                Sleep(200);
                                checkwinkn();
                            }
                        if (mode == 3) Sleep(400);
                    }
                }
                break;
            case 1:
                if (true)
                {
                    if (mode == -1)
                    {
                        int uuu = int(datafromfile[whereit]);
                        stringstream ss;
                        if (entermode != 1) { ss << "Счет в игре: " << int(datafromfile[whereit + 1]) - 33 << "\n"; }
                        beout("Инструкция\nИграть\nПередумал\n" + ss.str()); mode = 0;
                    }
                    if (mode == 0)
                    {
                        need.X = 0;
                        need.Y = 3;
                        SetConsoleCursorPosition(h, need);
                        //std::cout << crr.x << "  " << crr.y << "    ";
                        if (iscurin(0, 320, 23, 55))
                        {
                            need.Y = 0;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Инструкция";
                            setcolor(10, 0);
                            if (click())
                            {
                                mode = 1;
                            }
                        }
                        else
                        {
                            need.Y = 0;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Инструкция";
                        }
                        if (iscurin(0, 192, 55, 87))
                        {
                            need.Y = 1;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Играть";
                            setcolor(10, 0);
                            if (click())
                            {
                                mode = 2;
                            }
                        }
                        else
                        {
                            need.Y = 1;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Играть";
                        }
                        if (iscurin(0, 288, 87, 119))
                        {
                            need.Y = 2;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Передумал";
                            setcolor(10, 0);
                            if (click())
                            {
                                choosengame = -1; cls();
                                beout(maintext);
                            }
                        }
                        else
                        {
                            need.Y = 2;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Передумал";
                        }
                        if (mode == 1)
                        {
                            cls();
                            beout("Инструкция игры:\nКомпьютер загадывает 4 значное число \nбез повторений чисел.\n");
                            beout("Ваша задача - отгадать это число. \nВы можете вводить числа. \n");
                            beout("В ответ на введеное число компьютер \nвыдает два числа, \n");
                            beout("Первое число - сколько чисел совпадает, \nно не стоит на месте, \nВторое - сколько чисел совпадает \nи стоит на правильном месте.");
                        }
                        if (mode == 2)
                        {
                            cls();
                            beout("Я загадал число\nУгадай его\n"); Sleep(1750); cls();
                            bik = "";
                            for (int i = 0; i < 4; i++)
                            {
                                char need;
                                do
                                {
                                    need = char(48 + rand() % 10);
                                    for (int u = i - 1; u >= 0; u--) if (need == bik[u]) need = ' ';
                                } while (need == ' ');
                                bik = bik + need;
                            }
                            bik = bik + '\0';
                            beout("Введи число\n");
                            need.Y = 1;
                            SetConsoleCursorPosition(h, need);
                        }
                    }
                    if (mode == 1)
                    {
                        if (iscurin(0, 288, 407, 439))
                        {
                            need.Y = 12;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Вернуться";
                            setcolor(10, 0);
                            if (click())
                            {
                                mode = -1; cls();
                            }
                        }
                        else
                        {
                            need.Y = 12;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Вернуться";
                        }
                    }
                    if (mode == 2)
                    {
                        string input;
                        do
                        {
                            std::cin >> input;
                            if (input.length() < 4 || (input.length() >= 4 && (input[0] - 48 > 9 || input[1] - 48 > 9 || input[2] - 48 > 9 || input[3] - 48 > 9)))
                            {
                                beout("Ошибка ввода\n");
                            }
                        } while (input.length() < 4 || (input.length() >= 4 && (input[0] - 48 > 9 || input[1] - 48 > 9 || input[2] - 48 > 9 || input[3] - 48 > 9)));
                        int first = 0, second = 0;
                        for (int i = 0; i < 4; i++)
                            for (int u = 0; u < 4; u++)
                                if (input[i] == bik[u])
                                {
                                    first++;
                                    if (i == u) second++;
                                }
                        beout(to_string(first) + " " + to_string(second) + "\n");
                        if (first == 4 && second == 4)
                        {
                            beout("\nВы выйграли!\n"); enst();
                            mode = -1; cls(1); if (entermode != 1) if (datafromfile[whereit + 1] < 127) datafromfile[whereit + 1]++;
                            //beout(maintext);
                        }
                    }
                }
                break;
            case 2:
                if (true)
                {
                    if (mode == -1)
                    {
                        need.Y = 0;
                        SetConsoleCursorPosition(h, need);
                        stringstream ss;
                        if (entermode != 1) { ss << "Счет в игре: " << int(datafromfile[whereit + 2]) - 33 << "\n"; }
                        beout("Играть с\nЧеловеком\nКомпьютером\nПередумал\n" + ss.str()); mode = 0; wait = false; turn = 1;
                        remainingships[0][0] = 4; remainingships[0][1] = 3; remainingships[0][2] = 2; remainingships[0][3] = 1;
                        remainingships[1][0] = 4; remainingships[1][1] = 3; remainingships[1][2] = 2; remainingships[1][3] = 1;
                    }
                    if (mode == 0)
                    {
                        if (iscurin(0, 350, 55, 87))
                        {
                            need.Y = 1;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Человеком";
                            setcolor(10, 0);
                            if (click())
                            {
                                mode = 3;
                            }
                        }
                        else
                        {
                            need.Y = 1;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Человеком";
                        }
                        if (iscurin(0, 420, 87, 119))
                        {
                            need.Y = 2;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Компьютером";
                            setcolor(10, 0);
                            if (click())
                            {
                                mode = 4;
                            }
                        }
                        else
                        {
                            need.Y = 2;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Компьютером";
                        }
                        if (iscurin(0, 420, 119, 151))
                        {
                            need.Y = 3;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Передумал";
                            setcolor(10, 0);
                            if (click())
                            {
                                choosengame = -1; cls();
                                beout(maintext);
                            }
                        }
                        else
                        {
                            need.Y = 3;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Передумал";
                        }
                        if (mode != 0)
                        {
                            cls();
                            for (int g = 0; g < 4; g++)
                                for (int i = 0; i < 10; i++)
                                    for (int u = 0; u < 10; u++) polemb[g][i][u] = 0;
                            for (int i = 0; i < 10; i++)
                            {
                                for (int u = 0; u < 10; u++) { std::cout << "~"; if (!GetAsyncKeyState(1)) Sleep(1); }
                                std::cout << "\n";
                            }
                            beout("\n# # # #\n  # # #\n    # #\n      #\n4 3 2 1\n\nГотово"); while (GetAsyncKeyState(1)) {}
                        }
                    }
                    if (mode == 1 || mode == 2)
                    {
                        if (mode == 1 || (mode == 2 && turn == 1))
                            for (int yyy = 0; yyy < 10; yyy++)
                                for (int xxx = 0; xxx < 10; xxx++)
                                {
                                    if ((crr.x > 354 + xxx * 32 && crr.x < 386 + xxx * 32 && crr.y > 24 + yyy * 32 && crr.y < 56 + yyy * 32))
                                        if (click() && polemb[(turn - 1) * 2 + 1][yyy][xxx] == 0)
                                        {
                                            need.X = xxx + 11;
                                            need.Y = yyy;
                                            SetConsoleCursorPosition(h, need);
                                            if (polemb[(2 - turn) * 2][yyy][xxx] == 1)
                                            {

                                                polemb[(turn - 1) * 2 + 1][yyy][xxx] = 3; std::cout << "X";
                                                int th1, th2;
                                                th1 = mbstuff1((2 - turn) * 2, xxx, yyy);
                                                th2 = mbstuff1((turn - 1) * 2 + 1, xxx, yyy);
                                                if (th1 == th2) mbshtuka((turn - 1) * 2 + 1, xxx, yyy);
                                                need.Y = 0; need.X = 0;
                                                SetConsoleCursorPosition(h, need);
                                                for (int i = 0; i < 10; i++)
                                                {
                                                    for (int u = 0; u < 21; u++)
                                                    {
                                                        if (u < 10) if (polemb[(turn - 1) * 2][i][u] == 0) std::cout << "~"; else
                                                            if (polemb[(turn - 1) * 2][i][u] == 1) std::cout << "#"; else
                                                                if (polemb[(turn - 1) * 2][i][u] == 2) std::cout << "*"; else std::cout << "X";
                                                        if (u == 10) std::cout << "|";
                                                        if (u > 10) if (polemb[(turn - 1) * 2 + 1][i][u - 11] == 0) std::cout << "^"; else
                                                            if (polemb[(turn - 1) * 2 + 1][i][u - 11] == 1) std::cout << "-"; else
                                                                if (polemb[(turn - 1) * 2 + 1][i][u - 11] == 2) std::cout << "*"; else std::cout << "X";
                                                    }
                                                    std::cout << "\n";
                                                }
                                                Sleep(200);
                                                polemb[(2 - turn) * 2][yyy][xxx] += 2;
                                                bool iswin = true;
                                                for (int i = 0; i < 10; i++)
                                                    for (int u = 0; u < 10; u++)
                                                        if (polemb[(2 - turn) * 2][i][u] == 1) iswin = false;
                                                if (iswin)
                                                {
                                                    cls();
                                                    need.Y = 0; need.X = 0;
                                                    SetConsoleCursorPosition(h, need);
                                                    beout("Вы выйграли!!!\n", 75); Sleep(500); enst(); cls();
                                                    mode = -1; //beout(maintext); 
                                                    if (entermode != 1) if (datafromfile[whereit + 2] < 127) datafromfile[whereit + 2]++;
                                                }
                                            }
                                            else
                                            {
                                                polemb[(turn - 1) * 2 + 1][yyy][xxx] = 2; std::cout << "*"; polemb[(2 - turn) * 2][yyy][xxx] += 2;
                                                turn = 3 - turn; Sleep(1500);
                                                if (mode == 1)
                                                {
                                                    cls();
                                                    std::cout << "Позови другого игрока!\n"; enst();
                                                    need.Y = 0; need.X = 0;
                                                    SetConsoleCursorPosition(h, need);
                                                    cls();
                                                    for (int i = 0; i < 10; i++)
                                                    {
                                                        for (int u = 0; u < 21; u++)
                                                        {
                                                            if (u < 10) if (polemb[(turn - 1) * 2][i][u] == 0) std::cout << "~"; else
                                                                if (polemb[(turn - 1) * 2][i][u] == 1) std::cout << "#"; else
                                                                    if (polemb[(turn - 1) * 2][i][u] == 2) std::cout << "*"; else std::cout << "X";
                                                            if (u == 10) std::cout << "|";
                                                            if (u > 10) if (polemb[(turn - 1) * 2 + 1][i][u - 11] == 0) std::cout << "^"; else
                                                                if (polemb[(turn - 1) * 2 + 1][i][u - 11] == 1) std::cout << "-"; else
                                                                    if (polemb[(turn - 1) * 2 + 1][i][u - 11] == 2) std::cout << "*"; else std::cout << "X";
                                                            if (!GetAsyncKeyState(1)) Sleep(1);
                                                        }
                                                        std::cout << "\n";
                                                    }
                                                    while (GetAsyncKeyState(1)) {}
                                                }
                                            }
                                        }
                                }
                        if (mode != -1)
                            if (mode == 2 && turn == 2)
                            {
                                int xxx, yyy;
                                do
                                {
                                    xxx = rand() % 10; yyy = rand() % 10;
                                } while (polemb[(turn - 1) * 2 + 1][yyy][xxx] != 0);
                                need.X = xxx;
                                need.Y = yyy;
                                SetConsoleCursorPosition(h, need);
                                if (polemb[(2 - turn) * 2][yyy][xxx] == 1)
                                {
                                    polemb[(turn - 1) * 2 + 1][yyy][xxx] = 3; std::cout << "X";
                                    int th1, th2;
                                    th1 = mbstuff1((2 - turn) * 2, xxx, yyy);
                                    th2 = mbstuff1((turn - 1) * 2 + 1, xxx, yyy);
                                    if (th1 == th2) mbshtuka((turn - 1) * 2 + 1, xxx, yyy);
                                    need.Y = 0; need.X = 0;
                                    SetConsoleCursorPosition(h, need); turn = 3 - turn;
                                    for (int i = 0; i < 10; i++)
                                    {
                                        for (int u = 0; u < 21; u++)
                                        {
                                            if (u < 10) if (polemb[(turn - 1) * 2][i][u] == 0) std::cout << "~"; else
                                                if (polemb[(turn - 1) * 2][i][u] == 1) std::cout << "#"; else
                                                    if (polemb[(turn - 1) * 2][i][u] == 2) std::cout << "*"; else std::cout << "X";
                                            if (u == 10) std::cout << "|";
                                            if (u > 10) if (polemb[(turn - 1) * 2 + 1][i][u - 11] == 0) std::cout << "^"; else
                                                if (polemb[(turn - 1) * 2 + 1][i][u - 11] == 1) std::cout << "-"; else
                                                    if (polemb[(turn - 1) * 2 + 1][i][u - 11] == 2) std::cout << "*"; else std::cout << "X";
                                        }
                                        std::cout << "\n";
                                    }
                                    Sleep(500); turn = 3 - turn;
                                    polemb[(2 - turn) * 2][yyy][xxx] += 2;
                                    bool iswin = true;
                                    for (int i = 0; i < 10; i++)
                                        for (int u = 0; u < 10; u++)
                                            if (polemb[(2 - turn) * 2][i][u] == 1) iswin = false;
                                    if (iswin)
                                    {
                                        cls();
                                        need.Y = 0; need.X = 0;
                                        SetConsoleCursorPosition(h, need);
                                        beout("Вы проиграли!!!\n", 75); Sleep(500); enst(); cls();
                                        mode = -1; //beout(maintext);
                                    }
                                }
                                else
                                {
                                    polemb[(turn - 1) * 2 + 1][yyy][xxx] = 2; std::cout << "*"; polemb[(2 - turn) * 2][yyy][xxx] += 2;
                                    turn = 3 - turn; Sleep(500);
                                    need.Y = 0; need.X = 0;
                                    SetConsoleCursorPosition(h, need);
                                    for (int i = 0; i < 10; i++)
                                    {
                                        for (int u = 0; u < 21; u++)
                                        {
                                            if (u < 10) if (polemb[(turn - 1) * 2][i][u] == 0) std::cout << "~"; else
                                                if (polemb[(turn - 1) * 2][i][u] == 1) std::cout << "#"; else
                                                    if (polemb[(turn - 1) * 2][i][u] == 2) std::cout << "*"; else std::cout << "X";
                                            if (u == 10) std::cout << "|";
                                            if (u > 10) if (polemb[(turn - 1) * 2 + 1][i][u - 11] == 0) std::cout << "^"; else
                                                if (polemb[(turn - 1) * 2 + 1][i][u - 11] == 1) std::cout << "-"; else
                                                    if (polemb[(turn - 1) * 2 + 1][i][u - 11] == 2) std::cout << "*"; else std::cout << "X";
                                        }
                                        std::cout << "\n";
                                    }
                                }
                            }
                    }
                    if (mode == 3 || mode == 4)
                    {
                        if (iscurin(0, 192, 568, 600))
                        {
                            need.Y = 17; SetConsoleCursorPosition(h, need);
                            setcolor(11, 0); std::cout << "Готово"; setcolor(10, 0);
                            if (click())
                            {
                                if (remainingships[(turn - 1)][0] == 0 && remainingships[(turn - 1)][1] == 0 &&
                                    remainingships[(turn - 1)][2] == 0 && remainingships[(turn - 1)][3] == 0)
                                {
                                    if (turn == 2)
                                    {
                                        cls(); turn = 3 - turn;
                                        need.Y = 0; need.X = 0;
                                        SetConsoleCursorPosition(h, need);
                                        std::cout << "Позови другого игрока!\n"; enst(); cls();
                                        need.Y = 0; need.X = 0;
                                        SetConsoleCursorPosition(h, need);
                                        mode -= 2; cls();
                                        for (int i = 0; i < 10; i++)
                                        {
                                            for (int u = 0; u < 21; u++)
                                            {
                                                if (u < 10) if (polemb[(turn - 1) * 2][i][u] == 0) std::cout << "~"; else std::cout << "#";
                                                if (u == 10) std::cout << "|";
                                                if (u > 10) std::cout << "^";
                                                if (!GetAsyncKeyState(1)) Sleep(1);
                                            }
                                            std::cout << "\n";
                                        }
                                    }
                                    else
                                    {
                                        turn = 3 - turn;
                                        need.Y = 0; need.X = 0;
                                        SetConsoleCursorPosition(h, need);
                                        if (mode == 3)
                                        {
                                            cls();
                                            need.Y = 0; need.X = 0;
                                            SetConsoleCursorPosition(h, need);
                                            std::cout << "Позови другого игрока!\n"; enst();
                                            need.Y = 0; need.X = 0;
                                            SetConsoleCursorPosition(h, need); cls();
                                            for (int i = 0; i < 10; i++)
                                            {
                                                for (int u = 0; u < 10; u++) { std::cout << "~"; if (!GetAsyncKeyState(1)) Sleep(1); }
                                                std::cout << "\n";
                                            }
                                            beout("\n# # # #\n  # # #\n    # #\n      #\n4 3 2 1\n\nГотово");
                                        }
                                    }
                                }
                                else
                                {
                                    need.Y = 17; need.X = 7;
                                    SetConsoleCursorPosition(h, need);
                                    std::cout << "Ошибка постановки кораблей!"; Sleep(175);
                                    setcolor(11, 0);
                                    SetConsoleCursorPosition(h, need);
                                    std::cout << "Ошибка постановки кораблей!"; Sleep(175);
                                    setcolor(10, 0);
                                    SetConsoleCursorPosition(h, need);
                                    std::cout << "Ошибка постановки кораблей!"; Sleep(175);
                                    setcolor(11, 0);
                                    SetConsoleCursorPosition(h, need);
                                    std::cout << "Ошибка постановки кораблей!"; Sleep(175);
                                    setcolor(10, 0);
                                    SetConsoleCursorPosition(h, need);
                                    std::cout << "                             "; need.X = 0;
                                }
                            }
                        }
                        else
                        {
                            need.Y = 17;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Готово";
                        }
                        if (iscurin(0, 192, 600, 632))
                        {
                            need.Y = 18; SetConsoleCursorPosition(h, need);
                            setcolor(11, 0); std::cout << "Рандом"; setcolor(10, 0);
                            if (click())
                            {
                                if (remainingships[(turn - 1)][0] >= 0 && remainingships[(turn - 1)][1] >= 0 &&
                                    remainingships[(turn - 1)][2] >= 0 && remainingships[(turn - 1)][3] >= 0)
                                {
                                    genMbmap((turn - 1) * 2); 
                                    if (turn == 2 && mode == 3)
                                    {
                                        cls(); turn = 3 - turn;
                                        need.Y = 0; need.X = 0;
                                        SetConsoleCursorPosition(h, need);
                                        std::cout << "Позови другого игрока!\n"; enst(); cls(); while(GetAsyncKeyState(1)) {}
                                        need.Y = 0; need.X = 0;
                                        SetConsoleCursorPosition(h, need);
                                        mode -= 2;
                                        for (int i = 0; i < 10; i++)
                                        {
                                            for (int u = 0; u < 21; u++)
                                            {
                                                if (u < 10) if (polemb[(turn - 1) * 2][i][u] == 0) std::cout << "~"; else std::cout << "#";
                                                if (u == 10) std::cout << "|";
                                                if (u > 10) std::cout << "^";
                                                if (!GetAsyncKeyState(1)) Sleep(1);
                                            }
                                            std::cout << "\n";
                                        }
                                    }
                                    else
                                    {
                                        need.Y = 0; need.X = 0;
                                        SetConsoleCursorPosition(h, need);
                                        if (mode == 3)
                                        {
                                            cls();
                                            need.Y = 0; need.X = 0;
                                            SetConsoleCursorPosition(h, need);
                                            std::cout << "Позови другого игрока!\n"; enst(); cls();
                                            need.Y = 0; need.X = 0;
                                            SetConsoleCursorPosition(h, need);
                                            for (int i = 0; i < 10; i++)
                                            {
                                                for (int u = 0; u < 10; u++) { std::cout << "~"; if (!GetAsyncKeyState(1)) Sleep(1); }
                                                std::cout << "\n";
                                            }
                                            beout("\n# # # #\n  # # #\n    # #\n      #\n4 3 2 1\n\nГотово");
                                        } turn = 3 - turn;
                                    }
                                }
                                else
                                {
                                    need.Y = 17; need.X = 7;
                                    SetConsoleCursorPosition(h, need);
                                    std::cout << "Ошибка постановки кораблей!"; Sleep(175);
                                    setcolor(11, 0);
                                    SetConsoleCursorPosition(h, need);
                                    std::cout << "Ошибка постановки кораблей!"; Sleep(175);
                                    setcolor(10, 0);
                                    SetConsoleCursorPosition(h, need);
                                    std::cout << "Ошибка постановки кораблей!"; Sleep(175);
                                    setcolor(11, 0);
                                    SetConsoleCursorPosition(h, need);
                                    std::cout << "Ошибка постановки кораблей!"; Sleep(175);
                                    setcolor(10, 0);
                                    SetConsoleCursorPosition(h, need);
                                    std::cout << "                             "; need.X = 0;
                                }
                            }
                        }
                        else
                        {
                            need.Y = 18;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Рандом";
                        }
                        if (mode == 3 || (mode == 4 && turn == 1))
                            for (int yyy = 0; yyy < 10; yyy++)
                                for (int xxx = 0; xxx < 10; xxx++)
                                    if ((crr.x > 2 + xxx * 32 && crr.x < 34 + xxx * 32 && crr.y > 24 + yyy * 32 && crr.y < 56 + yyy * 32))
                                        if (click())
                                        {
                                            if (polemb[(turn - 1) * 2][yyy][xxx] == 0)
                                            {
                                                polemb[(turn - 1) * 2][yyy][xxx] = 1;
                                                need.X = xxx; need.Y = yyy;
                                                SetConsoleCursorPosition(h, need); std::cout << "#";
                                                int dadada = mbstuff((turn - 1) * 2, xxx, yyy);
                                                if (dadada > 1) remainingships[(turn - 1)][dadada - 2]++;
                                                if (dadada != -1) remainingships[(turn - 1)][dadada - 1]--;
                                                if (dadada == -1)
                                                {
                                                    if (remainingships[(turn - 1)][dadada - 1] < 0) remainingships[(turn - 1)][dadada - 1]++;
                                                    need.Y = 16;  need.X = 0; SetConsoleCursorPosition(h, need);
                                                    beout("ОШИБКА!"); Sleep(200);
                                                    need.Y = 16;  need.X = 0; SetConsoleCursorPosition(h, need);
                                                    beout("       "); Sleep(200);
                                                    polemb[(turn - 1) * 2][yyy][xxx] = 0;
                                                    need.X = xxx; need.Y = yyy;
                                                    SetConsoleCursorPosition(h, need); std::cout << "~";
                                                }
                                                need.Y = 15;  need.X = 0; SetConsoleCursorPosition(h, need);
                                                std::cout << remainingships[(turn - 1)][0] << " " << remainingships[(turn - 1)][1] << " "
                                                    << remainingships[(turn - 1)][2] << " " << remainingships[(turn - 1)][3] << "      ";
                                            }
                                            else
                                            {
                                                int dadada = mbstuff((turn - 1) * 2, xxx, yyy);
                                                if (dadada > 1) remainingships[(turn - 1)][dadada - 2]--;
                                                if (dadada != -1) remainingships[(turn - 1)][dadada - 1]++;
                                                polemb[(turn - 1) * 2][yyy][xxx] = 0;
                                                need.X = xxx; need.Y = yyy;
                                                SetConsoleCursorPosition(h, need); std::cout << "~";
                                                need.Y = 15;  need.X = 0; SetConsoleCursorPosition(h, need);
                                                std::cout << remainingships[(turn - 1)][0] << " " << remainingships[(turn - 1)][1] << " "
                                                    << remainingships[(turn - 1)][2] << " " << remainingships[(turn - 1)][3] << "      ";
                                            }
                                            Sleep(250);
                                        }
                        if (mode == 4 && turn == 2)
                        {
                            genMbmap((turn - 1) * 2);
                            mode -= 2; cls(); turn = 3 - turn;
                            for (int i = 0; i < 10; i++)
                            {
                                for (int u = 0; u < 21; u++)
                                {
                                    if (u < 10) if (polemb[(turn - 1) * 2][i][u] == 0) std::cout << "~"; else std::cout << "#";
                                    if (u == 10) std::cout << "|";
                                    if (u > 10) std::cout << "^";
                                    if (!GetAsyncKeyState(1)) Sleep(1);
                                }
                                std::cout << "\n";
                            }
                            while (GetAsyncKeyState(1)) {}
                        }
                    }
                }
                break;
            case 3:
                if (true)
                {
                    if (mode == -1)
                    {
                        need.Y = 0;
                        SetConsoleCursorPosition(h, need);
                        for (int i = 0; i < 15; i++) for (int u = 0; u < 15; u++) polesap[i][u] = 0;
                        for (int i = 0; i < 15; i++) for (int u = 0; u < 15; u++) polesapsee[i][u] = -2;
                        stringstream ss;
                        if (entermode != 1) { ss << "Счет в игре: " << int(datafromfile[whereit + 3]) - 33 << "\n"; }
                        beout("Играть\nПередумал\n" + ss.str()); mode = 0; sapqofbombs = 0;
                    }
                    if (mode == 0)
                    {
                        if (iscurin(0, 350, 23, 55))
                        {
                            need.Y = 0;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Играть";
                            setcolor(10, 0);
                            if (click())
                            {
                                mode = 1;
                            }
                        }
                        else
                        {
                            need.Y = 0;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Играть";
                        }
                        if (iscurin(0, 420, 55, 87))
                        {
                            need.Y = 1;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Передумал";
                            setcolor(10, 0);
                            if (click())
                            {
                                choosengame = -1; cls();
                                beout(maintext);
                            }
                        }
                        else
                        {
                            need.Y = 1;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Передумал";
                        }
                        if (mode != 0)
                        {
                            cls();
                            beout("25\n50\n75\n100\n125\n150\n175");
                        }
                    }
                    if (mode == 1)
                    {
                        for (int i = 1; i < 8; i++)
                        {
                            need.Y = i - 1; need.X = 0;
                            SetConsoleCursorPosition(h, need);
                            if (iscurin(0, 96, 24 + (i - 1) * 32, 24 + i * 32))
                            {
                                setcolor(11, 0);
                                if (click()) sapqofbombs = 25 * i;
                            }
                            else setcolor(10, 0);
                            std::cout << 25 * i;
                        }
                        if (sapqofbombs != 0)
                        {
                            for (int i = 0; i < sapqofbombs; i++)
                            {
                                int x, y;
                                do
                                {
                                    x = rand() % 15;
                                    y = rand() % 15;
                                } while (polesap[y][x] != 0);
                                polesap[y][x] = -1;
                            }
                            for (int yyy = 0; yyy < 15; yyy++)
                                for (int xxx = 0; xxx < 15; xxx++)
                                    if (polesap[yyy][xxx] != -1)
                                    {
                                        int what = 0;
                                        for (int xx = xxx - 1; xx <= xxx + 1; xx++)
                                            for (int yy = yyy - 1; yy <= yyy + 1; yy++)
                                                if (xx >= 0 && xx < 15 && yy >= 0 && yy < 15) if (polesap[yy][xx] == -1) what++;
                                        polesap[yyy][xxx] = what;
                                    }
                            cls();
                            need.Y = 0; need.X = 0;
                            SetConsoleCursorPosition(h, need);
                            for (int yyy = 0; yyy < 15; yyy++)
                            {
                                for (int xxx = 0; xxx < 15; xxx++)
                                {
                                    std::cout << char(127);
                                }
                                std::cout << endl;
                            }
                            mode = 2;
                        }
                    }
                    if (mode == 2)
                    {
                        for (int yyy = 0; yyy < 15; yyy++)
                            for (int xxx = 0; xxx < 15; xxx++)
                            {
                                if ((crr.x > 2 + xxx * 32 && crr.x < 34 + xxx * 32 && crr.y > 24 + yyy * 32 && crr.y < 56 + yyy * 32))
                                {
                                    if (click())
                                    {
                                        if (polesapsee[yyy][xxx] == -2)
                                        {
                                            if (polesap[yyy][xxx] >= 0)
                                            {
                                                sapshtuka(xxx, yyy);
                                                need.Y = 0; need.X = 0;
                                                SetConsoleCursorPosition(h, need);
                                                for (int yyy = 0; yyy < 15; yyy++)
                                                {
                                                    for (int xxx = 0; xxx < 15; xxx++)
                                                    {
                                                        if (polesapsee[yyy][xxx] == -2) std::cout << char(127);
                                                        if (polesapsee[yyy][xxx] == -1) std::cout << 'B';
                                                        if (polesapsee[yyy][xxx] == 0) std::cout << ' ';
                                                        if (polesapsee[yyy][xxx] > 0) std::cout << polesapsee[yyy][xxx];
                                                    }
                                                    std::cout << endl;
                                                }
                                            }
                                            if (polesap[yyy][xxx] == -1)
                                            {
                                                cls(); beout("Вы проиграли!\n", 75); enst();
                                                cls(); mode = -1; //beout(maintext);
                                            }
                                        }
                                        Sleep(200);
                                    }
                                    if (GetAsyncKeyState(32))
                                    {
                                        if (polesapsee[yyy][xxx] == -2)
                                        {
                                            polesapsee[yyy][xxx] = -1;
                                            Sleep(200);
                                            bool iswin = true;
                                            for (int yyy = 0; yyy < 15; yyy++)
                                                for (int xxx = 0; xxx < 15; xxx++)
                                                    if (polesap[yyy][xxx] == -1 && polesapsee[yyy][xxx] != -1) iswin = false;
                                            if (iswin)
                                            {
                                                cls(); beout("Вы выйграли!\n", 75); enst();
                                                cls(); mode = -1; //beout(maintext); 
                                                if (entermode != 1) if (datafromfile[whereit + 3] < 127) datafromfile[whereit + 3]++;
                                            }
                                        } else
                                        if (polesapsee[yyy][xxx] == -1)
                                        {
                                            polesapsee[yyy][xxx] = -2;
                                            Sleep(200);
                                        }
                                        if (mode != -1)
                                        {
                                            need.Y = 0; need.X = 0;
                                            SetConsoleCursorPosition(h, need);
                                            for (int yyy = 0; yyy < 15; yyy++)
                                            {
                                                for (int xxx = 0; xxx < 15; xxx++)
                                                {
                                                    if (polesapsee[yyy][xxx] == -2) std::cout << char(127);
                                                    if (polesapsee[yyy][xxx] == -1) std::cout << 'B';
                                                    if (polesapsee[yyy][xxx] == 0) std::cout << ' ';
                                                    if (polesapsee[yyy][xxx] > 0) std::cout << polesapsee[yyy][xxx];
                                                }
                                                std::cout << endl;
                                            }
                                        }
                                    }
                                }
                            }
                    }
                }
                break;
            case 4:
                if (true)
                {
                    if (mode == -1)
                    {
                        need.Y = 0;
                        SetConsoleCursorPosition(h, need);
                        for (int i = 0; i < 21; i++) for (int u = 0; u < 40; u++) polelab[i][u] = 3;
                        stringstream ss;
                        if (entermode != 1) { ss << "Счет в игре: " << int(datafromfile[whereit + 4]) - 33 << "\n"; }
                        beout("Играть\nПередумал\n" + ss.str()); mode = 0;
                    }
                    if (mode == 0)
                    {
                        if (iscurin(0, 350, 23, 55))
                        {
                            need.Y = 0;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Играть";
                            setcolor(10, 0);
                            if (click())
                            {
                                mode = 1;
                            }
                        }
                        else
                        {
                            need.Y = 0;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Играть";
                        }
                        if (iscurin(0, 420, 55, 87))
                        {
                            need.Y = 1;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Передумал";
                            setcolor(10, 0);
                            if (click())
                            {
                                choosengame = -1; cls();
                                beout(maintext);
                            }
                        }
                        else
                        {
                            need.Y = 1;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Передумал";
                        }
                        if (mode != 0)
                        {
                            cls();
                            labgen();
                            polelab[0][0] = 2;
                            int xx;
                            do
                            {
                                xx = rand() % 40;
                            } while (polelab[20][xx] != 0);
                            polelab[20][xx] = 1;
                            px = 0; py = 0;
                        }
                    }
                    if (mode == 1)
                    {
                        int slvall = 250;
                        if ((GetAsyncKeyState(87) || GetAsyncKeyState(38)) && py - 1 >= 0 && polelab[py - 1][px] != 3)
                        {
                            Sleep(slvall); py--;
                        }
                        if ((GetAsyncKeyState(65) || GetAsyncKeyState(37)) && px - 1 >= 0 && polelab[py][px - 1] != 3)
                        {
                            Sleep(slvall); px--;
                        }
                        if ((GetAsyncKeyState(83) || GetAsyncKeyState(40)) && py + 1 < 21 && polelab[py + 1][px] != 3)
                        {
                            Sleep(slvall); py++;
                        }
                        if ((GetAsyncKeyState(68) || GetAsyncKeyState(39)) && px + 1 < 40 && polelab[py][px + 1] != 3)
                        {
                            Sleep(slvall); px++;
                        }
                        string out;
                        for (int y = 0; y < 21; y++)
                        {
                            for (int x = 0; x < 40; x++)
                                if (py == y && px == x) out = out + 'O'; else
                                {
                                    if (polelab[y][x] == 0) out = out + ' ';
                                    if (polelab[y][x] == 1) out = out + 'X';
                                    if (polelab[y][x] == 2) out = out + char(134);
                                    if (polelab[y][x] == 3) out = out + char(127);
                                }
                            if (y != 20) out = out + '\n';
                        }
                        need.Y = 0; need.X = 0;
                        SetConsoleCursorPosition(h, need);
                        std::cout << out;
                        if (polelab[py][px] == 1)
                        {
                            cls(); beout("Вы выйграли!\n"); enst(); cls(); mode = -1; 
                            if (entermode != 1) if (datafromfile[whereit + 4] < 127) datafromfile[whereit + 4]++;
                        }
                    }
                }
                break;
            case 5:
                if (true)
                {
                    if (mode == -1)
                    {
                        need.Y = 0;
                        SetConsoleCursorPosition(h, need);
                        beout("Передумал\n"); mode = 0; formes = 0;
                        for (int i = 0; i < datafromfile.length() - 3; i++)
                            if (i == 0 || datafromfile[i - 1] == char(11))
                            {
                                names[formes] = "";
                                for (int g = 0; !(datafromfile[i + g] == '-' && datafromfile[i + g + 1] == '/' && datafromfile[i + g + 2] == '-'); g++)
                                {
                                    names[formes] = names[formes] + datafromfile[i + g];
                                    std::cout << datafromfile[i + g];
                                }
                                std::cout << endl;
                                formes++;
                            }
                    }
                    if (mode == 0)
                    {
                        if (iscurin(0, 420, 23, 55))
                        {
                            need.Y = 0;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Передумал";
                            setcolor(10, 0);
                            if (click())
                            {
                                choosengame = -1; cls();
                                beout(maintext);
                            }
                        }
                        else
                        {
                            need.Y = 0;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Передумал";
                        }
                        for (int i = 0; i < formes; i++)
                        {
                            if (iscurin(0, 32 * names[i].length(), 55 + i * 32, 87 + i * 32))
                            {
                                need.Y = 1 + i;
                                SetConsoleCursorPosition(h, need);
                                setcolor(11, 0);
                                std::cout << names[i];
                                setcolor(10, 0);
                                if (click())
                                {
                                    who = i; mode = 1; cls();
                                    beout("Вы пишите письмо " + names[who]);
                                    beout("\nНе используйте пробелы!"); showcursor(); 
                                    need.X = 0; need.Y = 1;
                                    SetConsoleCursorPosition(h, need); i = formes + 1;
                                }
                            }
                            else
                            {
                                need.Y = 1 + i;
                                SetConsoleCursorPosition(h, need);
                                std::cout << names[i];
                            }
                        }
                    }
                    if (mode == 1)
                    {
                        string themes;
                        std::cin >> themes; hidecursor();
                        messages = messages + names[who] + char{ 11 } + name + char{ 11 } + themes + char{ 11 };
                        for (int i = 0; i < messages.length(); i++) messages[i] = (messages[i] - 1) % 256;
                        std::ofstream out;
                        out.open("mess.den");
                        out << messages;
                        for (int i = 0; i < messages.length(); i++) messages[i] = (messages[i] + 1) % 256;
                        out.close();
                        beout("Письмо отправлено!\n"); Sleep(750); cls();
                        beout(maintext);
                        choosengame = -1;
                        SetConsoleCursorPosition(h, nach);
                    }
                }
                break;
            case 6:
                if (true)
                {
                    if (mode == -1)
                    {
                        need.Y = 0;
                        SetConsoleCursorPosition(h, need);
                        for (int i = 0; i < 5; i++) messagestext[i] = "Вам отправил сообщение ";
                        for (int i = 0; i < 5; i++) messtuff[i] = -1;
                        int nutipo = -1, dadada = 0;
                        for (int i = 0; i < messages.length(); i++)
                        {
                            if (((messages[i - 1] == char{ 11 } && i > 0) || i == 0)) nutipo++;
                            if (nutipo == 0)
                            {
                                bool ismy = true;
                                for (int u = 0; messages[i + u] != char{ 11 } && u < name.length(); u++)
                                {
                                    if (messages[i + u] != name[u]) ismy = false;
                                }
                                if (!ismy) nutipo -= 3; else
                                {
                                    messtuff[dadada] = i;
                                    nutipo++;
                                }
                            }
                            if (nutipo == 2)
                            {
                                for (int u = 0; messages[i + u] != char{ 11 }; u++) messagestext[dadada] = messagestext[dadada] + messages[i + u];
                                messagestext[dadada] = messagestext[dadada] + "\nТекст сообщения:\n"; nutipo++;
                            }
                            if (nutipo == 4)
                            {
                                for (int u = 0; messages[i + u] != char{ 11 }; u++) messagestext[dadada] = messagestext[dadada] + messages[i + u];
                                messagestext[dadada] = messagestext[dadada] + "\n"; dadada++;
                                nutipo = -1;
                            }
                        }
                        beout("Обратно\nВнимание, сообщения автоматически\nудаляются после прочтения!\n");
                        for (int i = 0; i < 5; i++) if (messagestext[i] != "Вам отправил сообщение ") beout(messagestext[i]);
                        mode = 0;
                    }
                    if (mode == 0)
                    {
                        if (iscurin(0, 224, 23, 55))
                        {
                            need.Y = 0;
                            SetConsoleCursorPosition(h, need);
                            setcolor(11, 0);
                            std::cout << "Обратно";
                            setcolor(10, 0);
                            if (click())
                            {
                                string buff = ""; int nutipo = 0;
                                for (int i = 0; i < messages.length(); i++)
                                {
                                    for (int u = 0; u < 5; u++) if (i == messtuff[u]) nutipo = -4;
                                    if (messages[i - 1] == char{ 11 } && i > 0) nutipo++;
                                    if (nutipo >= 0) buff = buff + messages[i];
                                }
                                messages.clear(); messages = buff; buff.clear();
                                for (int i = 0; i < messages.length(); i++) messages[i] = (messages[i] - 1) % 256;
                                std::ofstream out;
                                out.open("mess.den");
                                out << messages;
                                for (int i = 0; i < messages.length(); i++) messages[i] = (messages[i] + 1) % 256;
                                out.close();
                                choosengame = -1; cls();
                                beout(maintext);
                            }
                        }
                        else
                        {
                            need.Y = 0;
                            SetConsoleCursorPosition(h, need);
                            std::cout << "Обратно";
                        }
                    }
                }
                break;
            default:
                choosengame = -1;
                break;
            }
            if (tick == 0)
            {
                tick = 100;
                for (int i = 0; i < datafromfile.length(); i++) datafromfile[i] = (datafromfile[i] - 1) % 256;
                std::ofstream out;
                out.open("data.den");
                out << datafromfile;
                for (int i = 0; i < datafromfile.length(); i++) datafromfile[i] = (datafromfile[i] + 1) % 256;
            }
            tick--;
        }
        while (GetAsyncKeyState(1)) {}
        entermode = -1; work = true;
    }
}