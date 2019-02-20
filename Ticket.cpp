#include"Ticket.h"
Ticket *FileAddTicket(FILE *f)  //���ļ�������һ�����������������һ���ڵ�
{
	char temp[20];
	if (fscanf_s(f, "%s", temp, 20) != NULL&&!feof(f)) //��ֹ�հ׷������жϿհ��ļ����ļ���β
	{
		Ticket*tmp = new Ticket;
		strcpy_s(tmp->number, 4, temp);
		fscanf_s(f, "%s", tmp->train, 20);
		fscanf_s(f, "%s", tmp->start, 20);
		fscanf_s(f, "%s", tmp->end, 20);
		fscanf_s(f, "%d", &tmp->n);
		tmp->next = NULL;
		return tmp;
	}
	else return NULL;    
}
Ticket *AppAddTicket(Ticket*origin, Ticket*add)
{
	if (origin == NULL)
	{
		origin = add;
		return origin;
	}
	else if (add == NULL)return origin;
	else
	{
		Ticket*tail = origin;
		while (tail->next != NULL)tail = tail->next;
		tail->next = add;
		return origin;
	}
}
void AppDisplayTicketList(Ticket*head)     //��������ʱչʾȫ��������Ϣ
{
	if (head == NULL)cout << "���޶�����Ϣ��" << endl;
	else cout << setiosflags(ios::left) << setw(20)<<"������" << setw(20) <<"��κ�" << setw(20) <<"����վ" << setw(20) <<"����վ" << setw(20) <<"Ʊ��" << endl;
	while (head != NULL)
	{
		cout << setiosflags(ios::left) << setw(20) << head->number << setw(20) << head->train << setw(20) << head->start << setw(20) << head->end << setw(20) << head->n << endl;
		head = head->next;
	}
}
void AppDisplayOneTicket(Ticket*src)  //��������ʱ��ʾһ��������Ϣ
{
	cout <<setiosflags(ios::left)<< setw(20) << "������" << setw(20) << "��κ�" << setw(20) << "����վ" << setw(20) << "����վ" << setw(20) << "Ʊ��" << endl;
	cout << setiosflags(ios::left) << setw(20) << src->number << setw(20) << src->train << setw(20) << src->start << setw(20) << src->end << setw(20) << src->n << endl;
}
bool TicketHasTrain(Ticket*head, const char*train_name)  //���ݰ�κŲ�ѯʱ���иð�εĶ���
{
	Ticket*cur = head;
	while (cur != NULL && strcmp(cur->train, train_name) != 0)
		cur = cur->next;
	if (cur == NULL)return false;
	else return true;
}
bool HasStationBooked(Ticket*head, const char*station_name)     //�ж�ĳ��վ���Ƿ�Ϊ�����еĳ���վ�򵽴�վ
{
	Ticket*cur = head;
	while (cur != NULL)
	{
		if (strcmp(cur->start, station_name) == 0 || strcmp(cur->end, station_name) == 0)return true;
		else cur = cur->next;
	}
	return false;
}
void DeleteTicketList(Ticket*head)  //�黹��������ռ�õĿռ�
{
	if (head == NULL)
	{
		cout << "��δ�ҵ���Ӧ������Ϣ��" << endl;
	}
	while (head != NULL)
	{
		Ticket*temp = head->next;
		delete head;
		head = temp;
	}
}
void DeleteOneTicket(Ticket*&head, const char*ticket_number)  //��Ʊʱ���ݶ�����ɾ������������һ���ڵ�
{
	Ticket*cur = head, *pre = NULL;
	while (cur != NULL)
	{
		if (strcmp(cur->number, ticket_number) == 0)break;
		else
		{
			pre = cur;
			cur = cur->next;
		}
	}
	if (cur == NULL)
	{
		cout << "��δ�ҵ���Ӧ������Ϣ��" << endl;
		return;
	}
	else if (pre == NULL)
	{
		head = head->next;
		delete cur;
	}
	else 
	{
		pre->next = cur->next;
		delete cur;
	}
}
void SubstituteTrainName(Ticket*head, const char*origin_name,const char*sub_name)//�������ж�Ӧ��κ���sub_name�滻
{
	while (head != NULL)
	{
		if (strcmp(head->train, origin_name) == 0)strcpy_s(head->train,20, sub_name);
		head = head->next;
	}
}
Ticket *HeadInsertList(Ticket*src, Ticket*head)    //ͷ�����뷨��������
{
	if (src == NULL)return head;
	else if (head == NULL)
	{
		head = src;
		return head;
	}
	else
	{
		src->next = head;
		head = src;
		return head;
	}
}
Ticket *FindAllTicketToTrain(Ticket*&head1, const char*train_name)   //���Ҷ�Ӧ���εĶ������ɶ�������
{
	Ticket*head2 = NULL;
	Ticket*cur = head1, *pre = NULL;
	while (cur != NULL)
	{
		if (strcmp(cur->train, train_name) == 0)
		{
			if (pre == NULL)
			{
				head1 = head1->next;
				cur->next = NULL;
				head2 = HeadInsertList(cur, head2);
				cur = head1;
			}
			else
			{
				pre->next = cur->next;
				cur->next = NULL;
				head2 = HeadInsertList(cur, head2);
				cur = pre->next;
			}
		}
		else
		{
			pre = cur;
			cur = cur->next;
		}
	}
	return head2;
}  
char*GetTicketNumber(Ticket*head)    //��ö�����ˮ��
{
	Ticket*cur = head;
	char *temp = cur->number;
	while (cur != NULL)
	{
		if (strcmp(cur->number, temp) > 0)temp = cur->number;
		cur = cur->next;
	}
	return temp;
}
Ticket*FindTicket(Ticket*head, const char*ticket_number)  //���ݶ����Ų�ѯ����
{
	Ticket*cur = head;
	while (cur != NULL)
	{
		if (strcmp(cur->number, ticket_number) == 0)break;
		else cur = cur->next;
	}
	return cur;
}
void SortTicketListByNumber(Ticket*&head)   //���ݶ���������
{
	if (head == NULL)return;
	else if (head->next == NULL)return;
	bool flag = true;
	while (flag)
	{
		flag = false;
		Ticket*cur = head, *pre = NULL;
		while (cur->next != NULL)
		{
			if (strcmp(cur->number, cur->next->number) > 0)
			{
				if (pre == NULL)
				{
					head = cur->next;
					cur->next = head->next;
					head->next = cur;
					pre = head;
					flag = true;
				}
				else
				{
					pre->next = cur->next;
					cur->next = pre->next->next;
					pre = pre->next;
					pre->next = cur;
					flag = true;
				}
			}
			else
			{
				pre = cur;
				cur = cur->next;
			}
		}
	}
}
Ticket*MergeTicketList(Ticket*head1, Ticket*head2)  //�ϲ�������������
{
	Ticket*tail1 = head1;
	while (tail1->next != NULL)tail1 = tail1->next;
	tail1->next = head2;
	SortTicketListByNumber(head1);
	return head1;
}

