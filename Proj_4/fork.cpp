
#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
	cout<<"start"<<endl;
	pid_t pidB, pidC;
	
	pidB = fork();
	if(pidB<0)	//���̴���ʧ�� 
	{
		cout<<"���̴���ʧ�ܣ�"<<endl;
		return 1;
	}else if(pidB == 0)		//�����ӽ���B 
	{
		cout<<"B"<<endl;
	}else{
		pidC = fork(); 		//��������C 
		if(pidC < 0) {
			cout<<"���̴���ʧ�ܣ�"<<endl;
			return 2;
		}else if(pidC == 0){
			cout<<"C"<<endl;
		}else{
			cout<<"A"<<endl;
		}
	} 
	return 0;
}
