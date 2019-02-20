#include"Train.h"
Train *FileLoadTrain(FILE*f)        //���ļ�������һ���г�����Ϣ�����������һ���ڵ�
{
	char c = fgetc(f);     //��ֹ�հ׷������жϿհ��ļ����ļ���β
	if (feof(f))return NULL;
	Train*tmp = new Train;
	int i = 0;
	while (c != ',')
	{
		tmp->train[i] = c;
		c = fgetc(f);
		++i;
	}
	tmp->train[i] = '\0';
	fscanf_s(f, "%d", &tmp->maximun);
	tmp->start = NewTrainFileInput(f);          //����;��վ�������
	tmp->end = tmp->start;
	while (tmp->end->next != NULL)tmp->end = tmp->end->next;
	tmp->end->seat = 0;
	tmp->next = NULL;
	return tmp;
}
Train *AppAddTrain()         //��������ʱ���һ���г���Ϣ�����������һ���ڵ�
{
	Train*tmp = new Train;
	char c;
	if (c = getchar() == '\n')c = getchar(); //���⻺����δ����Ļ��з������г���κ�
	int i = 0;
	while (c != ',')
	{
		tmp->train[i] = c;
		i++;
		c = getchar();
	}
	tmp->train[i] = '\0';
	cin >> tmp->maximun;
	tmp->start = NewTrainAppInput();       //����;��վ�������
	tmp->end = tmp->start;
	while (tmp->end->next != NULL)tmp->end = tmp->end->next;
	tmp->end->seat = 0;
	tmp->next = NULL;
	return tmp;
}
void DeleteTrainList(Train*head)    //�黹�����Ϣ����Ŀռ�
{
	while (head != NULL)
	{
		DeleteStationList(head->start);
		Train*temp = head->next;
		delete head;
		head = temp;
	}
}
void AppDisplayOneTrain(Train*src)  //��������ʱ��ʾһ����ε���Ϣ
{
	cout << src->train << ", " << src->maximun;
	AppDisplayStation(src->start);
	cout << endl;
}
void AppDisplayTrainList(Train*head)    //��������ʱ��ʾȫ����ε���Ϣ
{
	while (head != NULL)
	{
		AppDisplayOneTrain(head);
		head = head->next;
	}
}
int CountMinSeat(Train*src)     //���������г�����С������
{
	int min = 99999999;
	Station*cur = src->start;
	while (cur->next != NULL)
	{
		if (cur->seat < min)min = cur->seat;
		cur = cur->next;
	}
	return min;
}
int CountRestTicket(Train*src, const char*from, const char*to)  //����ӳ���վ(from)������վ(to)��С��������Ϊ��Ʊ
{
	Station*start = FindStation(src->start, from);
	Station*end = FindStation(start, to);
	int min = 99999999;
	while (start != end)
	{
		if (start->seat < min)min = start->seat;
		start = start->next;
	}
	return min;
}
bool IsTrainInNeed(Train*tar, const char*from, const char*to)   //���ݳ���վ�͵���վ�ж�ĳ����Ƿ����·������
{
	Station*start = FindStation(tar->start, from);
	if (from != NULL)
	{
		Station*end = FindStation(start, to);
		if (end != NULL)return true;
		else return false;
	}
	else return false;
}
Train *HeadInsertList(Train*src, Train*head)    //ͷ��������������
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
Train *FindRelateTrainList(Train*&head1, const char*from, const char*to)  //���ݳ���վ�͵���վ��ѯ���Σ������ɶ�������
{
	Train*head2 = NULL;
	Train*cur = head1, *pre = NULL;
	while (cur != NULL)
	{
		if (IsTrainInNeed(cur, from, to))
		{
			if (pre == NULL)
			{
				head1 = head1->next;
				cur->next = NULL;
				head2 = HeadInsertList(cur, head2);
				cur = head1->next;
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
Train *FindTrain(Train*head, const char*train_name)   //���ݰ�κŲ�ѯ�г�
{
	Train*cur = head;
	while (cur != NULL)
	{
		if (strcmp(cur->train, train_name) == 0)break;
		else cur = cur->next;
	}
	return cur;
}
Train*MergeTrainList(Train*head1, Train*head2)  //�ϲ����������Ϣ������
{
	Train*tail1 = head1;
	while (tail1->next != NULL)tail1 = tail1->next;
	tail1->next = head2;
	SortTrainListByName(head1);
	return head1;
}
void SortTrainListByName(Train*&head)   //���հ�κ�����
{
	if (head == NULL)return;
	else if (head->next == NULL)return;
	bool flag = true;
	while (flag)
	{
		flag = false;
		Train*cur = head, *pre = NULL;
		while (cur->next != NULL)
		{
			if (strcmp(cur->train, cur->next->train) > 0)
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
void UpdateSeat(Train*tar, const char*from, const char*to,int change)  //������վ(from)������վ(to)֮��Ŀ���������
{
	Station*start = FindStation(tar->start, from);
	Station*end = FindStation(start, to);
	while (start != end->next)
	{
		start->seat += change;
		start = start->next;
	}
	tar->end->seat = 0;
}