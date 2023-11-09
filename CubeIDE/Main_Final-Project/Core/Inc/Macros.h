#ifndef  _DIO_Macros_H
#define  _DIO_Macros_H


#define Get_bit(num,bitnum)        ((num >> bitnum) & 1 )
#define Set_bit(reg,bitN)          ((reg) |=(1<<bitN))
#define Clear_bit(reg,bitN)        ((reg) &= ~(1<<bitN))
#define Toggle_bit(reg,bitN)        reg ^= 1<<bitN
#define Set_port(reg,num)           reg=(num)|(0b11111111)
#define port_Value(reg,num)         reg=(num)&(0b11111111)
#define Clear_port(num)            (num)&0
#define SetPortValue(num,value)    (num)=value|1






#endif
