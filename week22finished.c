#include "stdafx.h"
#include <stdio.h>
#include "string.h"
#include "stdarg.h"
#include "stdlib.h"
#include "time.h"

typedef enum S { CLUBS, DIAMONDS, HEARTS, SPADES } SUIT;
char suits[][10] = { "CLUBS", "DIAMONDS", "HEARTS", "SPADES" };

typedef enum F { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE } FACE;
char faces[][10] = { "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING", "ACE" };

char winner[][20] = { "YOU", "DEALER", "DRAW" };

typedef struct
{
	SUIT suit;
	FACE face;
} card;

typedef struct
{
	card cards[5];
} hand;

// function deals a random hand of cards - BUT .... same card CANNOT be dealt twice!
// so if same card already in the hand, you would need to draw again
// also, the card cannot appear in another hand either
hand dealHand(hand handsDealt[], int numHandsDealt);

// returns pointer to string containing, for example, "ACE of HEARTS"
char * printCard(card aCard);

// compares the FACE values of two cards (TWO is lowest, ACE is highest)
// returns pointer to string containing name of winner: "You" or "Dealer" (or "Draw" if the face values are the same)
char * compareCards(card yourCard, card dealersCard);

// returns true if the hand contains four ACES
bool fourAces(hand aHand);


void main()
{
	int i = 0;
	hand myHand, dealersHand;
	int seed = time(NULL);
	srand(seed);
	hand hands[10];

	// deal the first hand
	myHand = dealHand(hands, 0);

	// add this new hand to the set of dealt hands
	hands[0] = myHand;

	// deal another hand; let dealHand know what has already been dealt
	dealersHand = dealHand(hands, 1);

	// here you are just comparing each card one at a time in the two hands
	while (i<5)
	{
		printf("card#%d: %s (you) vs. %s (dealer). Winner: %s \n", i + 1, printCard(myHand.cards[i]), printCard(dealersHand.cards[i]), compareCards(myHand.cards[i], dealersHand.cards[i]));
		i++;
	}

	// now try to deal 4 Aces !
	while (1)
	{
		// deal a new hand; assume new deck every time, so nothing dealt already
		myHand = dealHand(hands, 0);
		
		// does it contain 4 ACES?
		if (fourAces(myHand)) break;
		i++; // keep track of number of hands dealt
	}
	// print out how many hands it took to find 4 aces
	printf("\n\n4 aces found after %d hands \n\n\n", i);
}

// compares the FACE values of two cards (TWO is lowest, ACE is highest)
// returns pointer to string containing name of winner: "You" or "Dealer" (or "Draw" if the face values are the same)
char * compareCards(card yourCard, card dealersCard)
{
	char *sptr;
	sptr = (char *)malloc(10 * sizeof(char));
	 

	
	if (FACE(yourCard.face) > FACE(dealersCard.face))
	{
		sptr = winner[0];
	}
	else if (FACE(yourCard.face) == FACE(dealersCard.face))
	{
		sptr = winner[2];
	}
	else
	{
		sptr = winner[1];
	}
	return sptr;
}

// returns pointer to string containing, for example, "ACE of HEARTS"
char * printCard(card aCard)
{
	char *sptr;
	char string[100];
	sptr = (char *)malloc(100 * sizeof(char));
	strcpy(sptr, faces[aCard.face]);
	strcat(sptr, " OF ");
	strcat(sptr, suits[aCard.suit]);
	return sptr;
}

// function deals a random hand of cards - BUT .... same card CANNOT be dealt twice!
// so if same card already in the hand, you would need to draw again
// also, the card cannot appear in another hand either
hand dealHand(hand handsDealt[], int numHands)
{
	int i, n;				//hands dealt = cards that have already appeared 
	int found = 0;
	hand newHand;
	int ncards = 0;
	SUIT newSuit;
	FACE newFace;

	for (i = 0; i < 5; i++)
	{
		newFace = FACE(rand() % 13);
		newSuit = SUIT(rand() % 4);
		newHand.cards[i].suit = newSuit;
		newHand.cards[i].face = newFace;
		for (i = 1; i < 5; i++)
		{
		
			for (n = 0; n < 5; n++)
			{
				if ((newHand.cards[i].suit == newHand.cards[n].suit && newHand.cards[i].face == newHand.cards[n].face) || (newHand.cards[i].suit == handsDealt[numHands].cards[n].suit && newHand.cards[i].face == handsDealt[numHands].cards[n].face));
				{
					newFace = FACE(rand() % 13);
					newSuit = SUIT(rand() % 4);
					newHand.cards[i].suit = newSuit;
					newHand.cards[i].face = newFace;
				}


			}
		}
	}
	return newHand;
}

// returns true if the hand contains four ACES
bool fourAces(hand aHand)
{
	int i = 0;
	int numAces = 0;
	bool fourAces = false;

	for (i = 0; i < 5; i++)
	{
		if (aHand.cards[i].face == FACE(12))
			numAces++;
	}
	
	if (numAces == 4)
		fourAces = true;

	return fourAces;

}

