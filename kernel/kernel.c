void main()
{
    int (*uart_spin_puts)(const char *) = (void *)0x1ff0000c;
    uart_spin_puts("Welcome to the kernel on the Arm!\r\n");
    uart_spin_puts("Waiting for the next programming!\r\n");
}
