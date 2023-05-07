#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define DEAFULT 10
#define CODE_ONE -111
#define CODE_TWO -222

char buf[1024];

int print_counter(char* argvs[]) {
    char** argv = argvs;
    int i = 1;
    char number[100];

    if(argv[1][0] == '-') {
        for(i=1; i<strlen(argv[1]);i++) {
            if(((int)(argv[1][i]))>=48 && ((int)(argv[1][i]))<=57) {
                number[i-1] = argv[1][i];
            }
            else {
                return CODE_ONE; // Illegal Option
            }
        }
        int linesToDisplay = (atoi)(number);
        return linesToDisplay;
    }
    else {
        for(i=0; i<strlen(argv[1]);i++) {
            if(((int)(argv[1][i]))>=48 && ((int)(argv[1][i]))<=57) {
                number[i] = argv[1][i];
            }
            else {
                return CODE_TWO;
            }
        }
        return CODE_TWO;
    }
}

void tail(int fd, int linesToPrint)
{
    int i, n;
    int filelines = 0;
    int tempfilelines = 0;
    int linesToPrintFn = linesToPrint;
    int indexstart;

    int tempFile = open("tempTailFile",O_CREATE | O_RDWR);

  // writing to a temporary location
    while((n = read(fd, buf, sizeof(buf))) > 0){
        write(tempFile, buf, n);
        for(i=0; i<n; i++){
            if(buf[i] == '\n')
                filelines++;
        }
    }
    close(tempFile);

    indexstart = filelines - linesToPrintFn;

    //opening to read the lines
    tempFile = open("tempTailFile", O_RDONLY);
    while((n = read(tempFile, buf, sizeof(buf))) > 0) {
        for(i=0; i<n; i++) {
            if(tempfilelines >= indexstart) {
                printf(1, "%c", buf[i]);
            }
            if(buf[i] == '\n') {
                tempfilelines++;
            }
        }
    }
    //removing the temp file
    unlink("tempTailFile");
}

int main(int argc, char *argv[]) {
    int fd, linecount;
    //To take command line inputs
    if(argc <= 1) {
        tail(0,DEAFULT);
        exit();
    }

    else if(argc == 2) {

        linecount = print_counter(argv);
        fd = open(argv[1], O_RDONLY);

        
        //for handling tail README
        if(fd >= 0) {
            tail(fd, DEAFULT);
            close(fd);
            exit();
        }
        
        // In cases where a file cannot be opened and the parameter following the "tail" command begins with a dash and is not a valid number.
        else if ((fd < 0) && (linecount == CODE_ONE)) {
            printf(1, "No such options\n");
            exit();
        }

        //When it's not possible to open a file and there is an issue with the parameter
        else if(fd < 0 && linecount == CODE_TWO) {
            printf(1, "unable to open file: %s\n", argv[1]);
            exit();
        }

        // For handling commands like cat README | tail -2
        else if((fd < 0) && ((linecount%2 == 0) || (linecount%2 == 1))) {
            tail (0,linecount);
            exit();
        }
        // When the file is not readable
        else if (fd < 0) {
            printf(1, "unable to open file: %s\n", argv[1]);
        }
    }

    else if(argc == 3) {

        linecount = print_counter(argv);

        if((fd = open(argv[2], O_RDONLY)) < 0){
            printf(1, "unable to open file: %s\n", argv[2]);
            exit();
        }
       //If the parameter after "tail" is incorrect and the value is -111, an Illegal Option error will be displayed
        if(linecount == CODE_ONE) {
            printf(1, "No such options\n");
            exit();
        }
        linecount = ((linecount == CODE_TWO) ? DEAFULT : linecount);
            tail(fd, linecount);
            close(fd);
            exit();     
    } 
    else {
        printf(1, "unable to open file: %s\n", argv[2]);
        exit();
    }
    exit();
}