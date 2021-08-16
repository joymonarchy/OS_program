#include <iostream>
#define _cylinder 8  //8������
#define _track 2		//2���ŵ�
#define _phy_record 4	//4�������¼

using namespace std;

int position_map[_cylinder][_track * _phy_record];

void assign_position() {
	int need;
	cout << "����������Ҫ������������" << endl;
	cin >> need;
	int free = 0;
	for(int i = 0;i<_cylinder;i++)
		for (int j = 0;j < _track * _phy_record;j++) {
			free++;
			if (free >= need)break;
		}
	if (free < need) {
		cout << "�ڴ治�㣡" << endl;
		return;
	}
	else {
		int free = 0;
		cout << "����\t�ŵ���\t�����¼��" << endl;
		for (int i = 0;i < _cylinder;i++)
			for (int j = 0;j < _track * _phy_record;j++) {
				if (position_map[i][j] == 0) {
					position_map[i][j] = 1;
					free++;
					cout << i << "\t" << j / 4 << "\t" << j % 4 << endl;
				}
				if (free >= need)return;
			}
	}
	cout << "�������" << endl;
	return;
}	  //�����ڴ�
void recover_position() {
	int cylinder;
	int track;
	int phy_record;
	cout << "�����������ͷŵ�����š��ŵ����������¼��" << endl;
	cin >> cylinder;
	cin >> track;
	cin >> phy_record;
	if (cylinder >= _cylinder || track >= _track || phy_record >= _phy_record) {
		cout << "����������������룡" << endl;
		return;
	}
	if (position_map[cylinder][track * 4 + phy_record] == 0) {
		cout << "���ڴ�δ��ռ�ã�" << endl;
		return;
	}
	else if (position_map[cylinder][track * 4 + phy_record] == 1){
		position_map[cylinder][track * 4 + phy_record] = 0;
		cout << "�ڴ����ͷţ�" << endl;
		return;
	}
	cout << "ϵͳ����" << endl;
	return;
}
void print_position() {
	cout << "����������������������λʾͼ����������������������" << endl;
	for (int i = 0;i < _cylinder;i++) {
		cout << "\t\t";
		for (int j = 0;j < _track * _phy_record;j++) {
			cout << position_map[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

int main() {
	char command;
	while (true)
	{
		cout << "����������Ҫ��" << endl;
		cout << "0������ռ�  1���ͷſռ�  ����:�˳�" << endl;
		cin >> command;
		switch (command)
		{
		case '0':assign_position();print_position();break;
		case '1':recover_position();print_position();break;
		default:
			return 0;break;
		}
	}
}

