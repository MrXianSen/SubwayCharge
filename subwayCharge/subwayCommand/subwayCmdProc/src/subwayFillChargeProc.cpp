#include "stdafx.h"
#include <iostream>
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
#include "subwayline.h"
#include "subwayPrice.h"
#include "subwayCommon.h"
#include "subwayError.h"
#include "subwayCmdParse/subwayCmdParse.h"
#include "subwayOutput/subwayOutput.h"
using namespace std;

/*
@ ��ֵ����
@ ��Σ�unCmd, ��������
@ ����: returnStr
@ ����ֵ: ��
*/
void ProcFillChargeCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    //��ȡ����Ϣ GetCardInfo
    unsigned int balance;
    unsigned int cardNo = unCmd.stCmdFillCharge.cardNo;
    EN_CARD_TYPE enCard;
    EN_RETURN_CODE enResult = GetCardInfo(cardNo, balance ,enCard);
    if (enResult != EN_RETURN_SUCC)
    {
        GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, enResult, cardNo, enCard, balance, returnStr);
        return;
    }


    //���г�ֵ RechargeCard
    enResult = RechargeCard(cardNo, unCmd.stCmdFillCharge.cardCharge);
    if (enResult != EN_RETURN_SUCC)
    {
        GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, enResult, cardNo, enCard, balance, returnStr);
        return;
    }


    //���ݳ�ֵ��Ŀ���Ϣ  GetCardInfo
    enResult = GetCardInfo(cardNo, balance ,enCard);
    GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, enResult, cardNo, enCard, balance, returnStr);
    
}