#include "server.h"

void main()
{
    signal(SIGINT, handle_interrupt_signal);

    start_server();
}