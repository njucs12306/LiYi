#include"File.h"
Train*LoadTrainInfo(const char *file_name)
{
	FILE *f;
	fopen_s(&f, file_name, "rt");
	Train*head = NULL, *tail = NULL;
	while (!feof(f))
	{
		Train*tmp = FileLoadTrain(f);
		if (head == NULL)head = tmp;
		else tail->next = tmp;
		tail = tmp;
	}
	fclose(f);
	return head;
}
void RecordTrainInfo(const char*file_name,Train*head)
{
	FILE*f;
	fopen_s(&f, file_name, "wt");
	while (head != NULL)
	{
		fprintf(f, "%s, %d", head->train, head->maximun);
		StationFileOutput(f, head->start);
		head = head->next;
	}
	fclose(f);
}
Ticket*LoadTicketInfo(const char *file_name)
{
	FILE *f;
	fopen_s(&f, file_name, "rt");
	Ticket*head = NULL,*tail = NULL;
	while (!feof(f))
	{
		Ticket*tmp = FileAddTicket(f);
		if (head == NULL)head = tmp;
		else tail->next = tmp;
		tail = tmp;
	}
	fclose(f);
	return head;
}
void RecordTicketInfo(const char*file_name, Ticket*head)
{
	FILE*f;
	fopen_s(&f, file_name, "wt");
	while (head != NULL)
	{
		fprintf(f, "%s %s %s %s %d\n", head->number, head->train, head->start, head->end, head->n);
		head = head->next;
	}
	fclose(f);
}