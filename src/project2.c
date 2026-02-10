#include "project2.h"

// Define constants
#define STRING_LENGTH 100

// Define a keymap to convert keyboard scancodes to ASCII
static char keymap[128] = {
    [0x1E] = 'a',
    [0x30] = 'b',
    [0x2E] = 'c',
    [0x20] = 'd',
    [0x12] = 'e',
    [0x21] = 'f',
    [0x22] = 'g',
    [0x23] = 'h',
    [0x17] = 'i',
    [0x24] = 'j',
    [0x25] = 'k',
    [0x26] = 'l',
    [0x32] = 'm',
    [0x31] = 'n',
    [0x18] = 'o',
    [0x19] = 'p',
    [0x10] = 'q',
    [0x13] = 'r',
    [0x1F] = 's',
    [0x14] = 't',
    [0x16] = 'u',
    [0x2F] = 'v',
    [0x11] = 'w',
    [0x2D] = 'x',
    [0x15] = 'y',
    [0x2C] = 'z',
    [0x0B] = '0',
    [0x02] = '1',
    [0x03] = '2',
    [0x04] = '3',
    [0x05] = '4',
    [0x06] = '5',
    [0x07] = '6',
    [0x08] = '7',
    [0x09] = '8',
    [0x0A] = '9',
    [0x39] = ' ',
    [0x34] = '.',
    [0x35] = '/',
    [0x1C] = '\n'};

#if PROJECT == 2
// This function runs when compiled with the #define PROJECT 2 flag for make
int kernel()
{
    while (1)
    {
        // Prompt
        print("Please type something: ");
        char string[STRING_LENGTH];
        scan(string);
        putchar('\n');

        // Result
        print("You typed: ");
        print(string);
        putchar('\n');
    }
    return 0;
}
#endif

char getchar()
{
    while (1)
    {
        // Wait for keyboard data to be available
        while (!(inb(0x64) & 0x01))
            continue;

        // Get scancode
        uint8 scancode = inb(0x60);

        // Ignore key releases
        if (scancode & 0x80)
            continue;

        // Check if it's a valid, mapped scancode
        if (scancode < sizeof(keymap) && keymap[scancode] != '\0')
        {
            return keymap[scancode];
        }
    }
}

void scan(char string[])
{   
    // Prep input loop
    char c = getchar();
    int length = 0;

    // While the user has not pressed ENTER
    while (c != '\n')
    {
        // Display character
        putchar(c);

        // Add char to array
        string[length] = c;
        length++;

        // If length of string greater than or equal to max
        // string length, including null char, break
        if(length >= (STRING_LENGTH - 1))
            break;

        // Get next character
        c = getchar();
    }

    // Terminate string with null char
    string[length] = '\0';
    return;
}