/*************************************************************************************
* Name:        	Jesus Aviles, cssc3040, RED ID: 823931557
				Dao Vo      , cssc3020, RED ID: 820901504
* Class:        CS530, Fall 2020 
* Assignment:   Project 3
* File:        	Parser.cpp
* Description:  Source code for lexical analysis using c++
*************************************************************************************/

#include "Parser.h"

//used to read from file and output to parse.txt
std::ifstream inStream;

/*************************************************************************************
 * 			                    PARSEFILE Function
 * 
 * - Scans designated file for input while simultaneously creating vector elements
 *   which append strings delimited by commas ',' into an array of vectors to be 
 * 	 later analyzed by the verify() and validate() functions
 * - Upon completetion of validation, then writes out resulted evaluations to a txt
 * 	 file... "parsed.txt"
 * 
*************************************************************************************/
void parseFile(char *file){
	char c;
	int size = 0;
	int arSize = 0;
	int index=0;
	char* tempChar = new char[15];
	vector <char*> parseVector;
	//parseVector.clear();

	inStream.open(file);
	inStream.get();

	while(!inStream.eof()){
		c = inStream.get();
		if(c == ' '){
			tempChar[index] = '\0';
			parseVector.push_back(tempChar);
			index = 0;
			tempChar = new char[15];

		}
		else if (c == '\n'){
			tempChar[index] = '\0';
			parseVector.push_back(tempChar);
			parseVector.push_back(strdup("END"));
			tempChar = new char[15];
			index = 0;
			vArray[arSize] = parseVector;
			arSize++;
			parseVector.clear();
			c = inStream.get();

		}
		else{
			tempChar[index] = c;
			index++;
		}
	}
	inStream.close();

	verify(arSize);

	//add eval to vArray
	int i,z;
	int row;
	int col;
	int spaces = 50;
	
	//remove "END" from back of vector and append evaluation result
	for(row=0; row<arSize;row++){
		vArray[row].pop_back();
		vArray[row].push_back(evaluation[row]);
	}

	char const * outFile = "parsed.txt";
	FILE *parsedFile;
    parsedFile = fopen(outFile, "w");

	for( row=0 ; row<arSize; row++){
		spaces = 50;
		for(col = 0; col < vArray[row].size();col++){
			fprintf(parsedFile,"%s ",vArray[row][col]);
			spaces -= strlen(vArray[row][col]);
			
			if((col+1 ) == vArray[row].size()-1){	
				spaces = spaces - col;
				for(i=0; i<spaces ;i++){
					fprintf(parsedFile, " ");
				}
			}
			
		}//end col for loop	
		fprintf(parsedFile,"\n");
	}
	
	//close files used
	fclose(parsedFile);
	inStream.close();
}

