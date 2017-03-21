#include "stdafx.h"
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "include/basePrice.h"
#include "include/deductPrice.h"
#include "subwayPrice.h"
#include <iostream>
using namespace std;

/*
@ ��ȡ�۷�Ʊ�ۣ��������;
@   1. �����Ϊ0����ʱ���շ�;
@   2. �������Ϊ0;
@ ����ֵ: 
*/
bool isDiscount(ST_SUBWAY_TIME &enterTime)
{
    //�жϽ�վʱ���Ƿ��� [10:00, 15:00]
    if (enterTime.hour >= 10 && enterTime.hour <= 14) 
        return true;

    return false;
    
}

int timeDiffMinutes(ST_SUBWAY_TIME &enterTime, ST_SUBWAY_TIME &exitTime)
{
    // �������վ֮���ʱ����minuteΪ��λ��
    int minSum = 0;
    minSum += 60 * (exitTime.hour - enterTime.hour);
    minSum += exitTime.minutes - enterTime.minutes;
    return minSum;
}

/*
@ ��ȡ�۷�Ʊ�ۣ��������;
@   1. �����Ϊ0����ʱ���շ�;
@   2. �������Ϊ0;
@ ����ֵ: 
*/
EN_RETURN_CODE GetDeductPrice(EN_CARD_TYPE enCardType, unsigned int balance, unsigned int meters, ST_SUBWAY_TIME &enterTime, ST_SUBWAY_TIME &exitTime, unsigned int &deductPrice)
{
    if (meters > 0) 
    {
        unsigned int basicPrice = GetBasePrice(meters);
        switch (enCardType) {
        case EN_CARD_TYPE_SINGLE: deductPrice = (basicPrice > balance)? basicPrice: balance; break;
        case EN_CARD_TYPE_ELDER: if(!isDiscount(enterTime)) deductPrice = basicPrice; else deductPrice = (int)(basicPrice * 0.8) ;break;
        case EN_CARD_TYPE_NOMAL: deductPrice = basicPrice; break;
        default: return EN_RETURN_INPUT_INVALID_CARDTYPE;
        }
    } else {
        int diffMinutes = timeDiffMinutes(enterTime, exitTime);
        // diffMInuts = DIFF_TIME((&exitTime), (&enterTime), diffMinutes);
        if (diffMinutes < 0) return EN_RETURN_INVALID_TIME;
        if (diffMinutes <= 30) 
        {
            switch (enCardType) {
            case EN_CARD_TYPE_SINGLE: deductPrice = balance; break;
            case EN_CARD_TYPE_ELDER: 
            case EN_CARD_TYPE_NOMAL: deductPrice = 0; break;
            case EN_CARD_TYPE_BUTT:
            default: return EN_RETURN_INPUT_INVALID_CARDTYPE;
            }
        } else {
            switch (enCardType) {
            case EN_CARD_TYPE_SINGLE: deductPrice = (balance > 3)? balance: 3; break;
            case EN_CARD_TYPE_ELDER: 
            case EN_CARD_TYPE_NOMAL: deductPrice = 3; break;
            case EN_CARD_TYPE_BUTT:
            default: return EN_RETURN_INPUT_INVALID_CARDTYPE;
            }
        }
    }
    return EN_RETURN_SUCC;
}

