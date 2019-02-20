#include"Modify.h"
Train*AddTrain(Train*head)    //程序运行中添加新的班次，在已有的train链表中插入新节点
{
	cout << "请输入列车信息："<<endl;
	Train*add = AppAddTrain();
	if (strcmp(add->train, head->train) < 0)
	{
		add->next = head;
		head = add;
		return head;
	}
	Train*pre = head;
	while (pre->next != NULL)
		if (strcmp(add->train, pre->next->train) < 0)break;
		else pre = pre->next;
	add->next = pre->next;
	pre->next = add;
	cout << "已记录新增班次信息！" << endl;
	cout << "新增班次信息如下：" << endl;
	AppDisplayOneTrain(add);
	return head;
}
Train*DeleteTrain(Train*head,Ticket*origin)   //从已有的列车链表中删除指定班次(节点)
{
	char train_name[20];
	cout << "请输入要删除的班次号："<<endl;
	cin >> train_name;
	Train*tar = head;
	tar = FindTrain(head, train_name); //查找目标班次
	while (tar == NULL)        //班次不存在时解决机制
	{
		cout << "该班次不存在！选择：1.重新输入  2.返回"<<endl;
		int i; cin >> i;
		while (i != 1 && i != 2)
		{
			cout << "该班次不存在！选择：1.重新输入  2.返回"<<endl;
			cin >> i;
		}
		if (i == 1)
		{
			cout << endl << "请输入要删除的班次号：" << endl;
			cin >> train_name;
		}
		else return head;
		tar = FindTrain(head, train_name);
	}
	if (TicketHasTrain(origin, train_name))cout << "该班次已有乘客订票，不能删除！"<<endl;
	else
	{
		if (tar==head)
		{
			head = head->next;
			DeleteStationList(tar->start);
			delete tar;
		}
		else
		{
			Train*pre = head;
			while (pre->next != tar)pre = pre->next;
			pre->next = tar->next;
			DeleteStationList(tar->start);
			delete tar;
		}
		cout << "已删除相应班次信息！" << endl;
	}
	return head;
}
void ChangeTrainName(Train*tar,Ticket*origin)  //修改班次号
{
	if (TicketHasTrain(origin, tar->train))
	{
		cout << "该班次已有乘客订票，是否将更改应用于对应订单？" << endl;
		cout << "请选择：1、放弃更改  2、更改并应用"<<endl;
		int i; cin >> i;
		while (i != 1 && i != 2)
		{
			cout << "输入无效！" << endl;
			cout << "该班次已有乘客订票，是否将更改应用于对应订单？" << endl;
			cout << "请选择：1、放弃更改  2、更改并应用"<<endl;
			cin >> i;
		}
		if (i == 1)return;
		else
		{
			cout << "请输入新的班次号："<<endl;
			char train_name[20];
			cin >> train_name;
			SubstituteTrainName(origin, tar->train, train_name);
			RecordTicketInfo(".\\ticket.txt", origin);
			strcpy_s(tar->train,20, train_name);
			cout << "更改成功！" << endl;
			cout << "更改后班次信息如下：" << endl;
			AppDisplayOneTrain(tar);
			return;
		}
	}
	else
	{
		cout << "请输入新的班次号";
		cin >> tar->train;
		cout << "更改成功！" << endl;
		cout << "更改后班次信息如下：" << endl;
		AppDisplayOneTrain(tar);
		return;
	}
}
void ChangeMaximun(Train*tar)
{
	int min_offset = CountMinSeat(tar);
	cout << "请输入新的最大承载量：" << endl;
	int temp; cin >> temp;
	while (tar->maximun - temp > min_offset)
	{
		cout << "更改失败！承载量不得少于已购票的乘客数量" << endl;
		cout << "请选择：1、重新输入  2、放弃更改" << endl;
		int i; cin >> i;
		while (i != 2 && i != 1)
		{
			cout << "输入无效！" << endl;
			cout << "请选择：1、重新输入  2、放弃更改" << endl;
			cin >> i;
		}
		if (i == 2)return;
		else
		{
			cout << "请输入新的最大承载量：" << endl;
			cin >> temp;
		}
	}
	UpdateSeat(tar, tar->start->name, tar->end->name, temp - tar->maximun);
	tar->maximun = temp;
	cout << "更改成功！" << endl;
	cout << "更改后班次信息如下：" << endl;
	AppDisplayOneTrain(tar);
}
void AddStation(Train*tar,Ticket*origin)
{
	if (TicketHasTrain(origin, tar->train))cout << "该班次已有订单，请确保不影响乘客出行！";
	Station*temp = new Station;
	cout << "请输入新站点名字：" << endl;
	cin >> temp->name;
	temp->next = NULL;
	cout << "请选择插入站点的方式：1、更新始发站  2、更新终点站  3、增加中途站" << endl;
	int i; cin >> i;
	while (i != 1 && i != 2 && i != 3)
	{
		cout << "输入无效！" << endl;
		cout << "请选择插入站点的方式：1、更新始发站  2、更新终点站  3、增加中途站" << endl;
		cin >> i;
	}
	switch (i)
	{
	case 1:temp->seat = tar->maximun;  //始发站空座数为最大承载量
		temp->next = tar->start;
		tar->start = temp; break;
	case 2:temp->seat = 0;  //终点站的空座数无意义
		tar->end->seat = tar->maximun;
		tar->end->next = temp;
		tar->end = temp; break;
	case 3:cout << "请输入增加站点插入位置前一站点名：" << endl;
		char station_ahead[20]; cin >> station_ahead;
		Station*pre = FindStation(tar->start, station_ahead);
		temp->seat = pre->seat;  //新增车站与前一车站空座数相同
		temp->next = pre->next;
		pre->next = temp; break;
	}
	cout << "增加成功！" << endl;
	cout << "更改后班次信息如下：" << endl;
	AppDisplayOneTrain(tar);
}
void DeleteStation(Train*tar,Ticket*&origin)
{
	char temp[20];
	cout << "请输入要删除的站点名：" << endl;
	cin >> temp;
	while (FindStation(tar->start, temp) == NULL)
	{
		cout << "无改站点信息！请确保输入无误！" << endl;
		cout << "1、重新输入  2、结束" << endl;
		int i; cin >> i;
		while (i != 1 && i != 2)
		{
			cout << "输入无效！" << endl;
			cout << "1、重新输入  2、结束" << endl;
			cin >> i;
		}
		if (i == 2)return;
		else
		{
			cout << "请输入要删除的站点名：" << endl;
			cin >> temp;
		}
	}
	Ticket*related_ticket = FindAllTicketToTrain(origin, tar->train);
	if (related_ticket != NULL && HasStationBooked(related_ticket, temp))
	{
		cout << "删除该站点会导致已购票乘客无法按原计划出行！更改失败！" << endl;
		origin=MergeTicketList(origin, related_ticket);
		return;
	}
	origin = MergeTicketList(origin, related_ticket);
	DeleteOneStation(tar->start, temp);
	cout << "删除成功！" << endl;
	cout << "更改后班次信息如下：" << endl;
	AppDisplayOneTrain(tar);
}
void ModifyTrain(Train*head,Ticket*&origin)
{
	char train_name[20];
	cout << "请输入要修改的班次号：" << endl;
	cin >> train_name;
	Train*tar = head;
	while (tar != NULL && strcmp(tar->train, train_name) != 0)tar = tar->next;  //查找目标班次
	while (tar == NULL)        //班次不存在时解决机制
	{
		cout << "该班次不存在！选择：1.重新输入  2.返回"<<endl;
		int i; cin >> i;
		while (i != 1 && i != 2)
		{
			cout << "该班次不存在！选择：1.重新输入  2.返回"<<endl;
			cin >> i;
		}
		if (i == 1)
		{
			cout << endl << "请输入要修改的班次号：" << endl;
			cin >> train_name;
		}
		else return;
		tar = head;
		while (tar != NULL && strcmp(tar->train, train_name) != 0)tar = tar->next;
	}
	cout << "对应班次信息如下：" << endl;
	AppDisplayOneTrain(tar);
	cout << "请选择修改的内容：1、变更班次号  2、修改最大承载人数  3、增加途经站点  4、删除途经站点" << endl;
	int i; cin >> i;
	while (i != 1 && i != 2 && i != 3 && i != 4)
	{
		cout << "输入无效"<<endl;
		cout << "请选择修改的内容：1、变更班次号  2、修改最大承载人数  3、增加途经站点  4、删除途经站点" << endl;
		cin >> i;
	}
	switch (i)
	{
	case 1:ChangeTrainName(tar,origin); break;
	case 2:ChangeMaximun(tar); break;
	case 3:AddStation(tar,origin); break;
	case 4:DeleteStation(tar,origin); break;
	}
}
void OperateTrainInfo(Train*&head, Ticket*&origin)
{
	if (head == NULL)
	{
		cout << "加载班次信息出错！" << endl;
		system("pause");
		return;
	}
	while (1)
	{
		system("cls");
		cout << "1、增加班次" << endl;
		cout << "2、删除班次" << endl;
		cout << "3、修改班次" << endl;
		cout << "4、返回主菜单" << endl;
		int i; cin >> i;
		while (i != 1 && i != 2 && i != 3 && i != 4)
		{
			cout << "输入无效！请重新输入！" << endl;
			cin >> i;
		}
		switch (i)
		{
		case 1:head = AddTrain(head); break;
		case 2:head = DeleteTrain(head,origin); break;
		case 3:ModifyTrain(head,origin); break;
		case 4:RecordTrainInfo(".\\train.txt", head); return;
		}
		system("pause");
	}
}