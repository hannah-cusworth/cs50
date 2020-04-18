#include <cs50.h>
#include <stdio.h>

int main(void)
{
//prompt user for height 
int height = get_int("Height:");
         
//reprompt if height is not between 1 and 8 
 while (height > 8 || height == 0 || height < 0)
    {
    height = get_int("Height:");      
    }

//print the pyramid for height = 1
if (height == 1)
    {
    printf("#  #\n");
    }
//print the pyramid when height = 2
 else if (height == 2)
    {
    printf(" #  #\n##  ##\n");
    }
//print the pyramid when height = 3
else if (height == 3)
    {
    printf("  #  #\n ##  ##\n###  ###\n");
    }
//print the pyramid when height = 4
else if (height == 4)
    {
    printf("   #  #\n  ##  ##\n ###  ###\n####  ####\n");       
    }
//print the pyramid when height = 5
else if (height == 5)
    {
    printf("    #  #\n   ##  ##\n  ###  ###\n ####  ####\n#####  #####\n");   
    }
//print the pyramid when height = 6
else if (height == 6)
    {
    printf("     #  #\n    ##  ##\n   ###  ###\n  ####  ####\n #####  #####\n######  ######\n");        
    }
//print the pyramid when height = 7
else if (height == 7)
    {
    printf("      #  #\n     ##  ##\n    ###  ###\n   ####  ####\n  #####  #####\n ######  ######\n#######  #######\n");   
    }
//print the pyramid when height = 8
else if (height == 8)
    {
    printf("       #  #\n      ##  ##\n     ###  ###\n    ####  ####\n   #####  #####\n  ######  ######\n #######  #######\n########  ########\n");        
    }
}
