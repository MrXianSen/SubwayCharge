#ifndef __SUBWAY_CARD_H__
#define __SUBWAY_CARD_H__
#include "subwayError.h"
#include "subwayGlobalDef.h"
#define MAX_STATION_NAME_LENGTH 32


//�������ϵͳ��100�ŵ�����
#define MAX_CARD_NUM 100

//������ֵ
#define MAX_BALANCE 999

//������С���ֵ
#define MIN_BALANCE 20

// ��ʷ��¼�������
#define MAX_HISTORY 20

//����������
typedef enum
{
    EN_CARD_TYPE_SINGLE = 0,
    EN_CARD_TYPE_ELDER,
    EN_CARD_TYPE_NOMAL,
    EN_CARD_TYPE_BUTT
}EN_CARD_TYPE;

// ��ʷ��¼
typedef struct hisNode
{
    ST_SUBWAY_TIME enterTime;
    ST_SUBWAY_TIME exitTime;
    char enterStation[MAX_STATION_NAME_LENGTH];
    char exitStation[MAX_STATION_NAME_LENGTH];
    unsigned int cost;
    hisNode* next;
}* pHisNode;

//������
typedef struct  
{
	unsigned int cardNo;
	unsigned int balance;
	EN_CARD_TYPE enCard;

    pHisNode history;
}subwayCard;




/*
@ ��ʼ�����п���Ϣ
@ ����ֵ: ��
*/
void InitCardManagerInfo();

/*
@ ���������俨�źͿ���Ϣ
@ ��Σ�enCard,������; charge: ��ֵ
@ ����: cardNo, ����Ŀ���
@ ����ֵ: EN_RETURN_SUCC������ɹ�; EN_RETURN_CARD_OVERLOW, ����ʧ��;
*/
EN_RETURN_CODE AssignCard(unsigned int &cardNo, EN_CARD_TYPE enCard, unsigned int charge);

/*
@ ��ֵ
@ ��Σ�cardNo,����; recharge: ��ֵ
@ ����: ��
@ ����ֵ: EN_RETURN_SUCC���ɹ�; ����, ʧ��;
*/
EN_RETURN_CODE RechargeCard(unsigned int cardNo, unsigned int recharge);

/*
@ ��ȡ����Ϣ
@ ��Σ�cardNo,����; 
@ ����: balance: ���
        enCard:  ������
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, ʧ��;
*/
EN_RETURN_CODE GetCardInfo(unsigned int cardNo, unsigned int &balance, EN_CARD_TYPE &enCard);

/*
@ ���۷�
@ ��Σ�cardNo,����; enCard, ������; deductPrice, �۷�Ʊ��
@ ����: balance, �۷Ѻ�����;
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, EN_RETURN_BALANCE_NOT_ENOUGH, ʧ��;
*/
EN_RETURN_CODE DeductCard(unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int deductPrice, unsigned int &balance);

/*
@ ���ݿ������ַ���, ʶ������
@ ��Σ�cardType,      �������ַ���; 
@ ����: enCard,        ������
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INPUT_INVALID_CARDTYPE, ʧ��;
*/
EN_RETURN_CODE GetCardType(char cardType[], EN_CARD_TYPE &enCard);

/*
@ ɾ������Ϣ
@ ��Σ�cardNo,����; 
@ ����: ��
@ ����ֵ: 0���ɹ�; -1, ʧ��;
*/
int DeleteCard(unsigned int cardNo);

/*
@ ��ȡ�������ַ���
@ ��Σ�enCard,������; 
@ ����: ��
@ ����ֵ: �������ַ���������"��ͨ��";
*/
char* GetCardTypeStr(EN_CARD_TYPE enCard);


/*
@ ������ʷ��¼
@ ��Σ����š����ѽ���վʱ�䡢��վվ������վʱ�䡢��վվ����
@ ���Σ���
@ ����ֵ��EN_RETURN_SUCC �ɹ���EN_RETURN_INNER_ERR �ڴ�mallocʧ�ܡ�
*/
EN_RETURN_CODE InsertHistory(unsigned int cardNo, unsigned int deductPrice, ST_SUBWAY_TIME enterTime, ST_SUBWAY_TIME exitTime, const char* enterStation, const char* exitStation);


/*
@ ��ѯ��ʷ��¼
@ ��Σ����ţ����洢�ַ���
@ ���Σ�����������ַ���
@ ����ֵ���ɹ�����Ч��
*/
EN_RETURN_CODE QueryHistory(unsigned int cardNo, char returnStr[MAX_SEND_BUFFER_LENGTH]);

#endif
