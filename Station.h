#pragma once
#ifndef STATION_H
#define STATION_H

#include <iostream>
using namespace std;
struct Station
{
	char name[20]; //վ��
	int seat;       //������
	Station *next; //��һͣ��վ
};

Station *NewTrainAppInput();
Station *NewTrainFileInput(FILE*f);
void StationFileOutput(FILE*f, Station*head);
void DeleteStationList(Station*head);
void AppDisplayStation(Station*head);
Station *FindStation(Station*head, const char*name);
void DeleteOneStation(Station*&head, const char*name);


#endif