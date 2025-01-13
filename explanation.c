parent pipe1[2];-------pipe[2];
|                      |
child1 pipe1[2]      child2 pipe[2]; READS FROM pipe1[0];
{                           {
    close pipe1[0];               close(pipe2[1]);
    dup2(infile_fd, 0);           dup2(pipe1[0], 0);
    dup2(pipe1[1], 1);            dup2(outfile_fd, 1);
}                            }
child1 reads from infile


parent proccess
{
    while (command)
    {
        pipe(pipe[2])
        fork();
        if (first command)
            dup2(infile_fd, 0);
        if (child)
        {
            
        }
        dup2(pipe[0], 0);
        close(pipe[0]);
    }
}