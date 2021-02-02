#include<bits/stdc++.h>
using namespace std;
class Process{
	public:
	int pid;
	int a_time;
	int p;
	int s;
	vector<int> b;
	int t_time;
	int w_time;
	int r_time;
	int ind;
	int len;
	int total_util;
	void input(){
		ind=0;
		cin>>pid;
		cin>>a_time;
		cin>>p;
		cin>>s;
		char c;
		cin>>c;
		while(c!='-'){
			int x;
			cin>>x;
			if(c=='C'){
				if(b.size()%2==0){
					b.push_back(x);
				}
				else{
					b[b.size()-1]+=x;
				}
			}
			else{
				if(b.size()%2==0){
					b[b.size()-1]+=x;
				}
				else{
					b.push_back(x);
				}
			}
			cin>>c;
		}
		len=b.size();
		cin>>c;
		total_util=accumulate(b.begin(),b.end(),0);
		/*for(auto x:b){
			cout<<x<<" ";
		}
		cout<<"\n";*/
	}
	
};

void avg(vector<Process> &a,vector<int> &g,vector<int> &io){
		for(auto &x:a){
			for(int i=0;i<g.size();i++){
				if(x.pid==g[i]){
					x.r_time=i-x.a_time;
					break;
				}
			}
			for(int i=g.size()-1;i>=0;i--){
				if(x.pid==g[i]||x.pid==io[i]){
					x.t_time=i+1-x.a_time;
					break;
				}
			}
			x.w_time=x.t_time-x.total_util;
		}
		

}
void stats(vector<Process> &a){
		float t=0,w=0,r=0;
		for(auto x:a){
			t+=x.t_time;
			w+=x.w_time;
			r+=x.r_time;
		}
		cout<<"Process\tResponse Time\tTurnaround time\tWaiting Time\n";
		for(auto x:a){
			cout<<x.pid<<"\t\t"<<x.r_time<<"\t\t"<<x.t_time<<"\t\t"<<x.w_time<<"\n";
		}
		cout<<"Average Response time: "<<r/a.size()<<"\n";
		cout<<"Average Turnaround time: "<<t/a.size()<<"\n";
		cout<<"Average Waiting time: "<<w/a.size()<<"\n";
}
int main(){

	freopen("process.dat","r",stdin);
	int n;
	cin>>n;
	vector<Process> arr(n);


	for(int i=0;i<n;i++){
		arr[i].input();
	}
	
	sort(arr.begin(),arr.end(),[](Process p1, Process p2){
		return p1.a_time<p2.a_time ||((p1.a_time==p2.a_time)&&(p1.pid<p2.pid));
	});


	int t=0;
	int ind=0;
	vector<int> g_cpu,g_io;
	queue<Process> rdc,rdi;
	while(rdc.empty()==false || rdi.empty()==false || ind!=n){
		while(ind<n && arr[ind].a_time<=t){
			rdc.push(arr[ind]);
			ind++;
		}
		int flag=0;
		if(rdc.empty()==false){
			Process &x=rdc.front();
			g_cpu.push_back(x.pid);
			x.b[x.ind]--;
			if(x.b[x.ind]==0){
				x.ind++;
				if(x.ind<x.len){
					rdi.push(x);
					if(rdi.size()==1){
						flag=1;
						g_io.push_back(-1);
					}
				}
				rdc.pop();
			}
		}
		else{
			g_cpu.push_back(-1);
		}
		if(flag==0){
			if(rdi.empty()==false){
				Process &x=rdi.front();
				g_io.push_back(x.pid);
				x.b[x.ind]--;
				if(x.b[x.ind]==0){
					x.ind++;
					if(x.ind<x.len){
						rdc.push(x);
					}
					rdi.pop();
				}
			}
			else{
				g_io.push_back(-1);
			}
		}
		t++;
		
	}
	t=1;
	
	cout<<"CPU and I/O Gantt Chart:\n";
	cout<<"------------------------\nTime\tCPU\tI/O\n";
	for(int i=0;i<g_cpu.size();i++){
		cout<<t<<"\t"<<g_cpu[i]<<"\t"<<g_io[i]<<"\n";
		t++;	
	}
	
	sort(arr.begin(),arr.end(),[](Process p1, Process p2){
		return p1.pid<p2.pid;
	});
	avg(arr,g_cpu,g_io);
	
	cout<<"\nProcess Gantt Chart:\n";
	cout<<"--------------------\nProcess\t";
	for(int i=0;i<g_cpu.size();i++){
		cout<<i+1;
		if(i+1<10){
			cout<<"  ";
		}
		else{
			cout<<" ";
		}
	}
	cout<<"\n";
	for(int i=0;i<n;i++){
		cout<<arr[i].pid<<"\t";

		for(int j=0;j<g_cpu.size();j++){

			if(g_cpu[j]==arr[i].pid){
				cout<<"R  ";
			}
			else{
				if(g_io[j]==arr[i].pid){
					cout<<"I  ";
				}
				else if(j+1>arr[i].a_time && arr[i].a_time+arr[i].t_time>j+1){
					cout<<"W  ";
				}
				else
				cout<<"0  ";
			}
		}
		cout<<"\n";
	}
	
	
	
	
	
	cout<<"\nStatistics:\n";
	cout<<"-----------\n";
	stats(arr);
	return 0;
}
