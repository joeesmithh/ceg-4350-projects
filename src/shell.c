#include "types.h"
#include "io.h"
#include "fat.h"
#include "multitasking.h"
#include "shell.h"

int createSelected()
{
	// Let the user type in a file name and extension
	char filename[100] = {0};
	char ext[100] = {0};
	char sub[100];

	// Ask if we're creating a subdirectory (not a file)
	print("Create subdirectory? (y/n): ");
	scan(sub);
	putchar('\n');

	char subdirectorySelected = sub[0] == 'y';

	print("Enter name: ");
	scan(filename);
	putchar('\n');

	if (subdirectorySelected)
	{
		// Search the directory to see if there exists an entry that contains the subdirectory
		char exists = directoryExists(filename);

		if (exists)
		{
			print("Error: Attempted to create a directory that already exists!\n");
			return 1;
		}

		print("Creating Subdirectory...\n");
		// Create the subdirectory on our file system (adds the subdirectory to our floppy disk)
		createSubdirectory(filename);
	}
	// If we're not creating a subdirectory, ask for the file extension and try to find it
	else
	{
		print("Enter extension: ");
		scan(ext);
		putchar('\n');

		// Search the directory to see if there exists an entry that contains the file name and extension
		char fileDoesNotExist = openFile(filename, ext);

		if (!fileDoesNotExist)
		{
			print("Error: Attempted to create a file that already exists!\n");
			return 1;
		}

		print("Creating File...\n");
		// Create the file on our file system (adds the empty file to our floppy disk)
		createFile(filename, ext);
	}

	return 0;
}

int writeSelected()
{
	// Let the user type in a file name and extension
	char filename[100];
	char ext[100];

	print("Enter filename: ");
	scan(filename);
	putchar('\n');

	print("Enter extension: ");
	scan(ext);
	putchar('\n');

	// Search the directory to see if there exists an entry that contains the file name and extension
	char fileDoesNotExist = openFile(filename, ext);

	if (fileDoesNotExist)
	{
		print("Error: Cannot write to a file that does not exist!\n");
		return 1;
	}

	clearscreen();
	print("Writing File...\n");
	print("Type enter once to add an additional sector to the file.\n");
	print("Type enter twice to close the file.\n");

	uint32 i = 0;
	uint8 prevByte = 0;
	uint8 byte = 0;

	// Let the user type in characters into the file (until they hit ENTER)
	do
	{
		prevByte = byte;
		byte = (uint8)getchar();

		if(byte != '\n')
		{
			// Print the character to the file
			putchar((char)byte);
			writeNextByte(byte);
			i++;
		}
		else if(byte == '\n' && prevByte != '\n')
		{
			clearscreen();
			print("Writing File...\n");
			print("Type enter once to add an additional sector to the file.\n");
			print("Type enter twice to close the file.\n");

			// Fill up the remaining sector with 0's to move onto the next sector
			writeBytes(0, 512 - (i % 512));
			i += 512 - (i % 512);
		}
		
	}while(!(byte == '\n' &&  prevByte == '\n'));
	
	// If we have not overwritten the entire sector, do so now
	// This prevents nasty leftovers in the sector from old writes
	writeBytes(0, 512 - i);
	i += 512 - i;

	// Close the file (save the results to the disk)
	putchar('\n');
	closeFile();

	clearscreen();

	return 0;
}

int readSelected()
{
	// Let the user type in a file name and extension
	char filename[100];
	char ext[100];

	print("Enter filename: ");
	scan(filename);
	putchar('\n');

	print("Enter extension: ");
	scan(ext);
	putchar('\n');

	// Search the directory to see if there exists an entry that contains the file name and extension
	char fileDoesNotExist = openFile(filename, ext);

	if (fileDoesNotExist)
	{
		print("Error: Cannot read from a file that does not exist!\n");
		return 1;
	}

	clearscreen();
	print("Reading File...\n");

	// Read one byte from the file
	uint8 byte = readNextByte();

	// Print the contents of the file to the string
	// We are using '-2' as a special code to tell when the last sector ends
	while(byte != (uint8)-2)
	{
		// Print the byte to the screen
		if (byte != 0) putchar((char)byte);

		// Read one byte from the file
		byte = readNextByte();
	}

	// Close the file
	putchar('\n');
	closeFile();

	return 0;
}

int deleteSelected()
{
	// Let the user type in a file name and extension
	char filename[100];
	char ext[100];

	print("Enter filename: ");
	scan(filename);
	putchar('\n');

	print("Enter extension: ");
	scan(ext);
	putchar('\n');

	// Search the directory to see if there exists an entry that contains the file name and extension
	char fileDoesNotExist = openFile(filename, ext);

	if (fileDoesNotExist)
	{
		print("Error: Attempted to delete a file that does not exist!\n");
		return 1;
	}

	print("Deleting File...\n");
	deleteFile();

	return 0;
}

int deleteSubdirectorySelected()
{
	// Let the user type in a subdirectory name
	char filename[100];

	print("Enter filename: ");
	scan(filename);
	putchar('\n');

	// Attempt to delete the subdirectory
	print("Deleting Subdirectory...\n");
	deleteSubdirectory(filename);

	return 0;
}

int navigateSelected()
{
	// Let the user type in a file name and extension
	char directoryName[100] = {0};
	
	print("Enter directory: ");
	scan(directoryName);
	putchar('\n');

	// Search the directory to see if there exists an entry that contains the directory
	char exists = directoryExists(directoryName);

	if (!exists)
	{
		print("Error: Attempted to navigate to a subdirectory that does not exist!\n");
		return 1;
	}

	openDirectory(directoryName);

	return 0;
}

char getMenuSelection()
{
	// Ask the user to make a selection
	print("Make a selection (c, d, s, r, w, n, q): ");
	char inputString[100];
	scan(inputString);
	char input = inputString[0];
	putchar('\n');
	return input;
}

// The shell processes
void procshell()
{	
	char input;

	// Initialize the file system
	init_fs();

	do
	{
		// Get the user's input
		input = getMenuSelection();

		// Execute based on what they typed
		if 		(input == 'c') createSelected();
		else if	(input == 'd') deleteSelected();
		else if	(input == 's') deleteSubdirectorySelected();
		else if	(input == 'r') readSelected();
		else if	(input == 'w') writeSelected();
		else if (input == 'n') navigateSelected();
		else if (input == 'q') print("Quitting...\n");
		else
		{
			// If the input was invalid, just restart loop
			print("Error: Invalid input: ");
			putchar(input);
			putchar('\n');
		}
		
	}while(input != 'q');

	exit();
}

void startshell()
{
	// Create the shell processes
	print("Shell process has started...\n");
	createuserprocess(procshell, (void *) 0x10000);

	// Schedule the next process
	int userprocs = ready_process_count();

	// As long as we have ready user processes to run
	while(userprocs > 0)
	{
		// Yield to them
		yield();
		userprocs = ready_process_count();
	}

    print("\n\nShell process has exited...\n");
    exit();
}