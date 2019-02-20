#pragma once
#ifndef TRAIN_H
#define TRAIN_H

#include"Station.h"
#include<iostream>
struct Train
{
	char train[20];//班次
	int maximun;   //最大承载量
	Station *start;//该班次的始发站（指向Station链表头节点）
	Station *end;  //该班次的终点站（指向Station链表尾节点）
	Train *next;   //下一班次
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
