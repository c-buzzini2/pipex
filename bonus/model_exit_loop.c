int main() {
    pid_t pid;
    int status;

    // Example: Creating an unknown number of child processes
    for (int i = 0; i < 5; i++) {  // You can replace 5 with a dynamic value
        pid = fork(); // here you keep replacing it. I have the option of saving this number first
        
        if (pid == 0) {
            // Child process
            printf("Child %d (PID %d) started\n", i, getpid());
            sleep(2); // Simulate some work
            exit(i);  // Each child exits with a different code
        }
    }

    // Parent process: wait for all child processes
    pid_t child_pid;
    while ((child_pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child PID %d exited with status %d\n", child_pid, WEXITSTATUS(status));
        } else {
            printf("Child PID %d terminated abnormally\n", child_pid);
        }
    }

    printf("All children have finished.\n");
    return 0;
}
