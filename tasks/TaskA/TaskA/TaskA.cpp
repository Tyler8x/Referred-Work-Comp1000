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
int findMatch(vector<string>& tokens, string& searchTerm, int& lineNumber);
string cleanText(string& text);
vector<string> tokenize(string& text);

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

        string cleanedSearchString = cleanText(searchString);
        string line;
        int lineCount(1);
        //iterate over every line in file, appending them to the contents string
        while (getline(file, line)) {
            string cleanedContents = cleanText(line);
            vector<string> tokens = tokenize(cleanedContents);
            findMatch(tokens, cleanedSearchString, lineCount);
            lineCount++;
        }
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

int findMatch(vector<string>& tokens, string& searchTerm, int& lineNumber) {
    //iterate over every token in the vector
    for (int i = 0; i < tokens.size(); i++) {
        //if the current token matches the cleaned search term, increment counter
        if (tokens[i] == searchTerm) {
            cout << "Search term found on line " << lineNumber << ", word " << i + 1 << endl;
        }
    }
    return 0;
}
string cleanText(string& text) {
    //this part is to convert the text all lowercase and remove all punctuation
    //initialise a new string to append all the lowercased chars to
    string cleanedText;
    //iterate over every char in original text
    for (int i = 0; i < text.size(); i++) {
        //check if the character is punctuation or not
        if (!ispunct(text[i])) {
            char x(text[i]);
            //append lowercased char to cleaned text
            cleanedText = cleanedText + (char)tolower(x);
        }
    }
    return cleanedText;
}

vector<string> tokenize(string& text) {
    string token;
    //initialise a vector that will hold every word, or 'token' after splitting the string
    vector<string> tokens;
    //delimiter is the character to split the string on, in this case ' ' to find each individual word
    stringstream textStream(text);
    char delimiter(' ');
    //continually fetch subsequent tokens from stringstream and add them to the end of the vector
    while (getline(textStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}