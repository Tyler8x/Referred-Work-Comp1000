#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <map>
#include <string>
using namespace std;

//See bottom of main
int findArg(int argc, char* argv[], string pattern);


/*
 *
 * The user can launch application as follows:
 *
 * TaskA <filename> <search term> [-regex]
 * 
 * <database file>              REQUIRED. Specifies the file to search (required). This is ALWAYS the first parameter. The file must exist in order to be searched
 * <search term>                REQUIRED. The search term as either a single word or a regular expression. 
                                This is a single word, made up of alpha-numeric characters only.
 * -regex                       OPTIONAL. If this flag is present, then the search term is a regular expression (as opposed to a single word). 
                                It must be a valid regex expression.
 *
 * ****************
 * *** EXAMPLES ***
 * ****************
 *
 * TaskA lorum.txt comp1000             Searches for the string comp1000 in the file lorum.txt
 * TaskA lorum.txt "^(\\d)\\d" -regex   Searches the file lorum.txt for all patterns that match the regular expression "^(\\d)\\d" 
 * TaskA lorum.txt -regex "^(\\d)\\d"   Searches the file lorum.txt for all patterns that match the regular expression "^(\\d)\\d" 
 * TaskA lorum.txt                      Error - search expression provided
 * 
 * *************
 * *** NOTES ***
 * *************
 *
 * o Try to write your code such that is can be reused in other tasks.
 * o Code should be consistently indented and commented
 * o Consider error conditions, such as missing parameters or non-existent files
*/


int main(int argc, char* argv[])
{
    // argv is an array of strings, where argv[0] is the path to the program, argv[1] is the first parameter, ...
    // argc is the number of strings in the array argv
    // These are passed to the application as command line arguments
    // Return value should be EXIT_FAILURE if the application exited with any form of error, or EXIT_SUCCESS otherwise

    if (argc == 3) {
        //Welcome message
        cout << "TaskA (c)2024" << endl;

        //BASIC EXAMPLE: Get parameters for the simple case
        string fileName(argv[1]);
        string searchString(argv[2]);

        //Confirm
        cout << "TaskA " << fileName << " " << searchString << endl;

        //stuff i've added
        string fileContents;
        ifstream file(fileName);
        if (!file.is_open()) {
            //when can't find file, display error message and return
            cerr << "File not found" << endl;
            return 1;
        }

        string line;
        //iterate over every line in file, appending them to the contents string
        while (getline(file, line)) {
            fileContents.append(line);
        }

        //output entire file to console
        cout << fileContents << endl;

        //this is for iterating over the whole file to remove any punctuation
        //instantiate string that will contain all non-punctuation characters
        string cleanedContents;

        //iterate over each character in the string
        for (int i = 0; i < fileContents.size(); i++) {
            //append the character to the cleanedContents string if not punctuation
            if (!ispunct(fileContents[i])) {
                //append it lowercase to avoid the same problem with capitalization making the same word not equal
                cleanedContents = cleanedContents + (char)tolower(fileContents[i]);
            }
        }


        stringstream cleanedContentsStream(cleanedContents);


        string token;
        //initialise a vector that will hold every word, or 'token' after splitting the string
        vector<string> tokens;
        //delimiter is the character to split the string on, in this case ' ' to find each individual word
        char delimiter = ' ';

        //continually fetch subsequent tokens from stringstream and add them to the end of the vector
        while (getline(cleanedContentsStream, token, delimiter)) {
            tokens.push_back(token);
        }

        //this part is to convert the search string all lowercase, to match the cleanedContents we turned all lowercase earlier
        //initialise a new string to append all the lowercased chars to
        string cleanedSearchString;
        //iterate over every char in original search string
        for (int i = 0; i < searchString.size(); i++) {
            char x(searchString[i]);
            //append lowercased char to cleaned search term
            cleanedSearchString = cleanedSearchString + (char)tolower(x);
        }

        //this part is to iterate over every token i.e every word in the cleaned file contents, and increment a counter every time a
        //match to the search term is found
        //initialise counter as 0
        int searchStringFrequency(0);
        //iterate over every token in the vector
        for (int i = 0; i < tokens.size(); i++) {
            //if the current token matches the cleaned search term, increment counter
            if (tokens[i] == cleanedSearchString) {
                searchStringFrequency++;
            }
        }

        //output results
        cout << "Found string: '" << searchString << "' a total of " << searchStringFrequency << " times." << endl;

        // end of stuff i've added
        //Done
        return EXIT_SUCCESS;
    }

    //EXAMPLE: Scan command line for -regex switch
    int p = findArg(argc, argv, "-regex");
    if (p) {
        cout << "The search term is a regular expression. See https://www.softwaretestinghelp.com/regex-in-cpp/ for examples of how to do this " << endl;
    }

    //**************************************************************
    //You could continue here :)
    //**************************************************************

    return EXIT_SUCCESS;
}

// Find an argument on the command line and return the location
int findArg(int argc, char* argv[], string pattern)
{
    for (int n = 1; n < argc; n++) {
        string s1(argv[n]);
        if (s1 == pattern) {
            return n;
        }
    }
    return 0;
}
