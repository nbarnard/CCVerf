#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/***************************************************************************
 * Function     : ccverf
 * Author       : Nicholas Clifton Barnard <nickb@pobox.com>
 * Date         : February 5, 1997
 * Description  : Validates a Credit Card Number
 * Arguments    : char card -  credit card number - Tolerant of Non-Numbers
 * int type - type of credit card
 * 1 - Visa
 * 2 - MasterCard
 * 3 - American Express
 * 4 - Discover 
 * Return Value : integer - 0 - invalid card number
 *                          1 - valid card number
 * Copyright    : Copyright (C) 1996 Nicholas Barnard.  All Rights Reserved.
 * Anyone may use this function within their programs as long as my
 * name and E-Mail address are contained within the documentation in the
 * same font and size as the main body of the documentation.  An E-Mail
 * is also requested if you use this function within your program.
 * You may modify this function, as long as you credit yourself
 * with your name and e-mail address.  You must also send a copy
 * of your modified version to me.
 * Special Thanks to Dave Paris <spider@servtech.com> for help with the
 * Mod 10 Algorithm.
 *************************************************************************/

int
ccverf(char *card, int type)
{
	int ccnumber[16];
	int final = 0;
	char temp[256];
	int digits = 0;
	int counter;
	int len;
	int start;
	int twice;

	/*
	 * Take card and throw all of the numbers from it into ccnumber
	 */
	for (len = strlen(card), counter = 0; len >= counter; counter++) {
		if ((isdigit(card[counter])) != 0) {
			if (digits == 17) {
				return (0);
			}
			ccnumber[digits] = ((card[counter]) - 48);
			digits++;
		}
	}
	/*
	 * See if the card number is 13, 15 or 16 digits, the only legal
	 * sizes for credit cards.
	 */
	if ((digits != 13) && (digits != 15) && (digits != 16)) {
		return (0);
	}
	/* Thirteen digit cards must be Visa's */
	if (digits == 13) {
		if (type != 1) {
			return (0);
		}
		/* The first digit of Visa's must be 4 */
		if ((type == 1) && (ccnumber[0] != 4)) {
			return (0);
		}
		/* Thirteen digit cards doubling start at the second digit */
		start = 1;
	}
	/* Fifteen digit cards must be American Express */
	if (digits == 15) {
		if (type != 3) {
			return (0);
		}
		/* The first digit of American Express's must be 3 */
		if ((type == 3) && (ccnumber[0] != 3)) {
			return (0);
		}
		/* Fifteen digit cards doubling start at the second digit */
		start = 1;
	}
	/* Sixteen digit cards can be Discover, MasterCard, or Visa */
	if (digits == 16) {
		if ((type != 1) && (type != 2) && (type != 4)) {
			return (0);
		}
		/* The first digit of Visa's must be 4 */
		if ((type == 1) && (ccnumber[0] != 4)) {
			return (0);
		}
		/* The first digit of MasterCard's must be 5 */
		if ((type == 2) && (ccnumber[0] != 5)) {
			return (0);
		}
		/* The first digit of Discover's must be 6 */
		if ((type == 4) && (ccnumber[0] != 6)) {
			return (0);
		}
		/* Sixteen digit cards doubling start at the first digit */
		start = 0;
	}
	/* Double every other digit starting at the correct spot */
	for (counter = start; counter < digits; counter += 2) {

		twice = ccnumber[counter] * 2;

		/*
		 * Performs single digit doubling on ccnumber[counter] i.e.
		 * 8 doubled into 7 (8 * 2 = 16 1 + 6 = 7)
		 */
		if (twice >= 10) {
			sprintf(temp, "%d", twice);
			ccnumber[counter] = (((temp[0]) - 48) + ((temp[1]) - 48));
		} else {
			ccnumber[counter] = twice;
		}
	}
	/* Adds up all of the digits */
	for (counter = 0; counter < digits; counter++) {
		final += ccnumber[counter];
	}

	/* See if the final digit is a zero, if so the card is valid. */
	sprintf(temp, "%d", final);
	if ((temp[(strlen(temp) - 1)]) != '0') {
		return (0);
	} else {
		return (1);
	}

}






