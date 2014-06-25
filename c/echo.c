#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stddef.h>

/**
 * struct sockaddr_in {
 *  sa_family_t sin_family;
 *  in_port_t sin_port;
 *  struct in_addr sin_addr;
 * };
 *
 */
int main(int argc, char * argv[]) {

    int fd, clifd;
    struct sockaddr_in addr_in;
    char buf[1024];
    char path[] = "test.sock";
    int len = sizeof(addr_in);

    if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        printf("create socket error %d:%s\n", errno, strerror(errno));
        return -1;
    }

    memset(&addr_in, 0, sizeof(addr_in));
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(9818);
    addr_in.sin_addr.s_addr = htonl(INADDR_ANY);


    if (bind(fd, (struct sockaddr *)&addr_in, len) < 0) {
        printf("bind socket error %d:%s\n", errno, strerror(errno));
        return -1;
    }

    if (listen(fd, 5) < 0) {
        printf("listen socket error %d:%s\n", errno, strerror(errno));
        return -1;
    }

    if ((clifd = accept(fd, (struct sockaddr *)&addr_in, &len)) < 0) {
        printf("accept socket error %d\n", errno);
        return -1;
    }


    while ((len = read(clifd, buf, sizeof(buf)-1)) > 0) {
        printf("RECV(%d):%s", len, buf);
        write(clifd, buf, len);
    }

    close(clifd);
    close(fd);
    return 0;
}
