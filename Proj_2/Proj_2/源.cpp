#include <iostream>
using namespace std;

class freed_area{
public:
	int index;
	int start_addr;
	int length;
	freed_area* next_area;
	freed_area() :next_area(NULL) {}
	~freed_area();
};

class occupied_area {
public:
	int start_addr;
	int length;
	string proj_name;
	occupied_area* next_area;
	occupied_area() :next_area(NULL) {}
	~occupied_area() {}
};

class memory//����ͷָ�룡��
{
public:
	freed_area* free_area;
	occupied_area* occ_area;
	memory();
	~memory() {}
};

memory::memory() {
	free_area = new freed_area();
	occ_area = new occupied_area();
}
memory& initial_mem() {
	memory* mem = new memory();
	freed_area * free= new freed_area();
	free->index = 1;
	free->start_addr=0;
	free->length = 128;
	mem->free_area->next_area = free;
	return *mem;
}

void mem_distribute(memory* mem, freed_area* free_area, int length, string name);
void mem_delete(memory* mem,occupied_area * occu_area);

void mem_apply(memory *mem) {
	string name;
	int length;
	freed_area* area;
	cout << "������������ҵ����" << endl;
	cin >> name;
	cout << "������������ҵ�����ڴ��С" << endl;
	cin >> length;
	area = mem->free_area;
	while(area->next_area !=NULL)
	{ 
		area = area->next_area;
		if(area->length >= length)
		{
			mem_distribute(mem,area,length,name);
			return;
		}
	}
	cout << "��ǰ�ڴ治�㣬�޷����䣡" << endl;
}
void mem_recover(memory* mem) {
	string name;
	occupied_area *area;
	cout << "������������յ���ҵ����" << endl;
	cin >> name;
	area = mem->occ_area;
	while (area->next_area != NULL ) {
		area = area->next_area;
		if (area->proj_name == name) {
			mem_delete(mem,area);
			return;
		}
	}
	cout << "δ�ҵ�����ҵ�������ԣ�" << endl;
}
void mem_distribute(memory* mem,freed_area* free, int length, string name) {
	occupied_area* occ_area;//ǰ�����½����̵�ǰһ������
	occupied_area* work = new occupied_area();
	work->proj_name = name;
	work->length = length;
	occ_area = mem->occ_area;
	if (occ_area->next_area == NULL)
	{
		work->start_addr = 0;
		occ_area->next_area = work;
	}
	else//�õ�occ_area����һ���Ƿ������ҵ
	{
		while (free->start_addr > occ_area->next_area->start_addr + occ_area->next_area->length) {
			occ_area = occ_area->next_area;
		}if (free->start_addr < mem->occ_area->next_area->start_addr) {
			work->next_area = mem->occ_area->next_area;
			mem->occ_area->next_area = work;
		}
		else {
			work->next_area = occ_area->next_area->next_area;
			occ_area->next_area->next_area = work;
		}
	}

	if (free->length <= length)//���ʣ��ռ䱻��ȫ����
	{
		if (free->index == 1)
		{
			mem->free_area->next_area = free->next_area;
			work->start_addr = free->start_addr;
		}//ע���������û��ʣ��ռ䣬�ǵú������շ���
		freed_area* tmp = free;

		while (tmp->next_area != NULL) {
			tmp->index--;
			tmp = tmp->next_area;
		}
	}
	else {
		work->start_addr = free->start_addr;
		free->start_addr = free->start_addr + length;
		free->length -= length ;
	}
}
void mem_delete(memory* mem,occupied_area * work) {
	freed_area *front_area = mem->free_area, *behind_area = mem->free_area;	//
	occupied_area* front_occ_area;
	front_occ_area = mem->occ_area;
	//�й�free��
	if (mem->free_area->next_area == NULL)//���mem��û�п��п�
	{
		freed_area* new_area = new freed_area();
		new_area->index = 1;
		new_area->length = work->length;
		new_area->start_addr = work->start_addr;
		mem->free_area->next_area = new_area;

	}
	else if (mem->free_area->next_area->start_addr > work->start_addr)//����ȫ��������ֻ�ܹ��˼�����
	{
		if (work->length + work->start_addr == mem->free_area->next_area->start_addr)//������Ժϲ�
		{
			mem->free_area->next_area->start_addr -=  work->length;
			mem->free_area->next_area->length += work->length;
		}
		else {
			freed_area* work_free = new freed_area();
			work_free->index = 1;
			work_free->start_addr = work->start_addr;
			work_free->length = work->length;
			freed_area* tmp = mem->free_area->next_area;
			work_free->next_area = mem->free_area->next_area;
			mem->free_area->next_area = work_free;
			while (tmp != NULL)
			{
				tmp->index++;
				tmp = tmp->next_area;
			}
		}
	}
	else 
	{
		do {
			front_area = front_area->next_area;
			behind_area = front_area->next_area;
		} while (front_area->start_addr + front_area->length > work->start_addr&&
			(behind_area == NULL || behind_area->start_addr < work->start_addr + work->length ));//�γ�һ���������֮��
		if (front_area->start_addr + front_area->length == work->start_addr) {
			if (behind_area!=NULL && behind_area->start_addr == work->start_addr + work->length) //������¶��ǿյģ���ȫ������
			{
				front_area->length += work->length + behind_area->length;
				front_area->next_area = behind_area->next_area;
				freed_area* tmp = front_area;
				while (tmp->next_area != NULL) {
					tmp = tmp->next_area;
					tmp->index --;
				}
			}
			else {
				front_area->length += work->length;
			}

		}
		else if (behind_area != NULL && behind_area->start_addr == work->start_addr + work->length)//
		{
			behind_area->start_addr = work->start_addr;
			behind_area->length += work->length;
		}
		else {
			freed_area* free = new freed_area();
			free->start_addr = work->start_addr;
			free->length = work->length;
			free->index = front_area->index;
			free->next_area = behind_area;
			front_area->next_area = free;
			freed_area* tmp = front_area;
			while (tmp->next_area != NULL) {
				tmp = tmp->next_area;
				tmp->index++;
			}
		}
	}

	//�й�occupied��
	if (mem->occ_area->next_area == work) {
		mem->occ_area->next_area = work->next_area;
	}
	else {
		while (front_occ_area->next_area != work && front_area->next_area != NULL)
		{
			front_occ_area = front_occ_area->next_area;
		}
		front_occ_area->next_area = work->next_area;
	}
}
void print_mem_list(memory* mem) {
	freed_area* free;
	occupied_area* occ;
	int index_num = 0;
	free = mem->free_area->next_area;
	occ = mem->occ_area->next_area;
	cout << "��ʼ��ַ\t" << "����\t" << "״̬" << endl;
	while (free!= NULL || occ != NULL) 
	{
		if ( free !=NULL && free->start_addr == index_num ) {
			cout << free->start_addr << "K\t" << free->length << "K\t" << "����" << endl;
			index_num += free->length;
			free = free->next_area;
		}
		else {
			cout << occ->start_addr << "K\t" << occ->length << "K\t" << occ->proj_name << endl;
			index_num += occ->length;
			occ = occ->next_area;
		}
	}
}

int main() {
	memory myMem = initial_mem();
	char instruct = '0';
	while (true) {
		cout << "����������Ҫ��" << endl;
		cout << "0������ռ�  1���ͷſռ�  ����:�˳�" << endl;
		try { cin >> instruct; }
		catch (...) {}
		switch (instruct)
		{
		case '0':mem_apply(&myMem);break;
		case '1':mem_recover(&myMem); break;
		default:
			return 0;break;
		}
		print_mem_list(&myMem);
	}
}
