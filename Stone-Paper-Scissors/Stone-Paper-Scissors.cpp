#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

enum eTools {
    Stone = 1, Paper, Scissors
};

enum eWinner {
    Player = 1, Computer, Draw
};

struct sRound {
    short NumberOfRound = 0;
    eTools ChoicePlayer;
    eTools ChoiceComputer;
    eWinner TheWinner;
    string WinnerName;
};

struct sGameResult {
    short GamesRound = 0;
    short PlayerWinTime;
    short ComputerWinTime;
    short DrawTime;
    eWinner FinalWinner;
    string GameWinner;
};

short RandomNumber(short from, short to) {
    return rand() % (to - from + 1) + from;
}

short RoundNumber() {
    short rounds = 0;
    do {
        cout << "How many rounds do you want to play (1 -> 10)? ";
        while (true) {
            cin >> rounds;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid number!\n";
            }
            else
                break;
        }
    } while (rounds <= 0 || rounds > 10);
    return rounds;
}

eTools ReadChoicePlayer() {
    short choice = 0;
    do {
        cout << "\n\nPlease choose [1]:Stone, [2]:Paper, [3]:Scissors: ";
        while (true) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid number!\n";
            }
            else
                break;
        }
    } while (choice < 1 || choice > 3);
    return (eTools)choice;
}

eTools ReadChoiceComputer() {
    return (eTools)RandomNumber(1, 3);
}

eWinner WhoWonTheRound(sRound roundwinner) {
    if (roundwinner.ChoicePlayer == roundwinner.ChoiceComputer)
        return eWinner::Draw;

    switch (roundwinner.ChoicePlayer) {
    case eTools::Stone:
        return (roundwinner.ChoiceComputer == eTools::Paper) ? eWinner::Computer : eWinner::Player;
    case eTools::Paper:
        return (roundwinner.ChoiceComputer == eTools::Scissors) ? eWinner::Computer : eWinner::Player;
    case eTools::Scissors:
        return (roundwinner.ChoiceComputer == eTools::Stone) ? eWinner::Computer : eWinner::Player;
    }
    return eWinner::Draw;
}

eWinner WhoWonTheGames(short player, short computer) {
    if (computer == player) {
        system("color 06");
        return eWinner::Draw;
    }
    else if (computer > player) {
        system("color 04");
        return eWinner::Computer;
    }
    else {
        system("color 02");
        return eWinner::Player;
    }
}

string ChoiceName(eTools choice) {
    string tool[] = { "Stone", "Paper", "Scissors" };
    return tool[choice - 1];
}

string PutWinnerName(eWinner name) {
    string winner[] = { "", "Player", "Computer", "Draw" };
    return winner[name];
}

void PrintResultRound(sRound result) {
    cout << "\n\n---------------- Round [" << result.NumberOfRound + 1 << "] -----------------" << endl;
    cout << setw(18) << "Player choice: " << ChoiceName(result.ChoicePlayer) << endl;
    cout << setw(18) << "Computer choice: " << ChoiceName(result.ChoiceComputer) << endl;
    cout << setw(18) << "Round Winner: " << result.WinnerName << endl;
    cout << "--------------------------------------------------" << endl;
}

sGameResult PlayGames(short HowManyRound) {
    sRound round;
    short Player = 0, Computer = 0, Draw = 0;

    for (short i = 0; i < HowManyRound; i++) {
        round.NumberOfRound = i;
        round.ChoicePlayer = ReadChoicePlayer();
        round.ChoiceComputer = ReadChoiceComputer();
        round.TheWinner = WhoWonTheRound(round);
        round.WinnerName = PutWinnerName(round.TheWinner);

        if (round.TheWinner == eWinner::Player) {
            system("color 02"); // ????
            Player++;
        }
        else if (round.TheWinner == eWinner::Computer) {
            system("color 04"); 
            cout << "\a";      
            Computer++;
        }
        else {
            system("color 06"); 
            Draw++;
        }

        PrintResultRound(round);
    }

    eWinner finalWinner = WhoWonTheGames(Player, Computer);
    string winnerName = PutWinnerName(finalWinner);

    return { HowManyRound, Player, Computer, Draw, finalWinner, winnerName };
}

void PrintResultGames(sGameResult result) {
    cout << "\n\t\t-----------------------------------------------" << endl;
    cout << "\t\t--------------- [Game Summary] ----------------" << endl;
    cout << "\t\t-----------------------------------------------" << endl;
    cout << "\t\tTotal Rounds:          " << result.GamesRound << endl;
    cout << "\t\tPlayer Wins:           " << result.PlayerWinTime << endl;
    cout << "\t\tComputer Wins:         " << result.ComputerWinTime << endl;
    cout << "\t\tDraws:                 " << result.DrawTime << endl;
    cout << "\t\tFinal Winner:          " << result.GameWinner << endl;
    cout << "\t\t-----------------------------------------------\n" << endl;
}

void StartGame() {
    char again = ' ';
    do {
        system("cls");
        system("color 07");
        sGameResult result = PlayGames(RoundNumber());
        PrintResultGames(result);

        cout << "\tDo you want to play again? (y/n): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');
}

int main() {
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
