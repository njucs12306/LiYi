#include"Station.h"

Station *NewTrainAppInput()  //������������Ӱ��ʱ���ã�¼��վ����Ϣ
{
	Station*head = NULL, *tail = NULL;
	char c;
	c = getchar();
	while (c != '\n')    //���з���ʶ¼�����
	{
		if (c == '|')c = getchar();
		if (c != '\n')
		{
			Station *tmp = new Station;
			int i = 0;
			while (c != '|'&&c != '\n')  //��'|'֮������ݴ���Station������
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
Station *NewTrainFileInput(FILE*f)   //���ļ���¼����ʱ���ã�¼��վ����Ϣ
{
	Station*head = NULL, *tail = NULL;
	char c;
	c = fgetc(f);
	while (c != '\n'&& !feof(f))          //���з���ʶ¼�����
	{
		if (c == '|')c = fgetc(f);
		if (c != '\n' && !feof(f))
		{
			Station *tmp = new Station;
			int i = 0;
			while (c != '|'&& c != ',')      //��'|'֮������ݴ���Station������,���Ǽ���վ��������Ʊ���ĸ�ʽ(|Nanjing,20|)
			{
				tmp->name[i] = c;
				i++;
				c = fgetc(f);
			}
			tmp->name[i] = '\0';
			if (c == ',')   //���վ�����������Ʊ��
			{
				fscanf_s(f, "%d", &tmp->seat);
				c = fgetc(f);
			}
			else tmp->seat = 100;     //���ʼ¼����ʱֻ��վ������Ĭ����ƱΪ100
			tmp->next = NULL;
			if (head == NULL)head = tmp;
			else tail->next = tmp;
			tail = tmp;
		}
	}
	return head;
}
void StationFileOutput(FILE*f,Station*head)   //���ļ��б�������Ϣʱ����д��վ�����Ʊ
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
void DeleteStationList(Station*head) //ɾ�����;����վ�������
{
	while (head != NULL)
	{
		Station*temp = head->next;
		delete head;
		head = temp;
	}
}  
void AppDisplayStation(Station*head)  //����Ļ����ʾĳ����г�;����վ����Ϣ
{
	while (head != NULL)
	{
		cout << "|" << head->name << "," << head->seat;
		head = head->next;
	}
	cout << "|";
}
Station *FindStation(Station*head,const char*name)  //�������ֲ��ҳ�վ
{
	Station*cur = head;
	while (cur != NULL && strcmp(cur->name, name) != 0)
		cur = cur->next;
	return cur;
}
void DeleteOneStation(Station*&head, const char*name)   //���ݳ�վ����վ������������ڵ�
{
	if (head == NULL)
	{
		cout << "ɾ��ʧ�ܣ���վ����Ϣ��" << endl;
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
	cout << "ɾ��ʧ�ܣ���վ����Ϣ��" << endl;
	return;
}
