#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_ARGS 10

int main() 
{
    char *command = "grep"; // Example command
    char *argument = "word"; // Example argument
    char *files[] = {"file1.txt", "file2.txt", "file3.txt", NULL};
    char *output_files[] = {"file4.txt", "file5.txt", NULL};

    int out_fds[2];

    // Open output files for writing
    for (int i = 0; i < 2; i++) 
	{
        out_fds[i] = open(output_files[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fds[i] == -1) 
		{
            perror("Failed to open output file");
            exit(EXIT_FAILURE);
        }
    }

    // Loop through each input file
    for (int i = 0; files[i] != NULL; i++) 
	{
        int in_fd = open(files[i], O_RDONLY);
        if (in_fd == -1) 
		{
            perror("Failed to open input file");
            exit(EXIT_FAILURE);
        }

        // Fork a child process
        pid_t pid = fork();
        if (pid == -1) 
		{
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Child process
            // Redirect standard input
            if (dup2(in_fd, STDIN_FILENO) == -1) 
			{
                perror("Input redirection failed");
                exit(EXIT_FAILURE);
            }
            close(in_fd);

            // Redirect standard output
            for (int j = 0; j < 2; j++) 
			{
                if (dup2(out_fds[j], STDOUT_FILENO) == -1) 
				{
                    perror("Output redirection failed");
                    exit(EXIT_FAILURE);
                }
            }

            // Execute the command with its argument
            char *args[MAX_ARGS];
            args[0] = command;
            args[1] = argument;
            args[2] = NULL;

            execve("/usr/bin/grep", args, NULL);
            perror("Execution failed");
            exit(EXIT_FAILURE);
        }
        close(in_fd);
    }

    // Wait for all child processes to finish
    for (int i = 0; files[i] != NULL; i++) 
	{
        int status;
        wait(&status);
    }

    // Close all file descriptors
    for (int i = 0; i < 2; i++) 
	{
        close(out_fds[i]);
    }

    printf("Command execution complete. Check file4.txt and file5.txt for results.\n");

    return 0;
}

