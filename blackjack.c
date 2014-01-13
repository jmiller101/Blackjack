#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define DECKSIZE 52
#define RANKSIZE 6
#define SUITSIZE 13

//Card data type
typedef struct
{
	int value;
	char suit[SUITSIZE];
	char rank[RANKSIZE];
} card;

//Functions
void deckMake(card *);
card newLineTrim(card);
void deckShuffle(card *);

int main(void)
{
	int i;
	card deck[DECKSIZE];

	//Generates the deck
	deckMake(deck);

	//Shuffles the deck
	deckShuffle(deck);

	//Deck test
	for(i = 0; i < DECKSIZE; i++)
	{
		printf("%d ", deck[i].value);
		printf("%s ", deck[i].rank);
		printf("%s ", deck[i].suit);

		printf("\n");
	}

	//deal
	//hitorstay
	//dealTurn
	//winner
	//deal
	//check for end of deck

	return 0;
}

//Generates the deck
void deckMake(card *pointer)
{
	int i, j, value[13];
	char rank[13][RANKSIZE], suit[4][SUITSIZE];
	FILE *valueFile, *suitFile, *rankFile;

	valueFile = fopen("value", "r");
	rankFile = fopen("rank", "r");
	suitFile = fopen("suit", "r");

	//Fills the rank array with the different ranks	
	for(i = 0; i < 13; i++)
	{
		fgets(rank[i], RANKSIZE, rankFile);
	}

	//Fills the suit array with the different suits	
	for(i = 0; i < 4; i++)
	{
		fgets(suit[i], SUITSIZE, suitFile);
	}

	//Fills the value array with the different values	
	for(i = 0; i < 10; i++)
	{
		fscanf(valueFile, "%d", &value[i]);
	}

	fclose(valueFile);
	fclose(rankFile);
	fclose(suitFile);

	//Does the actual deck generation
	//Generates the suits
	for(i = 0, j = 0; j < 4; i++)
	{
		strcpy(pointer[i].suit, suit[j]);

		if((i + 1) % 13)
		{
			j++;
		}
	}

	//Generates the ranks and values
	for(i = 0, j = 0; i < DECKSIZE; i++, j++)
	{
		strcpy(pointer[i].rank, rank[j]);

		pointer[i].value = value[j];

		if((i + 1) % 13)
		{
			j = 0;
		}
	}

	//Trims the '\n' from all the ranks and suits
	for(i = 0; i < DECKSIZE; i++)
	{
		pointer[i] = newLineTrim(pointer[i]);
	}
	
	return;
}

//Takes the '/n' off of the end from fgets
card newLineTrim(card cardToTrim)
{
	int newLineTrim;

	newLineTrim = strlen(cardToTrim.rank);
	newLineTrim -= 2;
 	cardToTrim.rank[newLineTrim] = '\0';

	newLineTrim = strlen(cardToTrim.suit);
	newLineTrim--;
	cardToTrim.suit[newLineTrim] = '\0';

	return cardToTrim;
}

//Shuffles the deck
void deckShuffle(card *deck)
{
	int i = 0, randomCardPlace;
	card temp;

	srand(time(NULL));

	while (i < DECKSIZE)
	{
		randomCardPlace = rand() %(DECKSIZE - 1);
		
		temp = deck[i];
		deck[i] = deck[randomCardPlace];
		deck[randomCardPlace] = temp;

		i++;
	}

	return;
}
