#include"Manage.h"
void IntToStr(char*str, int number, int maxlen)
{
	int i = 0;
	char *tail = str;
	while (i < maxlen)
	{
		*tail = '0';
		i++;
		tail++;
	}
	*tail = '\0';
	tail--;
	while (number > 0)
	{
		*tail = number % 10 + '0';
		number /= 10;
	}
}
int StrToInt(const char*str)
{
	const char*cur = str;
	while (*cur == '0')cur++;
	int temp = 0;
	for (; *cur != '\0'; cur++)
		temp = temp * 10 + *cur - '0';
	return temp;
}
void BookTicket(Train *&train_head, Ticket*&origin)
{
	if (train_head == NULL)
	{
		cout << "班次信息加载出错！" << endl;
		return;
	}
	char start[20], end[20];
	cout << "请依次输入出发站和到达站：" << endl;
	cin >> start >> end;
	Train*relate_train = FindRelateTrainList(train_head, start, end);
	SortTrainListByName(relate_train);
	if (relate_train == NULL)cout << "抱歉！暂无匹配的班次，请更换交通工具！";
	else
	{
		cout << "查询到的列车如下：" << endl;
		cout <<setiosflags(ios::left)<< setw(20) << " 车次"<< setw(20) <<"始发站" << setw(20) <<"终点站" << setw(20) <<"余票" << endl;
		Train*cur = relate_train;
		while (cur != NULL)
		{
			cout << setiosflags(ios::left) << setw(20) << cur->train << setw(20) << cur->start->name << setw(20) << cur->end->name << setw(20) << CountRestTicket(cur, start, end) << endl;
			cur = cur->next;
		}
		cout << "请输入要预定的班次：" << endl;
		char train_name[20]; cin >> train_name;
		Train*tar = FindTrain(relate_train, train_name);
		while (tar == NULL)
		{
			cout << "无相应班次！请确保输入的班次号无误！" << endl;
			cout << "请选择：1、重新输入  2、结束" << endl;
			int i; cin >> i;
			while (i != 1 && i != 2)
			{
				cout << "输入无效！请重新输入" << endl;
				cin >> i;
			}
			if (i == 2)
			{
				train_head = MergeTrainList(train_head, relate_train);
				return;
			}
			else
			{
				cout << "请输入班次号：" << endl;
				cin >> train_name;
				tar = FindTrain(relate_train, train_name);
			}
		}
		cout << "请输入要购买的票数：" << endl;
		int num; cin >> num;
		int max = CountRestTicket(tar, start, end);
		while (num > max)
		{
			cout << "抱歉,余票(仅" << max << ")不足！请选择：1、放弃购票  2、重新输入" << endl;
			int i; cin >> i;
			while (i != 1 && i != 2)
			{
				cout << "输入无效！" << endl;
				cout<< "请选择：1、放弃购票  2、重新输入" << endl;
				cin >> i;
			}
			if (i == 1)
			{
				train_head=MergeTrainList(train_head, relate_train);
				return;
			}
			else
			{
				cout << "请输入购票数量：" << endl;
				cin >> num;
			}
		}
		int ticket_number;
		if (origin == NULL)ticket_number = 1;
		else
		{
			char*temp_number = GetTicketNumber(origin);
			ticket_number = StrToInt(temp_number);
			ticket_number++;
		}
		Ticket*addition = new Ticket;
		IntToStr(addition->number, ticket_number, 3);
		strcpy_s(addition->start, 20, start);
		strcpy_s(addition->end, 20, end);
		strcpy_s(addition->train, 20, train_name);
		addition->n = num;
		addition->next = NULL;
		UpdateSeat(tar, start, end, -num);
		origin = AppAddTicket(origin, addition);
		train_head = MergeTrainList(train_head, relate_train);
		cout << "订票成功！您的订单号为"<<addition->number<<" 请妥善记录" << endl;
	}
}
void DeleteTicket(Train *train_head,Ticket*&origin)
{
	if (origin == NULL)
	{
		cout << "订单信息为空，请确认是否正确加载订单信息或暂无订单！" << endl;
		return;
	}
	if (train_head == NULL)
	{
		cout << "班次信息加载出错！" << endl;
		return;
	}
	cout << "请输入退订车票的订单号！" << endl;
	char temp_number[4]; cin >> temp_number;
	Ticket*tar = FindTicket(origin, temp_number);
	while (tar == NULL)
	{
		cout << "未查询到改订单信息！请选择：1、重新输入订单号  2、结束" << endl;
		int i; cin >> i;
		while (i != 1 && i != 2)
		{
			cout << "输入无效！" << endl;
			cout<<"请选择：1、重新输入订单号  2、结束" << endl;
			cin >> i;
		}
		if (i == 2)return;
		else
		{
			cout << "请输入订单号：" << endl;
			cin >> temp_number;
			tar = FindTicket(origin, temp_number);
		}
	}
	cout << "订单信息如下，请确认" << endl;
	AppDisplayOneTicket(tar);
	system("pause");
	Train*tar_train = FindTrain(train_head, tar->train);
	UpdateSeat(tar_train, tar->start, tar->end, tar->n);
	DeleteOneTicket(origin, temp_number);
	cout << "退票成功！" << endl;
}


