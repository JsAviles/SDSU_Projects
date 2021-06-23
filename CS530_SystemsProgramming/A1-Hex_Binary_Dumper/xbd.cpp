/*
File: xbd.cpp (source code file) for Assignment #1 
Name: Jesus Sebastian Aviles
REDID: 823931557
Edoras Account: cssc3040
Class: CS530 Fall 2020
*/

#include "xbd.h"

//main
int main (int argc, char* argv[])
{   
    if(argc>3 || argc==3 && std::string(argv[1])!= "-b")
    {
        printf("\nError: Incorrect or too many entries in the command line, please try again. (Use -b for binary or no option for hex)\n");
        return 0;
    }
    else if(std::string(argv[1]) == "-b") //binary dump if the flag bit is in argv[1] is found to be '-b'
    {   
        binary_dump(argv[2]);
    }
    else //hexdump if no flag bit was entered and the initial conditions had failed
    {
        
        hex_dump(argv[1]);
    }
   return 0;
}

//Function called to being a Hex Dump
void hex_dump (char* arg)
{   
    int size=0;
    char c;
    std::ifstream read_file;
    ifstream ifile(arg);
    //Error check for whether or not the designated file is accessible or present
    if (!ifile)
    {
        printf("Error: File may not exist or may not be accessible.\n");
        return;
    }
    read_file.open(arg, std::ifstream::in);
    c = read_file.get();

    /*The proceeding while loop is intended to traverse the file to be dumped
    and increment a size integer variable in order to create an array of proper
    size*/
    while(!read_file.eof())
    {
        size++;
        c = read_file.get();
    }
    read_file.close();
    read_file.clear();

    /*check to see if after the file was opened, whether or not it contained any 
    information or if it was blank, i.e. size ==0*/
    if(size==0)
    {
        printf("Error: File is empty.\n");
    }
        
    char dump[size];
    int index = 0;
    read_file.open(arg, std::ifstream::in);
    c = read_file.get();

    /*Traverse the file to be byte dumped and enter every character into an
    array which will be used to manipulate the data*/
    while(!read_file.eof())
    {
        dump[index] = c;
        c = read_file.get();
        index ++;
        if(read_file.eof())             //Add new line char to the end, just like xxd does
        {
            dump[index] = '\n';
        }
    }
    read_file.close();
    read_file.clear();

    int spacectr = 0;                   //variable used to calculate the amount of space needed for the last row of print to be properlly formatted
    int address = 0;                    //incremented Address counter 
    
    /*for loop where all calculations take place*/
    for(int i=0;i<size;i+=16)
    {
        /*Because each row is going to contain 16 bytes, by dividing "size" using integer division then multiplying it
        by 16 again to remove the remainder, the if statement will only run the amount of times necessary (16 byte row)*/
        if(i!=((size/16)*16))
        {
            /*For characters with a hex value that exceeds 8 bits, 0xff masks unwanted bytes off of characters with more than
            2 bits in representation*/
            printf("%07x: %02x%02x %02x%02x %02x%02x %02x%02x %02x%02x %02x%02x %02x%02x %02x%02x  ", address, (0xff & dump[i+0]), (0xff & dump[i+1]), (0xff & dump[i+2]), (0xff & dump[i+3]), (0xff & dump[i+4]), (0xff & dump[i+5]), 
            (0xff & dump[i+6]), (0xff & dump[i+7]), (0xff & dump[i+8]), (0xff & dump[i+9]), (0xff & dump[i+10]), (0xff & dump[i+11]), (0xff & dump[i+12]), (0xff & dump[i+13]), (0xff & dump[i+14]), (0xff & dump[i+15]));

            /*After the 16 bytes have been represented the next for loop prints the corresponding characters
            also checking to make sure any characters not within the designated printable range (space to tilde)
            and produces a period/dot for any characters not in the range */
            for(int j=i; j<i+16;j++)
            {   
                if(dump[j] <='~' && dump[j] >=' ')
                {
                    printf("%c",dump[j]);
                }
                else
                {
                    printf(".");        
                }     
            }
            //increment address for printing purposes
            address+=16;
        }
        /*once i reaches the max amount of full 16 byte rows that can be represented, only the
        last row is left to represent*/
        else
        {
            int last = size-i;              //last represents how many bytes are left to represent
            printf("%07x: ", address);      //print address for the last row

            /*If the last row has an even number of bytes left, print the remaining bytes in pairs*/
            if((last%2) == 0)
            {
                for(int k = 0; k<(((size-i)/2)*2);k+=2)
                {
                    printf("%02x%02x ",(0xff & dump[i+k]),(0xff & dump[i+k+1]));
                    spacectr += 2;
                }
            }
            /*if only 1 byte remains then print it and be done*/
            else if(last<2)
            {
                printf("%02x ",(0xff & dump[i]));
                spacectr += 1;
            }
            /*For an odd number of bytes left greater than 1, print pairs till last byte remains*/
            else
            {
                for(int h = i; h<size ;h+=2)
                {
                    if((h+1==size))
                    {
                        printf("%02x ",(0xff & dump[h+1]));
                        h+=2;
                        spacectr += 1;
                    }
                    else
                    {
                        printf("%02x%02x ",(0xff & dump[h]),(0xff & dump[h+1]));
                        spacectr += 2;
                    }
                    
                }
            }
            last = (spacectr/2)+(spacectr*2)+(spacectr%2);      //formula to calculate number of spaces required for proper formatting
            int spaces = 41-last;                               //the actual number of spaces to be printed for formatting
            for(int r=0;r<spaces;r++)
            {
                printf(" ");
            }

            /*duplicate print loop for the characters corresponding to bytes*/
            for(int j=i; j<size;j++)
            {                                                             
                if(dump[j] <= '~' && dump[j] >=' ')
                {
                    printf("%c",dump[j]);
                }
                else
                {
                    printf(".");        
                }     
            }
            address+=16;
        }
        printf("\n");
    }
}

