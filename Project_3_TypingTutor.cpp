
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>
#include <iterator>
#include <iomanip>
using namespace std;

// Initialize variables.
const int NMISP = 5;
const int RNG_RANGE = 100;

// This function displays the header of the program.
void display_header(const int ndict, const int nmiss)
{
  // Outputs header.
  cout << "*** Typing Tutor"<< endl;
  cout << "There are " << ndict << " words in the dictionary." << endl;
  cout << "There are " << nmiss << " commonly misspelled words." << endl;
}

// This function displays the menu options of the program.
void display_menu_options()
{
    cout << endl << "*** Select a menu option:" << endl
         << "1. Spell commonly misspelled words" << endl
         << "2. Type random words from the full dictionary" << endl
         << "3. Display some words from one of the lists" << endl
         << "4. Use binary search to lookup a word in the dictionary" << endl
         << "5. Exit the program." << endl
         << "Your choice: ";
}

// This function takes two integers n and max as input parameters, and returns a vector of size n filled with random integers.
vector<int> randn(const int n, const int max)
{
    vector<int> vect; // Create and initialize vector vect.
  
    for (int i = 0; i < n; i++) // The loop will run n times.
    {
    // Generates a random integer between 0 and RAND_MAX, then takes the remainder by dividing that integer by max.
    // The result is an integer between 0 and max, which is pushed into the vector.
    vect.push_back(rand() % (max + 1)); 
    }
    return vect; // Returns the vector filled with random integers.
}

// This function takes in a reference to a string called "src_file" and returns an ifstream object.
ifstream open(const string& src_file)
{
    ifstream src{src_file};

    // Create a new ifstream object called "src" and initialize it with the value of "src_file".
    if (!src.is_open()) {
      
        // If the file was not opened, print an error message to the console indicating that the file could not be found.
        cout << "Could not find file " << src_file << "." << endl;

        // Exit the program with an error code of 1.
        exit(1);
    }
    // If the file was successfully opened, return the ifstream object.
    return src;
}

// This function extracts words from a file and adds them to a vector of strings passed in as reference.
void extract_dict(vector<string>& dst, const string& src_file)
{
  // Reads in number of words for header from dictionary.txt using the ifstream function.
  ifstream dict_extract;
  dict_extract.open(src_file);

  // Create a string to hold each line of the file.
  string file_string;

  /* First, we use the function 'get_line' to read lines from a file called dict_extract, which we
     declared earlier. Next, we can see that each line of the file is stored as a string variable      
     called 'file_string'. The for loop iterates over each line of the file, and for each line in
     the file, it adds the line to a vector called 'dst' using the 'push_back' function. The 'dst'
     vector is passed into the function as a reference, so changes made to it will persist             
     outside the function.
  */

  for(string i; getline (dict_extract, file_string);)
  {
    dst.push_back(file_string);
  }
}

// This function extracts misspelled words and their correct versions from a file and stores them in two separate vectors.
void extract_misspelled(vector<string>& misspelled, vector<string>& correct,const string& src_file)
{
    // Reads in number of words for header from misspelled.txt using the ifstream function.
    ifstream misspelled_extract;
    misspelled_extract.open(src_file);

    // Create a string to hold each line of the file.
    string file_string;

    // Read each line of the file.
    while (getline(misspelled_extract, file_string)) {

        // Use istringstream to extract the misspelled word and correct version.
        istringstream iss(file_string);
        string misspelled_word, correct_word;
        iss >> misspelled_word >> correct_word;

        // Add misspelled word and correct version to their respective vectors.
        misspelled.push_back(misspelled_word);
        correct.push_back(correct_word);
    }
}

// This function takes two arguments:
// 1. a vector of strings (src) which contains the elements to be displayed.
// 2. a vector of integers (positions) which contains the indices of the elements to be displayed.
void display_elems(const vector<string>& src, const vector<int>& positions)
{
    // Loop through the positions vector (int) and print out the elements in the src vecor at those indices (positions).
    for (int i = 0; i < positions.size(); i++)
      {
        cout << src[positions[i]];
        if (i != positions.size() - 1) // Prints a space after each element except for the last one.
          cout << " ";
      }
}

void extract_spelling_answers(vector<string>& dst, const vector<string>& correct,const vector<int> positions)
{
    // Loop through the positions vector (int) and print out the elements in the src vecor at those indices (positions).
    for (int i = 0; i < positions.size(); i++)
      {
        int pos = positions[i]; // At each iteration we retrieve the index 'pos' from 'positions'.
        dst.push_back(correct[pos]); // Then, we use the previous line to access the corresponding element from 'correct' vector.
      }                              // Finally, we add this element to the end of 'dst' vector using push_back method.
}

