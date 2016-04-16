#ifndef _ROBOLINK_H_
#define _ROBOLINK_H_

#include <queue>

#define ControlWordIndex (0)
#define ModesofOperationIndex (1)
#define TargetCurrentIndex (2)
#define TargetVelocityIndex (3)
#define TargetPositionIndex (4)
#define MaxCurrentIndex (5)
#define MaxVelocityIndex (6)
#define MaxPositionIndex (7)
#define MinPositionIndex (8)
#define ProfileAccIndex (9)
#define ProfileDecIndex (10)
#define ProfileVelocityIndex (11)
#define InterpolatedPosition (12)
/* Status Index */
#define StatusWordIndex (50)
#define ActualCurrentIndex (51)
#define ActualVelocityIndex (52)
#define ActualPositionIndex (53)

typedef struct
{
    char id;
    char data[8];
}sendMsgObj;


typedef struct
{
  unsigned int StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */

  unsigned int ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */

  unsigned char IDE;     /*!< Specifies the type of identifier for the message that
                        will be received. This parameter can be a value of
                        @ref CAN_identifier_type */

  unsigned char RTR;     /*!< Specifies the type of frame for the received message.
                        This parameter can be a value of
                        @ref CAN_remote_transmission_request */

  unsigned char DLC;     /*!< Specifies the length of the frame that will be received.
                        This parameter can be a value between 0 to 8 */

  unsigned char Data[8]; /*!< Contains the data to be received. It ranges from 0 to
                        0xFF. */

  unsigned char FMI;     /*!< Specifies the index of the filter the message stored in
                        the mailbox passes through. This parameter can be a
                        value between 0 to 0xFF */
} CanRxMsg;

extern std::queue<sendMsgObj> sendMsgQueue;
int roboLinkInit(void);
void servoOn(void);
void servoOff(void);
void timerInit(void);
void sendIPM(short dp1, short dp2, short dp3, short dp4);
int sendBufSize(void);
#endif
