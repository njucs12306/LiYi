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
		cout << "�����Ϣ���س���" << endl;
		return;
	}
	char start[20], end[20];
	cout << "�������������վ�͵���վ��" << endl;
	cin >> start >> end;
	Train*relate_train = FindRelateTrainList(train_head, start, end);
	SortTrainListByName(relate_train);
	if (relate_train == NULL)cout << "��Ǹ������ƥ��İ�Σ��������ͨ���ߣ�";
	else
	{
		cout << "��ѯ�����г����£�" << endl;
		cout <<setiosflags(ios::left)<< setw(20) << " ����"<< setw(20) <<"ʼ��վ" << setw(20) <<"�յ�վ" << setw(20) <<"��Ʊ" << endl;
		Train*cur = relate_train;
		while (cur != NULL)
		{
			cout << setiosflags(ios::left) << setw(20) << cur->train << setw(20) << cur->start->name << setw(20) << cur->end->name << setw(20) << CountRestTicket(cur, start, end) << endl;
			cur = cur->next;
		}
		cout << "������ҪԤ���İ�Σ�" << endl;
		char train_name[20]; cin >> train_name;
		Train*tar = FindTrain(relate_train, train_name);
		while (tar == NULL)
		{
			cout << "����Ӧ��Σ���ȷ������İ�κ�����" << endl;
			cout << "��ѡ��1����������  2������" << endl;
			int i; cin >> i;
			while (i != 1 && i != 2)
			{
				cout << "������Ч������������" << endl;
				cin >> i;
			}
			if (i == 2)
			{
				train_head = MergeTrainList(train_head, relate_train);
				return;
			}
			else
			{
				cout << "�������κţ�" << endl;
				cin >> train_name;
				tar = FindTrain(relate_train, train_name);
			}
		}
		cout << "������Ҫ�����Ʊ����" << endl;
		int num; cin >> num;
		int max = CountRestTicket(tar, start, end);
		while (num > max)
		{
			cout << "��Ǹ,��Ʊ(��" << max << ")���㣡��ѡ��1��������Ʊ  2����������" << endl;
			int i; cin >> i;
			while (i != 1 && i != 2)
			{
				cout << "������Ч��" << endl;
				cout<< "��ѡ��1��������Ʊ  2����������" << endl;
				cin >> i;
			}
			if (i == 1)
			{
				train_head=MergeTrainList(train_head, relate_train);
				return;
			}
			else
			{
				cout << "�����빺Ʊ������" << endl;
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
		cout << "��Ʊ�ɹ������Ķ�����Ϊ"<<addition->number<<" �����Ƽ�¼" << endl;
	}
}
void DeleteTicket(Train *train_head,Ticket*&origin)
{
	if (origin == NULL)
	{
		cout << "������ϢΪ�գ���ȷ���Ƿ���ȷ���ض�����Ϣ�����޶�����" << endl;
		return;
	}
	if (train_head == NULL)
	{
		cout << "�����Ϣ���س���" << endl;
		return;
	}
	cout << "�������˶���Ʊ�Ķ����ţ�" << endl;
	char temp_number[4]; cin >> temp_number;
	Ticket*tar = FindTicket(origin, temp_number);
	while (tar == NULL)
	{
		cout << "δ��ѯ���Ķ�����Ϣ����ѡ��1���������붩����  2������" << endl;
		int i; cin >> i;
		while (i != 1 && i != 2)
		{
			cout << "������Ч��" << endl;
			cout<<"��ѡ��1���������붩����  2������" << endl;
			cin >> i;
		}
		if (i == 2)return;
		else
		{
			cout << "�����붩���ţ�" << endl;
			cin >> temp_number;
			tar = FindTicket(origin, temp_number);
		}
	}
	cout << "������Ϣ���£���ȷ��" << endl;
	AppDisplayOneTicket(tar);
	system("pause");
	Train*tar_train = FindTrain(train_head, tar->train);
	UpdateSeat(tar_train, tar->start, tar->end, tar->n);
	DeleteOneTicket(origin, temp_number);
	cout << "��Ʊ�ɹ���" << endl;
}


void TicketInfoManage(Train *&train_head, Ticket*&origin)
{
	while (1)
	{
		system("cls");
		cout << "1����Ʊ" << endl;
		cout << "2���������" << endl;
		cout << "3����Ʊ" << endl;
		cout << "4���������˵�" << endl;
		int i; cin >> i;
		while (i != 1 && i != 2 && i != 3 && i != 4)
		{
			cout << "������Ч�����������룡" << endl;
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
		cout << "���ذ����Ϣ����" << endl;
		system("pause");
		return;
	}
	while (1)
	{
		system("cls");
		cout << "1��������/����վ��ѯ" << endl;
		cout << "2������κŲ�ѯ" << endl;
		cout << "3�����ȫ�����" << endl;
		cout << "4���������˵�" << endl;
		int i; cin >> i;
		while (i != 1 && i != 2 && i != 3&&i!=4)
		{
			cout << "������Ч�����������룡" << endl;
			cin >> i;
		}
		if (i == 1)
		{
			char start[20], end[20];
			cout << "�������������վ�͵���վ" << endl;
			cin >> start >> end;
			Train*relate_train = FindRelateTrainList(train_head, start, end);
			SortTrainListByName(relate_train);
			if (relate_train == NULL)cout << "��Ǹ������ƥ��İ��" << endl;
			else
			{
				cout << "��ѯ�����г����£�" << endl;
				cout << setiosflags(ios::left) << setw(20) << " ����" << setw(20) <<"ʼ��վ" << setw(20) <<"�յ�վ" << setw(20) <<"��Ʊ" << setw(20) << endl;
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
			cout << "�������κ�" << endl;
			cin >> train_number;
			Train*tar = FindTrain(train_head, train_number);
			while (tar == NULL)
			{
				cout << "δ��ѯ�������Ϣ����ѡ��1����������  2������" << endl;
				int i; cin >> i;
				while (i != 1 && i != 2)
				{
					cout << "������Ч��" << endl;
					cout << "��ѡ��1����������  2������" << endl;
					cin >> i;
				}
				if (i == 2)goto END;
				else
				{
					cout << "�������κţ�" << endl;
					cin >> train_number;
					tar = FindTrain(train_head, train_number);
				}
			}
			cout << "��ѯ���İ����Ϣ���£�" << endl;
			AppDisplayOneTrain(tar);
		}
		else if (i == 3)AppDisplayTrainList(train_head);
		else return;
	END:;
		system("pause");
	}
}