//Function called to being a binary dump
void binary_dump (char* arg)
{   
    int size=0;
    char read;
    std::ifstream read_file;
    read_file.open(arg, std::ifstream::in);
    ifstream ifile(arg);
    //Error check for whether or not the designated file is accessible or present
    if (!ifile)
    {
        printf("Error: File may not exist or may not be accessible.\n");
        return;
    }
    read = read_file.get();
    /*The proceeding while loop is intended to traverse the file to be dumped
    and increment a size integer variable in order to create an array of proper
    size*/
    while(read_file.is_open() && !read_file.eof())
    {
        size++;
        read = read_file.get();
    }
    read_file.close();
    read_file.clear(); 

    /*check to see if after the file was opened, whether or not it contained any 
    information or if it was blank, i.e. size ==0*/  
    if(size==0)
    {
        printf("Error: File is empty.\n");
    }
        
    char dump[size];
    int index = 0;
    read_file.open(arg, std::ifstream::in);
    read = read_file.get();
    
    /*Traverse the file to be byte dumped and enter every character into an
    array which will be used to manipulate the data*/
    while(!read_file.eof())
    {
        dump[index] = read;
        read = read_file.get();
        index ++;
        if(read_file.eof())                 //Add new line char to the end, just like xxd does
        {
            dump[index] = '\n';
        }
    }
    read_file.close();
    read_file.clear();
    int address = 0;

    /*In order to represent the ASCII values in binary I implented the by-hand arithmetic
    for converting a decimal number to binary, and because the bits are calculated in order
    of least significance, I created a custom 2d array and added the bits to the corresponding
    [row][column] beginning from the least significant position in the array [][7]*/
    int div,rem;
    char bdump[size][8];
    for(int i=0; i<size; i++)
    {
        div = dump[i];
        int column=7;
        for(int j=7; j>=0 ;j--)
        {   if(div!=0)
            {
                rem = div%2;
                div = div/2;
                bdump[i][j] = rem;
            }
            else
            {
                bdump[i][j] = 0;
            }
            
        }
    }

    //integer divison to find how many full rows there are, then complete that many rows just as in the Hex dumping function
    for(int address = 0; address<((size/6)*6);address+=6) 
    {   
        printf("%07x: ", address);
        for(int i=address; i<(address+6);i++) //= 0 ,6 , 12, 18, 24, 30, 36 etc...
        {   
            //for each byte, print the corresponding bits in the 2d array
            for(int j=0; j<8; j++)
            {
                printf("%d",bdump[i][j]);
            }
            printf(" ");
            //if the end of the byte row is met, begin printing the corresponding characters
            if ((i+1)==(address+6))
            {    
                printf(" ");
                //check to see if dump contains an acceptible ASCII char, if not fill it with a period/dot
                for(int r=address; r<address+6;r++)            
                {   
                    //check to see if the character is acceptible for representation
                    if(dump[r] <= '~' && dump[r] >=' ')
                    {
                        printf("%c",dump[r]);
                    }
                    else
                    {
                        printf(".");        
                    }     
                }
            }
        }
        printf("\n");
        //print the final row of bytes in binary representation
        if((address+6)==(size-(size%6)) && (address+6) != size)                                
        {
            printf("%07x: ", address+6);
            for(int k = address+6; k < size; k++)
            {
                for(int j=0; j<8; j++)
                {
                    printf("%d",bdump[k][j]);
                }
                printf(" ");
                if ((k+1)==(size))//done posting binary, space out and add corresponding letters
                {   
                    //formula constructed to consistently format spacing for any number of bits
                    int spaces = 64 -((size-(address+5))*9);      
                    for(int r=0;r<spaces;r++)
                    {
                        printf(" ");
                    }
                    /*duplicate print loop for the characters corresponding to bytes*/
                    for(int r=address+6; r<size; r++)
                    {   
                        if(dump[r] < '~' && dump[r] >=' ')
                        {
                            printf("%c",dump[r]);
                        }
                        else
                        {
                            printf(".");        
                        }     
                    }
                }
            }
            printf("\n");
        }  
    }
}