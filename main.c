/*
Author: Ronan Singpurwala
Starting Date: 19/02/2021
Last Edited: 25/02/2021

Description:
This program allows the user to enter in a code.
Encrypt the coe and check if it's the same as the access code.
Display how many times the encrypted code was the same as the access code and the amount of times is wasn't.
A user can't encrypt or decrypt their code twice.
A user can encrypt and decrypt the same code repetitively, however a user can only get the same code correct or incorrect once.

This program was made in VSC.
*/

#include <stdio.h>
#include <stdlib.h>

//function signatures
void menu();
void create_code(int []);
int input_and_validation(int *, int *);
void encrypt_and_verify_code(int [], const int [], int *, int *, int *);
void decrypt_code(int[], int *);
void print_access_attempts(int *, int *);
int exit_program();

//symbolic numbers
#define SIZE 4

//main function
int main(void)
{
	//variables
    char *pointer, string[100];
    int menu_option;
	int user_code[SIZE];
	int user_input;
	int exit_option;

	//access code is constant as it does not change
	const int access_code[SIZE] = {4, 5, 2, 3};
	int code_created = 0;
    int code_encrypted = 0;
	int success = 0, failure = 0;
	int code_created_decyption_check;

	//program loop
	do
	{
        //user menu and input
		menu();
		printf("\n\nEnter an option: ");

		//the smallest and biggest number a user can input
        int min = 1, max = 5;

        //gets the users choice from with in the menu options, returns -1 if not an option
        menu_option = input_and_validation(&min, &max);

		//menu choices
		switch(menu_option)
		{
            //Option 1 - Create Code
			case 1:
			{
				//calling function
				create_code(user_code);

				//when user's code is created
				code_created = 1;

				//code not encrypted yet
                code_encrypted = 0;
				code_created_decyption_check = 1;

				break;
			}

            //Option 2 - Encrypt and verify unencrypted code
            case 2:
            {
				//if user made a code and the code isnt already encrypted
                if (code_created && !code_encrypted)
				{
                    encrypt_and_verify_code(user_code, access_code, &success, &failure, &code_created_decyption_check);

					//setting code_encrypted to 1 so user can now decrypt
                    code_encrypted = 1;
                }

                else
                {
                    printf("\n\aERROR - Please enter an unencrypted code and don't encrypt the same code twice\n");
                }
                //end if

                break;
            }

            //Option 3 - Decrypt encrypted code
            case 3:
            {
				//if the code was encrypted
                if (code_encrypted)
                {
					//call function
				    decrypt_code(user_code, &code_created_decyption_check);

					//setting code_encrypted to 0 so user can encrypt
                    code_encrypted = 0;
                }

                else
                {
                    printf("\n\aERROR - Please enter an encrypted code and don't decrypt the same code twice\n");
                }
                //end if

                break;
            }

            //Option 4 - Print failed and successfull access attempts
            case 4:
            {
				print_access_attempts(&success, &failure);
				break;
            }

            //Option 5 - Exit gracefully with user confirmation
            case 5:
            {
				exit_option = exit_program();

				//leaving program
				if (exit_option == 1)
				{
					break;
				}

				//back to menu
				else if (exit_option == 2)
				{
					menu_option = 1;
					break;
				}
            }

            //input \aERROR for menu option or exit confirmation
            default:
            {
				printf("\n\aERROR - Please enter a number between %d and %d\n", min, max);
				break;
            }
		}
        //end switch
	} while (menu_option != 5);
	//end do while

    //Exit confirmation
    printf("\nExited Successfully.");

    return 0;
}
//end main

//menu
void menu()
{
    printf("\n---------------------------------------------------------| MENU |--------------------------------------------------------------");
	printf("\n\nPlease choose an option:");
	printf("\n\n\t1. Enter any code");
	printf("\n\t2. Encrypt code entered and verify if correct");
	printf("\n\t3. Decrypt code");
	printf("\n\t4. Display the number of times the encrypted code entered matches the authorised code (i) Successfully (ii) Incorrectly");
	printf("\n\t5. Exit Program");
    printf("\n\n-------------------------------------------------------------------------------------------------------------------------------");
}
//end menu()

//input validation for integer input given min and max values
int input_and_validation(int *min, int *max)
{
	//variables
    char *char_pointer, string[100];
    int user_input;

    //gets the input as a string
    fgets(string, sizeof(string), stdin);

    //convert the input using strtol which returns the input in a base 10 long and assigns the memory address of the string remaning to a given pointer
    user_input = strtol(string, &char_pointer, 10);

    //if the input is empty or not within range
    if (char_pointer == string || *char_pointer != '\n' || user_input < *min || user_input > *max)
    {
        return -1;
    }

    //else the int input is returned
	else
    {
        return user_input;
    }
    //end if
}
//end input_and_validation()


