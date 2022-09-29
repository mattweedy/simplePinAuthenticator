// a program to authenticate an encrypted password PIN. the user can choose to either:
// 1. encrypt any 4 digit code
// 2. encrypt the code entered and verify if it matches the (hardcoded) authorised code (4523)
// 3. decrypt the user-inputted code
// 4. display the amount of times the code was entered i) correctly ii) incorrectly || (if it matches authorised code)
// 5. exit the program
// the program uses separate functions with pass by reference for each step, 
// and certain options should not be allowed to run if the user has not entered a code yet 

// Visual Studio Code - GCC via mingw64
// started 22/02/21
// finished 26/02/21 16:45

// matthew tweedy 

#include <stdio.h>
#include <stdlib.h>

// defining symbolic names
#define SIZE 4

// functions signatures
int * codeInput();
void codeEncrypt(const int [], int [], int *, int *, int *);
void codeDecrypt(int []);
void codeCount(int *, int *);
int exitProgram();

int main()
{
    const int access_code[SIZE] = {4, 5, 2, 3}; // the hardcoded authorised code (encrypted version of 1234)
    int *input_code;                            // user's entered code array (array pointer)
    static int checkINP;                        // this is a counter used between the functions to ensure the user has entered a code so they can encrypt it
    static int checkENC;                        // var that signifies if code has been encrypted already
    static int checkDEC;                        // var that signifies if code has been decrypted already
    int counterIncAllow;                    // var that signifies if the current code has been counted as incorrect/correct (resets upon new code entry)
    int correctCount = 0;                       // count for how many times correct code was entered
    int incorrectCount = 0;                     // count for how many times incorrect code was entered
    int choice = 0;                             // user's choice for the menu

    do // start do
    {
        // printing the menu
        printf("----------------------------------------------------------------------");
        printf("\nchoose one of the following:\n");
        printf("\t1. enter any code\n");
        printf("\t2. encrypt code entered and verify if correct\n");
        printf("\t3. decrypt code\n");
        printf("\t4. display the number of times the encrypted code entered matches the autorised code i) successfully ii) incorrectly\n");
        printf("\t5. exit program\n");
        printf("----------------------------------------------------------------------\n");
        printf("\nchoice: ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) // start switch using the choice variable
        {
            case 1: // if user inputs 1
            {
                input_code = codeInput();
                // setting vars so further options can be used
                checkINP = 1;
                checkENC = 0;
                checkDEC = 0;
                counterIncAllow = 0;
                break;
            }       // end case
            case 2: // if user inputs 2
            {
                if (checkINP == 0)                // check if code has been entered
                {
                    printf("\nyou must enter a code before encrypting!\n\n");
                    break;
                } else if (checkENC == 1)         // check if code has been encrypted already
                {
                    printf("\ncode already encrypted!\n\n");
                    break;
                } else                            // if it passes both checks, call function
                {
                    codeEncrypt(access_code, input_code, &correctCount, &incorrectCount, &counterIncAllow);
                    // setting encrypted check to 1 so the option cant be chosen until code is decrypted again
                    checkENC = 1;
                    checkDEC = 0;
                    counterIncAllow = 1;
                    break;
                }
            }       // end case
            case 3: // if user inputs 3
            {
                if (checkINP == 0)                // check to see if the code has been entered in the first place
                {
                    printf("\nyou must enter a code before decrypting!\n\n");
                    break;
                } else if (checkDEC == 1)         // check to see if the code has already been decrypted
                {
                    printf("\ncode already decrypted!\n\n");
                    break;
                } else if (checkENC == 0)         // check if code has been encrypted before it gets decrypted
                {
                    printf("\nyou must encrypt before you can decrypt!\n\n");
                    break;
                } else                            // if passes all checks, call function
                {
                    codeDecrypt(input_code);
                    // setting decrypted check to 1 so the option cant be chosen until code is encrypted again
                    checkDEC = 1;
                    checkENC = 0;
                    break;
                }
            } // end case
            case 4: // if user inputs 4
            {
                codeCount(&correctCount, &incorrectCount);
                break;
            }        // end case 4
            case 5: // if user inputs 5
            {
                choice = exitProgram();
                break;
            }        // end case 5
            default: // if the user inputs anything else
            {
                    printf("\nplease enter a choice between 1 and 5\n\n");
                    fflush(stdin);
                    break;
            }              // end default
        }                  // end switch
    } while (choice != 5); // end do while
}                          // end main

// (option 1) function codeInput will take the input and store it in a 1-D array
int * codeInput()
{
    int i;
    static int user_code[SIZE];
    char *p, s[100];
    for ( i = 0; i < SIZE; i++)
    {
        printf("\nenter digit %d: ", i+1);                // prompts user input
        while (fgets(s, sizeof(s), stdin))
        {
            *(user_code + i) = strtol(s, &p, 10);         // current index of user_code[] is set to converted long int from strtol()
            if (p == s || *p != '\n') {                   // if *p doesn't == \n then input is incorrect | discards string output
                printf("\nerror: characters detected\n"); // prints error
                printf("\nenter digit %d: ", i+1);        // prompts again
            } else break;
        } // end while

        if (*(user_code + i) >= 10 || *(user_code + i) < 0) // checks if number entered was > 10 or < 0
        {
            printf("\nerror: number entered was invalid\n");
            printf("enter valid number (0-9)\n");
            i--; // makes the loop stay on the same array index until user inputs num 0-9
        }
    }
    
    printf("\n");
    
    return user_code; // returns the code array to main
}                     // end codeInput()

// (option 2) function codeEncrypt will apply the encryption process to the users input and also verify if it matches the auth code
void codeEncrypt(const int access_code[], int user_code[], int *correctCount, int *incorrectCount, int *counterIncAllow)
{
    // accessing the memory address for the variables correctCount to allow a function
    *correctCount;
    *incorrectCount;
    *counterIncAllow;

    int digitMatch = 0; // increments every time a digit from user's code matches auth code
    int i, t;           // t var acts as temp to allow the swapping of variables

    for (i = 0; i < 2; i++) // for loop to swap the numbers in the array
    {
        t = *(user_code + i);                    // temp var "t" to hold the value of the 1st entry in user_code array
        *(user_code + i) = *(user_code + (i+2)); // swapping the 1st & 3rd / 2nd & 4th
        *(user_code + (i+2)) = t;
    } // end for
    
    for (i = 0; i < SIZE; i++)      // this for loop handles both the second half of the encryption of the user's code AND verifying it against the authorised code
    {
        *(user_code + i) += 1;      // incrementing all numbers by 1
        if (*(user_code + i) == 10) // setting any numbers equal to 10 as 0
        {
            *(user_code + i) = 0;
        }
        
        if (*(user_code + i) == *(access_code + i)) // verification of the entered code vs auth code
        {
            digitMatch++; // incrementing a counter for each digit that match when comparing user code and auth code
        }
    } // end for

    printf("encrypted : "); // printing the encrypted code
    for ( i = 0; i < SIZE; i++)
    {
        printf("%d", *(user_code + i));
    } // end for

    printf("\n\n");

    if (*counterIncAllow == 0) // this checks if the current code entered has already been counted as an incorrect or correct entry
    {
        if (digitMatch == 4) // if all the digits match in both (encrypted) codes
        {
            printf("\ncorrect code entered\n\n");
            (*correctCount)++;
        }
        else                // if the digits dont all match
        {
            printf("\nincorrect code entered\n\n");
            (*incorrectCount)++;
        }
    }
    
} // end codeEncrypt()

// (option 3) function codeDecrypt will reverse the process of option 2 (only if the code has already been encrypted)
void codeDecrypt(int user_code[])
{
    int i, t;

    for (i = 0; i < SIZE; i++) // for loop subtracting 1 from all numbers in code
    {
        *(user_code + i) -= 1;

        if (*(user_code + i) == -1) // setting any numbers equal to 10 as 0
        {
            *(user_code + i) = 9;
        }
    } // end for

    for (i = 0; i < 2; i++) // for loop to swap the numbers in the array
    {
        t = *(user_code + i);                    // temp var "t" to hold the value of the 1st entry in user_code array
        *(user_code + i) = *(user_code + (i+2)); // swapping the 1st & 3rd / 2nd & 4th
        *(user_code + (i+2)) = t;
    } // end for

    printf("decrypted : ");
    for ( i = 0; i < SIZE; i++) // printing the decrypted code
    {
        printf("%d", *(user_code + i));
    } // end for
    printf("\n\n");
}

// (option 4) function codeCount() prints the amount of times the code was entered i) correctly ii) incorrectly || (if it matches authorised code)
void codeCount(int *correct, int *incorrect)
{
    printf("\ni) correct entries    : %d", *correct);   // prints the correct var that was passed by reference from the main
    printf("\nii) incorrect entries : %d", *incorrect); // prints the incorrect var that was passed by reference from the main
    printf("\n\n");
}

// (option 5) function exitProgram() will be called when the user wishes to exit the program, and will double check they wish to
int exitProgram()
{
    int end;        // var to check if user wants to end program
    int choice = 0; // var to pass back if user does not want to end program

    printf("\nenter either:\n0 (return to the main menu)\n1 (end the program)\n");
    printf("\nchoice: ");
    scanf("%d", &end);
    fflush(stdin);

    switch (end)
    {
        case 0: // if user enters 0
        {
            printf("\nreturning to menu...\n\n");
            return choice;
            break;
        } // end case
        case 1: // if user enters 1
        {
            printf("\nending program...");
            exit(0);
            break;
        } // end case
        default: // if user enters anything else 
        {
            exitProgram();
        } // end default
    }     // end switch
}         // end exitProgram()