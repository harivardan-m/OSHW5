#include "types.h"
#include "stat.h"
#include "user.h"

char buffer[1024];
char line[1024]; // Stores the current line being processed
char previousLine[1024]; // Stores the previous line that was processed
int caseInsensitive, deleteDuplicate, ignoreEmptyLines; // Flags to control behavior
// Function to determine if the current line is the same as the previous line
int isSameLine(){
	int sameLine, j;
	sameLine = 1;
	j = 0;
	while(line[j]!='\0'){
		if(caseInsensitive){int currentChar, alternateChar, previousChar;
			currentChar = (int) line[j];
			if(currentChar>=65 && currentChar<=90){
				alternateChar = currentChar+32;
			}else if(currentChar>=97 && currentChar<=122){
				alternateChar = currentChar-32;
			}else{
				alternateChar = currentChar;
			}
			previousChar = (int)previousLine[j];
			
			if(previousChar!=currentChar && previousChar!=alternateChar){
				sameLine = 0;
			}
			}else{
			if(line[j]!=previousLine[j]){
				sameLine = 0;
			}
		}
		j++;
	}
	return sameLine;
}

void storeLine(){
	
	memset(previousLine,'\0',sizeof(previousLine));
	int k = 0;
	while(line[k]!='\0' && k<sizeof(previousLine)){		
		previousLine[k] = line[k];
		k++;
	}
	memset(line,'\0',sizeof(line));
}

void printPreviousLine(int totalLine){
	
	if(deleteDuplicate){
		if(!(ignoreEmptyLines && totalLine<=1)) printf(1,"\t%d %s",totalLine,previousLine);
	}else{
		if(!(ignoreEmptyLines && totalLine<=1)) printf(1,"%s",previousLine);
	}
	
}

void uniq(int fileDescriptor, char *fileName){
	int i,n,linePointer,currentLineCount, isFirstLine;


	memset(previousLine,'\0',sizeof(previousLine));
	memset(line,'\0',sizeof(line));


	linePointer = 0;
	currentLineCount = isFirstLine = 1;

	while((n = read(fileDescriptor, buffer, sizeof(buffer))) > 0){
		for(i=0;i<n;i++){
			
			line[linePointer] = buffer[i];
			
			if(buffer[i]=='\n'){
				linePointer = 0;
				int isSame = 0;
				//compare line to previousLine
				isSame = isSameLine();

				if(isSame){//if same line
					currentLineCount ++;//add line count
					memset(line,'\0',sizeof(line));
				}else{//if not same line
					if(isFirstLine){
						storeLine();
						isFirstLine = 0;
					}else{
						printPreviousLine(currentLineCount);
						storeLine();
					}
					currentLineCount = 1;//reset line count
				}

			if(i+1>=n){//last line
					printPreviousLine(currentLineCount);
				}	
				
			}else{
				linePointer ++;
			}
		}
	}
		if(n<0){
		printf(1,"uniq: read error\n");
		exit();
	}
}

int main(int argc, char *argv[]){
  int i, fileDescriptor;
  

  caseInsensitive = deleteDuplicate = ignoreEmptyLines = 0; // initialize flags to false

  // Parse command line arguments
  for(i = 1; i < argc; i++){
    if(argv[i][0] == '-'){
      if(argv[i][1] == 'i'){ // case-insensitive flag
        caseInsensitive = 1;
      }
      else if(argv[i][1] == 'c'){ // delete duplicate flag
        deleteDuplicate = 1;
      }
      else if(argv[i][1] == 'd'){ // ignore empty lines flag
        ignoreEmptyLines = 1;
      }
      else{
        printf(1, "uniq: invalid option -- '%c'\n", argv[i][1]);
        exit();
      }
    }
     else{
      break;
    }
  }

  if(i == argc){ // read from standard input
    fileDescriptor = 0;
    uniq(fileDescriptor, "");
  }
   else{
    for(; i < argc; i++){ // read from files
      if((fileDescriptor = open(argv[i], 0)) < 0){
        printf(1, "uniq: cannot open %s\n", argv[i]);
        exit();
      }
      else{
        uniq(fileDescriptor, argv[i]);
        close(fileDescriptor);
      }
    }
  }

  exit();
}