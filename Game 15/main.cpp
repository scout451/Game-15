#include <iostream>
#include <ctime>

using namespace std;

int Field[4][4];
int pointX, pointY;


void CreateFieldComp()
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
    case LEFT:
    {
        if (pointX > 0)
        {
            Field[pointX][pointY] = Field[pointX - 1][pointY];
            Field[pointX - 1][pointY] = 0;
            pointX--;
        }
    } break;
    case UP:
    {
        if (pointY > 0)
        {
            Field[pointX][pointY] = Field[pointX][pointY - 1];
            Field[pointX][pointY - 1] = 0;
            pointY--;
        }
    } break;
    case RIGHT:
    {
        if (pointX < 3)
        {
            Field[pointX][pointY] = Field[pointX + 1][pointY];
            Field[pointX + 1][pointY] = 0;
            pointX++;
        }
    } break;
    case DOWN:
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

bool FieldIsCorrect()
{
    for (int i = 0; i < 15; i++)
        if (Field[i % 4][i / 4] != i + 1)
            return false;
    return true;
}


void main()
{
    int counter = 0;
    int startTime = clock() / 1000.0 / 60.0;
    CreateFieldComp();
    DrawField();
    char choice;
    while (!FieldIsCorrect())
    {
        cin >> choice;
        switch (choice)
        {
        case 76: 
            Move(LEFT);
            counter++;
            break;
        case 85: 
            Move(UP);
            counter++;
            break;
        case 82: 
            Move(RIGHT);
            counter++;
            break;
        case 68: 
            Move(DOWN);
            counter++;
            break;
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