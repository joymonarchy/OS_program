#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct state		//����״̬
{
	char ready = 'R';
	char execute = 'I';
	char end = 'E';
};
struct state  _state;

class PCB {
public:
	string PCB_name;
	PCB* next_PCB;
	unsigned int time;
	unsigned int priority;
	char PCB_state;
	
	PCB(string name): PCB_name(name),next_PCB(NULL),PCB_state(_state.ready) {}
	~PCB() {}
	PCB(const PCB& p) {}
	//��ʼ��ϵͳ�Զ�����PCB���֣�Ĭ��״̬ΪEnd
};

void initial_pcb(PCB* p_head);
void sort_pcb(PCB* p_change, PCB* p_head);
void run_pcb(PCB* p_head);
void delete_pcb(PCB* p_delete, PCB* p_head);
void exe_pcb(PCB* p_exe);


void initial_pcb(PCB *p_head) {
	PCB *this_pcb,*head = p_head;
	for (int i = 0;i < 5;i++) {
		string name = "P" + to_string(i + 1);
		this_pcb = new PCB(name);
		unsigned int time;
		unsigned int priority;
		cout << "Please input " << name << " running time" << endl;
		try { cin >> time; }
		catch (...) {}
		cout << "Please input " << name << " priority " << endl;
		try { cin >> priority; }
		catch (...) {}

		this_pcb->time = time;
		this_pcb->priority = priority;
		
		PCB* p = head;

		while (p->next_PCB != NULL) {
			if (p->next_PCB->priority < this_pcb->priority)
				break;
			else
				p = p->next_PCB;
		}
		this_pcb->next_PCB = p->next_PCB;
		p->next_PCB = this_pcb;
	}

	PCB* p = head;
}
void sort_pcb(PCB * p_change,PCB *p_head) {
	PCB* p = p_change;
	PCB* q = p_head;
	cout << p_change->PCB_name << " sort" << endl;
	while (q->next_PCB != p_change && p->next_PCB!=NULL )
	{
		q = q->next_PCB;
	}//��qΪp��ǰ���ڵ�	
	 //m����Ҫ������λ�õ�ǰ����㣬������һ����ĩβ���Ľ��
	PCB* m = p->next_PCB;
	if(p->next_PCB !=NULL && p->next_PCB->priority >= p->priority) //��Ҫ��λ�õ�ʱ��
	{
		while(m->next_PCB !=NULL && m->next_PCB->priority >= p->priority)//�����¸����ȼ�Ҳ�ȵ�ǰ���ȼ����ʱ��
		{
			m = m->next_PCB;
		}
		q->next_PCB = p->next_PCB;		//q��ǰ���ڵ�ָ��p�ĺ������
		p->next_PCB = m->next_PCB;		//p�ĺ������ָ��m
		m->next_PCB = p;				//mָ��p

	} 
}
void run_pcb(PCB *p_head) {
	initial_pcb(p_head);
	while (p_head ->next_PCB!= NULL)
	{
		if (p_head->next_PCB->time <= 0) {
			delete_pcb(p_head->next_PCB, p_head);
		}
		else {
			exe_pcb(p_head->next_PCB);
			if (p_head->next_PCB->time <= 0) delete_pcb(p_head->next_PCB, p_head);
			if (p_head->next_PCB == NULL) break;
			sort_pcb(p_head->next_PCB, p_head);
		}
	}

	cout << "end run" << endl;
}
void exe_pcb(PCB* p_exe) {
	cout << p_exe->PCB_name << " exe" << endl;
	p_exe->PCB_state = _state.execute;
	p_exe->priority--;
	p_exe->time--;
	p_exe->PCB_state = _state.ready;
}
void delete_pcb(PCB *p_delete,PCB *p_head) {
	PCB* p = p_head;
	p_delete->PCB_state = _state.end;
	cout << p_delete->PCB_name << " delete" << endl;

	p_head->next_PCB = p_delete->next_PCB;

}

int main() {
	PCB* p = new PCB("head");
	PCB* q = p;
	run_pcb(p);
}