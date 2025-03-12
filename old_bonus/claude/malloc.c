int **create_pipes(int pipe_count)
{
    int **pipes = malloc(sizeof(int *) * pipe_count);
    if (!pipes)
        return NULL;
    
    for (int i = 0; i < pipe_count; i++)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (!pipes[i])
        {
            // Free previously allocated memory
            while (--i >= 0)
                free(pipes[i]);
            free(pipes);
            return NULL;
        }
        if (pipe(pipes[i]) == -1)
        {
            perror("Error creating pipe");
            // Free all allocated memory
            while (i >= 0)
                free(pipes[i]);
            free(pipes);
            return NULL;
        }
    }
    return pipes;
}

void free_pipes(int **pipes, int pipe_count)
{
    for (int i = 0; i < pipe_count; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        free(pipes[i]);
    }
    free(pipes);
}

int main(int argc, char *argv[], char *envp[])
{
    int cmd_count = argc - 3;
    int pipe_count = cmd_count - 1;
    
    int **pipes = create_pipes(pipe_count);
    if (!pipes)
    {
        perror("Error allocating pipes");
        exit(1);
    }

    // Rest of your pipe logic here...

    // Don't forget to free at the end
    free_pipes(pipes, pipe_count);
    return 0;
}