#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_SIZE 4   // Define the window size
#define TOTAL_PACKETS 10 // Total number of packets to send

// Function to simulate random acknowledgment reception
bool receive_ack() {
    return rand() % 2; // Randomly return true or false (simulating ACK or NAK)
}

int main() {
    int base = 0;
    int next_seq_num = 0;
    bool acked[TOTAL_PACKETS] = {false};  // Array to track acknowledgment of each packet

    // Seed random number generator
    srand(time(0));

    while (base < TOTAL_PACKETS) {
        // Send packets within the window
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_PACKETS) {
            if (!acked[next_seq_num]) { // Only send unacknowledged packets
                printf("Sending packet %d\n", next_seq_num);
            }
            next_seq_num++;
        }

        // Check for acknowledgments within the current window
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_PACKETS; i++) {
            if (!acked[i]) { // Check only unacknowledged packets
                if (receive_ack()) {
                    printf("Acknowledgment received for packet %d\n", i);
                    acked[i] = true; // Mark packet as acknowledged
                } else {
                    printf("Packet %d lost. Will resend.\n", i);
                }
            }
        }

        // Slide the window if the base packet is acknowledged
        while (base < TOTAL_PACKETS && acked[base]) {
            base++;
        }

        // Reset next_seq_num to the new base to resend any lost packets in the window
        next_seq_num = base;
        printf("Window moved to base %d\n\n", base);
    }

    printf("All packets sent and acknowledged successfully!\n");
    return 0;
}