// This function takes in three parameters, 
// 1. A destination vector of strings.
// 2. A string to grade.
// 3. A vector of correct spellings.
void extract_spelling_mistakes(vector<string>& dst, const string& to_grade,const vector<string>& correct)
{
    // Clear the destination vector.
    dst.clear();
    
    // Create a string stream from the user's answer.
    istringstream iss(to_grade);
    
    // Loop over each word in the user's answer.
    string word;
    int i = 0;
    while (iss >> word)
    {
      // Check if the word is misspelled.
      if (word != correct[i])
      {
        // Add the misspelling to the destination vector.
        dst.push_back(word + " -> " + correct[i]);
      }
        i++;
    }
}

// This function takes in two parameters, a vector of misspelled words and the total number of words.
void report_misspell_mistakes(const vector<string>& mistakes,const int num_words)
{
    // Math for score calculation.
    int num_incorrect = mistakes.size();
    int num_correct = num_words - mistakes.size();
  
    int correct_score = num_correct * 3;
    int incorrect_score = num_incorrect * 6;
  
    int score = correct_score - incorrect_score;

    // The functions first print outs the number of misspelled words.
    if (mistakes.empty()) 
    {
      cout << "No misspelled words!" << endl;
    } 
    else 
    {
      cout << "Misspelled words: " << endl;
      for (const auto& mistake : mistakes) 
      {
        cout << "    " << mistake << endl; // Next, the function prints out each mistake in the vector 'mistakes' with a bullet point preceding it.
      }
    }
    // Print out the score breakdown and total score.
    cout << endl << correct_score << " points: " << num_correct << " spelled correctly x 3 points for each." << endl;
    cout << incorrect_score << " point penalty: " << num_incorrect << " spelled incorrectly x -6 points for each." << endl;
    cout << "Score: " << score << endl;
}

// This function takes in two parameters, a vector of source words and a vector of positions.
void evaluate_user_misspells(const vector<string>& src, const vector<int>& positions)
{
    // Get user input.
    string input;
    getline(cin, input);

    // Declare vectors.
    vector<string> mistakes;
    vector<string> answers;

    // With the src vector (of words -- full dict or misspelled).
    extract_spelling_answers(answers, src, positions);

    // With correct answers and the user input, store mistypes in vector mistakes.
    extract_spelling_mistakes(mistakes, input, answers);

    // With the mistakes and the answers, output the message with the score calculations.
    report_misspell_mistakes(mistakes, positions.size());
  }

// This function takes in two vectors of strings called "mspelled" and "correct".
void misspelled(const vector<string>& mspelled, const vector<string>& correct)
{
    // Print a message to the console indicating that commonly misspelled words are being used.
    cout << "\n*** Using commonly misspelled words." << endl;

    // Create a new vector of integers called "misspelled" that contains a random selection of indexes into the "mspelled" vector.
    vector<int>misspelled  = randn(NMISP, mspelled.size() - 1);

    // Call the "display_elems" function to display the misspelled words to the user.
    display_elems(mspelled, misspelled);

    // Print a message to the console asking the user to type the words above with the correct spelling.
    cout << "\nType the words above with the correct spelling:" << endl;

    // Call the "evaluate_user_misspells" function to evaluate the user's responses.
    evaluate_user_misspells(correct, misspelled);
}

// This function takes in a vector of strings called "dict".
void full_dict(const vector<string>& dict)
{
    // Create a new vector of integers called "misspelled" that contains a random selection of indexes into the "dict" vector.
    vector<int>misspelled = randn(NMISP, dict.size() - 1);

    // Print a message to the console indicating that the full dictionary is being used.
    cout << "\n*** Using full dictionary." << endl;

    // Call the "display_elems" function to display the selected words to the user.
    display_elems(dict, misspelled);

    // Print a message to the console asking the user to correctly type the words that were displayed.
    cout << "\nCorrectly type the words above: " << endl;

    // Call the "evaluate_user_misspells" function to evaluate the user's responses.
    evaluate_user_misspells(dict, misspelled);
}

void display_words_prompt()
{
    // This displays the data set choices for menu option 3
    cout << endl << "*** Displaying word list entries." << endl
         << "Which words do you want to display?" << endl
         << "A. Dictionary of all words" << endl
         << "B. Commonly misspelled words (wrongly spelled)" << endl
         << "C. Commonly misspelled words (correctly spelled)" << endl
         << "Your choice: ";
}

// This function takes in a vector of strings called "data".
void print_range(const vector<string>& data)
{
    // Declare three integer variables for the start index, end index, and range.
    int start_range;
    int end_range;
    int range = data.size() - 1;

    // Print a message to the console asking the user to enter the start and end indices for the range of elements to print.
    cout << "*** Enter the start and end indices between 0 and " << range << ": ";
    cin >> start_range >> end_range;

    // If the user enters invalid input (i.e., the end index is before the start index or the indices are out of range), print an error message to the console.
    if ((start_range < 0) || (end_range > range - 1))
    {
      cout << "The end index must come after the start, and the indices must be in range." << endl;
    }
    // Otherwise, iterate over the range of indices and print each element and its index to the console.
    else
    {
      for (int i = start_range; i <= end_range; i++)
      {
        cout << i << ". " << data.at(i) << endl;
      }
    }
}

