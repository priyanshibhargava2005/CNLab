#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_SIZE 4    // Define the window size for selective repeat
#define TOTAL_PACKETS 10 // Total number of packets to send

// Function to simulate random acknowledgment reception (simulating ACK or NAK)
bool receive_ack()
{
    return rand() % 2; // Randomly return true (ACK received) or false (NAK received)
}

int main()
{
    int base = 0;                        // First unacknowledged packet in the window
    int next_seq_num = 0;                // Next packet to be sent
    bool acked[TOTAL_PACKETS] = {false}; // Array to track the acknowledgment status of each packet

    // Seed the random number generator for simulating packet acknowledgment/loss
    srand(time(0));

    // Loop until all packets are acknowledged
    while (base < TOTAL_PACKETS)
    {
        // Send packets within the window limit
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_PACKETS)
        {
            if (!acked[next_seq_num])
            { // Only send packets that have not been acknowledged
                printf("Sending packet %d\n", next_seq_num);
            }
            next_seq_num++;
        }

        // Check for acknowledgments within the current window range
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_PACKETS; i++)
        {
            if (!acked[i])
            { // Check only packets that have not yet been acknowledged
                if (receive_ack())
                {
                    printf("Acknowledgment received for packet %d\n", i);
                    acked[i] = true; // Mark packet as acknowledged
                }
                else
                {
                    printf("Packet %d lost. Will resend.\n", i);
                }
            }
        }

        // Slide the window forward if the base packet has been acknowledged
        while (base < TOTAL_PACKETS && acked[base])
        {
            base++; // Move the base to the next unacknowledged packet
        }

        // Reset `next_seq_num` to the new base, allowing resending of any lost packets in the window
        next_seq_num = base;
        printf("Window moved to base %d\n\n", base);
    }

    // Print completion message once all packets are acknowledged
    printf("All packets sent and acknowledged successfully!\n");
    return 0;
}
