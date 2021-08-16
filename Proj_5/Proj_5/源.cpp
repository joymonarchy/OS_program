#include <iostream>

using namespace std;

class resource {
public:
	int R1;
	int R2;
	int R3;
	resource operator +(resource re);
	resource operator -(resource re);
	bool operator>=(resource re);
	bool operator==(resource re);
	resource() {}
	resource(int a,int b,int c):R1(a),R2(b),R3(c){}
};
class process {
public:
	string name;
	resource re_max;
	resource re_allo;
	resource re_need;
	process* next_pro;
	process() :next_pro(NULL){}
	process(string _name, resource max, resource allo, resource need) :name(_name), re_max(max), re_allo(allo), re_need(need),next_pro(NULL) {}
	~process() {}
};
class mem {
public:
	resource re_avai;
	process* procession;
	mem() {procession = new process();}
	mem(resource res) :re_avai(res) { procession = new process(); }
	~mem() {}
	void mem_add_pro(process *pro);
	void mem_delete_pro(process *pro);
	void allocate();
};

const resource re0 = { 0,0,0 };

resource resource::operator +(resource re) {
	resource tmp;
	tmp.R1 = this->R1 + re.R1;
	tmp.R2 = this->R2 + re.R2;
	tmp.R3 = this->R3 + re.R3;
	return tmp;
}
resource resource::operator -(resource re) {
	resource tmp;
	tmp.R1 = this->R1 - re.R1;
	tmp.R2 = this->R2 - re.R2;
	tmp.R3 = this->R3 - re.R3;
	return tmp;
}
bool resource::operator>=(resource re) {
	if (this->R1 >= re.R1 && this->R2 >= re.R2 && this->R3 >= re.R3)
		return true;
	return false;
}
bool resource::operator==(resource re) {
	if (this->R1 == re.R1 && this->R2 == re.R2 && this->R3 == re.R3)
		return true;
	return false;
}

bool can_allo(const mem& memory, process this_pro, resource re);

mem* ini_mem()//���ڴ��ʼ���ú�����һ��
{
	resource re_on_book = { 9,3,6 };
	mem* my_mem = new mem(re_on_book);
	process* P1 = new process("P1", resource(3, 2, 2), resource(1, 0, 0), resource(2, 2, 2));
	process* P2 = new process("P2", resource(6, 1, 3), resource(5, 1, 1), resource(1, 0, 2));
	process* P3 = new process("P3", resource(3, 1, 4), resource(2, 1, 1), resource(1, 0, 3));
	process* P4 = new process("P4", resource(4, 2, 2), resource(0, 0, 2), resource(4, 2, 0));
	my_mem->mem_add_pro(P1);
	my_mem->mem_add_pro(P2);
	my_mem->mem_add_pro(P3);
	my_mem->mem_add_pro(P4);
	return my_mem;
}

void mem::mem_add_pro(process *pro)	//�����ǽ��̵ļ��룬������޹�
{
	if (this->re_avai >= pro->re_allo)
	{
		process* tmp_pro = this->procession;
		while (tmp_pro->next_pro != NULL)
			tmp_pro = tmp_pro->next_pro;
		tmp_pro->next_pro = pro;
		this->re_avai = this->re_avai - pro->re_allo;
		cout << "����" << pro->name << "����ɹ���" << endl;
	}
	else {
		cout << "�ڴ治�㣬���̼������" << endl;
	}
}
void mem::mem_delete_pro(process *pro) {
	process *tmp = this->procession;
	while (tmp->next_pro != NULL && tmp->next_pro != pro)
		tmp = tmp->next_pro;
	this->re_avai = this->re_avai + pro->re_allo;
	tmp->next_pro = pro->next_pro;
	delete pro;
}
void mem::allocate() {
	string name;
	resource res;
	cout << "������������Դ�Ľ�����" << endl;
	cin >> name;
	process* tmp = this->procession;
	while (tmp->next_pro != NULL)
	{
		tmp = tmp->next_pro;
		if (tmp->name == name)break;
	}
	if (tmp!=NULL && tmp->name != name) {
		cout << "�����ڸý��̣�" << endl;
		return;
	}
	cout << "������ý����������Դ��Ŀ" << endl;
	cout << "R1:";
	cin >> res.R1;
	cout << "R2:";
	cin >> res.R2;
	cout << "R3:";
	cin >> res.R3;
	if (!(res >= re0)) {
		cout << "��Դ��������С���㣡" << endl;
		return;
	}
	else if (res >= this->re_avai && !(res == this->re_avai))//���Ǵ��ڡ���������д����������
	{
		cout << "�������Է���ķ�Χ��" << endl;
		return;
	}
	else {
		if (can_allo(*this, *tmp, res)) {
			tmp->re_allo = tmp->re_allo + res;
			this->re_avai = this->re_avai - res;
			cout << "����ɹ��������ȫ��" << endl;
			cout << "����������Դ" << endl;
			cout << "R1\tR2\tR3" << endl;
			cout << this->re_avai.R1 << "\t" << this->re_avai.R2 << "\t" << this->re_avai.R3 << endl;
		}
		else {
			cout << "�����м��㷨��֤���������ȫ���ܾ����䣡" << endl;
		}
	}
}
bool can_allo(const mem& memory, process this_pro, resource re) {
	mem tmp_mem = memory;
	tmp_mem.re_avai = tmp_mem.re_avai - re;
	int count = 0;
	while (tmp_mem.procession->next_pro != NULL) //�ý�����ȫ���ͷ�
	{
		count++;
		process* p = tmp_mem.procession;
		while (p->next_pro != NULL) {
			p = p->next_pro;
			if (p->name == this_pro.name) {
				p->re_allo = p->re_allo + re;
				p->re_need = p->re_need - re;
			}
			if (tmp_mem.re_avai >= p->re_need)
			{
				tmp_mem.mem_delete_pro(p);
				break;
			}
		}
		if (count > 4) return false;
	}
	return true;
}


int main() {
	mem* my_mem = ini_mem();
	cout << "���п�����Դ" << endl;
	cout << "R1\tR2\tR3" << endl;
	cout<<my_mem->re_avai.R1 << "\t"<<my_mem->re_avai.R2 <<"\t"<< my_mem->re_avai.R3<<endl;
	my_mem->allocate();
}