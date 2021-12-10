# Functions:

## fork
int fork(void)

Result value:
- Zero: if it is the child process(Process created).
- Positive value: if it is the parent process.
- Negative value: if an error ocurred.

## getpid & getppid
Get process identification.
From: "unistd.h"

pid_t getpid(void)
pid_t getppid(void)

return value: pid_t

## wait
pid_t wait(int *status)

## waitpid

pid_t waitpid(pid_t pid, int *status, int options);
