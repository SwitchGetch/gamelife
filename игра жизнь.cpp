#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <windows.h>
using namespace std;

HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cord;

void FieldCreation(vector<string>& field, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        string temp = "";

        for (int j = 0; j < y; j++)
        {
            if (!i || i == x - 1 || !j || j == y - 1)
            {
                temp += '#';
            }
            else
            {
                if (!(rand() % 4))
                {
                    temp += '*';
                }
                else
                {
                    temp += ' ';
                }
            }
        }

        field.push_back(temp);
    }

    return;
}

void FieldOutput(vector<string>& field, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if (field[i][j] == '#')
            {
                SetConsoleTextAttribute(hand, 11);
            }
            else
            {
                SetConsoleTextAttribute(hand, 12);
            }

            cout << field[i][j] << " ";
        }

        cout << endl;
    }
}

void NewGeneration(vector<string>& field, vector<int> B, vector<int> S, int x, int y)
{
    vector<vector<int>> neighbours;

    for (int i = 0; i < x; i++)
    {
        vector<int> temp;

        for (int j = 0; j < y; j++)
        {
            temp.push_back(0);
        }

        neighbours.push_back(temp);
    }

    for (int i = 1; i < x - 1; i++)
    {
        for (int j = 1; j < y - 1; j++)
        {
            if (field[i][j] == '*')
            {
                for (int i0 = i - 1; i0 < i + 2; i0++)
                {
                    for (int j0 = j - 1; j0 < j + 2; j0++)
                    {
                        if (i0 == i && j0 == j)
                        {
                            continue;
                        }
                        else
                        {
                            neighbours[i0][j0]++;
                        }
                    }
                }
            }
        }
    }

    for (int i = 1; i < x - 1; i++)
    {
        for (int j = 1; j < y - 1; j++)
        {
            if (field[i][j] == '*')
            {
                bool death = true;

                for (int i0 = 0; i0 < S.size(); i0++)
                {
                    if (neighbours[i][j] == S[i0])
                    {
                        death = false;

                        break;
                    }
                }

                if (death)
                {
                    field[i][j] = ' ';
                }
            }
            else
            {
                for (int i0 = 0; i0 < B.size(); i0++)
                {
                    if (neighbours[i][j] == B[i0])
                    {
                        field[i][j] = '*';

                        break;
                    }
                }
            }
        }
    }
}

int main()
{
    srand(time(NULL));

    vector<string> field;
    vector<int> B, S;
    string temp;
    int GenCount = 0, x, y;

    SetConsoleTextAttribute(hand, 15);

    cout << "B: ";
    cin >> temp;

    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i] < 58 && temp[i] > 47)
        {
            B.push_back(temp[i] - '0');
        }
    }

    cout << "S: ";
    cin >> temp;

    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i] < 58 && temp[i] > 47)
        {
            S.push_back(temp[i] - '0');
        }
    }

    cout << "field (file name / random): ";
    cin >> temp;

    if (temp == "random")
    {
        cout << "length: ";
        cin >> x;

        cout << "width: ";
        cin >> y;

        FieldCreation(field, x, y);
    }
    else
    {
        ifstream ifile;
        string line;

        ifile.open(temp);

        while (getline(ifile, line))
        {
            field.push_back(line);
        }

        ifile.close();

        x = field.size();
        y = field[0].size();
    }

    system("cls");

    while (true)
    {
        cord.X = 0;
        cord.Y = 0;

        SetConsoleCursorPosition(hand, cord);

        SetConsoleTextAttribute(hand, 15);

        cout << "B: ";

        for (int i = 0; i < B.size(); i++)
        {
            cout << B[i] << " ";
        }

        cout << endl;

        cout << "S: ";

        for (int i = 0; i < S.size(); i++)
        {
            cout << S[i] << " ";
        }

        cout << endl;

        cout << "field (file name / random): " << temp << endl;

        cout << "length: " << x << endl;
        cout << "width: " << y << endl;

        cout << "generation: " << GenCount << endl;

        FieldOutput(field, x, y);

        NewGeneration(field, B, S, x, y);

        GenCount++;
    }
}
