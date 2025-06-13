#include <stdio.h>
#include <libusb-1.0/libusb.h>

#define VENDOR_ID  0x0bda
#define PRODUCT_ID 0x2838

int main() 
{
    libusb_context *ctx = NULL;
    libusb_device_handle *dev_handle = NULL;

    int r = libusb_init(&ctx);
    if (r < 0) {
        fprintf(stderr, "libusb init error\n");
        return 1;
    }

    dev_handle = libusb_open_device_with_vid_pid(ctx, VENDOR_ID, PRODUCT_ID);
    if (!dev_handle) 
    {
        fprintf(stderr, "Cannot open RTL-SDR device\n");
        libusb_exit(ctx);
        return 1;
    }

    // Now safe to check for kernel driver
    if (libusb_kernel_driver_active(dev_handle, 0) == 1) 
    {
        printf("Kernel driver active, detaching...\n");
        if (libusb_detach_kernel_driver(dev_handle, 0) != 0) 
        {
            fprintf(stderr, "Failed to detach kernel driver\n");
            libusb_close(dev_handle);
            libusb_exit(ctx);
            return 1;
        }
    }

    printf("RTL-SDR device opened successfully\n");

    // Claim interface 0 (used for data)
    if (libusb_claim_interface(dev_handle, 0) < 0) {
        fprintf(stderr, "Failed to claim interface\n");
        libusb_close(dev_handle);
        libusb_exit(ctx);
        return 1;
    }

    // Example: read USB control data (you need reverse-engineered commands for real use)
    unsigned char data[1];
    int status = libusb_control_transfer(
        dev_handle,
        LIBUSB_ENDPOINT_IN | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE,
        0x00,  // bRequest (depends on command)
        0x0000, 0x0000, // wValue, wIndex
        data, sizeof(data),
        1000
    );

    if (status >= 0) {
        printf("Control transfer successful: %02x\n", data[0]);
    } else {
        fprintf(stderr, "Control transfer failed\n");
    }

    libusb_release_interface(dev_handle, 0);
    libusb_close(dev_handle);
    libusb_exit(ctx);
    return 0;
}

