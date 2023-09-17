#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define CHANCES 6

int selectCategory(void)
{
	int category;
	int invalidCategory = 0;

	printf("\nBelow are the categories for the word you will be guessing!\n\n");

	printf("Categories:\n");
	printf("\t1 - Colors\n");
	printf("\t2 - States\n");
	printf("\t3 - Animals (with shells!)\n");
	printf("\t4 - Random Words\n");

	do
	{
		printf("\nPlease enter the number of your chosen category: \n");
		scanf("%d", &category);

		if (category < 1 || category > 4)
		{
			invalidCategory = 1;
			printf("\n\tSorry that isn't an option. Please try again!\n\n");
		}
		else
		{
			invalidCategory = 0;
		}
	} while (invalidCategory);

	return category;
}

void printHangMan(int numIncorrect)
{
	printf("\t   _____\n");

	printf("\t  |\t|\n");
	printf("\t  |\t");

	if (numIncorrect > 0)
		printf("O");
	printf("\n");

	printf("\t  |    ");
	if (numIncorrect < 3)
		printf(" ");
	if (numIncorrect > 2)
	printf("/");
	if (numIncorrect > 1)
		printf("|");
	if (numIncorrect > 3)
		printf("\\");
	printf("\n");

	printf("\t  |   ");
	if (numIncorrect > 4)
		printf("_/ ");
	if (numIncorrect > 5)
		printf("\\_");
	printf("\n");

	printf("\t  |\n");

	printf("\t=====\n");

	return;
}

void generateDashes(int len, char *dashedWord, char *spaces)
{
	int i;

	for (i = 0; i < len; i++)
	{
		dashedWord[i] = '_';
		if (i < len - 1)
			spaces[i] = ' ';
	}

	return;
}

void printRevealedLetters(int len, char *dashedWord, char *spaces)
{
	int i;

	printf("     ");

	for (i = 0; i < len; i++)
	{
		printf("%c", dashedWord[i]);
		if (i < len - 1)
			printf("%c", spaces[i]);
	}
	printf("\n");
}

void fireworks(void)
{
	printf("       .''.      .        *''*    :_\\/_:     .\n      :_\\/_:   _\\(/_  .:.*_\\/_*   : /\\ :  .'.:.'.\n  .''.: /\\ :   ./)\\   ':'* /\\ * :  '..'.  -=:o:=-\n :_\\/_:'.:::.    ' *''*    * '.\\'/.' _\\(/_'.':'.'\n : /\\ : :::::     *_\\/_*     -= o =-  /)\\    '  *\n  '..'  ':::'     * /\\ *     .'/.\\'.   '\n      *            *..*         :\n     *\n        *\n");
}

void won(int len, char *dashedWord, char *spaces, int numIncorrect)
{
	int i;

	printHangMan(numIncorrect);
	printRevealedLetters(len, dashedWord, spaces);
	printf("\n");

	fireworks();
	printf("\nCongratulations!!!!! You WON! :D\n");
}

int notUsed(char letter, char *usedLetters)
{
	int i;

	for (i = 0; i < 26; i++)
	{
		if (usedLetters[i] == letter)
		{
			return 0;
		}
	}

	return 1;
}

void printWrongLetters(char *wrongLetters)
{
	int j;

	printf("\nIncorrect Guesses: ");
	for (j = 0; j < 26; j++)
	{
		printf("%c ", wrongLetters[j]);
	}
	printf("\n");
}

