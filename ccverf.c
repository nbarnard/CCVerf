#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

/***************************************************************************
 * Function     : ccverf
 * Author       : Nicholas Clifton Barnard <nickb@pobox.com>
 * Date         : April 14, 2003
 * Description  : Validates a Credit Card Number
 * Arguments    : char card -  credit card number - Tolerant of Non-Numbers
 * int type - type of credit card
 * 1 - Visa
 * 2 - MasterCard
 * 3 - American Express
 * 4 - Discover 
 * Return Value : integer - 0 - invalid card number
 *                          1 - valid card number
 * Update notes : 4/14/2003 - Got rid of silly uses of sprintf now uses casting
 *                            out nines and the modulus operator and released 
 *                            under the LGPL
 * Special Thanks to Dave Paris <spider@servtech.com> for help with the
 * Mod 10 Algorithm.
 *
 * An E-Mail is requested if you use this function within your program.  It is
 * also requested that you send a copy of modified version to me.
 *
 * Copyright (C) 1996,2003 Nicholas Clifton Barnard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *************************************************************************/

int
ccverf(char *card, int type)
{
	int ccnumber[16];
	int final = 0;
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
		 * 8 doubled into 7 (8 * 2 = 16 1 + 6 = 7) by casting out nines
		 */
		if (twice >= 10) {
			ccnumber[counter] = twice-9;                        
		} else {
			ccnumber[counter] = twice;
		}
	}
	/* Adds up all of the digits */
	for (counter = 0; counter < digits; counter++) {
		final += ccnumber[counter];
	}

	/* See if the final digit is a zero, if so the card is valid. */
	
        if ((final%10)!=0) {
		return (0);
	} else {
		return (1);
	}

}






