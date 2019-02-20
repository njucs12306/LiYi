#pragma once
#ifndef TICKET_H
#define TICKET_H

#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;
struct Ticket
{
	char number[4]; //������
	char train[20];  //�г���
	char start[20];  //ʼ��վ
	char end[20];    //�յ�վ
	int n;    //Ʊ��
	Ticket *next; //��һ����
};

Ticket *FileAddTicket(FILE *f);
bool TicketHasTrain(Ticket*head, const char*train_name);
void DeleteTicketList(Ticket*head);
void SubstituteTrainName(Ticket*head, const char*origin_name, const char*sub_name);
Ticket *FindAllTicketToTrain(Ticket*&head1, const char*train_name);
bool HasStationBooked(Ticket*head, const char*station_name);
char*GetTicketNumber(Ticket*head);
void SortTicketListByNumber(Ticket*&head);
Ticket *AppAddTicket(Ticket*origin, Ticket*add);
void AppDisplayTicketList(Ticket*head);
void AppDisplayOneTicket(Ticket*src);
void DeleteOneTicket(Ticket*&head, const char*ticket_number);
Ticket*FindTicket(Ticket*head, const char*ticket_number);
Ticket*MergeTicketList(Ticket*head1, Ticket*head2);

#endif // !TICKET_H