void TicketInfoManage(Train *&train_head, Ticket*&origin)
{
	while (1)
	{
		system("cls");
		cout << "1、售票" << endl;
		cout << "2、订单浏览" << endl;
		cout << "3、退票" << endl;
		cout << "4、返回主菜单" << endl;
		int i; cin >> i;
		while (i != 1 && i != 2 && i != 3 && i != 4)
		{
			cout << "输入无效！请重新输入！" << endl;
			cin >> i;
		}
		switch (i)
		{
		case 1:BookTicket(train_head, origin); break;
		case 2:SortTicketListByNumber(origin);
			AppDisplayTicketList(origin); break;
		case 3:DeleteTicket(train_head,origin); break;
		case 4:return;
		}
		system("pause");
	}
}
void SearchTrainInfo(Train *&train_head)
{
	if (train_head == NULL)
	{
		cout << "加载班次信息出错！" << endl;
		system("pause");
		return;
	}
	while (1)
	{
		system("cls");
		cout << "1、按出发/到达站查询" << endl;
		cout << "2、按班次号查询" << endl;
		cout << "3、浏览全部班次" << endl;
		cout << "4、返回主菜单" << endl;
		int i; cin >> i;
		while (i != 1 && i != 2 && i != 3&&i!=4)
		{
			cout << "输入无效！请重新输入！" << endl;
			cin >> i;
		}
		if (i == 1)
		{
			char start[20], end[20];
			cout << "请依次输入出发站和到达站" << endl;
			cin >> start >> end;
			Train*relate_train = FindRelateTrainList(train_head, start, end);
			SortTrainListByName(relate_train);
			if (relate_train == NULL)cout << "抱歉！暂无匹配的班次" << endl;
			else
			{
				cout << "查询到的列车如下：" << endl;
				cout << setiosflags(ios::left) << setw(20) << " 车次" << setw(20) <<"始发站" << setw(20) <<"终点站" << setw(20) <<"余票" << setw(20) << endl;
				Train*cur = relate_train;
				while (cur != NULL)
				{
					cout << setiosflags(ios::left) << setw(20) << cur->train << setw(20) << cur->start->name << setw(20) << cur->end->name << setw(20) << CountRestTicket(cur, start, end) << setw(20) << endl;
					cur = cur->next;
				}
				train_head = MergeTrainList(train_head, relate_train);
			}
		}
		else if (i == 2)
		{
			char train_number[20];
			cout << "请输入班次号" << endl;
			cin >> train_number;
			Train*tar = FindTrain(train_head, train_number);
			while (tar == NULL)
			{
				cout << "未查询到班次信息！请选择：1、重新输入  2、结束" << endl;
				int i; cin >> i;
				while (i != 1 && i != 2)
				{
					cout << "输入无效！" << endl;
					cout << "请选择：1、重新输入  2、结束" << endl;
					cin >> i;
				}
				if (i == 2)goto END;
				else
				{
					cout << "请输入班次号：" << endl;
					cin >> train_number;
					tar = FindTrain(train_head, train_number);
				}
			}
			cout << "查询到的班次信息如下：" << endl;
			AppDisplayOneTrain(tar);
		}
		else if (i == 3)AppDisplayTrainList(train_head);
		else return;
	END:;
		system("pause");
	}
}

