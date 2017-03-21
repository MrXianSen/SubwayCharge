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
@ ������Ʊ
@ ��Σ�unCmd, ��������
@ ����: returnStr
@ ����ֵ: ��
*/

void ProcCreateSingleTicketCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    //��ȡ����վ��������� GetSubwayStationDis

    //��ȡ����վ���Ļ���Ʊ��  GetBasePrice

    //�쵥�̿� AssignCard

    //����ַ���
    //GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, returnCode, cardNo, EN_CARD_TYPE_SINGLE, basePrice, returnStr);
    char *srcStation = unCmd.stCmdSingleTicket.srcStation;
    char *dstStation = unCmd.stCmdSingleTicket.dstStation;
    unsigned int dis = 0;
    int charge = 0;
    unsigned int cardNo = 0;
    EN_CARD_TYPE enCard = EN_CARD_TYPE_SINGLE;
    EN_RETURN_CODE enResult = GetSubwayStationDis(srcStation, dstStation, dis);
    if (enResult != EN_RETURN_SUCC){
        GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, enResult, cardNo, enCard, charge, returnStr);
        return;
    }
    charge = GetBasePrice(dis);
    enResult = AssignCard(cardNo, enCard, charge);
    GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, enResult, cardNo, enCard, charge, returnStr);
    return;
}