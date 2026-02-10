#include "project1.h"

// Define our constants that will be widely used
#define TEXT_COLOR 0x07
#define ROWS 25
#define COLS 80

// Global variables
int cursorCol = 0;
int cursorRow = 0;

#if PROJECT == 1
/** This function runs when compiled with the #define PROJECT 1 flag */
int kernel()
{
    // Print hello world to the display then stop
    print("Hello World!\n");
    return 0;
}
#endif

/** Set the global position of the display cursor.
    @param x The cursor position on the horizontal axis.
    @param y The cursor position on the vertical axis.
*/
void setCursor(int x, int y)
{
    cursorCol = x % COLS;
    cursorRow = (y + (x / COLS)) % ROWS;
}

/** Prints a single character on the display at the current global cursor position.
    @param character The character to print.
    @returns The character that was printed.
 */
char putchar(char character)
{
    // If character is newline, set global cursor to new line and return
    if (character == '\n')
    {
        setCursor(0, cursorRow + 1);
        return character;
    }

    // Write characters to screen at memory offset
    int memOffset = 2 * (cursorCol + cursorRow * COLS); // Create memory address offset
    char *vidmem = (char *)(memOffset + 0xB8000);       // Create pointer to memory address offset from 0xB8000
    *vidmem = character;                                // Write character to display
    *(vidmem + 1) = TEXT_COLOR;                         // Write character color to display

    // Increment column and, if on last column, increment row
    setCursor(cursorCol + 1, cursorRow);

    return character;
}

/** Print an array of characters on the display.
    @param string The character array to print.
    @returns The number of characters printed to the display.
*/
int print(char string[])
{
    int i = 0;            // Iterator
    char cur = string[i]; // Current character

    // Print characters
    while (cur)
    {
        putchar(cur);
        i++;
        cur = string[i];
    }

    return i;
}

/** Clear all characters from the display. */
void clearscreen()
{
    // Initialize cursor to beginning
    setCursor(0, 0);

    // Insert spaces for all columns and rows
    int charsToPrint = ROWS * COLS;
    int charsPrinted = 0;
    while (charsPrinted < charsToPrint)
    {
        putchar(' ');
        charsPrinted++;
    }

    // Initialize cursor to beginning
    setCursor(0, 0);

    return;
}