#pragma once
#ifndef MANAGE_H
#define MANAGE_H

#include"Train.h"
#include"Ticket.h"
#include"File.h"
#include<iostream>
using namespace std;
#include<cstring>
#include<conio.h>
#include<iomanip>

void TicketInfoManage(Train *&train_head, Ticket*&origin);
void SearchTrainInfo(Train *&train_head);
#endif // !MANAGE_H
