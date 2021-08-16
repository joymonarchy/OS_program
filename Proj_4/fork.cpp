
#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
	cout<<"start"<<endl;
	pid_t pidB, pidC;
	
	pidB = fork();
	if(pidB<0)	//进程创建失败 
	{
		cout<<"进程创建失败！"<<endl;
		return 1;
	}else if(pidB == 0)		//运行子进程B 
	{
		cout<<"B"<<endl;
	}else{
		pidC = fork(); 		//创建进程C 
		if(pidC < 0) {
			cout<<"进程创建失败！"<<endl;
			return 2;
		}else if(pidC == 0){
			cout<<"C"<<endl;
		}else{
			cout<<"A"<<endl;
		}
	} 
	return 0;
}
