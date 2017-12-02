#include <fstream>
#include <string>
#include "../game/Game.h"

using namespace std;


static void createGoldenDataSet(const string& outFile,const int iteration) {
    std::ofstream out(outFile);
    auto originalOutStream = std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out!

    char const* args[2];
    for (int i = 0; i<iteration;i++){
        auto iStr = to_string(i);
        args[1]=iStr.c_str();
        gameRunner(2,args);
    }//for

    //restore the original cout
    std::cout.rdbuf(originalOutStream);
    out.close();
}

static bool fileAreEqual(const string &goldenFile, const string &testFile) {

    ifstream expected(goldenFile);
    ifstream test(testFile);

    string expectedLine,testLine;

    while(expected){
        getline(expected,expectedLine);
        getline(test,testLine);
        if(expectedLine!=testLine){
            cout<<"expected:"<<expectedLine<<"\nfound:"<<testLine;
            return false;
        }
    }

    return true;

}

using namespace std;

static bool exist(const string& file){
    return ifstream(file).good();
}

int main(int argc,char *args[]){
    //file where store the original execution output
    constexpr auto goldenFileName("goldenOut.txt");
    //file where store the current execution output
    constexpr auto testFileName("currentOut.txt");
    //number of game to run
    constexpr auto testIteration(100);

    if (exist(goldenFileName)) {
        //run the current game implementation and store in testFileName
        createGoldenDataSet(testFileName, testIteration );
        //compare with the reference output
        return fileAreEqual(goldenFileName, testFileName) ? EXIT_SUCCESS : EXIT_FAILURE;
    }else {
        cout<<"Generate the reference output\n";
        createGoldenDataSet(goldenFileName, testIteration);
        cout<<"Reference test created\n";
        return EXIT_FAILURE; //fail since we didn't run any test
    }
}


