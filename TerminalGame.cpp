#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

using namespace std;
int c = 0;
int m[4][4];      // We use it to save our data.
int selection[4]; // To move a, b, c and d from Initialization to Shift function.
bool moved = false;

int getRandom()
{

    return (rand() % 4);
}

void addRandomNum()
{
    int x = getRandom();
    int y = getRandom();

    if (m[x][y] != 0)
    {
        addRandomNum();
    }
    else
    {
        m[x][y] = 2;
    }
}

int ParseTheMatrix(int par, int num) // Change line and column to a, b, c and d
{
    int i = 0;
    int j = 0;
    int k1 = 0;
    int k2 = 0;

    switch (par)
    {
    case 0:
        selection[0] = m[0][num];
        selection[1] = m[1][num];
        selection[2] = m[2][num];
        selection[3] = m[3][num];
        break;
    case 1:
        selection[0] = m[num][3];
        selection[1] = m[num][2];
        selection[2] = m[num][1];
        selection[3] = m[num][0];
        break;
    case 2:
        selection[0] = m[3][num];
        selection[1] = m[2][num];
        selection[2] = m[1][num];
        selection[3] = m[0][num];
        break;
    case 3:
        selection[0] = m[num][0];
        selection[1] = m[num][1];
        selection[2] = m[num][2];
        selection[3] = m[num][3];
        break;
    }

    return selection[4];
}

void PassToMatrix(int par, int num, int a, int b, int c, int d) // This function save our a, b, c and d at list m.
{
    int i, j, k1, k2;
    k1 = 0;
    k2 = 0;

    switch (par)
    {
    case 0:
        m[0][num] = a;
        m[1][num] = b;
        m[2][num] = c;
        m[3][num] = d;
        break;
    case 1:
        m[num][3] = a;
        m[num][2] = b;
        m[num][1] = c;
        m[num][0] = d;
        break;
    case 2:
        m[3][num] = a;
        m[2][num] = b;
        m[1][num] = c;
        m[0][num] = d;
        break;
    case 3:
        m[num][0] = a;
        m[num][1] = b;
        m[num][2] = c;
        m[num][3] = d;
        break;
    }
}

void Sum(int par, int num, int a, int b, int c, int d) // For sum a, b, c and d.
{
    if (a == b && a != 0)
    {
        a += b;
        b = c;
        c = d;
        d = 0;
        moved = true;
    }

    if (b == c && b != 0)
    {
        b += c;
        c = d;
        d = 0;
        moved = true;
    }

    if (c == d && c != 0)
    {
        c += d;
        d = 0;
        moved = true;
    }

    PassToMatrix(par, num, a, b, c, d);
}

void Shift(int par, int num) // Shift a, b, c and d.
{
    ParseTheMatrix(par, num);
    int a, b, c, d;
    a = selection[0];
    b = selection[1];
    c = selection[2];
    d = selection[3];

    for (int i = 0; i < 3; ++i)
    {

        if (a == 0)
        {
            if (!(b == 0 && c == 0 && d == 0))
            {
                a = b;
                b = c;
                c = d;
                d = 0;
                moved = true;
            }
        }

        if (b == 0)
        {

            if (!(c == 0 && d == 0))
            {
                b = c;
                c = d;
                d = 0;
                moved = true;
            }
        }

        if (c == 0)
        {
            if (d != 0)
            {
                c = d;
                d = 0;
                moved = true;
            }
        }
    }

    Sum(par, num, a, b, c, d);
}

bool isLoser()
{
    bool losed = false;
    int counter = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (m[i][j] != 0)
            {
                counter++;
            }
        }
    }

    if (counter == 16)
    {

        counter = 0;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (m[i][j] != m[i][j + 1])
                {
                    counter++;
                }
            }
        }

        if (counter == 12)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (m[j][i] != m[j + 1][i])
                    {
                        counter++;
                    }
                }
            }
        }

        if (counter == 24)
        {
            losed = true;
        }
    }

    return losed;
}

void initialization()
{

    srand(time(0));

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m[i][j] = 0;
        }
    }

    int x1 = getRandom();
    int y1 = getRandom();
    int x2 = getRandom();
    int y2 = getRandom();

    while (x1 == x2 && y1 == y2)
    {
        x1 = getRandom();
        y1 = getRandom();
        x2 = getRandom();
        y2 = getRandom();
    }

    m[x1][y1] = 2;
    m[x2][y2] = 2;
}

void setTable()
{
    cout << "+-------+-------+-------+-------+" << '\n';
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {

            switch (m[i][j])
            {
            case 0 ... 9:
                cout << "|   " << m[i][j] << "   ";
                break;
            case 10 ... 99:
                cout << "|   " << m[i][j] << "  ";
                break;
            case 100 ... 999:
                cout << "|  " << m[i][j] << "  ";
                break;
            case 1000 ... 9999:
                cout << "|  " << m[i][j] << " ";
                break;
            case 10000 ... 99999:
                cout << "| " << m[i][j] << " ";
                break;
            case 100000 ... 999999:
                cout << "| " << m[i][j] << "";
                break;
            }
            if (j == 3)
            {
                cout << "|" << '\n'
                     << "+-------+-------+-------+-------+" << '\n';
            }
        }
    }
}

void play()
{

    while (true)
    {
        cout << "\n\n";

        // set the gameTable
        setTable();

        // check if user losed
        if (isLoser() == true)
        {
            cout << "GAME OVER!" << '\n';
            system("pause");
            break;
        }

        c = 0;

        // action to user movement
        switch ((c = getch()))
        {
        case 72:
            for (int i = 0; i < 4; ++i)
            {
                Shift(0, i);
            }
            break;
        case 80:
            for (int i = 0; i < 4; ++i)
            {
                Shift(2, i);
            }
            break;
        case 75:
            for (int i = 0; i < 4; ++i)
            {
                Shift(3, i);
            }
            break;
        case 77:
            for (int i = 0; i < 4; ++i)
            {
                Shift(1, i);
            }
            break;
        default:
            cout << endl
                 << "null" << endl; // not arrow
            break;
        }

        // check boolean if have movement or not
        if (moved)
        {
            addRandomNum();
            moved = false;
        }

        system("CLS");
    }
}

int main()
{
    initialization();
    play();

    return 0;
}