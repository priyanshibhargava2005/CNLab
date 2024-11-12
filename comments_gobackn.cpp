#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_SIZE 4    // Define the window size, i.e., the number of packets sent without waiting for an ACK
#define TOTAL_PACKETS 10 // Total number of packets to be sent

int main()
{
    int base = 0;         // 'base' is the starting position of the window, tracking the first unacknowledged packet
    int next_seq_num = 0; // 'next_seq_num' keeps track of the next packet sequence number to be sent

    // Seed the random number generator for simulating packet loss and acknowledgments
    srand(time(0));

    // Continue sending packets until all packets are acknowledged
    while (base < TOTAL_PACKETS)
    {
        // Send packets within the current window size
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_PACKETS)
        {
            printf("Sending packet %d\n", next_seq_num); // Send the packet
            next_seq_num++;                              // Move to the next packet in sequence
        }

        // Simulate receiving an acknowledgment (ACK) or a packet loss (NAK)
        bool ack_received = rand() % 2; // Randomly simulate ACK (1) or NAK (0)

        if (ack_received) // If ACK received
        {
            printf("Acknowledgment received for packet %d\n", base); // Print ACK for the base packet
            base++;                                                  // Slide the window forward by one, as the base packet was acknowledged
        }
        else // If packet was lost (NAK received)
        {
            printf("Packet %d lost. Resending from packet %d\n", base, base);
            next_seq_num = base; // Reset next_seq_num to the base to resend all packets from base onwards
        }
    }

    printf("All packets sent successfully!\n"); // Final message once all packets have been successfully acknowledged
    return 0;
}
