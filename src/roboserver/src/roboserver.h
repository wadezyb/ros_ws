#ifndef _ROBOSERVER_H_
#define _ROBOSERVER_H_
typedef struct
{
	char ID;
	char Status;
	char TargetPositon;
	char TargetAcc;
}roboAxisObj;

typedef struct
{
	int Status;
	int Counter;

}roboServerObj;
#endif
