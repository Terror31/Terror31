#include <stdint.h>
#include <stdio.h>

// Constants for device types
#define DEVICE_TYPE_AGITO  0x01
#define DEVICE_TYPE_MASTER 0x02
#define DEVICE_TYPE_HUB    0x03

// Function to decode and check the packet contents
void decodeBuffer(uint8_t *packetBuffer) {
    // Extract packet header fields
    uint8_t deviceType = packetBuffer[0];
    uint8_t deviceID = packetBuffer[1];
    uint8_t packetLength = packetBuffer[2];
    uint32_t checksum = *(uint32_t*)&packetBuffer[3];
    uint16_t dataAddress = *(uint16_t*)&packetBuffer[7];
    uint8_t rwCommand = packetBuffer[9];

    // Check for valid device types
    if (deviceType != DEVICE_TYPE_AGITO && deviceType != DEVICE_TYPE_MASTER && deviceType != DEVICE_TYPE_HUB) {
        printf("Invalid device type\n");
        return;
    }

    // Calculate the expected checksum 
    uint32_t expectedChecksum = calculateChecksum(packetBuffer, packetLength + 3);

    if (checksum != expectedChecksum) {
        printf("Checksum mismatch\n");
        return;
    }

    // Handle payload data (if any)
    if (packetLength > 0) {
        // Extract and process payload data
        uint8_t *payload = &packetBuffer[10];

        // checking device type input
        printf("Device Type: ");
        if (deviceType == DEVICE_TYPE_AGITO) {
            printf("AGITO");
        } else if (deviceType == DEVICE_TYPE_MASTER) {
            printf("MASTER");
        } else if (deviceType == DEVICE_TYPE_HUB) {
            printf("HUB");
        } else {
            printf("Unknown");
        }
        printf("\n");

        printf("Packet Length: %d\n", packetLength);
        printf("Data Address: %u\n", dataAddress);

        printf("Read/Write Command: ");
        if (rwCommand == 0x01) {
            printf("Read\n");
        } else if (rwCommand == 0x02) {
            printf("Write\n");
        } else {
            printf("Unknown\n");
        }

        
    } else {
        printf("No payload data to process\n");
    }
}

// Function to calculate the checksum (
uint32_t calculateChecksum(uint8_t *buffer, uint8_t length) {
    

int main() {
    // Sample raw data buffer
    uint8_t rawData[] = {0x01, 0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x11, 0x22, 0x33, 0x44};//raw data for comparing

    decodeBuffer(rawData);

    return 0;
}
