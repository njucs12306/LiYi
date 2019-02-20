#include"Train.h"
Train *FileLoadTrain(FILE*f)        //从文件中载入一条列车的信息，返回链表的一个节点
{
	char c = fgetc(f);     //防止空白符干扰判断空白文件或文件结尾
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
	tmp->start = NewTrainFileInput(f);          //生成途经站点的链表
	tmp->end = tmp->start;
	while (tmp->end->next != NULL)tmp->end = tmp->end->next;
	tmp->end->seat = 0;
	tmp->next = NULL;
	return tmp;
}
Train *AppAddTrain()         //程序运行时添加一条列车信息，返回链表的一个节点
{
	Train*tmp = new Train;
	char c;
	if (c = getchar() == '\n')c = getchar(); //避免缓冲区未清除的换行符存入列车班次号
	int i = 0;
	while (c != ',')
	{
		tmp->train[i] = c;
		i++;
		c = getchar();
	}
	tmp->train[i] = '\0';
	cin >> tmp->maximun;
	tmp->start = NewTrainAppInput();       //生成途经站点的链表
	tmp->end = tmp->start;
	while (tmp->end->next != NULL)tmp->end = tmp->end->next;
	tmp->end->seat = 0;
	tmp->next = NULL;
	return tmp;
}
void DeleteTrainList(Train*head)    //归还班次信息链表的空间
{
	while (head != NULL)
	{
		DeleteStationList(head->start);
		Train*temp = head->next;
		delete head;
		head = temp;
	}
}
void AppDisplayOneTrain(Train*src)  //程序运行时显示一个班次的信息
{
	cout << src->train << ", " << src->maximun;
	AppDisplayStation(src->start);
	cout << endl;
}
void AppDisplayTrainList(Train*head)    //程序运行时显示全部班次的信息
{
	while (head != NULL)
	{
		AppDisplayOneTrain(head);
		head = head->next;
	}
}
int CountMinSeat(Train*src)     //计算整个列车的最小空座数
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
int CountRestTicket(Train*src, const char*from, const char*to)  //计算从出发站(from)至到达站(to)最小空座数作为余票
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
bool IsTrainInNeed(Train*tar, const char*from, const char*to)   //根据出发站和到达站判断某班次是否符合路线条件
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
Train *HeadInsertList(Train*src, Train*head)    //头部插入生成链表
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
Train *FindRelateTrainList(Train*&head1, const char*from, const char*to)  //根据出发站和到达站查询车次，并生成独立链表
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
Train *FindTrain(Train*head, const char*train_name)   //根据班次号查询列车
{
	Train*cur = head;
	while (cur != NULL)
	{
		if (strcmp(cur->train, train_name) == 0)break;
		else cur = cur->next;
	}
	return cur;
}
Train*MergeTrainList(Train*head1, Train*head2)  //合并两个班次信息的链表
{
	Train*tail1 = head1;
	while (tail1->next != NULL)tail1 = tail1->next;
	tail1->next = head2;
	SortTrainListByName(head1);
	return head1;
}
void SortTrainListByName(Train*&head)   //按照班次号排序
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
void UpdateSeat(Train*tar, const char*from, const char*to,int change)  //将出发站(from)至到达站(to)之间的空座数更新
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