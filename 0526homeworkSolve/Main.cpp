#include "stdafx.h"

#define ARROWNUM 10 // ��ġ���� ��ũ�η� �����س��°� ����/������ ���Ƽ� �������ϸ� �صδ°� ����
#define SUCCESS 5
#define TIMELIMIT 7

void Start();
void ReSet();
bool Update();
void Render();

enum class Arrow
{
    UP = 72,
    LEFT = 75,
    RIGHT = 77,
    DOWN = 80
};

Arrow answer[ARROWNUM];

int curSuccess = 0;
int curArrow = 0;

Stopwatch currentTime;

int main()
{
    Start();
    ReSet();

    while (Update())
    {
        Render();
    }

    return 0;
}


void Start() // �ܼ� ���� ���Ժδ� �ظ��ϸ� �̷��� ¥�°� ����.
{
    system("title TypingGame");
    system("mode con:cols=60 lines=30");

    {
        HANDLE hConsole;
        CONSOLE_CURSOR_INFO ConsoleCursor;

        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        ConsoleCursor.bVisible = 0;
        ConsoleCursor.dwSize = 1;

        SetConsoleCursorInfo(hConsole, &ConsoleCursor);
    }

    std::cout << "ȭ��ǥ Ÿ���� ����!!!" << std::endl;

    system("pause");
    system("cls");
}

void ReSet()
{
    currentTime.Start();
    curArrow = 0;

    for (int i = 0; i < ARROWNUM; i++)
    {
        int arrow = Math::Random(0, 3);

        switch (arrow)
        {
        case 0:
        {
            answer[i] = Arrow::UP;
            break;
        }
        case 1:
        {
            answer[i] = Arrow::DOWN;
            break;
        }
        case 2:
        {
            answer[i] = Arrow::RIGHT;
            break;
        }
        case 3:
        {
            answer[i] = Arrow::LEFT;
            break;
        }
        }
    }
}

bool Update()
{
    if (_kbhit())
    {
        int key;

        key = _getch();

        if (key == 224)
        {
            key = _getch();

            if (answer[curArrow] == static_cast<Arrow>(key))
            {
                ++curArrow;

                if (ARROWNUM <= curArrow)
                {
                    ReSet();
                    ++curSuccess;

                    if (SUCCESS <= curSuccess)
                    {
                        std::cout << "�¸�!! ������ �����մϴ�" << std::endl;
                        return false;
                    }
                }
            }
            else
            {
                curArrow = 0;
            }
        }
    }

    if (TIMELIMIT <= currentTime.GetElapsedTimeSec())
    {
        std::cout << "�й�! ������ �����մϴ�." << std::endl;
        return false;
    }

    return true;
}

void Render()
{
    system("cls");

    std::cout << "TIME : ";

    for (int i = 0; i < TIMELIMIT; i++)
    {
        if (currentTime.GetElapsedTimeSec() < i)
        {
            std::cout << "��";
        }
    }

    std::cout << std::endl;

    for (int i = 0; i < ARROWNUM; i++)
    {
        if (curArrow <= i)
        {
            switch (answer[i])
            {
            case Arrow::UP:
            {
                std::cout << "��";
                break;
            }
            case Arrow::DOWN:
            {
                std::cout << "��";
                break;
            }
            case Arrow::LEFT:
            {
                std::cout << "��";
                break;
            }
            case Arrow::RIGHT:
            {
                std::cout << "��";
                break;
            }
            }
        }
        else
        {
            std::cout << "��";
        }
    }
    std::cout << std::endl;

    std::cout << "���� Ƚ�� : " << SUCCESS - curSuccess << std::endl;
}
