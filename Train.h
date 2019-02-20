#pragma once
#ifndef TRAIN_H
#define TRAIN_H

#include"Station.h"
#include<iostream>
struct Train
{
	char train[20];//���
	int maximun;   //��������
	Station *start;//�ð�ε�ʼ��վ��ָ��Station����ͷ�ڵ㣩
	Station *end;  //�ð�ε��յ�վ��ָ��Station����β�ڵ㣩
	Train *next;   //��һ���
};
Train *FileLoadTrain(FILE*f);
Train *AppAddTrain();
void DeleteTrainList(Train*head);
void AppDisplayOneTrain(Train*src);
void AppDisplayTrainList(Train*head);
int CountMinSeat(Train*src);
int CountRestTicket(Train*src, const char*from, const char*to);
Train *FindRelateTrainList(Train*&head1, const char*from, const char*to);
Train *FindTrain(Train*head, const char*train_name);
Train*MergeTrainList(Train*head1, Train*head2);
void SortTrainListByName(Train*&head);
void UpdateSeat(Train*tar, const char*from, const char*to, int change);

#endif // !TRAIN_H
