#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/syscall.h>

int x=6, y=-1, z=-1;
int f(void *arg)
{
if (z > getpid()) {
x++;
printf("%d,", x); fflush(stdout);
}
else {
x += 2;
if (y == syscall(SYS_gettid)) {
printf("%d,", x); fflush(stdout);
}
else {
x--;
printf("%d,", x); fflush(stdout);
}
}
return x;
}
int main(void)
{
void *child_stack;
int u = fork();
if (u==0) {
z = getpid();
x=x/2;
child_stack = malloc(16384);
clone(f, child_stack+16384, CLONE_VM | CLONE_THREAD | CLONE_SIGHAND, NULL);
while(1);
printf("%d,", x); fflush(stdout);
}
else {
wait(NULL);
x = f(NULL);
printf("%d,", x); fflush(stdout);
}
x -= 4;
printf("%d,", x); fflush(stdout);
return 0;
}