/**************************************************************
 * 			          VERIFY Function
 * 
 * - Accepts an integer value (size of array)
 * - Iterates the array and evaluates for proper grammar
 * 
**************************************************************/
void verify(int size) {
	int i;
	int j;
	int k;
    int spaces = 50;
	int tempSpace;

	int row;
	int col;
	char * tempCh;
	char * temp;
	int openIndex;
	int closeIndex;
	bool pFlag;
	vector <char*> evalArray[50];
	bool asn;

	//size is equal to arSize
	for (row=0; row < size;row++){
		pFlag = true;
		asn = false;

		for(col = 0; strcmp(vArray[row][col],"END") !=0; col++){
			tempCh = new char[15];
			tempCh = vArray[row][col];
			i = 0;
			while(tempCh[i]!= '\0'){	
				//save position of vector element where paranthesis start
				if(tempCh[i] == '('){	
					//openIndex = col;
					pFlag = false;
				}
				//save position of vector element where paranthesis ends
				else if(tempCh[i] == ')'){
					//paranthesis balanced
					if (pFlag == false){
						pFlag = true;
					}
					//closeIndex = col;
				}
				i++;
			}

			temp = valid(tempCh, strlen(tempCh));
			
			//if first element checked is not an ID break and check next row
			if(col == 0 && (strcmp(temp,"id") != 0)){
				evaluation[row] = strdup("-- invalid expression");
				evalArray[row].push_back(temp);
				break;
			}
		        if (strcmp(temp, "=") == 0){
				asn = true;
			}

			if(strcmp(temp,"=") == 0){
				//printf("Equals sign");
				if(col == 1){
					if (strcmp(evalArray[row][col -1],"id") != 0 ){
						evaluation[row] = strdup("-- invalid assignment");
						evalArray[row].push_back(temp);
						break;
					}
				}
				else if(col ==0 || col >1){
					if(strcmp(evalArray[row][col -1],"=") ==0){
						evaluation[row] = strdup("-- invalid expression");
						evalArray[row].push_back(temp);
						break;
					}
					else{
						evaluation[row] = strdup("-- invalid assignment");
						evalArray[row].push_back(temp);
						break;
					}
				}
			}
			//back to back op
			if(strcmp(temp,"op")==0){
				if(strcmp(evalArray[row][col -1],"op")==0){
					evaluation[row] = strdup("-- invalid expression - op op");
					evalArray[row].push_back(temp);
					break;
				}
                                else if (strcmp(vArray[row][col+1],"END") == 0){
                                        evaluation[row] = strdup("-- invalid expression");
					evalArray[row].push_back(temp);
					break;
                                }
			}
			//id
			if(strcmp(temp,"id")==0 && col!=0){	
				//back 2 back id
				if(strcmp(evalArray[row][col -1],"id") ==0 ){
					evaluation[row] = strdup("-- invalid expression - id id");
					evalArray[row].push_back(temp);
					break;
				}

				else if(strcmp(vArray[row][col+1],"END") ==0 && asn == true){
					evaluation[row] = strdup("-- invalid assignment - missing ';'");
					evalArray[row].push_back(temp);
					break;
				}
			}
			//end of line
			if (strcmp(temp,";") == 0){
				if(strcmp(vArray[row][col+1],"END") ==0 && pFlag == true && asn == true && (strcmp(evalArray[row][col -1],"id") == 0)){
					evaluation[row] = strdup("-- valid");
					evalArray[row].push_back(temp);
				}
				else{
					evaluation[row] = strdup("-- invalid assignment");
					evalArray[row].push_back(temp);
					break;
				}
			}
			//check valid expression
			else if(strcmp(vArray[row][col+1],"END") ==0 && asn == false){
				evaluation[row] = strdup("-- valid");
				evalArray[row].push_back(temp);
			}
			//if next column element is "END, and temp = ";" and assignment is true (= identified earlier);
			else if(strcmp(vArray[row][col+1],"END") ==0 && ( strcmp(temp,";") == 0) && asn == true){
				evaluation[row] = strdup("-- invalid assignment missing ';'");
				evalArray[row].push_back(temp);
			}//check validity 
			else if (strcmp(temp,"invalid")==0){	
				//25 chars 0-24
				evaluation[row] = strdup("-- invalid token ");
				for(i=0; i<strlen(tempCh);i++){
					evaluation[row][i+17]= tempCh[i];
				}
				evalArray[row].push_back(temp);
				break;
			}
			else{
				evalArray[row].push_back(temp);	
				evaluation[row] = strdup("-- valid");
			}	
		}//end for loop...increment row index
	}
}//End verify()

