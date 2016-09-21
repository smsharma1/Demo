#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>

#define SUM_KEY 19


int main (void)
{
        int i, shm_id;
        char *shm;
        shm_id = shmget(SUM_KEY, 256, 0777 | IPC_CREAT);

        if (fork() == 0) {
                shm = (char*)shmat(shm_id, 0, 0);
		scanf("%s",shm);
		//printf("This is shmctl:%d\n", shmctl(shm_id, IPC_RMID, NULL));
        }
        else {
                shm = (char*)shmat(shm_id, 0, 0);
                wait(NULL);
		printf("%s\n",shm);
                printf("This is shmctl in parent:%d\n",shmctl(shm_id, IPC_RMID, NULL));
             }
        shmdt(shm);
        return 0;
}
                   
