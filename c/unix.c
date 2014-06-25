#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>

/**
 * struct sockaddr_un {
 *  sa_family_t sun_family;
 *  char sun_path[108];
 * };
 *
 */
int main(int argc, char * argv[]) {

    int fd, clifd;
    struct sockaddr_un un;
    char buf[1024];
    char path[] = "test.sock";
    int len = sizeof(struct sockaddr_un);

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        printf("create socket error %d:%s\n", errno, strerror(errno));
        return -1;
    }

    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, path);

    unlink(path);

    if (bind(fd, (struct sockaddr *)&un, len) < 0) {
        printf("bind socket error %d:%s\n", errno, strerror(errno));
        return -1;
    }

    if (listen(fd, 5) < 0) {
        printf("listen socket error %d:%s\n", errno, strerror(errno));
        return -1;
    }

    if ((clifd = accept(fd, (struct sockaddr *)&un, &len)) < 0) {
        printf("accept socket error %d\n", errno);
        return -1;
    }


    while ((len = read(clifd, buf, sizeof(buf)-1)) > 0) {
        printf("RECV:%s", buf);
        write(clifd, buf, len);
    }

    close(clifd);
    close(fd);
    return 0;
}
