volatile int mmio_data  __attribute__((section(".mmio")));

int main()
{
    int a = 1;
    int b = 2;
    int c =a + b;
    mmio_data = 0x55;
    return 0;
}