/***************************************************************
 * 			          VALID Function
 * 
 * - Accepts a char* and strlen(char*)
 * - Evaluates current input and checks for validity
 * - Returns a char* containing result of evaluation
 * 
***************************************************************/
char * valid(char *tempV, int size){
	int ctr = 0;
	bool intFlag = false;
	bool chFlag = true;

	while(ctr<size){
		//printf("%c",tempV[ctr]);
		//check if end of line (tempV[0] equal to ';'
		if (tempV[ctr] == ';'){
		  	if (size > 2)
				return strdup("invalid");
			else if(ctr > 0)
				return strdup("invalid");
        //printf("returning '%s'\n",tempV);
		return tempV;
		}

		//check equals
		if (tempV[ctr] == '='){
		  	if (tempV[1] != '\0'){
				//printf("= is invalid\0");
				return strdup("invalid");
			}
			else if(ctr != 0)
				return strdup("invalid");
			else
				return strdup("=");
		}
	
		//op 
		if ( tempV[ctr] == '+' || tempV[ctr] == '-' || tempV[ctr] == '/' || tempV[ctr] == '*' || tempV[ctr] == '%'){	
			
			if (size>2)
				return strdup("invalid");
			else if(ctr != 0)
				return strdup("invalid");
			else if(ctr == 0 && tempV[ctr+1]== '\0')
				return strdup("op");
		}
		if(tempV[ctr] == '('){
			if (tempV[1] == '\0')
				return strdup("invalid");
			else
				ctr++;
		}
		//char a-z or A-Z range
		else if ( (tempV[ctr] > '`' && tempV[ctr] < '{') || ( tempV[ctr] > '@' && tempV[ctr] < '[')){	
			intFlag = false;
			if((ctr+1)== size)
				return strdup("id");
			else
				ctr++;
		}
		//digits
		else if(tempV[ctr] > '/' && tempV[ctr] < ':'){
		    //check if digit is the first character read	
			if(ctr == 0){
				intFlag = true;
				//single digit integer
				if (tempV[1] == '\0'){
					return strdup("integer");
				}
				//if the following character is a digit, increment ctr
				else if((tempV[ctr+1] > '/' && tempV[ctr+1] < ':')){
					ctr++;
				}
				//else if digit is first and next is char return invalid
				else if((tempV[ctr+1] > '`' && tempV[ctr+1] < '{') || ( tempV[ctr+1] > '@' && tempV[ctr+1] < '['))
					return strdup("invalid");
			}
			//if there is another integer after ctr > 0
			else if((tempV[ctr+1] > '/' && tempV[ctr+1] < ':')){
				ctr++;
			}
			else if (tempV[ctr+1] == '\0'){
				if(intFlag){
					return strdup("integer");
				}
				else{
					return strdup("id");
				}		
			}
			//else if ctr > 1 and integer is true but it find a character 
			else if(intFlag == true && ((tempV[ctr+1] > '`' && tempV[ctr+1] < '{') || ( tempV[ctr+1] > '@' && tempV[ctr+1] < '['))){
				return strdup("invalid");
			}
			//else if the integer flag is false, continue reading characters
			else if ((tempV[ctr+1] > '`' && tempV[ctr+1] < '{') || ( tempV[ctr+1] > '@' && tempV[ctr+1] < '[')){
				ctr++;
			}
			else if(ctr+1 == size){
				if(intFlag){
					return strdup("integer");	
				}
				else{
					return strdup("id");
				}
			}	
			else{	
				return strdup("id");
			}
		}
		else if(tempV[ctr] == ')'){
			if (tempV[ctr+1] != '\0')
				return strdup("invalid");
			else if(ctr == 0)
				return strdup("invalid");
			else{
				ctr++;
			}
		}
		else{
			return strdup("invalid");
		}
	}
//if tempV is a valid combination of ids (char followed by combo of digit and chars) it exits the while loop and returns id
return strdup("id");
}//end valid()

/************************************
 * 			    MAIN
*************************************/
int main(int argc, char *argv[]) {
    char * filename;

	if(argc>=2){
		ifstream ifile(argv[1]);
		//Error check for whether or not the designated file is accessible or present
		if (!ifile){
			printf("Error: File may not exist or may not be accessible.\n");
			return 0;
		}
		filename = argv[1];
	}
    else{
        filename = strdup("statements.txt");
    }

	parseFile(filename);
    printf("\n- Created parsed.txt file in cwd.\n");
	printf("- Please use cat -v parsed.txt to properly view the created file.\n");
	printf("\n                             **OR**\n\n");
	printf("- Consult the README.txt for the 'sed' command that removes the ^M\n");
	printf("  characters from parsed.txt and allows for cleaner readability.\n\n");

    return 0;
}