// This function takes in three vectors of strings: "dict", "mspelled", and "correct".
void display_in_range(const vector<string>& dict, const vector<string>& mspelled, const vector<string>& correct)
{

void display_in_range(const vector<string>& dict, const vector<string>& mspelled, const vector<string>& correct);

    // Print a message to the console indicating that the function will display word list entries, and give the user a choice of which words to display.
    cout << endl << "*** Displaying word list entries." << endl;
    cout << "Which words do you want to display?" << endl;
    cout << "A. Dictionary of all words" << endl;
    cout << "B. Commonly misspelled words (wrongly spelled)" << endl;
    cout << "C. Commonly misspelled words (correctly spelled)" << endl;
    cout << "Your choice: ";

    // Declare a character variable called "let" and read the user's input into it.
    char let;
    cin >> let;

    // Use a switch statement to determine which vector of strings to print based on the user's input.
    switch(toupper(let))
    {
        // If the user enters 'A', print the entire dictionary using the "print_range" function.
        case 'A':
            print_range(dict);
            break;
        // If the user enters 'B', print the commonly misspelled words (with errors) using the "print_range" function.
        case 'B':
            print_range(mspelled);
            break;
        // If the user enters 'C', print the commonly misspelled words (with corrections) using the "print_range" function.
        case 'C':
            print_range(correct);
            break;
    }
}

// This function performs a binary search on a sorted vector of strings to find a specific target string.
void bsearch(const vector<string>& data)
{
    // Declare a string variable to store the user's search target.
    string target;

    // Prompt the user to enter the search target and store it in the `target` variable.
    cout << "*** Enter word to search: ";
    cin >> target;

    // Declare integer variables for the middle, lower, and upper indices of the search range, and a count variable to keep track of the number of comparisons.
    int middle;
    int lower;
    int higher;
    int count = 1;

    // Set the `lower` and `higher` variables to the start and end indices of the `data` vector, respectively.
    lower = 0;
    higher = data.size();

    // Enter a while loop that continues as long as there are indices to search.
    while (higher > lower)
    {
      // Calculate the middle index.
      middle = (lower + higher) / 2;

    // Print out the current count and the string being compared.
    cout << setw(5) << count << ". Comparing to: " << data.at(middle) << endl;
    count++;

    // If the middle string is less than the target, adjust the lower index to the middle plus one.
    if (data.at(middle) < target)
    {
      lower = middle + 1;
    }
    // If the middle string is greater than the target, adjust the higher index to the middle.
    else if(data.at(middle) > target)
    {
      higher = middle;
    }
    // If the middle string is equal to the target, print out a message and return.
    else
    {
      cout << target << " was found." << endl;
      return;
    }
  }
   // If the target string was not found, print out a message indicating so.
   cout << target << " was NOT found." << endl;
}

// This function extracts all the data from files and stores it in three vectors: `dict`, `mspelled`, and `correct`.
void extract_all_data(vector<string>& dict, vector<string>& mspelled,
                    vector<string>& correct)
{
    // Extract the dictionary data from "dictionary.txt" and store it in the `dict` vector.
    extract_dict(dict, "dictionary.txt");

    // Extract the misspelled and correctly spelled data from "misspelled.txt" and store them in the `mspelled` and `correct` vectors, respectively.
    extract_misspelled(mspelled, correct, "misspelled.txt");
}

int main()
{
    // Seed the random number generator with a fixed value for reproducibility.
    srand(1);

    // Initialize vectors to hold dictionary data.
    vector<string> dict, mspelled, correct;

    // Extract all data from files and store in corresponding vectors.
    extract_all_data(dict, mspelled, correct);

    // Display the header message with the total number of words.
    display_header(dict.size(), correct.size());

    // Prompt user to choose an option and loop until user chooses to exit or input is ended.
    unsigned int choice;
    do {
        display_menu_options(); // display the menu options.
        cin >> choice; // read user input choice.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining characters in the input buffer.

        // Execute the corresponding function based on the user's choice.
        switch (choice) {
        case 1:
            misspelled(mspelled, correct); // test the user on commonly misspelled words.
            break;
        case 2:
            full_dict(dict); // test the user on the full dictionary.
            break;
        case 3:
            display_in_range(dict, mspelled, correct); // display a range of words from the dictionary or misspelled word list.
            break;
        case 4:
            bsearch(dict); // search for a word in the dictionary using binary search.
            break;
        case 5:
            cout << "Exiting." << endl; // exit the program.
            break;
        default:
            cout << "No menu option " << choice << ". "
                 << "Please try again." << endl; // prompt the user to try again if an invalid choice is entered.
        }
    } while ((choice != 5) && !cin.eof()); // loop until user chooses to exit or input is ended.

    return 0;
}
