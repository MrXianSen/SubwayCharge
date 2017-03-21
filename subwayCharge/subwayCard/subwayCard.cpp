#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
//#include "list.h"
#include "subwayGlobalDef.h"
//#include "subwayMacro.h"
#include "subwayCard.h"

using namespace std;

//static unsigned int _cardNumber;
static vector<subwayCard*> _subwayCards;

/*
@ ��ʼ�����п���Ϣ
@ ����ֵ: ��
*/
void InitCardManagerInfo()
{
    //_cardNumber = 0;  // <- To be deleted.

    int curCardNum = _subwayCards.size();
    for (int i = 0; i < curCardNum; ++i) {
        if (NULL != _subwayCards[i]) {
            free(_subwayCards[i]);
            _subwayCards[i] = NULL;
        } 
    }

    _subwayCards = vector<subwayCard*>(MAX_CARD_NUM, NULL);
}



/*
@ ���������俨�źͿ���Ϣ
@ ��Σ�enCard,������; charge: ��ֵ
@ ����: cardNo, ����Ŀ���
@ ����ֵ: EN_RETURN_SUCC������ɹ�; EN_RETURN_CARD_OVERLOW, ����ʧ��;
*/
EN_RETURN_CODE AssignCard(unsigned int &cardNo, EN_CARD_TYPE enCard, unsigned int charge)
{
    if (charge > MAX_BALANCE) return EN_RETURN_RECHARGE_OVERFLOW;

    cardNo = MAX_CARD_NUM;
    for (int i = 0; i < MAX_CARD_NUM; ++i) {
        if (NULL == _subwayCards[i]) {
            cardNo = i;
            break;
        }
    }
    if (MAX_CARD_NUM == cardNo) return EN_RETURN_CARD_OVERLOW;
    
    
    subwayCard *pCard = (subwayCard*)malloc(sizeof(subwayCard));
    if (NULL != pCard) {
        pCard->cardNo = cardNo;
        pCard->balance = charge;
        pCard->enCard = enCard;
        pCard->history = NULL;
        _subwayCards[cardNo] = pCard;
    } else
        return EN_RETURN_INNER_ERR;

    return EN_RETURN_SUCC;
}



/*
@ ��ֵ
@ ��Σ�cardNo,����; recharge: ��ֵ
@ ����: ��
@ ����ֵ: EN_RETURN_SUCC���ɹ�; ����, ʧ��;
*/
EN_RETURN_CODE RechargeCard(unsigned int cardNo, unsigned int recharge)
{

    if (cardNo >= _subwayCards.size() || NULL == _subwayCards[cardNo]) 
        return EN_RETURN_INVALID_CARD;
    if (EN_CARD_TYPE_SINGLE == _subwayCards[cardNo]->enCard) 
        return EN_RETURN_SINGLE_CARD_CANNOT_RECHARGE;
    if ((recharge + _subwayCards[cardNo]->balance) > MAX_BALANCE) 
        return EN_RETURN_RECHARGE_OVERFLOW;

    _subwayCards[cardNo]->balance += recharge;
    return EN_RETURN_SUCC;
}



/*
@ ��ȡ�����
@ ��Σ�cardNo,����; 
@ ����: balance: ���
        enCard:  ������
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, ʧ��;
*/
EN_RETURN_CODE GetCardInfo(unsigned int cardNo, unsigned int &balance, EN_CARD_TYPE &enCard)
{
    if (cardNo >= _subwayCards.size() || NULL == _subwayCards[cardNo]) 
        return EN_RETURN_INVALID_CARD;
    
    balance = _subwayCards[cardNo]->balance;
    enCard = _subwayCards[cardNo]->enCard;
    return EN_RETURN_SUCC;
}



/*
@ ���۷�
@ ��Σ�cardNo,����; enCard, ������; deductPrice, �۷�Ʊ��
@ ����: balance, �۷Ѻ�����
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, EN_RETURN_BALANCE_NOT_ENOUGH, ʧ��;
*/
EN_RETURN_CODE DeductCard(unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int deductPrice, unsigned int &balance)
{
    if (cardNo >= _subwayCards.size() || NULL == _subwayCards[cardNo]) 
        return EN_RETURN_INVALID_CARD;
    if(_subwayCards[cardNo]->balance < deductPrice)
        return EN_RETURN_BALANCE_NOT_ENOUGH;

    _subwayCards[cardNo]->balance -= deductPrice;
    balance = _subwayCards[cardNo]->balance;

    return EN_RETURN_SUCC;
}



/*
@ ɾ������Ϣ
@ ��Σ�cardNo,����; 
@ ����: ��
@ ����ֵ: 0���ɹ�; -1, ʧ��;
*/
int DeleteCard(unsigned int cardNo)
{
    if (cardNo >= _subwayCards.size() || NULL == _subwayCards[cardNo])
        return -1;

    // �ͷ���ʷ��¼�ռ�
    pHisNode pHead = _subwayCards[cardNo]->history, pTmp;
    while (pHead != NULL)
    {
        pTmp = pHead->next;
        free(pHead);
        pHead = pTmp;
        if (pHead == _subwayCards[cardNo]->history)
            break;
    }

    free(_subwayCards[cardNo]);
    _subwayCards[cardNo] = NULL;
    return 0;
}



