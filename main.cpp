#include <iostream>
#include <algorithm>
#include <array>
#include <ctime>
#include <random>
using namespace std;

void PrintPrizeValues();
void GenerateNumbers(int);
void CheckNumbers(array<int, 10>, array<int, 10>);

int main()
{

    setlocale(LC_ALL, "fi_FI");

    int option{};
    bool error{}, playing{true};

    cout << "Tervetuloa helppoon lottoon, voiton saaminen on helppoa!\n\n";

    do
    {

        error = false;

        cout << "Mitä haluaisit tehdä? (Syötä numero 1-4)\n";
        cout << "1: Katso palkintosummat\n";
        cout << "2: Pelaa koneen arpomalla rivillä\n";
        cout << "3: Pelaa omilla numeroilla\n";
        cout << "4: Lopeta pelaaminen" << endl;
        cin >> option;

        if (cin.fail() || option < 1 || option > 4)
        {
            error = true;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (option)
        {
        case 1:
            PrintPrizeValues();
            break;
        case 2:
        case 3:
            GenerateNumbers(option);
            break;
        case 4:
            playing = false;
            cout << "\nKiitos pelaamisesta, näkemiin!";
            break;
        default:
            cout << "\nVirheellinen arvo!\n";
        }

    } while (error || playing);

    return 0;
}

void PrintPrizeValues()
{

    cout << "\n\n\nNumeroita + lisänumeroita oikein\tVoittosumma" << endl;
    cout << "7\t\t\t\t\t10 000 000 e" << endl;
    cout << "6+1\t\t\t\t\t1 000 000 e" << endl;
    cout << "6\t\t\t\t\t100 000 e" << endl;
    cout << "5\t\t\t\t\t2000 e" << endl;
    cout << "4\t\t\t\t\t50 e" << endl;
    cout << "3+1\t\t\t\t\t10 e" << endl;
    cout << "2\t\t\t\t\t2 e" << endl;
    cout << "1\t\t\t\t\t1 e" << endl;
    cout << "-----------------------------------------------------------\n\n\n\n";

}

// Function that generates player's and winning numbers
void GenerateNumbers(int option)
{

    array<int, 40> lotteryNumbers;
    array<int, 10> playerNumbers, winningNumbers;
    int playerNum{};
    bool error{};

    // Generating a seed using the computer's internal clock
    unsigned seed = time(nullptr);

    // Creating a randomizer engine using the seed
    auto rng = default_random_engine{seed};

    for (int i = 0; i < lotteryNumbers.size(); i++)
    {
        lotteryNumbers[i] = i + 1;
    }

    // Shuffling the lottery numbers using the engine
    shuffle(lotteryNumbers.begin(), lotteryNumbers.end(), rng);

    // Generating random winning numbers
    for (int i = 0; i < winningNumbers.size(); i++)
    {
        winningNumbers[i] = lotteryNumbers[i];
    }

    shuffle(lotteryNumbers.begin(), lotteryNumbers.end(), rng);

    // If player wants to play with computer-generated numbers
    if (option == 2)
    {
        // Generating random numbers for player
        for (int i = 0; i < playerNumbers.size(); i++)
        {
            playerNumbers[i] = lotteryNumbers[i];
        }
    }

    // If player wants to play with own numbers
    else
    {
        cout << "\n\n";

        // Prompting user for numbers
        for (int i = 0; i < playerNumbers.size(); i++)
        {
            do
            {
                error = false;

                if (i < 7)
                {
                    cout << "Syötä lottorivin numero " << i + 1 << ": ";
                    cin >> playerNum;
                }
                else
                {
                    cout << "Syötä bonusrivin numero " << i - 6 << ": ";
                    cin >> playerNum;
                }

                // Checking if the number user entered is already in the array
                if (cin.fail() || playerNum < 1 || playerNum > 40 || find(playerNumbers.begin(), playerNumbers.end(), playerNum) != playerNumbers.end())
                {
                    error = true;
                    cout << "\nVirheellinen arvo." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            } while (error);

            playerNumbers[i] = playerNum;
        }
    }

    cout << "\n\n\n\nLottorivisi on: ";

    for (int i = 0; i < 7; i++)
    {
        cout << playerNumbers[i] << ", ";
    }

    cout << "ja bonusnumerot ";

    for (int i = 7; i < playerNumbers.size(); i++)
    {
        cout << playerNumbers[i];
        if (i < playerNumbers.size() - 1)
        {
            cout << ", ";
        }
        else
        {
            cout << ".";
        }
    }

    CheckNumbers(playerNumbers, winningNumbers);

}

// Function that compares the players numbers to the winning numbers and outputs the result
void CheckNumbers(array<int, 10> playerNumbers, array<int, 10> winningNumbers)
{

    int playerNumbersCorrect{}, playerBonusCorrect{}, prizeSum{};

    cout << "\n\nJa voittonumerot ovat... ";

    for (int i = 0; i < 7; i++)
    {
        cout << winningNumbers[i] << ", ";

        for (int j = 0; j < 7; j++)
        {
            if (playerNumbers[i] == winningNumbers[j])
            {
                playerNumbersCorrect++;
            }
        }
    }

    cout << "ja bonusnumerot ";

    for (int i = 7; i < winningNumbers.size(); i++)
    {
        cout << winningNumbers[i];
        if (i < winningNumbers.size() - 1)
        {
            cout << ", ";
        }
        else
        {
            cout << ".";
        }

        for (int j = 7; j < winningNumbers.size(); j++)
        {
            if (playerNumbers[i] == winningNumbers[j])
            {
                playerBonusCorrect++;
            }
        }
    }

    cout << "\n\nSait " << playerNumbersCorrect << " + " << playerBonusCorrect << " oikein!\n";

    switch (playerNumbersCorrect)
    {
    case 0:
        break;
    case 1:
        prizeSum = 1;
        break;
    case 2:
        prizeSum = 2;
        break;
    case 3:
        if (playerBonusCorrect > 0)
        {
            prizeSum = 10;
        }
        else
        {
            prizeSum = 2;
        }
        break;
    case 4:
        prizeSum = 50;
        break;
    case 5:
        prizeSum = 2000;
        break;
    case 6:
        if (playerBonusCorrect > 0)
        {
            prizeSum = 1000000;
        }
        else
        {
            prizeSum = 100000;
        }
        break;
    case 7:
        prizeSum = 10000000;
        break;
    default:
        prizeSum = -1;
    }

    if (prizeSum > 1)
    {
        cout << "Olet voittanut " << prizeSum << " euroa!";
    }
    else if (prizeSum == 1)
    {
        cout << "Olet voittanut " << prizeSum << " euron!";
    }
    else
    {
        cout << "Valitettavasti et voittanut mitään tällä kertaa.";
    }

    cout << "\n\n\n\n";

}
