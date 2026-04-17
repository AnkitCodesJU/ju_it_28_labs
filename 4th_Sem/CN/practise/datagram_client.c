#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <sys/socket.h>a
// #include<arpa/inet.in>

#define ip_address "172.16.5.13"
#define port 8080
int main()
{
    int c_sockfd;
    // int c_len, count=0;
    socklen_t c_len; // changed
    int count = 0;   // changed
    char in_buffer[100], out_buffer[100];
    struct sockaddr_in c_address;

    c_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    c_address.sin_family = AF_INET;
    c_address.sin_port = htons(port);
    c_address.sin_addr.s_addr = inet_addr(ip_address);
    c_len = sizeof(c_address);

    while (count != 5)
    {
        printf("enter your message: ");
        scanf("%[^\n]", out_buffer);
        getchar();
        sendto(c_sockfd, out_buffer, strlen(out_buffer) + 1, 0, (struct sockaddr *)&c_address, c_len);

        recvfrom(c_sockfd, in_buffer, sizeof(in_buffer), 0, (struct sockaddr *)&c_address, &c_len);
        printf("received message: %s \n", in_buffer);

        count++;
    }
    close(c_sockfd);
}
