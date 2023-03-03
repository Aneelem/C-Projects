/**------------------------------------------
    Program 2: Great 13

    Course: CS 141, Spring 2023
    System: Linux x86_64 and G++
    Author: Meleena Torres
 ---------------------------------------------**/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <map>
#include <string>

using namespace std;

// Function that displays the instructions to the user

void display_instructions()
{
    cout << "Class: CS 141" << endl
         << "Program 2: Great 13" << endl << endl
         << "Make a series of jumps until there is a single piece left" << endl
         << "anywhere on board. On each move you must jump an adjacent" << endl
         << "piece   into   an  empty  square,  jumping  horizontally," << endl
         << "vertically, or diagonally." << endl << endl
         << "Input of 'R' resets the board back to the beginning, and " << endl
         << "'X' exits the game." << endl;
}

// The internal representation of the board as an array. Do not modify directly.

char board[13]{};

/* These two functions are how you will get and set elements on the board. Only
use these two when changing, or reading the board. */

char get_element(char position)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to get element at position " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    return board[position - 'A'];
}

void set_element(char position, char value)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to set element at postion " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    board[position - 'A'] = value;
}

// print out the board with the legend on the right

void display_board()
{
    cout << endl;
    cout << setw(7) << "Board" << setw(12) << "Position" << endl;
    cout << setw(5) << board[0] << setw(11) << 'A' << endl
         << setw(3) << board[1] << ' ' << board[2] << ' ' << board[3]
         << setw(11) << "B C D" << endl
         << board[4] << ' ' << board[5] << ' ' << board[6] << ' '
         << board[7] << ' ' << board[8] << ' '
         << " E F G H I" << endl
         << setw(3) << board[9] << ' ' << board[10] << ' ' << board[11]
         << setw(11) << "J K L" << endl
         << setw(5) << board[12] << setw(11) << 'M' << endl;
    cout << endl;
}

/* This is the end of the starter code, and below is where you can
add your own code. Feel free to add helper functions or variables.
*/

/* forward declarations for the functions you will write later. This
is so the order of the function definitions, in this file,  does not
matter. */

void make_move();
void initialize_board();
bool game_over();

int main()
{
    display_instructions();
    initialize_board(); //Call initialize board in int main(). This makes the board appear.
    do
    {
      display_board();
      make_move();
    } while (!game_over() && !cin.eof());
    return 0;
}

// Function to check invalid commands.
bool valid_input(string input)
{
   // Variables
    char start = input[0];
    char middle = input[1];
    char end = input[2];
      
  // Invalid output: 1
  // When the command does not have 3 characters and is not 'X' or 'R'
  // *** Invalid sequence. Please retry.
    if ((input.length() == 1))
    {
      if ((input.at(0) != 'X') && (input.at(0) != 'R'))
      {
       cout << "*** Invalid sequence. Please retry. " << endl;   
       return false;
      }
    if((input.length() > 3) || (input.length() == 2))
    {
      cout << "*** Invalid sequence. Please retry. " << endl;   
      return false;
    }
    }


    // Invalid output: 2
    // When a command has positions not in range A → M, print the following message.
    // *** Given move has positions not on the board! Please retry.
    if(input.length() == 3)
    {
      if ((input.at(0) < 'A' || input.at(0) > 'M') && (input.at(1) < 'A' || input.at(1) > 'M') && (input.at(2) < 'A' || input.at(2) > 'M'))
      {
        cout << "*** Given move has positions not on the board! Please retry. " << endl;
        return false;
      }
    } 
      
    // Invalid output: 3
    // When the command has a peg jump over an empty space, print the following message.
    // *** Must jump a piece. Please retry.
    if (get_element (middle) == '.')
    {
      cout << "*** Must jump a piece. Please retry. " << endl;
      return false;
    }

  
    // Invalid output: 4
    // When the command uses an empty space as the jumping peg, print the following message.
    // *** Source needs a piece. Please retry.
    if (get_element(start) == '.')
    {
      cout << "*** Source needs a piece. Please retry. " << endl;
      return false;
    }

  
    // Invalid output: 5
    // When the user enters a command that would jump the peg into a position, that is
    // already occupied, then print the following message.
    // *** Destination must be empty. Please retry.
    if (get_element(end) == '#') 
    {
      cout << "*** Destination must be empty. Please retry. " << endl;
      return false;
    }

  
    // Invalid output: 6
    // When the command refers to a sequence of positions that is not valid (for example IHK), 
    // print the following. *** Move is invalid. Please retry.
    if (!(input == "ABE") && !(input == "EJM") && !(input == "MLI") && !(input == "ADI") && !(input == "JGD") && !(input == "BGL") &&
        !(input == "EBA") && !(input == "MJE") && !(input == "ILM") && !(input == "IDA") && !(input == "DGJ") && !(input == "LGB") &&
        !(input == "BFJ") && !(input == "ACG") && !(input == "CGK") && !(input == "GKM") && !(input == "DHL") && !(input == "JFB") &&
        !(input == "GCA") && !(input == "KGC") && !(input == "MKG") && !(input == "LMD") && !(input == "BCD") && !(input == "EFG") &&
        !(input == "FGH") && !(input == "GHI") && !(input == "JKL") && !(input == "DCD") && !(input == "GFE") && !(input == "HGF") &&
        !(input == "IHG") && !(input == "LKJ")&& !(input == "LHD")) {
      
      cout << "*** Move is invalid. Please retry. " << endl;
      return false;
  }
  return true;
}


void make_move()
{
  string input; // Create variable for user move.

  cout << "Enter positions from, jump, and to (e.g. EFG): "; // Prompt user to enter move.
  cin >> input; // Read in user input.
  for(int i = 0; i < input.length(); i++)
  {
    input.at(i) = toupper(input.at(i));
  }
  // call valid move function

  // Exits the game if user inputs X
  if (input == "X")
  {
    cout << "Exiting." << endl;
    exit(0);
  }
  // Restarts the game if user inputs R
  else if (input == "R")
  {
    cout << "Restarting game." << endl;
    initialize_board();
    return;
  }

  if (valid_input(input)) // If statement for two cases of user move.
  {
  // Code for if the user enters valid response.
    char start = input[0];
    char middle = input[1];
    char end = input[2];
    
    set_element(start, '.');
    set_element(middle, '.');
    set_element(end, '#');
  }
  } // Closes function make_move

/* TODO: Write a function that returns true only if there is one
    one peg left, or if the user gives up by entering 'X' (or 'x')*/
bool game_over()
{
    int pegs = 0;
    for (char input = 'A'; input <= 'M'; input++)
    {
        if ('#' == get_element(input))
        {
          pegs = pegs + 1;
        }
    }
      if (pegs == 1)
      {
        cout << "Congrats you win!" << endl;
        return true;
      }
      else
      {
        return false;
      }
  }
void initialize_board()
{
    /* TODO: Initialize the board to have all pegs, besides the very
    center hole.  ONLY use the functions get_element and set_element
    to update  the board,  do not access  the array 'board' directly.
    */
    for (int i = 0; i < 13; i++) // Step 1: This for loop initializes the board. Sets 12 positions to be "#".
    {
      set_element('A' + i, '#');
    }
   char position = 'G'; // Step 2: Sets middle to be "."
    set_element ('G', '.');
}
