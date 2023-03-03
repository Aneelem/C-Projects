/**------------------------------------------
    Program 1: ASCII Flowers
    Prompt for the number of flower layers and display

    Course: CS 141, Fall 2023
    System: Linux_x86_64 and G++
    Author: Meleena Torres
 ---------------------------------------------**/
#include <iostream>
#include <iomanip>
using namespace std;

void drawRoots(int layers, int spacing)
{

    bool Leaf_is_on_Left = true; // this will keep track which side the leaf should be (Notice that the leaf side changes, left to right.) if the leaf is not on the left, we change this to FALSE
    int roots = layers * 2; // Noticed that the amount of lines for the roots is just the amount of sections * 2

    for (int i = 0; i < roots; i++)
    { // We print each root.

        for (int space = 0; space < spacing; space++)
        { // This centers the roots by the spacing we found earlier
            cout << " ";
        }

        if (i % 2 == 0)
        { // We noticed that every root with a leaf is in even incremients. Notice how the 0 root has a leaf, the 2nd root has a leaf, the 4th root has a leaf as so on.
            if (Leaf_is_on_Left == true)
            { // checks to see if leaf is on left side of root
                cout << " |/\n";
                Leaf_is_on_Left = false; // after we place that leaf, make sure to change variable to false since the leaf now needs to be put on the right side of the root
            }
            else
            {
                cout << "\\|\n";
                Leaf_is_on_Left = true; // After we place leaf, change variable to true since we now need to put leaf on left side of root
            }
        }
        else
        {
            cout << " |\n";
        }
    }
}
int main()
{
    // display the prompt to the user
    cout << "Program 1: ASCII Flowers\n"
         << "Choose from the following options:\n"
         << "   1. Display the HELLO graphic\n"
         << "   2. Display The Flower\n"
         << "   3. Exit the program\n"
         << "Your choice -> ";

    // read in the user's choice
    int menu_option;
    cin >> menu_option;

    // handle option to quit
    if (menu_option == 3)
    {
        exit(0);
    }
    // handle the HELLO graphic choice
    if (menu_option == 1)
    {
        char frame;
        cout << "Enter your frame character: ";
        cin >> frame;
        // top border
        cout << endl;
        for (int i = 0; i < 2; i++)
        {
            cout << setfill(frame) << setw(36) << ' ' << endl;
        }
        // message
        cout << setfill(frame) << setw(3) << right << " "
             << "** ** ***** **    **    *****"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** ***** **    **    *****"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** **    **    **    ** **"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "***** ***** **    **    ** **"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "***** ***** **    **    ** **"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** **    **    **    ** **"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** ***** ***** ***** *****"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** ***** ***** ***** *****"
             << setfill(frame) << setw(3) << left << " " << endl
             << right;
        // bottom border
        for (int i = 0; i < 2; i++)
        {
            cout << setfill(frame) << setw(36) << " " << endl;
        }
    }
    if (menu_option == 2)
    {
        // Declare variables
        int layers;

        // Get user input
        cout << "Enter number of sections:" << endl;
        cin >> layers;

        int rows = 1; // how many rows a section has. We know that in section 1, there will only be one row. We will add more rows when we enter a new section of the flower

        int spacing = layers; // number of spaces to have space, nothing gets chopped off

        if (layers > 0)
        { // only run if we have at least 1 or more sections. Exit program if anything else.
            for (int sections = 1; sections <= layers; sections++)
            { // Loops for every section. Hence, if there are 3 sections, there will be 3 parts to the flower

                for (int space = 0; space < spacing; space++)
                { // spaces out to set border in place
                    cout << " ";
                }

                for (int line = 0; line < 3; line++)
                { // border for each section
                    if (line == 2)
                    {
                        cout << "-\n";
                    }
                    else
                    {
                        cout << "-";
                    }
                }
                int middle = (rows + 1) / 2; // the middle row where there needs to be a @
                int row_charinc = 3;         // first row will always have 3 ":"s inside EXCEPT the middle row, since the middle row needs a @. This will increase ny 2 as we move down the rows. Notice how there are 2 extra ":"s in each row as we go to the middle row. THEN, we decrease by 2 ":"s after we pass the middle row.

                for (int row = 1; row <= rows; row++)
                { // loops through the number of rows in a certain section

                    if (row == middle)
                    {                                                        // if we reach the row that happens to be the middle of its section...
                        int num_of_chars = rows + 2;                         // the number of seimicolons and the @ for the middle row EX: say for section 3: there are 5 rows + 2 = 7 chars === :::@:::
                        int row_middle = (num_of_chars + 1) / 2;             // the index for the middle char in middle row AKA the @ (Used median formula to find middle index)
                        int row_middle_spacing = (spacing - row_middle) + 1; // mathy math to find how many spaces to center the middle row

                        for (int row_middle_space = 0; row_middle_space < row_middle_spacing; row_middle_space++)
                        { // spacing for the middle rows of each section
                            cout << " ";
                        }

                        cout << "{";

                        for (int chars = 1; chars <= num_of_chars; chars++)
                        { // prints the ":" AND "@" for the middle row of a section
                            if (chars == row_middle)
                            {
                                cout << "@";
                            }
                            else
                            {
                                cout << ":";
                            }
                        }
                        cout << "}\n";
                        row_charinc = num_of_chars - 2; // preps for next row!, we know that once we pass the middle row, the number of ":" will start to decrease. We see that each row decreases the amount of ":" by 2 always.
                    }

                    else
                    { // Do this when we are NOT looking at a row that is in the middle of a section

                        int row_center_index = (row_charinc + 1) / 2; // finds the center to figure out the spacing of the row
                        int row_spacing = (spacing - row_center_index) + 1;

                        for (int row_space = 0; row_space < row_spacing; row_space++)
                        {
                            cout << " ";
                        }

                        cout << "{";

                        for (int colon = 1; colon <= row_charinc; colon++)
                        { // adds in the correct amount of ":"s
                            cout << ":";
                        }

                        cout << "}\n";

                        if (row > middle)
                        { // This is important, this checks if the row we are at has passed the middle row, if we have already pass the middle row, keep decreasing by 2 ":"s to set up for the next row.
                            row_charinc -= 2;
                        }
                        else
                        {
                            row_charinc += 2; // If we have not reached the middle row yet,keep increasing the ":"s by 2.
                        }
                    }
                }

                rows = rows + 2; // Once we finish with a section and all of its rows, the next section will have 2 more rows than its previous section. (Section 2 has 3 rows, so we know that Section 3 will have 5 rows!!)
            }

            for (int space = 0; space < spacing; space++)
            { // Spacing stuff
                cout << " ";
            }

            for (int line = 0; line < 3; line++)
            { // border for each section
                cout << "-";
            }

            cout << "\n"; // leave space for the roots

            drawRoots(layers, spacing);
        }
    }
    return 0;
}