﻿#ifndef __SUBWAY_ERR_INFO_H__
#define __SUBWAY_ERR_INFO_H__

//返回原因值
typedef enum
{
    EN_RETURN_SUCC = 0,
    EN_RETURN_INVALID_LINE,
    EN_RETURN_BALANCE_NOT_ENOUGH,
    EN_RETURN_BALANCE_TOO_LOW,
    EN_RETURN_INVALID_CMD,
    EN_RETURN_INVALID_TIME,
    EN_RETURN_INVALID_CARD,
    EN_RETURN_ADD_STATION_REPEAT,
    EN_RETURN_INVALID_STATION,
    EN_RETURN_STATION_UNUSED,
    EN_RETURN_CARD_OVERLOW,
    EN_RETURN_SINGLE_CARD_CANNOT_RECHARGE,
    EN_RETURN_INPUT_INVALID_CARDTYPE,
    EN_RETURN_INVALID_DIS,
    EN_RETURN_RECHARGE_OVERFLOW,
    EN_RETURN_INNER_ERR,
    EN_RETURN_SINGLE_CARD_CANNOT_HISTORY,
    EN_RETURN_BUTT
}EN_RETURN_CODE;

/*
@ 返回错误字符串
@ 入参：enErrCode,错误码; 
@ 出参: 无
@ 返回值: 错误字符串;
*/
char* GetErrStr(EN_RETURN_CODE enErrCode);
#endif
