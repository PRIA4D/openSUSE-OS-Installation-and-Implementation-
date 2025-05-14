#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main() {
    const char *filename = "example.txt";
    const char *data = "This data must be flushed to disk!\n";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    size_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    if (fdatasync(fd) == -1) {
        perror("fdatasync");
        close(fd);
        return 1;
    }

    printf("Data written and flushed to disk using fdatasync().\n");

    close(fd);
    return 0;
}
