#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "../game/game.h"

static void runGame(const int nIteration){
    char *args[2];
    char numberBuff[8];
    args[0]=NULL;
    args[1]=numberBuff;

    for (int i = 0; i<nIteration;i++){
        sprintf(numberBuff,"%d",i);
        args[1]=numberBuff;
        run_game(2,args);
    }//for

}

static void createGoldenDataSet(const char *outFile,const int iteration) {

    FILE *out = fopen (outFile, "w");

    if(out==NULL){
        fprintf(stderr,"error opening the file %s (%d)",outFile,errno);
        exit(EXIT_FAILURE);
    }
    fflush(stdout);//flush the original stdout to be secure to have a clean situation
    //copy stdout
    int origStdout = dup(STDOUT_FILENO);
    //change stdout to out
    dup2(fileno(out),STDOUT_FILENO);

    runGame(iteration);

    //close out
    fflush(stdout);
    fclose(out);

    //restore stdout
    dup2(origStdout,STDOUT_FILENO);

}

static long fileSize(FILE *f){
    // Seek the last byte of the file
    fseek(f, 0, SEEK_END);
    // Offset from the first to the last byte, or in other words, filesize
    long int fileSize = ftell(f);
    // go back to the start of the file
    rewind(f);
    return fileSize;
}

static int fileAreEqual(const char *goldenFile, const char *testFile) {

    FILE *golden = fopen(goldenFile,"r");
    FILE *test = fopen(testFile,"r");

    if(golden == NULL || test == NULL){
        fprintf(stderr,"error opening the files\n");
        exit(EXIT_FAILURE);
    }

    long goldenLen = fileSize(golden);
    long testLen = fileSize(test);

    if(goldenLen != testLen){
        fprintf(stderr,"file size are different\n");
        fclose(golden);
        fclose(test);
        return false;
    }

    char *goldenBuf = calloc(goldenLen+1,sizeof(char));
    char *testBuf = calloc(testLen+1, sizeof(char));

    fread(goldenBuf, sizeof(char),goldenLen,golden);
    fread(testBuf, sizeof(char),testLen,test);

    goldenBuf[goldenLen]='\0';
    testBuf[testLen]='\0';

    int ret = strncmp(goldenBuf,testBuf,goldenLen);

    free(goldenBuf);
    free(testBuf);

    fclose(golden);
    fclose(test);

    return ret == 0;
}


static int exist(const char* file){
    return access(file,R_OK)==0;
}

int main(int argc,char *args[]){
    //file where store the original execution output
    const char* goldenFileName = "goldenOut.txt";
    //file where store the current execution optuput
    const char* testFileName = "currentOut.txt";
    //number of game to run
    const int testIteration = 100;

    if (exist(goldenFileName)) {
        //run the current game implementation and store in testFileName
        createGoldenDataSet(testFileName, testIteration );
        //compare with the reference output
        return fileAreEqual(goldenFileName, testFileName) ? EXIT_SUCCESS : EXIT_FAILURE;
    }else {
        printf("Generate the reference output\n");
        createGoldenDataSet(goldenFileName, testIteration);
        printf("Reference test created\n");
        return EXIT_FAILURE; //fail since we didn't run any test
    }
}


