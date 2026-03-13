#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    int in, out;
    ssize_t nread;
    char buffer[1024];

    if (argc != 3) {
        fprintf(stderr,"Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(1);
    }

    in = open(argv[1], O_RDONLY);
    if (in < 0) {
        perror("Error opening source file");
        exit(1);
    }

    out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out < 0) {
        perror("Error opening destination file");
        close(in);
        exit(1);
    }

    while ((nread = read(in, buffer, sizeof(buffer))) > 0) {
        write(out, buffer, nread);
    }

    close(in);
    close(out);

    return 0;
}
