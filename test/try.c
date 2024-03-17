#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main() 
{
    // Fork to create a child process
    pid_t pid = fork();

    if (pid == -1) 
	{
        perror("Error forking process");
        exit(EXIT_FAILURE);
    } 
	else if (pid == 0) 
	{ // Child process
        // Open file5.txt for writing (creating if it doesn't exist, truncating it to zero length otherwise)
        int file5_fd = open("file5.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (file5_fd == -1) 
		{
            perror("Error opening file5.txt");
            exit(EXIT_FAILURE);
        }
        // Close stdout file descriptor
/*
		if (close(STDOUT_FILENO) == -1) 
		{
            perror("Error closing stdout");
            close(file5_fd);
            exit(EXIT_FAILURE);
        }
  */
		// Duplicate file descriptor for file5.txt to stdout (file descriptor 1)
        if (dup2(file5_fd, STDOUT_FILENO) == -1) 
		{
            perror("Error duplicating file descriptor for file5.txt");
            close(file5_fd);
            exit(EXIT_FAILURE);
        }
        // Open file1.txt for reading (file descriptor 3)
        int file1_fd = open("file1.txt", O_RDONLY);
        if (file1_fd == -1) 
		{
            perror("Error opening file1.txt");
            exit(EXIT_FAILURE);
        }
        // Duplicate file descriptor for file1.txt to stdin (file descriptor 0)
        if (dup2(file1_fd, STDIN_FILENO) == -1) 
		{
            perror("Error duplicating file descriptor for file1.txt");
            close(file1_fd);
            close(file5_fd);
            exit(EXIT_FAILURE);
        }
        // Close file descriptor for file1.txt
        if (close(file1_fd) == -1) 
		{
            perror("Error closing file1.txt");
            close(file5_fd);
            exit(EXIT_FAILURE);
        }
        // Execute grep command with argument
        char *args[] = {"/usr/bin/grep", "word", NULL};
        execve("/usr/bin/grep", args, NULL);
        // If execve returns, it means an error occurred
        perror("Error executing grep command on file5.txt");
        close(file5_fd);
        exit(EXIT_FAILURE);
    } 
	else 
	{ // Parent process
        // Open file4.txt for writing (creating if it doesn't exist, truncating it to zero length otherwise)
        int file4_fd = open("file4.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (file4_fd == -1) 
		{
            perror("Error opening file4.txt");
            exit(EXIT_FAILURE);
        }
        // Close stdout file descriptor
/* 
		if (close(STDOUT_FILENO) == -1) 
		{
            perror("Error closing stdout");
            close(file4_fd);
            exit(EXIT_FAILURE);
        }
*/		
        // Duplicate file descriptor for file4.txt to stdout (file descriptor 1)
        if (dup2(file4_fd, STDOUT_FILENO) == -1) 
		{
            perror("Error duplicating file descriptor for file4.txt");
            close(file4_fd);
            exit(EXIT_FAILURE);
        }
        // Open file1.txt for reading (file descriptor 3)
        int file1_fd = open("file1.txt", O_RDONLY);
        if (file1_fd == -1) 
		{
            perror("Error opening file1.txt");
            close(file4_fd);
            exit(EXIT_FAILURE);
        }
        // Duplicate file descriptor for file1.txt to stdin (file descriptor 0)
        if (dup2(file1_fd, STDIN_FILENO) == -1) 
		{
            perror("Error duplicating file descriptor for file1.txt");
            close(file1_fd);
            close(file4_fd);
            exit(EXIT_FAILURE);
        }
        // Close file descriptor for file1.txt
        if (close(file1_fd) == -1) 
		{
            perror("Error closing file1.txt");
            close(file4_fd);
            exit(EXIT_FAILURE);
        }
        // Execute grep command with argument
        char *args[] = {"/usr/bin/grep", "word", NULL};
        execve("/usr/bin/grep", args, NULL);
        // If execve returns, it means an error occurred
        perror("Error executing grep command on file4.txt");
        close(file4_fd);
        exit(EXIT_FAILURE);
    }
}

