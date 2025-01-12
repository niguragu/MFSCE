#define len 14
volatile char mmio_data[len] __attribute__((section(".mmio")));

int main()
{
    const char *str = "Hello, world!";

    for (int i = 0; i < len; i++)
    {
        mmio_data[i] = str[i];
    }

    return 0;
}