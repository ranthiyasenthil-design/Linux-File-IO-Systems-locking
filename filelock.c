#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>

int main(int argc, char *argv[])
{
    int fd;

    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    printf("Opening file: %s\n", argv[1]);

    fd = open(argv[1], O_WRONLY | O_CREAT, 0644);

    if (fd == -1)
    {
        perror("Error opening file");
        exit(1);
    }

    printf("Trying to acquire lock...\n");

    if (flock(fd, LOCK_EX) == -1)
    {
        perror("Error locking file");
        close(fd);
        exit(1);
    }

    printf("File locked successfully.\n");
    printf("Press Enter to unlock the file...\n");
    getchar();

    if (flock(fd, LOCK_UN) == -1)
    {
        perror("Error unlocking file");
        close(fd);
        exit(1);
    }

    printf("File unlocked successfully.\n");

    close(fd);

    return 0;
}
