#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void display_dash()
{
    for (int i = 0; i != 21; ++i)
        cout << "-";
    cout << endl;
}

void display_arr(int (*arr)[4])
{
    display_dash();

    for (int i = 0; i < 4; ++i)
    {
        cout << "|";
        for (int j = 0; j < 4; ++j)
        {
            if (arr[i][j] != 0)
                cout << setw(4) << arr[i][j] << "|";
            else
                cout << "    |";
        }
        cout << endl;
        display_dash();       
    }
}

bool check_dead(int (*arr)[4])
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (arr[i][j] == 0 || arr[i][j+1] == 0)
            {
                return false;
            }

            if (arr[i][j] == arr[i][j+1])
            {
                return false;
            }
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (arr[j][i] == 0 || arr[j+1][i] == 0)
            {
                return false;
            }

            if (arr[j][i] == arr[j+1][i])
            {
                return false;
            }
        }
    }

    return true;
}

bool move_left(int (*arr)[4])
{
    bool moved = false;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (arr[i][j] == 0)
            {
                for (int k = j+1; k < 4; ++k)
                {
                    if (arr[i][k] != 0)
                    {
                        arr[i][j] = arr[i][k];
                        arr[i][k] = 0;
                        moved = true;
                        break;
                    }
                }
            }
        }

        for (int j = 0; j < 3; ++j)
        {
            if (arr[i][j] == arr[i][j+1])
            {
                arr[i][j] += arr[i][j+1];
                arr[i][j+1] = 0;
                moved = true;
                for (int k = j+1; k < 3; ++k)
                {
                    arr[i][k] = arr[i][k+1];
                    arr[i][k+1] = 0;
                }
            }
        }
    }

    return moved;
}

bool move_down(int (*arr)[4])
{
    bool moved = false;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 3; j > 0; --j)
        {
            if (arr[j][i] == 0)
            {
                for (int k = j-1; k >= 0; --k)
                {
                    if (arr[k][i] != 0)
                    {
                        arr[j][i] = arr[k][i];
                        arr[k][i] = 0;
                        moved = true;
                        break;
                    }
                }
            }
        }

        for (int j = 3; j > 0; --j)
        {
            if (arr[j][i] == arr[j-1][i])
            {
                arr[j][i] += arr[j-1][i];
                arr[j-1][i] = 0;
                moved = true;
                for (int k = j-1; k > 0; --k)
                {
                    arr[k][i] = arr[k-1][i];
                    arr[k-1][i]= 0;
                }
            }
        }
    }

    return moved;
}

bool move_up(int (*arr)[4])
{
    bool moved = false;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (arr[j][i] == 0)
            {
                for (int k = j+1; k < 4; ++k)
                {
                    if (arr[k][i] != 0)
                    {
                        arr[j][i] = arr[k][i];
                        arr[k][i] = 0;
                        moved = true;
                        break;
                    }
                }
            }
        }

        for (int j = 0; j < 3; ++j)
        {
            if (arr[j][i] == arr[j+1][i])
            {
                arr[j][i] += arr[j+1][i];
                arr[j+1][i] = 0;
                moved = true;
                for (int k = j+1; k < 3; ++k)
                {
                    arr[k][i] = arr[k+1][i];
                    arr[k+1][i]= 0;
                }
            }
        }
    }

    return moved;
}

bool move_right(int (*arr)[4])
{
    bool moved = false;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 3; j > 0; --j)
        {
            if (arr[i][j] == 0)
            {
                for (int k = j-1; k >= 0; --k)
                {
                    if (arr[i][k] != 0)
                    {
                        arr[i][j] = arr[i][k];
                        arr[i][k] = 0;
                        moved = true;
                        break;
                    }
                }
            }
        }

        for (int j = 3; j > 0; --j)
        {
            if (arr[i][j] == arr[i][j-1])
            {
                arr[i][j] += arr[i][j-1];
                arr[i][j-1] = 0;
                moved = true;
                for (int k = j-1; k > 0; --k)
                {
                    arr[i][k] = arr[i][k-1];
                    arr[i][k-1] = 0;
                }
            }
        }
    }

    return moved;
}

void game_start(int (*arr)[4])
{
    srand(time(NULL));
    int first = rand() % 16;
    int second = rand() % 16;
    while (first == second)
    {
        second = rand() % 16;
    }

    arr[first / 4][first % 4] = 2;
    arr[second / 4][second % 4] = 2;
}

int random_choice(int *arr, int len)
{
    return arr[rand() % len];
}

void random_tile(int (*arr)[4])
{
    int free = 0;
    int choice[16] = {0};

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (arr[i][j] == 0)
            {
                choice[free++] = i * 4 + j;
            }
        }
    }

    int choose = random_choice(choice, free);
    int random_number = rand() % 100;
    if (random_number < 75)
        arr[choose / 4][choose % 4] = 2;
    else
        arr[choose / 4][choose % 4] = 4;
}

void game_run(int (*arr)[4])
{
    while (!check_dead(arr))
    {
        char c;
        cin >> c;

        bool moved = false;

        switch (c)
        {
            case 'a': moved = move_left(arr); break;
            case 's': moved = move_down(arr); break;
            case 'w': moved = move_up(arr); break;
            case 'd': moved = move_right(arr); break;
        }

        if (moved)
        {
            random_tile(arr);
            display_arr(arr);
        }       
    }
}

int score(int (*arr)[4])
{
    int sum = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            sum += arr[i][j];
        }
    }
    return sum;
}

int main()
{
    int a[4][4] = {0};

    game_start(a);
    display_arr(a);

    game_run(a);

    int sum = score(a);
    cout << "Your score is " << sum << endl;

    return 0;
}