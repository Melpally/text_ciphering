#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//Declaring the size of the key array
const int NUM_LETTERS = 26;
//Declaring an array for (uppercase) letters and also some punctutation
char abc_up[NUM_LETTERS + 5] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', ',', '.', '5', '0'};
//Declaring an array for lowercase letters
char abc_low[NUM_LETTERS] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

bool uniqueCharacters(char str[])
{

    // If at any time we encounter 2
    // same characters, return false
    for (int i = 0; i < strlen(str) - 1; i++)
    {
        for (int j = i + 1; j < strlen(str); j++)
        {
            if (str[i] == str[j])
            {
                return false;
            }
        }
    }

    // If no duplicate characters encountered,
    // return true
    return true;
}
//Function that converts plaintext to ciphertext and prints out the cipher
void cipher_function(string plain_text, char key[NUM_LETTERS])
{
    //Finding the length of the plain text
    int n = strlen(plain_text);
    //Declaring an array to store the indexes of the letters
    int indexes[n];
    //Declaring an array for storing characters of the cipher text
    char cipher_text[n];
    //For loop to find and initialize the indexes of the text
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        //nested for loop actually
        for (int j = 0; j < n; j++)
        {
            //Checking if the letter is UPPERCASE or lowercase
            if (plain_text[j] == abc_up[i] || plain_text[j] == abc_low[i])
            {
                //Assigning the index to the array
                indexes[j] = i;
            }
        }
    }
    //Another for loop to cipher the text
    for (int k = 0; k < n; k++)
    {
        //Checking if the letter is lowercase
        if (islower(plain_text[k]))
        {
            cipher_text[k] = (char) tolower(key[indexes[k]]);
        }
        //Checking if a character is punctuation
        else if (plain_text[k] == ',' || plain_text[k] == '.' || plain_text[k] == ' ' || plain_text[k] == '5' || plain_text[k] == '0')
        {
            //The text stays the same in this case
            cipher_text[k] = plain_text[k];
        }
        else
        {
            //Uppercase
            cipher_text[k] = (char) toupper(key[indexes[k]]);
        }
    }
    //Printing out the cipher text
    //I couldn't figure out how to return an array properly
    //So I just decided to use the void function instead
    for (int l = 0; l < n; l++)
    {
        printf("%c", cipher_text[l]);
    }
    printf("\n");
}

//The main function takes an argument from command line
int main(int argc, string argv[])
{
    //Creating and Initializing the array
    char key[NUM_LETTERS];
    //Checking if the user has typed exactly 2 command-line arguments
    if (argc == 2)
    {
        //Checking with a for loop if the characters of the array are valid
        //i.e. not numeric or repeated
        int count;
        for (int i = 0; i < NUM_LETTERS; i++)
        {
            key[i] = argv[1][i];
            if (!isalpha(key[i]))
            {
                printf("Enter valid key\n");
                return 1;
            }

        }
        if (!uniqueCharacters(key))
        {
            printf("Do not enter duplicate elements!\n");
            return 1;
        }
    }
    else if (argc > 2 || argc == 1)
    {
        //Raise an error
        printf("two arguments are needed: filename and key.\n");
        return 1;
    }
    //Getting the texts and printing the result
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    cipher_function(plaintext, key);
    return 0;
}