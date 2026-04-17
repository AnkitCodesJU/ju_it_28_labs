#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_PKT_SIZE 100

typedef struct {
    char data[MAX_PKT_SIZE];
} Packet;

typedef struct {
    Packet payload;
} Frame;

typedef enum { frame_arrival, no_event } event_type;

// Global variable to simulate the physical medium/channel
Frame shared_channel;

// --- Functional Prototypes ---
void sender(void);
void receiver(void);

// Helper functions as per requirements
void WaitForEvent(event_type *event);
void GetData(Packet *p);
Frame MakeFrame(Packet p);
void SendFrame(Frame f);
void ReceiveFrame(Frame *f);
Packet ExtractData(Frame f);
void DeliverData(Packet p);

// --- Main Execution ---
int main() 
{
    printf("--- Simplest Protocol Simulation ---\n\n");
     sender();
    printf("\n------------------------------------------\n\n");
    receiver();
    return 0;
}

// --- Sender Site Implementation ---
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
    shared_channel = f;
    printf("Frame sent to the channel.\n");
}

// --- Receiver Site Implementation ---
void receiver(void) {
    Packet buffer;
    Frame r;
    event_type event;
    WaitForEvent(&event);
    if (event == frame_arrival) {
        ReceiveFrame(&r);
        buffer = ExtractData(r);
        DeliverData(buffer);
    }
}

void ReceiveFrame(Frame *f) {
    *f = shared_channel;
    printf("Frame picked up from channel.\n");
}

Packet ExtractData(Frame f) {
    printf("Extracting packet from frame...\n");
    return f.payload;
}

void DeliverData(Packet p) {
    printf("DATA DELIVERED: %s\n", p.data);
}

void WaitForEvent(event_type *event) {
    *event = frame_arrival;
}
