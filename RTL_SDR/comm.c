#include <stdio.h>
#include <rtl-sdr.h>

int main() {
    rtlsdr_dev_t *dev = NULL;
    int r = rtlsdr_open(&dev, 0);
    if (r < 0) {
        fprintf(stderr, "Failed to open RTL-SDR device\n");
        return 1;
    }
    printf("RTL-SDR device opened\n");

    // Set sample rate to 2.4 MHz
    r = rtlsdr_set_sample_rate(dev, 2400000);
    if (r < 0) {
        fprintf(stderr, "Failed to set sample rate\n");
        rtlsdr_close(dev);
        return 1;
    }
    printf("Sample rate set to 2.4 MHz\n");

    // Set frequency to 94.5 MHz (94500000 Hz)
    r = rtlsdr_set_center_freq(dev, 94500000);
    if (r < 0) {
        fprintf(stderr, "Failed to set frequency\n");
        rtlsdr_close(dev);
        return 1;
    }
    printf("Frequency set to 94.5 MHz\n");

    rtlsdr_reset_buffer(dev);

    #define BUF_SIZE 16384
    uint8_t buf[BUF_SIZE];
    int n_read = 0;

    r = rtlsdr_read_sync(dev, buf, BUF_SIZE, &n_read);
    if (r < 0) {
        fprintf(stderr, "rtlsdr_read_sync failed: %d\n", r);
        rtlsdr_close(dev);
        return 1;
    }
    printf("Read %d bytes\n", n_read);

    r = rtlsdr_read_sync(dev, buf, BUF_SIZE, &n_read);
    if (r < 0) {
        fprintf(stderr, "rtlsdr_read_sync failed: %d\n", r);
        rtlsdr_close(dev);
        return 1;
    }
    printf("Read %d bytes\n", n_read);

    rtlsdr_close(dev);
    return 0;
}
