#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


static void exitsig(int signum)
{
    if (signum == SIGINT)
        exit (1);
}

static void father_sig_handler(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
    sa.sa_handler = exitsig;
    sigaction(SIGINT, &sa, NULL);

    printf("Start %d\n", signum);
    sleep(1);
    printf("Stop\n");
}

int main(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGTERM);

    sa.sa_handler = father_sig_handler;

    while (1)
        sigaction(SIGINT, &sa, NULL);
    return 0;
}
