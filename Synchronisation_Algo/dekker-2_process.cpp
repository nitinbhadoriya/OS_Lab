#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/wait.h> 
#include <sys/ipc.h>
#include <sys/shm.h>	
using namespace std;
int main()
{
	int shmid, status;
	int *a, *b, *c;

	shmid = shmget(IPC_PRIVATE, 3*sizeof(int), 0777|IPC_CREAT);
	c= (int *) shmat(shmid, 0, 0);
	c[0]=0,c[1]=0,c[2]=1;
	if (fork() == 0) {

		/* Child Process */

		
		b = (int *) shmat(shmid, 0, 0);
		
		while(1){
			b[0]=1;
			while(b[1]==1){
				if(b[2]==2){
					b[0]=0;
					while(b[2]!=1);
					b[0]=1;
				}
			}
			sleep(1);
			cout<<"1 is entering critical section\n";
			//critical section
			sleep(1);
			cout<<"1 is leaving critical section\n";
			b[2]=2;
			b[0]=0;
		}

	}
	else {

		/* Parent Process */
		a = (int *) shmat(shmid, 0, 0);
		while(1){
			a[1]=1;
			while(a[0]==1){
				if(a[2]==1){
					a[1]=0;
					while(a[2]!=2);
					a[1]=1;
				}
			}
			sleep(1);
			cout<<"2 is entering critical section\n";
			//critical section
			sleep(1);
			cout<<"2 is leaving critical section\n";
			a[2]=1;
			a[1]=0;
		}
	}
}
