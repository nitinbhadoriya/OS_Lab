#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

bool wantp=false,wantq=false;
int turn=1;
void*p(void*arg){
	while(1){
		//non-critical section
		
		wantp=true;
		while(wantq==true){
			if (turn==2){
				wantp=false;
				while(turn!=1);
				wantp=true;
			}
		}
		//critical section
		sleep(1);
		cout<<"1 is in critical section\n";
		sleep(1);
		cout<<"1 is leaving critical section\n";
		turn=2;
		wantp=false;
	}
}
void q(){
	while(1){
		//non-critical section
		
		wantq=true;
		while(wantp==true){
			if(turn==1){
				wantq=false;
				while(turn!=2);
				wantq=true;
			}
		}
		//critical section
		sleep(1);
		cout<<"2 is in critical section\n";
		sleep(1);
		cout<<"2 is leaving critical section\n";
		turn=1;
		wantq=false;
	}
}

int main() {
	pthread_t thread_p,thread_q;
	pthread_create(&thread_p,NULL,p,NULL);
	q();
	return 0;
}
