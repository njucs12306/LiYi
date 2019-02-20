#include<iostream>
#include"File.h"
#include"Manage.h"
#include"Modify.h"
using namespace std;
int Option();
int main()
{
	Train*train_head = NULL;
	Ticket*ticket_head = LoadTicketInfo(".\\ticket.txt");
	while (1)
	{
		system("cls");
		cout << "1、录入班次信息" << endl;
		cout << "2、操作班次信息" << endl;
		cout << "3、查询班次信息" << endl;
		cout << "4、 售票与退票 " << endl;
		cout << "5、导出票务信息" << endl;
		cout << "6、  退出系统  " << endl;
		int i = Option();
		switch (i)
		{
		case 1:train_head=LoadTrainInfo(".\\train.txt");
			cout << "录入成功！" << endl; break;
		case 2:OperateTrainInfo(train_head,ticket_head); break;
		case 3:SearchTrainInfo(train_head); break;
		case 4:TicketInfoManage(train_head, ticket_head); break;
		case 5:RecordTicketInfo(".\\ticket.txt", ticket_head); break;
		case 6:RecordTrainInfo(".\\train.txt", train_head);
			RecordTicketInfo(".\\ticket.txt", ticket_head);
			return 0;
		}
	}
}

int Option()
{
	int i; cin >> i;
	while (i != 1 && i != 2 && i != 3 && i != 4 && i != 5 && i != 6)
	{
		cout << "输入无效！请重新输入！" << endl;
		cin >> i;
	}
	return i;
}