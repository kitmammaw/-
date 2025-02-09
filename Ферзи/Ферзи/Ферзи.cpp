#include <iostream>
using namespace std;

int board[8][8];

void resetQ(int i, int j)
{
    for (int x = 0; x < 8; ++x)
    {
        --board[x][j];
        --board[i][x];
        int k;
        k = j - i + x;
        if (k >= 0 && k < 8)
            --board[x][k];
        k = j + i - x;
        if (k >= 0 && k < 8)
            --board[x][k];
    }
    board[i][j] = 0;
}

void setQ(int i, int j)
{
    for (int x = 0; x < 8; ++x)
    {
        ++board[x][j];
        ++board[i][x];
        int k;
        k = j - i + x;
        if (k >= 0 && k < 8)
            ++board[x][k];
        k = j + i - x;
        if (k >= 0 && k < 8)
            ++board[x][k];
    }
    board[i][j] = -1;
}

bool tryQ(int i)
{
    bool result = false;
    for (int j = 0; j < 8; ++j)
    {
        if (board[i][j] == 0)
        {
            setQ(i, j);
            if (i == 7)
                result = true;
            else
            {
                if (!(result = tryQ(i + 1)))
                    resetQ(i, j);
            }
        }
        if (result)
            break;
    }
    return result;
}
int main()
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            board[i][j] = 0;
    tryQ(0);
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[i][j] == -1)
                cout << "1 ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
}
