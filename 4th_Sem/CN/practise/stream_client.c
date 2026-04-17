#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>

#define ip_address "172.16.5.13"
#define port 8080

int main()
{
   int c_sockfd;
   int count = 0;
   char in_buffer[100], out_buffer[100];
   struct sockaddr_in c_address;

   // Create socket
   c_sockfd = socket(AF_INET, SOCK_STREAM, 0);

   // Server address
   c_address.sin_family = AF_INET;
   c_address.sin_port = htons(port);
   c_address.sin_addr.s_addr = inet_addr(ip_address);

   // Connect to server
   connect(c_sockfd, (struct sockaddr*)&c_address, sizeof(c_address));

   while(count != 5)
   {
       // Send message
       printf("Enter your message: ");
       scanf("%[^\n]", out_buffer);
       getchar();
       send(c_sockfd, out_buffer, strlen(out_buffer)+1, 0);
       // Receive reply
       recv(c_sockfd, in_buffer, sizeof(in_buffer), 0);
       printf("Received message: '%s'\n", in_buffer);

       count++;
   }

   close(c_sockfd);
   return 0;
}
