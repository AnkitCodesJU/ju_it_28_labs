#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>

#define port 8080

int main()
{
   int s_sockfd, c_sockfd;
   //int s_len, c_len, count = 0;
   int count=0;//changed
   socklen_t s_len,c_len;
   char in_buffer[100], out_buffer[100];
   struct sockaddr_in s_address, c_address;

   // Create socket
   s_sockfd = socket(AF_INET, SOCK_STREAM, 0);

   // Server address
   s_address.sin_family = AF_INET;
   s_address.sin_port = htons(port);
   s_address.sin_addr.s_addr = htonl(INADDR_ANY);
   s_len = sizeof(s_address);

   // Bind
   bind(s_sockfd, (struct sockaddr*)&s_address, s_len);

   // Listen
   listen(s_sockfd, 5);

   // Accept connection
   c_len = sizeof(c_address);
   c_sockfd = accept(s_sockfd, (struct sockaddr*)&c_address, &c_len);

   while(count != 5)
   {
       // Receive from client
       recv(c_sockfd, in_buffer, sizeof(in_buffer), 0);
       printf("\nReceived message: '%s'\n", in_buffer);

       // Send to client
       printf("Enter your message: ");
       scanf("%[^\n]", out_buffer);
       getchar();

       send(c_sockfd, out_buffer, strlen(out_buffer)+1, 0);

       count++;
   }

   close(c_sockfd);
   close(s_sockfd);
   return 0;
}
