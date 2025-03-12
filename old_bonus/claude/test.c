void ft_intermediate_child(char *argv[], char *envp[], int prev_pipe[], int next_pipe[], int cmd_index)
{
    // Close unused pipe ends
    close(prev_pipe[1]);  // Close write end of previous pipe
    close(next_pipe[0]);  // Close read end of next pipe
    
    // Redirect stdin to read end of previous pipe
    if (dup2(prev_pipe[0], STDIN_FILENO) < 0)
    {
        perror("Error duplicating reading end of pipe");
        exit(1);
    }
    
    // Redirect stdout to write end of next pipe
    if (dup2(next_pipe[1], STDOUT_FILENO) < 0)
    {
        perror("Error duplicating writing end of pipe");
        exit(1);
    }
    
    // Close used pipe ends after duplication
    close(prev_pipe[0]);
    close(next_pipe[1]);
    
    char *args[] = {"/bin/sh", "-c", argv[cmd_index], NULL};
    execve("/bin/sh", args, envp);
}

int main(int argc, char *argv[], char *envp[])
{
    int cmd_count = argc - 3;  // number of commands (excluding input/output files)
    int pipe_count = cmd_count - 1;
    int pipes[pipe_count][2];  // array of pipes
    
    // Create all pipes
    for (int i = 0; i < pipe_count; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("Error creating pipe");
            exit(1);
        }
    }
    
    // For each command...
    for (int i = 0; i < cmd_count; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            if (i == 0)  // First command
                ft_first_child(argv, envp, pipes[0]);
            else if (i == cmd_count - 1)  // Last command
                ft_last_child(argv, envp, pipes[i-1]);
            else  // Intermediate command
                ft_intermediate_child(argv, envp, pipes[i-1], pipes[i], i+2);
        }
    }
    
    // Close all pipes in parent
    for (int i = 0; i < pipe_count; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    
    // Wait for all children
    int status;
    for (int i = 0; i < cmd_count; i++)
        wait(&status);
        
    return WEXITSTATUS(status);
}