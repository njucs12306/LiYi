#include"Station.h"

Station *NewTrainAppInput()  //程序运行中添加班次时调用，录入站点信息
{
	Station*head = NULL, *tail = NULL;
	char c;
	c = getchar();
	while (c != '\n')    //换行符标识录入结束
	{
		if (c == '|')c = getchar();
		if (c != '\n')
		{
			Station *tmp = new Station;
			int i = 0;
			while (c != '|'&&c != '\n')  //将'|'之间的内容存入Station的名字
			{
				tmp->name[i] = c;
				i++;
				c = getchar();
			}
			tmp->name[i] = '\0';
			tmp->seat = 100;
			tmp->next = NULL;
			if (head == NULL)head = tmp;
			else tail->next = tmp;
			tail = tmp;
		}
	}
	return head;
}
Station *NewTrainFileInput(FILE*f)   //从文件中录入班次时调用，录入站点信息
{
	Station*head = NULL, *tail = NULL;
	char c;
	c = fgetc(f);
	while (c != '\n'&& !feof(f))          //换行符标识录入结束
	{
		if (c == '|')c = fgetc(f);
		if (c != '\n' && !feof(f))
		{
			Station *tmp = new Station;
			int i = 0;
			while (c != '|'&& c != ',')      //将'|'之间的内容存入Station的名字,考虑兼容站点后紧接余票数的格式(|Nanjing,20|)
			{
				tmp->name[i] = c;
				i++;
				c = fgetc(f);
			}
			tmp->name[i] = '\0';
			if (c == ',')   //如果站点名后紧接余票数
			{
				fscanf_s(f, "%d", &tmp->seat);
				c = fgetc(f);
			}
			else tmp->seat = 100;     //最初始录入班次时只有站点名，默认余票为100
			tmp->next = NULL;
			if (head == NULL)head = tmp;
			else tail->next = tmp;
			tail = tmp;
		}
	}
	return head;
}
void StationFileOutput(FILE*f,Station*head)   //向文件中保存班次信息时用于写入站点和余票
{
	while (head != NULL)
	{
		fputc('|', f);
		fprintf(f, "%s,%d", head->name,head->seat);
		head = head->next;
	}
	fputc('|', f);
	fputc('\n', f);
}
void DeleteStationList(Station*head) //删除班次途经各站点的链表
{
	while (head != NULL)
	{
		Station*temp = head->next;
		delete head;
		head = temp;
	}
}  
void AppDisplayStation(Station*head)  //在屏幕上显示某班次列车途经的站点信息
{
	while (head != NULL)
	{
		cout << "|" << head->name << "," << head->seat;
		head = head->next;
	}
	cout << "|";
}
Station *FindStation(Station*head,const char*name)  //根据名字查找车站
{
	Station*cur = head;
	while (cur != NULL && strcmp(cur->name, name) != 0)
		cur = cur->next;
	return cur;
}
void DeleteOneStation(Station*&head, const char*name)   //根据车站名在站点链表中清除节点
{
	if (head == NULL)
	{
		cout << "删除失败！无站点信息！" << endl;
		return ;
	}
	Station*cur = head, *pre = NULL;
	while (cur != NULL)
	{
		if (strcmp(name, cur->name) == 0)
		{
			if (pre == NULL)
			{
				head = head->next;
				delete cur;
				cur = head;
				return;
			}
			else
			{
				pre->next = cur->next;
				delete cur;
				cur = pre->next;
				return;
			}
		}
		else
		{
			pre = cur;
			cur = cur->next;
		}
	}
	cout << "删除失败！无站点信息！" << endl;
	return;
}
