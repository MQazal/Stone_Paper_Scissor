#include<iostream>
#include<cstdlib>
using namespace std;

enum enGameChoices { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct strRoundInfo
{
	short RoundNumber = 0;
	enGameChoices Player1Choice;
	enGameChoices ComputerChoice;
	enWinner RoundWinner;
	string EachRoundWinnerName = "";
};
struct strGameResults
{
	short TotalGameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner FinalGameWinner;
	string FinalGameWinnerName = "";
};

short ReadHowManyRounds()
{
	short GameRounds = 0;
	do
	{
		cout << "Welcome dear player, how many rounds you want to play from 1 to 10 ? \n";
		cin >> GameRounds;
	} while (GameRounds < 1 || GameRounds > 10);
	return GameRounds;
}

enGameChoices ReadPlayer1Choice()
{
	short Choice = 0;
	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return (enGameChoices)Choice;
}

string ChoiceName(enGameChoices Choice)
{
	string arrGameChoices[3] = { "Stone", "Paper", "Scissors" }; // return back to CO#3 with menus
	return arrGameChoices[Choice - 1];
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

enGameChoices GetComputerChoice()
{
	return (enGameChoices)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(strRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}
	switch (RoundInfo.Player1Choice)
	{
	case enGameChoices::Stone:
		if (RoundInfo.ComputerChoice == enGameChoices::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoices::Paper:
		if (RoundInfo.ComputerChoice == enGameChoices::Scissors)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoices::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoices::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player1;
}

string RoundWinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1", "Computer", "No Winner" };
	return arrWinnerName[Winner - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;

	default:
		system("color 6F");
		break;
	}
}

enWinner WhoWonTheFullGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (ComputerWinTimes > Player1WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

void PrintRoundResults(strRoundInfo RoundInfo)
{
	cout << "\n____________Round [" << RoundInfo.RoundNumber << "]____________\n\n";
	cout << "Player1  Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner	: [" << RoundInfo.EachRoundWinnerName << "]\n";
	cout << "__________________________________\n" << endl;

	SetWinnerScreenColor(RoundInfo.RoundWinner);
}

strGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	strGameResults FullGameResults;

	FullGameResults.TotalGameRounds = GameRounds;
	FullGameResults.Player1WinTimes = Player1WinTimes;
	FullGameResults.ComputerWinTimes = ComputerWinTimes;
	FullGameResults.DrawTimes = DrawTimes;
	FullGameResults.FinalGameWinner = WhoWonTheFullGame(Player1WinTimes, ComputerWinTimes);
	FullGameResults.FinalGameWinnerName = RoundWinnerName(FullGameResults.FinalGameWinner);
	return FullGameResults;
}

strGameResults PlayGame(short HowManyRounds)
{
	strRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short RoundsCounter = 1; RoundsCounter <= HowManyRounds; RoundsCounter++)
	{
		cout << "\nRound [" << RoundsCounter << "] begins:\n";
		RoundInfo.RoundNumber = RoundsCounter;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
		RoundInfo.EachRoundWinnerName = RoundWinnerName(RoundInfo.RoundWinner);

		if (RoundInfo.RoundWinner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.RoundWinner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo); // strRoundInfo is full to print its variables details, so each time will be filled and empty
	}

	return  FillGameResults(HowManyRounds, Player1WinTimes,
		ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
	string space = "";

	for (int i = 1; i < NumberOfTabs; i++)
	{
		space = space + "\t";
		cout << space;
	}
	return space;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "__________________________________________________________\n\n";
	cout << Tabs(2) << "                 +++ G a m e  O v e r +++ \n";
	cout << Tabs(2) << "__________________________________________________________\n\n";
}

void ShowFinalGameResults(strGameResults FullGameResults)
{
	cout << Tabs(2) << "_____________________[Game Results]_____________________\n\n";
	cout << Tabs(2) << "Game Rounds Total        : " << FullGameResults.TotalGameRounds << endl;
	cout << Tabs(2) << "Player1 won times        : " << FullGameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer won times       : " << FullGameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw won times           : " << FullGameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner	         : " << FullGameResults.FinalGameWinnerName << endl;
	cout << Tabs(2) << "___________________________________________________________\n";
	SetWinnerScreenColor(FullGameResults.FinalGameWinner);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		strGameResults FullGameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(FullGameResults);
		cout << endl << Tabs(3) << "Do you want to play again? Y/N?";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}