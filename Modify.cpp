#include"Modify.h"
Train*AddTrain(Train*head)    //��������������µİ�Σ������е�train�����в����½ڵ�
{
	cout << "�������г���Ϣ��"<<endl;
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
	cout << "�Ѽ�¼���������Ϣ��" << endl;
	cout << "���������Ϣ���£�" << endl;
	AppDisplayOneTrain(add);
	return head;
}
Train*DeleteTrain(Train*head,Ticket*origin)   //�����е��г�������ɾ��ָ�����(�ڵ�)
{
	char train_name[20];
	cout << "������Ҫɾ���İ�κţ�"<<endl;
	cin >> train_name;
	Train*tar = head;
	tar = FindTrain(head, train_name); //����Ŀ����
	while (tar == NULL)        //��β�����ʱ�������
	{
		cout << "�ð�β����ڣ�ѡ��1.��������  2.����"<<endl;
		int i; cin >> i;
		while (i != 1 && i != 2)
		{
			cout << "�ð�β����ڣ�ѡ��1.��������  2.����"<<endl;
			cin >> i;
		}
		if (i == 1)
		{
			cout << endl << "������Ҫɾ���İ�κţ�" << endl;
			cin >> train_name;
		}
		else return head;
		tar = FindTrain(head, train_name);
	}
	if (TicketHasTrain(origin, train_name))cout << "�ð�����г˿Ͷ�Ʊ������ɾ����"<<endl;
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
		cout << "��ɾ����Ӧ�����Ϣ��" << endl;
	}
	return head;
}
void ChangeTrainName(Train*tar,Ticket*origin)  //�޸İ�κ�
{
	if (TicketHasTrain(origin, tar->train))
	{
		cout << "�ð�����г˿Ͷ�Ʊ���Ƿ񽫸���Ӧ���ڶ�Ӧ������" << endl;
		cout << "��ѡ��1����������  2�����Ĳ�Ӧ��"<<endl;
		int i; cin >> i;
		while (i != 1 && i != 2)
		{
			cout << "������Ч��" << endl;
			cout << "�ð�����г˿Ͷ�Ʊ���Ƿ񽫸���Ӧ���ڶ�Ӧ������" << endl;
			cout << "��ѡ��1����������  2�����Ĳ�Ӧ��"<<endl;
			cin >> i;
		}
		if (i == 1)return;
		else
		{
			cout << "�������µİ�κţ�"<<endl;
			char train_name[20];
			cin >> train_name;
			SubstituteTrainName(origin, tar->train, train_name);
			RecordTicketInfo(".\\ticket.txt", origin);
			strcpy_s(tar->train,20, train_name);
			cout << "���ĳɹ���" << endl;
			cout << "���ĺ�����Ϣ���£�" << endl;
			AppDisplayOneTrain(tar);
			return;
		}
	}
	else
	{
		cout << "�������µİ�κ�";
		cin >> tar->train;
		cout << "���ĳɹ���" << endl;
		cout << "���ĺ�����Ϣ���£�" << endl;
		AppDisplayOneTrain(tar);
		return;
	}
}
void ChangeMaximun(Train*tar)
{
	int min_offset = CountMinSeat(tar);
	cout << "�������µ�����������" << endl;
	int temp; cin >> temp;
	while (tar->maximun - temp > min_offset)
	{
		cout << "����ʧ�ܣ����������������ѹ�Ʊ�ĳ˿�����" << endl;
		cout << "��ѡ��1����������  2����������" << endl;
		int i; cin >> i;
		while (i != 2 && i != 1)
		{
			cout << "������Ч��" << endl;
			cout << "��ѡ��1����������  2����������" << endl;
			cin >> i;
		}
		if (i == 2)return;
		else
		{
			cout << "�������µ�����������" << endl;
			cin >> temp;
		}
	}
	UpdateSeat(tar, tar->start->name, tar->end->name, temp - tar->maximun);
	tar->maximun = temp;
	cout << "���ĳɹ���" << endl;
	cout << "���ĺ�����Ϣ���£�" << endl;
	AppDisplayOneTrain(tar);
}
void AddStation(Train*tar,Ticket*origin)
{
	if (TicketHasTrain(origin, tar->train))cout << "�ð�����ж�������ȷ����Ӱ��˿ͳ��У�";
	Station*temp = new Station;
	cout << "��������վ�����֣�" << endl;
	cin >> temp->name;
	temp->next = NULL;
	cout << "��ѡ�����վ��ķ�ʽ��1������ʼ��վ  2�������յ�վ  3��������;վ" << endl;
	int i; cin >> i;
	while (i != 1 && i != 2 && i != 3)
	{
		cout << "������Ч��" << endl;
		cout << "��ѡ�����վ��ķ�ʽ��1������ʼ��վ  2�������յ�վ  3��������;վ" << endl;
		cin >> i;
	}
	switch (i)
	{
	case 1:temp->seat = tar->maximun;  //ʼ��վ������Ϊ��������
		temp->next = tar->start;
		tar->start = temp; break;
	case 2:temp->seat = 0;  //�յ�վ�Ŀ�����������
		tar->end->seat = tar->maximun;
		tar->end->next = temp;
		tar->end = temp; break;
	case 3:cout << "����������վ�����λ��ǰһվ������" << endl;
		char station_ahead[20]; cin >> station_ahead;
		Station*pre = FindStation(tar->start, station_ahead);
		temp->seat = pre->seat;  //������վ��ǰһ��վ��������ͬ
		temp->next = pre->next;
		pre->next = temp; break;
	}
	cout << "���ӳɹ���" << endl;
	cout << "���ĺ�����Ϣ���£�" << endl;
	AppDisplayOneTrain(tar);
}
void DeleteStation(Train*tar,Ticket*&origin)
{
	char temp[20];
	cout << "������Ҫɾ����վ������" << endl;
	cin >> temp;
	while (FindStation(tar->start, temp) == NULL)
	{
		cout << "�޸�վ����Ϣ����ȷ����������" << endl;
		cout << "1����������  2������" << endl;
		int i; cin >> i;
		while (i != 1 && i != 2)
		{
			cout << "������Ч��" << endl;
			cout << "1����������  2������" << endl;
			cin >> i;
		}
		if (i == 2)return;
		else
		{
			cout << "������Ҫɾ����վ������" << endl;
			cin >> temp;
		}
	}
	Ticket*related_ticket = FindAllTicketToTrain(origin, tar->train);
	if (related_ticket != NULL && HasStationBooked(related_ticket, temp))
	{
		cout << "ɾ����վ��ᵼ���ѹ�Ʊ�˿��޷���ԭ�ƻ����У�����ʧ�ܣ�" << endl;
		origin=MergeTicketList(origin, related_ticket);
		return;
	}
	origin = MergeTicketList(origin, related_ticket);
	DeleteOneStation(tar->start, temp);
	cout << "ɾ���ɹ���" << endl;
	cout << "���ĺ�����Ϣ���£�" << endl;
	AppDisplayOneTrain(tar);
}
void ModifyTrain(Train*head,Ticket*&origin)
{
	char train_name[20];
	cout << "������Ҫ�޸ĵİ�κţ�" << endl;
	cin >> train_name;
	Train*tar = head;
	while (tar != NULL && strcmp(tar->train, train_name) != 0)tar = tar->next;  //����Ŀ����
	while (tar == NULL)        //��β�����ʱ�������
	{
		cout << "�ð�β����ڣ�ѡ��1.��������  2.����"<<endl;
		int i; cin >> i;
		while (i != 1 && i != 2)
		{
			cout << "�ð�β����ڣ�ѡ��1.��������  2.����"<<endl;
			cin >> i;
		}
		if (i == 1)
		{
			cout << endl << "������Ҫ�޸ĵİ�κţ�" << endl;
			cin >> train_name;
		}
		else return;
		tar = head;
		while (tar != NULL && strcmp(tar->train, train_name) != 0)tar = tar->next;
	}
	cout << "��Ӧ�����Ϣ���£�" << endl;
	AppDisplayOneTrain(tar);
	cout << "��ѡ���޸ĵ����ݣ�1�������κ�  2���޸�����������  3������;��վ��  4��ɾ��;��վ��" << endl;
	int i; cin >> i;
	while (i != 1 && i != 2 && i != 3 && i != 4)
	{
		cout << "������Ч"<<endl;
		cout << "��ѡ���޸ĵ����ݣ�1�������κ�  2���޸�����������  3������;��վ��  4��ɾ��;��վ��" << endl;
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
		cout << "���ذ����Ϣ����" << endl;
		system("pause");
		return;
	}
	while (1)
	{
		system("cls");
		cout << "1�����Ӱ��" << endl;
		cout << "2��ɾ�����" << endl;
		cout << "3���޸İ��" << endl;
		cout << "4���������˵�" << endl;
		int i; cin >> i;
		while (i != 1 && i != 2 && i != 3 && i != 4)
		{
			cout << "������Ч�����������룡" << endl;
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