//opt 1 - creates a 4 single-digit integer code with validation
void create_code(int user_code[])
{
    //min and max set for single digit ie between 0 and 9
    int min = 0, max = 9, user_input;

    printf("\nEnter a code:\n");

	//looping through array
    for (int i = 0; i < SIZE; i++)
	{
        printf("\n\tDigit %d: ", i+1);

        // gets input with given validation returns int or -1 if invalid
        user_input = input_and_validation(&min, &max);

        // if the input is valid
        if (user_input != -1)
		{
            *(user_code + i) = user_input;
        }

		//user enters a number thats not between min and max (invalid)
		else
		{
            printf("\n\aERROR - Please enter an integer between %d and %d\n", min, max);
            i--;
        }
        //end if
	}
    //end for

	printf("\nYour code: ");

	for (int i = 0; i < SIZE; i++)
	{
        printf("%d ", *(user_code + i));
	}
    //end for

	printf("\n");
}
//end create_code()


//option 2 - encrypting user's code and checking if it matches the access code
void encrypt_and_verify_code(int user_code[], const int access_code[], int *success, int *failure, int *code_created_decyption_check)
{
	//variables
    int temp, i;

    //Swap the 1st number with the 3rd number
    temp = *user_code;
    *user_code = *(user_code + 2);
    *(user_code + 2) = temp;

    //Swap the 2nd number with the 4th number
    temp = *(user_code + 1);
    *(user_code + 1) = *(user_code + 3);
    *(user_code + 3) = temp;

    //Loop through code array
    for (i = 0; i < SIZE; i++)
	{
        //Add 1 to each number
		*(user_code + i) = *(user_code + i) + 1;
    }
    //end for

    for (i = 0; i < SIZE; i++)
    {
        //If any number has a value equal to 10, change this value to 0
        if (*(user_code + i) == 10)
		{
            *(user_code + i) = 0;
        }
        //end if
	}
    //end for

    printf("\nEncrypted code: ");

	//prints code
	for (i = 0; i < SIZE; i++)
	{
		printf("%d ", *(user_code + i));
	}
    //end for

	//loops through code to see if its correct or not
	for (i = 0; i < SIZE; i++)
	{
		//verify encrypted number
		if (*(user_code + i) != *(access_code + i))
		{
			printf("\n\nWrong Code entered\n");

			//if the user hasnt tried checking the same code more than once
			if (*code_created_decyption_check)
			{
				//increments amount of failed attempts by 1
				*failure += 1;
				return;
			}

			return;
		}
        //end if
	}
    //end for

    printf("\n\nCorrect Code entered\n");

	//if the user hasnt tried checking the same code more than once
	if (*code_created_decyption_check)
	{
		//increases amount successfull matches by 1
    	*success += 1;
	}
	//end if
}
//end encrypt_and_verify_code()

//option 3 - decrypting user's code
void decrypt_code(int user_code[], int *code_created_decyption_check)
{
	//variables
    int temp, i;

	*code_created_decyption_check = 0;

    //Loop through code array
    for (i = 0; i < SIZE; i++)
	{
        //Subtract 1 from each number
		*(user_code + i) = *(user_code + i) - 1;
    }
    //end for

    for (i = 0; i < SIZE; i++)
	{
        //If any number has a value equal to -1, change this value to 9
        if (*(user_code + i) == -1)
		{
            *(user_code + i) = 9;
        }
        //end if
    }
    //end for

    //Swap the 1st number with the 3rd number
    temp = *user_code;
    *user_code = *(user_code + 2);
    *(user_code + 2) = temp;

    //Swap the 2nd number with the 4th number
    temp = *(user_code + 1);
    *(user_code + 1) = *(user_code + 3);
    *(user_code + 3) = temp;

    //displaying decrypted code
    printf("\nDecrypted code: ");

    for (i = 0; i < SIZE; i++)
	{
		printf("%d ", *(user_code + i));
	}
    //end for

    printf("\n");
}
//end decrypt_code()


//opt 4 - prints the access attempt counters passed by reference
void print_access_attempts(int *success, int *failure)
{
	//displaying successful and failed matchess with the access code
    printf("\n (i)  Access Successes: %d", *success);
    printf("\n(ii)  Access Failures: %d\n", *failure);
}
//end print_access_attempts

//opt 5 - exit program
int exit_program()
{
	//variables
	int min = 1, max = 2, user_input, error_check;

	//loop until correct input is entered
	do
	{
		//if user doesnt a enter a correct input the first time display an \aERROR
		if (error_check == 1)
		{
			printf("\n\aERROR - Please enter either 1 or 2\n");
		}
		//end if

		//user enters if they want to exit or not
		printf("\nEnter 1 to exit or 2 to cancel: ");

		//setting error_check to 1 so an error can display for incorrect inputs
		error_check = 1;

		user_input = input_and_validation(&min, &max);

		//if they want to continue the code return 1 to main
		if (user_input == 1)
		{
			return 1;
		}
		//end if

		//if they don't want to exit the program return 2
		else if (user_input == 2)
		{
			break;
		}
		//end if
	} while (user_input > 2 || user_input < 1);
	//end do while

	return 2;
}
//end exit_program()