void runGame(char *word, char *name)
{
	int numIncorrect = 0, loseFlag = 0, len = strlen(word), i, j, firstRound = 1;
	int lettersLeft = len, nextIndex1 = 0, nextIndex2 = 0, containsLetter;
	char letter;
	char *dashedWord = malloc(sizeof(char) * (len + 1));
	char *spaces = malloc(sizeof(char) * len);
	char *usedLetters = malloc(sizeof(char) * 26);
	char *wrongLetters = malloc(sizeof(char) * 26);

	// fill usedLetters & wrongLetters with placeholders
	for (j = 0; j < 26; j++)
	{
		usedLetters[j] = '-';
		wrongLetters[j] = ' ';
	}

	printf("\nNow we will begin the game....\n");
	printf("\tYou have %d chances until %s is DEAD.\n\n", CHANCES, name);

	while (numIncorrect < CHANCES + 1)
	{
		printHangMan(numIncorrect);

		if (firstRound)
		{
			generateDashes(len, dashedWord, spaces);
			firstRound = 0;
		}

		// print dashes and correct letters
		printRevealedLetters(len, dashedWord, spaces);

		// if there are chances left
		if (numIncorrect < CHANCES)
		{
			printWrongLetters(wrongLetters);

			printf("\nEnter a letter: ");
			scanf(" %c", &letter);
			printf("\n");

			letter = tolower(letter);

			// default doesn't have letter
			containsLetter = 0;

			// loop through all of the letters and search for entered letter
			for (i = 0; i < len; i++)
			{
				// if letter matches, add it to the dashed display
				if (word[i] == letter)
				{
					dashedWord[i] = letter;
					containsLetter = 1;

					// if the correct letter hasn't been used before, subtract from the remaining correct letters
					if (notUsed(letter, usedLetters))
						lettersLeft--;
				}

				// if you got all letters correct, you've won
				if (lettersLeft == 0)
				{
					printf("--------------------------------------------------------------------\n\n");
					won(len, dashedWord, spaces, numIncorrect);
					free(dashedWord);
					free(spaces);
					free(usedLetters);
					return;
				}
			}

			// add the current letter to the usedLetters
			if (notUsed(letter, usedLetters))
				usedLetters[nextIndex1++] = letter;

			if (containsLetter)
			{
				printf("Let's go! That letter is in the word.\n");
			}
			else
			{
				printf("\nSorry! That letter is not in the word.\n");

				// if (letter is not in wrongLetters)

				if (notUsed(letter, wrongLetters))
				{
					numIncorrect++;
					wrongLetters[nextIndex2++] = letter;
				}
			}
			printf("\n--------------------------------------------------------------------\n\n");
		}

		// if you have run out of chances
		if (numIncorrect >= CHANCES)
		{
			loseFlag = 1;
			break;
		}
	}

	if (loseFlag)
	{
		printHangMan(numIncorrect);

		printRevealedLetters(len, dashedWord, spaces);
		printf("\n\n");

		printf("  N\n　   O\n　　　 O\n　　　　 o\n　　　　　o\n　　　　　 o\n　　　　　o\n　　　　 。\n　　　 。\n　　　.\n　　　.\n　　　 .\n　　　　.\n");
		printf("\t  You lost! :(\n\n");
		printf("The word was: %s\n", word);
	}

	free(dashedWord);
	free(spaces);
	free(usedLetters);
	return;
}

void chooseWord(int categoryNum, char *word)
{
	char colors[][9] = {"violet", "lavender", "navy", "burgundy", "cyan", "gold", "silver", "rainbow"};
	char states[][12] = {"florida", "alabama", "washington", "mississippi", "hawaii", "oregon", "wyoming"};
	char animals[][10] = {"turtle", "crab", "armadillo", "snail", "lobster", "clam"};
	char random[][11] = {"shellhacks", "saxophone", "bootcamp", "shower", "mansion", "waterfall", "vinyl"};
	int index;

	if (categoryNum == 1)
	{
		index = rand() % 8;
		strcpy(word, colors[index]);
	}
	else if (categoryNum == 2)
	{
		index = rand() % 7;
		strcpy(word, states[index]);
	}
	else if (categoryNum == 3)
	{
		index = rand() % 6;
		strcpy(word, animals[index]);
	}
	else
	{
		index = rand() % 7;
		strcpy(word, random[index]);
	}

	return;
}

int main(void)
{
	int categoryNum;
	char name[1024];
	char *word;

	srand(time(NULL));

	printf("Welcome to Hangman!\nBy Kian Bacon\nCoded in C\n");
	printf("--------------------------------------------------------------------\n\n");

	printf("Please enter your name: \n");
	scanf("%s", name);

	categoryNum = selectCategory();

	// select random word
	word = malloc(sizeof(char) * 13);
	chooseWord(categoryNum, word);

	runGame(word, name);

	free(word);

	printf("\n");

	return 0;
}
