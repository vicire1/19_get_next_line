# Get_Next_Line

<img width="654" alt="Get_next_line" src="https://github.com/user-attachments/assets/d42866fe-7b13-4c51-8cb1-97c2e8c323c8">

## Description

The **Get Next Line** project involves writing a function that reads a line from a file descriptor and returns it. This project is an excellent opportunity to learn about static variables in C, which allow you to maintain state across multiple function calls.

## Project Objectives

- Implement a function that reads and returns a line from a file descriptor.
- Understand and utilize static variables in C.
- Handle file I/O in a controlled and efficient manner.
- Develop a reusable function that can be integrated into future projects.

## Content

- **Mandatory Part:**
  - Implement the `get_next_line()` function with the following prototype:

    ```c
    char *get_next_line(int fd);
    ```

  - The function should:
    - Return a line from the file descriptor, including the newline character (`\n`).
    - Return `NULL` when there is nothing more to read or if an error occurs.
    - Handle both file input and standard input (stdin).

  - Constraints:
    - The function should work with multiple consecutive calls, returning one line at a time.
    - Must be able to handle varying buffer sizes defined by the `BUFFER_SIZE` macro.

  - Compilation:
    - The function should be compiled with the following command, where `42` is an example buffer size:
      ```bash
      cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c
      ```

- **Bonus Part:**
  - Implement the following additional features:
    - Support multiple file descriptors simultaneously without losing track of the current reading position.
    - Use only one static variable per file descriptor.

## Compilation

1. **Compile the library:**

   ```bash
   make
   ```

2. **Clean object files:**

   ```bash
   make clean
   ```

3. **Remove all generated files, including the library:**

   ```bash
   make fclean
   ```

4. **Recompile everything from scratch:**

   ```bash
   make re
   ```

5. **Include bonus functions:**

   ```bash
   make bonus
   ```

## Usage

To use the get_next_line() function in your project, include the necessary header files and compile your program with the appropriate source files:

```c
#include "get_next_line.h"

int main(void) {
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

To compile a program using Get_next_line:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 your_program.c get_next_line.c get_next_line_utils.c -o your_program
```
