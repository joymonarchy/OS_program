#include <iostream>
#define _cylinder 8  //8个柱面
#define _track 2		//2个磁道
#define _phy_record 4	//4个物理记录

using namespace std;

int position_map[_cylinder][_track * _phy_record];

void assign_position() {
	int need;
	cout << "请输入您需要分配的物理块数" << endl;
	cin >> need;
	int free = 0;
	for(int i = 0;i<_cylinder;i++)
		for (int j = 0;j < _track * _phy_record;j++) {
			free++;
			if (free >= need)break;
		}
	if (free < need) {
		cout << "内存不足！" << endl;
		return;
	}
	else {
		int free = 0;
		cout << "柱面\t磁道号\t物理记录号" << endl;
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
	cout << "分配错误！" << endl;
	return;
}	  //分配内存
void recover_position() {
	int cylinder;
	int track;
	int phy_record;
	cout << "请输入您想释放的柱面号、磁道号与物理记录号" << endl;
	cin >> cylinder;
	cin >> track;
	cin >> phy_record;
	if (cylinder >= _cylinder || track >= _track || phy_record >= _phy_record) {
		cout << "输入错误，请重新输入！" << endl;
		return;
	}
	if (position_map[cylinder][track * 4 + phy_record] == 0) {
		cout << "该内存未被占用！" << endl;
		return;
	}
	else if (position_map[cylinder][track * 4 + phy_record] == 1){
		position_map[cylinder][track * 4 + phy_record] = 0;
		cout << "内存已释放！" << endl;
		return;
	}
	cout << "系统错误！" << endl;
	return;
}
void print_position() {
	cout << "———————————位示图———————————" << endl;
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
		cout << "请问您的需要？" << endl;
		cout << "0：申请空间  1：释放空间  其他:退出" << endl;
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

