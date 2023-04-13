#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_PATH_LENGTH 256
#define MAX_BUF_SIZE 1024

void fatal_error(char *message) {
    printf("[!] Error: %s\n", message);
    exit(1);
}

void print_memory_addresses(pid_t pid) {
    // Construct the path to the process's maps file
    char path[MAX_PATH_LENGTH];
    sprintf(path, "/proc/%d/maps", pid);
    // Open the process's maps file for reading
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        fatal_error("Failed to open process maps file");
    }
    // Read the memory map entries from the file and print the open memory addresses
    char buffer[MAX_BUF_SIZE];
    while (read(fd, buffer, MAX_BUF_SIZE) > 0) {
        char *ptr = strtok(buffer, "\n");
        while (ptr != NULL) {
            char *start_address_str = strtok(ptr, "-");
            char *end_address_str = strtok(NULL, " ");
            if (start_address_str != NULL && end_address_str != NULL) {
                void *start_address = (void *)strtoul(start_address_str, NULL, 16);
                void *end_address = (void *)strtoul(end_address_str, NULL, 16);
                if (start_address != NULL && end_address != NULL) {
                    printf("[+] Open memory address range: %p - %p\n", start_address, end_address);
                }
            }
            ptr = strtok(NULL, "\n");
        }
    }
    // Close the process's maps file
    close(fd);
}

int main(int argc, char *argv[]) {
    // Check the command-line arguments
    if (argc != 2) {
        fatal_error("Usage: memmap <pid>");
    }
    // Parse the process ID from the command-line argument
    pid_t pid = atoi(argv[1]);
    if (pid <= 0) {
        fatal_error("Invalid process ID");
    }
    // Print the process ID and the open memory addresses
    printf("[+] Found process %d\n", pid);
    print_memory_addresses(pid);
    return 0;
}

