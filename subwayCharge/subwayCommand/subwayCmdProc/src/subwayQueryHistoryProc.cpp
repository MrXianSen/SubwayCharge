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
@ ��ѯ��ʷ���Ѽ�¼
@ ��Σ�unCmd, ��������
@ ����: returnStr
@ ����ֵ: ��
*/
void ProcQueryHistoryCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    // ��ѯ��ʷ���Ѽ�¼

    // ���ҿ���Ϣ GetCardInfo()
    unsigned int cardNo = unCmd.stCmdQueryHis.cardNo;
    unsigned int balance = 0;
    EN_CARD_TYPE enCard;
    EN_RETURN_CODE enResult = GetCardInfo(cardNo, balance ,enCard);
    if (enResult != EN_RETURN_SUCC)
    {
        GetOutputResultStr(EN_CMD_TYPE_QUERY_HIS, enResult, cardNo, enCard, balance, returnStr);
        return;
    }

    // �ж��Ƿ��� ���̿�
    if (EN_CARD_TYPE_SINGLE == enCard)
    {
        GetOutputResultStr(EN_CMD_TYPE_QUERY_HIS, EN_RETURN_SINGLE_CARD_CANNOT_HISTORY, cardNo, enCard, balance, returnStr);
        return;
    }

    // ��ȡ��ʷ��¼���ѽ����ӵ� returnStr �ĺ��
    GetOutputResultStr(EN_CMD_TYPE_QUERY_HIS, enResult, cardNo, enCard, balance, returnStr);
    QueryHistory(cardNo, returnStr);
}
