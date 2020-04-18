#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
//Get user input and calculate length of number
long number = get_long("Number:");
int length = 1 + log10(number);

//***Get digits***
//Get 2nd digit   
int a = (number % 100)/10; 
//Get 4th digit
int b = (number % 10000)/1000; 
//Get 6th digit
int c = (number % 1000000)/100000; 
//Get 8th digit
int d = (number % 100000000)/10000000; 
//Get 10th digit
int e = (number % 10000000000)/1000000000; 
//Get 12th digit
int f = (number % 1000000000000)/100000000000; 
//declare g and h
int h = 0;
int g =0;
//get 14th digit if longer than 13
if (length > 13)
{
    g = (number % 100000000000000)/10000000000000; 
}
else 
{
    g = 0;
}
//Get 16th digit if 16 digits long
if (length > 15)
{
    h = (number % 10000000000000000)/1000000000000000;
}
else 
{
    h = 0;
}
//***check digits don't multiply to more than 10***
//Declare new ints
int aa = 0;
int bb = 0;
int cc = 0;
int dd = 0;
int ee = 0;
int ff = 0;
int gg = 0;
int hh = 0;
//check a 
if (a < 5)
{
    aa = a*2;
}
else 
{
    aa = (a*2 - 10) + 1;
}
//check b 
if (b < 5)
{
    bb = b*2;
}
else 
{
    bb = (b*2 - 10) + 1;
}
//check c
if (c < 5)
{
    cc = c*2;
}
else 
{
    cc = (c*2 - 10) + 1;
}
//check d 
if (d < 5)
{
    dd = d*2;
}
else 
{
    dd = (d*2 - 10) + 1;
}
//check e 
if (e < 5)
{
    ee = e*2;
}
else 
{
    ee = (e*2 - 10) + 1;
}
//check f 
if (f < 5)
{
    ff = f*2;
}
else 
{
    ff = (f*2 - 10) + 1;
}
//check g 
if (g < 5)
{
    gg = g*2;
}
else 
{
    gg = (g*2 - 10) + 1;
}
//check h 
if (h < 5)
{
    hh = h*2;
}
else 
{
    hh = (h*2 - 10) + 1;
}
//***get other digits***
//Declare if variables
int p = 0;
//Get 1st digit   
int i = (number % 10); 
//Get 3rd digit
int j = (number % 1000)/100; 
//Get 5th digit
int k = (number % 100000)/10000; 
//Get 7th digit
int l = (number % 10000000)/1000000; 
//Get 9th digit
int m = (number % 1000000000)/100000000; 
//Get 11th digit
int n = (number % 100000000000)/10000000000; 
 //Get 13th digit
int o = (number % 10000000000000)/1000000000000; 
 //Get 15th digit if there 
 if (length > 14)
{
     p = (number % 1000000000000000)/100000000000000;
}
else 
{
    p = 0;
}
    
    
// // *** final stage of algorithm ***
// add together new products
int add = aa + bb + cc + dd + ee + ff + gg + hh + i + j + k + l + m + n + o + p;
//get last digit of add
int tens = add % 10;
//check length is 13, 15 or 16
if (length != 13 && length != 15 && length != 16)  
{
    printf("INVALID\n");
}
//If last digit of tens isn't 0 print invalid
else if (tens != 0)
{
    printf("INVALID\n");
}
//If first digits 34 it's AMEX - this is the 15th digit
 else if (p == 3 && g == 4 && length == 15)
{
     printf("AMEX\n");
}
//If first digits 37 it's AMEX - this is the 15th digit
 else if (p == 3 && g == 7 && length == 15)
{
     printf("AMEX\n");
}
//If its 13 long and starts in a 4 it must be a visa 
 else if (length == 13 && o == 4)
{
     printf("VISA\n");
}
//16 long and starts with a 51 it must be a mastercard
 else if (length == 16 &&  h == 5 && p == 1 )
{
     printf("MASTERCARD\n");
}
//16 long and starts with a 52 it must be a mastercard
 else if (length == 16 &&  h == 5 && p == 2 )
{
     printf("MASTERCARD\n");
}
//16 long and starts with a 53 it must be a mastercard
 else if (length == 16 &&  h == 5 && p == 3 )
{
     printf("MASTERCARD\n");
}
//16 long and starts with 54 it must be a mastercard
 else if (length == 16 &&  h == 5 && p == 4 )
{
     printf("MASTERCARD\n");
}
//16 long and starts with 55 it must be a mastercard
 else if (length == 16 &&  h == 5 && p == 5 )
{
     printf("MASTERCARD\n");
}
//16 lond and starts in a 4 it must be a visa
 else if (length == 16 && h == 4)
{
     printf("VISA\n");
}
else 
{
    printf("INVALID\n");
}
}
