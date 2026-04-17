#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_PKT_SIZE 100

typedef struct {
    char data[MAX_PKT_SIZE];
} Packet;

typedef struct {
    Packet payload;
} Frame;

typedef enum { frame_arrival, no_event } event_type;

int sock; // Global socket descriptor

// -------- Function Prototypes --------
void sender(void);
void WaitForEvent(event_type *event);
void GetData(Packet *p);
Frame MakeFrame(Packet p);
void SendFrame(Frame f);

// -------- Main --------
int main() {

    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n\n");

    sender();

    close(sock);
    return 0;
}

// -------- Sender Implementation --------
void sender(void)
{
    Packet buffer;
    Frame s;
    event_type event;

    WaitForEvent(&event);
    GetData(&buffer);
    s = MakeFrame(buffer);
    SendFrame(s);
}

void GetData(Packet *p) {
    printf("Enter message to send: ");
    fgets(p->data, MAX_PKT_SIZE, stdin);
    p->data[strcspn(p->data, "\n")] = 0;
}

Frame MakeFrame(Packet p) {
    Frame f;
    f.payload = p;
    printf("[Sender] Frame created successfully.\n");
    return f;
}

void SendFrame(Frame f) {
    send(sock, &f, sizeof(f), 0);
    printf("Frame sent to server.\n");
}

void WaitForEvent(event_type *event) {
    *event = frame_arrival;
}

