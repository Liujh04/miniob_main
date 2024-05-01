#pragma once
#include <stdint.h>
#include<stdio.h>
#include<string>
#include<sstream>
#include"common/rc.h"
#include"sql/parser/parse_defs.h"

inline bool is_leap_year(int year)
{
    return(year%4==0&&year %100!=0)|| year % 400 ==0;
}

inline RC string_to_date(const char *str, int32_t &date)
{
    int year = 0;
    int month =0;
    int day = 0;
    int ret=sscanf(str,"%d-%d-%d",&year,&month,&day);
    if(ret !=3){
        return RC::INVALID_ARGUMENT;
    }
    // validate
    if(year<1900||year >9999 ||(month<=0||month>12)||(day<=0 || day>31)){
        return RC::INVALID_ARGUMENT;
    }

    int max_day_in_month[]={31,29,31,30,31,30,31,31,30,31,30,31};
    const int max_day =max_day_in_month[month-1];
    if(day>max_day){
        return RC::INVALID_ARGUMENT;
    }
    if(month==2 && !is_leap_year(year)&& day>28){
        return RC::INVALID_ARGUMENT;
    }
    date=year*10000+month*100+ day;
    return RC::SUCCESS;
}


inline std::string date_to_string(int32_t date)
{
    std::stringstream ss;
    ss << date;
    return ss.str().substr(0,4)+"-"+ss.str().substr(4,2)+"-"+ss.str().substr(6,2);
}