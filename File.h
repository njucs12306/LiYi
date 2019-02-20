#pragma once
#ifndef FILE_H
#define FILE_H

#include<iostream>
using namespace std;
#include<assert.h>
#include"Train.h"
#include"Ticket.h"

Train*LoadTrainInfo(const char *file_name);
Ticket*LoadTicketInfo(const char *file_name);
void RecordTrainInfo(const char*file_name, Train*head);
void RecordTicketInfo(const char*file_name, Ticket*head);

#endif // !FILE_H