/*
@ ��ȡ�������ַ���
@ ��Σ�enCard,������; 
@ ����: ��
@ ����ֵ: �������ַ���;
*/
char cardNames[][30] = {
    "���̿�",
    "���꿨",
    "��ͨ��",
    "δ֪������"
};
char cardName[30] = "δ֪������";
char* GetCardTypeStr(EN_CARD_TYPE enCard)
{
	switch (enCard)
	{
	case EN_CARD_TYPE_SINGLE: return cardNames[enCard];
	case EN_CARD_TYPE_ELDER: return cardNames[enCard];
	case EN_CARD_TYPE_NOMAL: return cardNames[enCard];
	case EN_CARD_TYPE_BUTT: return cardNames[enCard];
	default: return cardName;
	}
    //return cardNames[enCard];
}
/*
@ ���ݿ������ַ���, ʶ������
@ ��Σ�cardType,      �������ַ���; 
@ ����: enCard,        ������
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INPUT_INVALID_CARDTYPE, ʧ��;
*/
EN_RETURN_CODE GetCardType(char cardType[], EN_CARD_TYPE &enCard)
{
    if (NULL == cardType) 
        return EN_RETURN_INPUT_INVALID_CARDTYPE;

    switch (cardType[0]) {
        case 'A':
        case 'a': enCard = EN_CARD_TYPE_SINGLE; break;
        case 'B':
        case 'b': enCard = EN_CARD_TYPE_ELDER; break;
        case 'C':
        case 'c': enCard = EN_CARD_TYPE_NOMAL; break;
        default: enCard = EN_CARD_TYPE_BUTT; return EN_RETURN_INPUT_INVALID_CARDTYPE;
    }

    return EN_RETURN_SUCC;
}





/*
@ ������ʷ��¼
@ ��Σ����š����ѽ���վʱ�䡢��վվ������վʱ�䡢��վվ����
@ ���Σ���
@ ����ֵ��EN_RETURN_SUCC �ɹ���EN_RETURN_INNER_ERR �ڴ�mallocʧ�ܡ�
*/
EN_RETURN_CODE InsertHistory(unsigned int cardNo, unsigned int deductPrice, ST_SUBWAY_TIME enterTime, ST_SUBWAY_TIME exitTime, const char* enterStation, const char* exitStation)
{
    pHisNode pHistory = (pHisNode) malloc(sizeof(hisNode));
    if (pHistory == NULL)
    {
        return EN_RETURN_INNER_ERR;
    }

    pHistory->enterTime = enterTime;
    pHistory->exitTime = exitTime;
    errno_t ret1 = strcpy_s(pHistory->enterStation, enterStation);
    errno_t ret2 = strcpy_s(pHistory->exitStation, exitStation);
	if (ret1 != ret2) ret1 = ret2;
    pHistory->cost = deductPrice;
    pHistory->next = NULL;

    pHisNode pHead = _subwayCards[cardNo]->history;
    if (pHead == NULL) {
        _subwayCards[cardNo]->history = pHistory;
    } else {
        int historyCount = 1;
        while (pHead->next != NULL)
        {
            historyCount ++;
            if (historyCount >= MAX_HISTORY)
            {
                pHead->next->next = pHistory;
                pHistory->next = _subwayCards[cardNo]->history->next;
                free(_subwayCards[cardNo]->history);
                _subwayCards[cardNo]->history = pHistory->next;
                break;
            }
            pHead = pHead->next;
        }
        if (historyCount < MAX_HISTORY)
        {
            pHead->next = pHistory;
        }
    }

    return EN_RETURN_SUCC;
}



/*
@ ��ѯ��ʷ��¼
@ ��Σ����ţ����洢�ַ���
@ ���Σ�����������ַ���
@ ����ֵ���ɹ�����Ч��
*/
EN_RETURN_CODE QueryHistory(unsigned int cardNo, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    if (cardNo >= _subwayCards.size() || NULL == _subwayCards[cardNo]) 
        return EN_RETURN_INVALID_CARD;
    
    ostringstream outs;
    pHisNode pHead = _subwayCards[cardNo]->history;
    int count;
    for (count = 1; count <= MAX_HISTORY; ++ count)
    {
        if (pHead == NULL) break;

        outs << "\r\n<���=" << count;
        outs << ",��վʱ��=" << pHead->enterTime.hour << ":" << pHead->enterTime.minutes;
        outs << ",��վվ��=" << pHead->enterStation;
        outs << ",��վʱ��=" << pHead->exitTime.hour << ":" << pHead->exitTime.minutes;
        outs << ",��վվ��=" << pHead->exitStation;
        outs << ",���ѽ��=" << pHead->cost;
        outs << ">";
        pHead = pHead->next;
    }

    string out = outs.str();
    if (_subwayCards[cardNo]->history == NULL)
        out = "\r\n<�����Ѽ�¼>";

    const char* pCopyTmp = out.c_str();
    unsigned int lenFirstLine = strlen(returnStr);
    unsigned int lenHistory = strlen(pCopyTmp);
    //cout << lenFirstLine << " , " << lenHistory << endl;

    unsigned int copyIndex = lenFirstLine;
    for (; copyIndex < lenFirstLine + lenHistory; ++ copyIndex)
    {
        returnStr[copyIndex] = pCopyTmp[copyIndex - lenFirstLine];
    }
    returnStr[lenFirstLine + lenHistory] = '\0';
    //strcpy_s(returnStr, strlen(pCopyTmp), pCopyTmp);
    //strcpy(returnStr, pCopyTmp);

    return EN_RETURN_SUCC;
}
