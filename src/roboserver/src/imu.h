#ifndef _IMU_H_
#define _IMU_H_


#define BUF_LENGTH (30)
/* Struct */
typedef struct
{
  int start;
  char lastInData;
  char buf[32];
  int n;
  char sum;
  int error;
}serialObj;

typedef struct
{
    short x;
    short y;
    short z;
}xyzObj;

typedef struct
{
    xyzObj acc;
    xyzObj gyro;
    xyzObj mag;
    xyzObj angle;
    int pressure;
}imuObject;

void imu_task(void);


#endif
