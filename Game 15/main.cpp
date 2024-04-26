#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;


int Field[4][4];
int pointX, pointY;

void CreateFieldComp(int sizeField)
{
    if(sizeField==16)
    {
        bool NumIsFree[15];
        int Nums[15];
        for (int i = 0; i < 15; i++)
            NumIsFree[i] = true;
        srand(time(0));
        bool Ok;
        int RandNum;
        for (int i = 0; i < 15; i++)
        {
            Ok = false;
            while (!Ok)
            {
                RandNum = rand() % 15 + 1;
                if (NumIsFree[RandNum - 1])
                    Ok = true;
            }
            Nums[i] = RandNum;
            NumIsFree[RandNum - 1] = false;
        }
        int Chaos = 0;
        int CurrNum;
        for (int i = 0; i < 14; i++)
        {
            CurrNum = Nums[i];
            for (int j = i + 1; j < 15; j++)
                if (CurrNum > Nums[j])
                    Chaos++;
        }
        if (Chaos % 2 == 1)
        {
            int temp = Nums[13];
            Nums[13] = Nums[14];
            Nums[14] = temp;
        }
        for (int i = 0; i < 15; i++)
            Field[i % 4][i / 4] = Nums[i];
        Field[3][3] = 0;
        pointX = 3; pointY = 3;
    }
    
    if (sizeField == 9)
    {
        bool NumIsFree[8];
        int Nums[8];
        for (int i = 0; i < 8; i++)
            NumIsFree[i] = true;
        srand(time(0));
        bool Ok;
        int RandNum;
        for (int i = 0; i < 8; i++)
        {
            Ok = false;
            while (!Ok)
            {
                RandNum = rand() % 8 + 1;
                if (NumIsFree[RandNum - 1])
                    Ok = true;
            }
            Nums[i] = RandNum;
            NumIsFree[RandNum - 1] = false;
        }
        int Chaos = 0;
        int CurrNum;
        for (int i = 0; i < 7; i++)
        {
            CurrNum = Nums[i];
            for (int j = i + 1; j < 8; j++)
                if (CurrNum > Nums[j])
                    Chaos++;
        }
        if (Chaos % 2 == 0)
        {
            int temp = Nums[7];
            Nums[7] = Nums[6];
            Nums[6] = temp;
        }
        for (int i = 0; i < 8; i++)
            Field[i % 3][i / 3] = Nums[i];
        Field[2][2] = 0;
        pointX = 2; pointY = 2;
    }
}

void DrawField()
{
    system("cls");
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (Field[i][j])
                cout << "++++";
            else
                cout << "    ";
        }
        cout << endl;
        for (int i = 0; i < 4; i++)
        {
            if (Field[i][j])
            {
                cout << "+";
                cout.width(2);
                cout << Field[i][j] << "+";
            }
            else
                cout << "    ";
        }
        cout << endl;
        for (int i = 0; i < 4; i++)
        {
            if (Field[i][j])
                cout << "++++";
            else
                cout << "    ";
        }
        cout << endl;
    }
}

enum Direction { LEFT, UP, RIGHT, DOWN };

void Move(Direction dir)
{
    switch (dir)
    {
    case Direction::LEFT:
    {
        if (pointX > 0)
        {
            Field[pointX][pointY] = Field[pointX - 1][pointY];
            Field[pointX - 1][pointY] = 0;
            pointX--;
        }
    } break;
    case Direction::UP:
    {
        if (pointY > 0)
        {
            Field[pointX][pointY] = Field[pointX][pointY - 1];
            Field[pointX][pointY - 1] = 0;
            pointY--;
        }
    } break;
    case Direction::RIGHT:
    {
        if (pointX < 3)
        {
            Field[pointX][pointY] = Field[pointX + 1][pointY];
            Field[pointX + 1][pointY] = 0;
            pointX++;
        }
    } break;
    case Direction::DOWN:
    {
        if (pointY < 3)
        {
            Field[pointX][pointY] = Field[pointX][pointY + 1];
            Field[pointX][pointY + 1] = 0;
            pointY++;
        }
    } break;
    }
}

bool FieldIsCorrect(int sizeField) 
{
    int count = 0;
    if(sizeField == 16)
    {
        int proverka = 1;
        for (int i = 3; i != (-1); i--)
        {
            for (int j = 0; j < 4; j++)
                if (Field[j][i] == proverka++)
                    count++;
        }
        if (count == 15) return true;
        count = 0;
        return false;
    }

    if (sizeField == 9)
    {
        int proverka = 1;
        for (int i = 2; i != (-1); i--)
        {
            for (int j = 0; j < 3; j++)
                if (Field[j][i] == proverka++)
                    count++;
        }
        if (count == 8) return true;
        count = 0;
        return false;
    }
}

void main()
{
    int sizeField;
    cout << "Select field size: 16 (4x4) or 9 (3x3): ";
    cin >> sizeField;
    int counter = 0;
    int startTime = clock() / 1000.0 / 60.0;
    CreateFieldComp(sizeField);
    DrawField();
    while (!FieldIsCorrect(sizeField))
    {
        switch (_getch())
        {
        case 72:
            Move(Direction::UP);
            counter++;
            break;
        case 80:
            Move(Direction::DOWN);
            counter++;
            break;
        case 75:
            Move(Direction::LEFT);
            counter++;
            break;
        case 77:
            Move(Direction::RIGHT);
            counter++;
            break;;
        }
        DrawField();
    }
    int endTime = clock() / 1000.0 / 60.0;
    int time = endTime - startTime;
    cout << endl << endl;
    cout << "Congratulations! It took " << counter << " shifts and " << time << " mins." << endl;
    cout << "Press Enter to exit!" << endl;
    cin.get();
    system("pause");
}