What CCVerf is
==============
CCVerf is a ANSI C function that checks the mathematical veracity of major credit card numbers.

What CCVerf does
=================

Check the mathematical veracity of the card number against the MOD10 algorithm.
Check if the card number fits the format for the brand of the credit card. (i.e. Visa, MasterCard, American Express and Discover)

What CCVerf does not do:
========================

* Check the actual validly of a card number with a bank.
* Check the balance available on the card number in question.
* Check the expiration date of the card number in question.

Why CCVerf is useful
====================

*Reduce verification costs related to per verification costs, or related connection costs.
*Provide a simple method for off-line verification.
*Reduce customer wait time while credit card numbers are checked versus the credit card network, just to get a response that the card number is invalid.

What CCVerf accepts at its arguments (inputs)
=============================================

A string, which is accessed via pointer, which contains the card number in question. This string may contain extraneous non numerical characters, that CCVerf will ignore.
A integer between one and four, which corresponds to the card type, as stated by the chart below:

<table border="" cellspacing="0" cellpadding="4">
<tr>
<td>Integer Input</td>

<td>Corresponding Card Type</td>
</tr>

<tr>
<td align="right">1 -</td>

<td>Visa</td>
</tr>

<tr>
<td align="right">2 -</td>

<td>Master Card</td>
</tr>

<tr>
<td align="right">3 -</td>

<td>American Express/Diner's Club</td>
</tr>

<tr>
<td align="right">4 -</td>

<td>Discover</td>
</tr>
</table>

How CCVerf checks the credit card number
========================================

First, CCVerf strips out all the non numeric characters and checks the number of digits. If number of digits isn't 13, 15, or 16 it rejects the card.

Second, CCVerf checks the length of the number versus the type. Visa cards numbers must be 13 or 16 digits. American Express card numbers must be 15 digits. MasterCard and Discover card numbers must be 16 digits.

Third, CCVerf checks the first digit of the card number versus the type. American Express card numbers must start with '3'. Visa card numbers must start with '4'. MasterCard numbers must start with '5'. Discover card numbers must start with '6'.

Finally, CCVerf checks the card number versus the MOD10 algorithm. The MOD10 algorithm works by utilizing a single digit doubling system on every other digit starting on the first digit on sixteen digit cards, and on the second digit on thirteen and fifteen digit cards. [i.e. five doubles into one. (5x2 = 10, 1+0=1) Eight doubles into seven. (8x2=16, 1+6=7) Four doubles into eight. (4x2=8, 0+8=8)] Next, the MOD10 algorithm adds the resulting doubled digits together and verifies the result is divisible by ten.

An example of how CCVerf checks the credit card number
———————————————————————————

The string "4791-0600-2310-2329" and the integer '1' is passed to CCVerf. CCVerf starts by pulling all of the numerical digits out of the string and placing them in a array, represented by following table: 

<table border="" cellspacing="0" cellpadding="4">
<tr>
<td>Array Position</td>

<td>00</td>

<td>01</td>

<td>02</td>

<td>03</td>

<td>04</td>

<td>05</td>

<td>06</td>

<td>07</td>

<td>08</td>

<td>09</td>

<td>10</td>

<td>11</td>

<td>12</td>

<td>13</td>

<td>14</td>

<td>15</td>
</tr>

<tr>
<td>Digit Contained</td>

<td>4</td>

<td>7</td>

<td>9</td>

<td>1</td>

<td>0</td>

<td>6</td>

<td>0</td>

<td>0</td>

<td>2</td>

<td>3</td>

<td>1</td>

<td>0</td>

<td>2</td>

<td>3</td>

<td>2</td>

<td>9</td>
</tr>
</table>

CCVerf first checks and sees that the length of the card is sixteen digits, an acceptable length for a card number. It then checks the digit in array position zero and confirms that the first digit is four, since this card was reported as a Visa. CCVerf then doubles every other digit of the array starting at the 00 array position and replaces the original digit with the doubled digit. Leaving the array in the following state: 

<table border="" cellspacing="0" cellpadding="4">
<tr>
<td>Array Position</td>

<td>00</td>

<td>01</td>

<td>02</td>

<td>03</td>

<td>04</td>

<td>05</td>

<td>06</td>

<td>07</td>

<td>08</td>

<td>09</td>

<td>10</td>

<td>11</td>

<td>12</td>

<td>13</td>

<td>14</td>

<td>15</td>
</tr>

<tr>
<td>Digit Contained</td>

<td>8</td>

<td>7</td>

<td>9</td>

<td>1</td>

<td>0</td>

<td>6</td>

<td>0</td>

<td>0</td>

<td>4</td>

<td>3</td>

<td>2</td>

<td>0</td>

<td>4</td>

<td>3</td>

<td>4</td>

<td>9</td>
</tr>
</table>

When the digits are added the total is sixty, since sixty is divisible by ten, and the card has passed all the other requirements the card is considered valid.

License
=======
CCVerf is released under the GNU Lesser General Public License: <http://www.gnu.org/copyleft/lesser.html>

How to contact CCVerf's author
==============================
Nicholas Barnard may be contacted via his website form at <http://www.inmff.net/mailme.html>