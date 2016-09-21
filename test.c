#include<stdlib.h>
#include<stdio.h>
int main(){
int i;
for(i=0;i<6;i++){
	if(fork()==0){
		printf("i%d\n",getpid());
		break;
	}
}
if(i>=6){
	for(i=0;i<6;i++){
		printf("w%d\n",getpid());
		wait(NULL);
		}
}
return 0;
}
