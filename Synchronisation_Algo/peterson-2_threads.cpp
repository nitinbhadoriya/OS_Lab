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
		turn=2;
		while(wantq==true && turn==2);
		//critical section
		sleep(1);
		cout<<"1 is in critical section\n";
		sleep(1);
		cout<<"1 is leaving critical section\n";
		wantp=false;
	}
}
void q(){
	while(1){
		//non-critical section
		
		wantq=true;
		turn=1;
		while(wantp==true && turn==1);
		//critical section
		sleep(1);
		cout<<"2 is in critical section\n";
		sleep(1);
		cout<<"2 is leaving critical section\n";
		wantq=false;
	}
}

int main() {
	pthread_t thread_p,thread_q;
	pthread_create(&thread_p,NULL,p,NULL);
	q();
	return 0;
}
