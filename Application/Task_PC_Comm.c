#include "config.h"
#include "cmsis_os.h"
#include "interface.h"
#include "string.h"
#include "FM_Uart.h"
#include "Task_PC_Comm.h"


static uint8_t index;


/********************************************************************************/
/*函数名：  PC_Comm_Init                                                             */
/*功能说明：模块初始化函数                                                        */
/*输入参数：无*/
/*输出参数：无                                                                   */
/********************************************************************************/
void PC_Comm_Init(void)
{//模块初始化
  //RTU_AddReqBlock(&rtu_ctx[RTU_Req_ReadCurrent_Thres.chnindex],&RTU_Req_ReadCurrent_Thres);
  index=0;
}

/********************************************************************************/
/*函数名：  PC_Comm_MainFunction                                                       */
/*功能说明：RTU master主task, 分时调用，减少CPU load                                         */
/*输入参数：无                                                                        */
/*输出参数：无                                                                        */
/*******************************************************************************/
void PC_Comm_MainFunction(void *p_arg)
{
  USARTCHN_Recv_t Recv_Data;
  uint16_t da_val;
  if( Que_UartID[UART_CHN_PC_COMM] != 0)    
  {// 从创建的队列中接收一个消息，如果消息无效，阻塞在此处        
    if(xQueueReceive( Que_UartID[UART_CHN_PC_COMM], &(Recv_Data), ( portTickType ) 10 ) )        
    {// 现在pcRxedMessage 指向由vATask任务投递进来的结构体Amessage变量        }    }
      da_val = Recv_Data.databuf[0]*256+Recv_Data.databuf[1];
      Spi5541_WriteOneByte(da_val);
    }
	}
}

