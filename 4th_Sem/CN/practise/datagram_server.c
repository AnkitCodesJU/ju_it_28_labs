#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <sys/socket.h>
// #include<arpainet.in>

#define port 8080
int main()
{
    int s_sockfd;
    // int s_len, c_len, count=0;
    socklen_t s_len, c_len; // changed
    int count = 0;          // changed
    char in_buffer[100], out_buffer[100];
    struct sockaddr_in s_address, c_address;

    s_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    s_address.sin_family = AF_INET;
    s_address.sin_port = htons(port);
    s_address.sin_addr.s_addr = htonl(INADDR_ANY);
    s_len = sizeof(s_address);

    bind(s_sockfd, (struct sockaddr *)&s_address, s_len);

    c_len = sizeof(c_address);
    while (count != 5)
    {
        recvfrom(s_sockfd, in_buffer, sizeof(in_buffer), 0, (struct sockaddr *)&c_address, &c_len);
        printf("\n received message: ‘%s’ \n", in_buffer);

        printf("enter your message: ");
        scanf("%[^\n]", out_buffer);
        getchar();
        sendto(s_sockfd, out_buffer, strlen(out_buffer) + 1, 0, (struct sockaddr *)&c_address, c_len);
        count++;
    }
    close(s_sockfd);
}
