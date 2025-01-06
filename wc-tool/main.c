#include <stdio.h>
#include <stdlib.h>

// Function to get the size of the file in bytes
long int getFileSize(const char *filename) {
    FILE *fp = fopen(filename, "rb"); // Open the file in binary mode
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }
    if (fseek(fp, 0L, SEEK_END) != 0) { // Move to the end of the file
        perror("Error seeking file");
        fclose(fp);
        return -1;
    }

    long int size = ftell(fp); // Get the current position in the file (size in bytes)
    if (size == -1) {
        perror("Error determining file size");
    }

    fclose(fp);
    return size;
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        // Check if the first argument is "-c"
        if (argv[1][0] == '-' && argv[1][1] == 'c' && argv[1][2] == '\0') {
            long int fileSize = getFileSize(argv[2]);
            if (fileSize != -1) {
                printf("%ld\n", fileSize);
            }
        } else {
            fprintf(stderr, "Invalid option. Usage: %s -c <filename>\n", argv[0]);
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s -c <filename>\n", argv[0]);
        return 1;
    }

    return 0;
}

