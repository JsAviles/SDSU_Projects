/*************************************************************************************
* Name:        	Jesus Aviles, cssc3404, RED ID: 823931557
				Dao Vo      , cssc3459, RED ID: 820901504
* Class:        CS570 Spring 2021
* Assignment:   Assignment #1
* File:        	myls.cpp
* Description:  Source Code file for myls, emulate ls command in linux/Unix
*************************************************************************************/

#include "myls.h"

//main
int main (int argc, char* argv[])
{   
    DIR *dir;
    struct dirent *dirPointer;
    dir = opendir(".");
    bool hidden = false;

    //if there are no arguments given in the terminal --> List current directory files
    if(argc == 1)
    {;
        printf("\n%s\n", get_current_dir_name());
        while ((dirPointer=readdir(dir)) != NULL) 
        { 
            //while the directory is not empty, list all visible files, excluding hidden files (starting with a period)
            if (dirPointer->d_name[0] != '.' )
            {
                printf("%s\n", dirPointer->d_name);
            } 
        }
    } 
    //else if there are no directories given but the flag -h is given --> list all visible files + hidden files in current directory
    else if(string(argv[1])== "-h" && argc < 3)
    {
        printf("\n%s\n", get_current_dir_name()); 
        //while the directory is not empty, list all visible + hidden files
        while ((dirPointer=readdir(dir)) != NULL) 
        {
            printf("%s\n", dirPointer->d_name);
        }
    }
    //if a directory is given in the terminal --> explore the directory/directories and list their content
    else
    {
        int i = 1;
        //check for -h flag
        if (string(argv[1])== "-h")
        {
            //set -h flag to true for printing hidden files in the directory
            hidden = true;
            i++;
        }
        //open the first directory given
        while(i < argc)
        {
            dir = opendir(argv[i]);
            printf("\n");
            if(dir) 
            {      
                printf("%s\n", argv[i]);
                //puts("OK the directory is opened, let's see its files:");
                while ((dirPointer = readdir(dir)))
                {
                    //check to see if the current dirPointer points to a hidden file and if the flag 'hidden' is set to true, list those files in the output
                    if (dirPointer->d_name[0] == '.' && hidden)
                    {
                        printf("%s\n", dirPointer->d_name);
                    } 
                    //otherwise if the dirPointer is not pointing to a hidden file, list the file/directory in the output
                    else if(dirPointer->d_name[0] != '.')
                    {
                        printf("%s\n", dirPointer->d_name);
                    }
                }
                //close the directory when finished parsing through its content
                closedir(dir);
            } 
            //error checking for various scenarios
            else if (errno == ENOENT)
                printf("Cannot access %s\n", argv[i]);
            else if (errno == ENOTDIR)
                printf("Cannot access %s\n", argv[i]);
            else if (errno == EACCES)
                printf("Cannot access %s\n", argv[i]);
            else
                printf("That's a new error, check the manual.");
            i++;
        }
    }
    printf("\n");
    return 0;
}