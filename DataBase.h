#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include "Class.h"
#include <map>
class DataBase
{
    friend class Manager;
    friend class Interface;
private:
    static std::map<int,State> states_DB;
    static std::map<int,Res> res_DB;
    static std::map<int,Sight> sight_DB;
    static std::vector<Alliance> alliance_DB;
    static std::vector<TradeOrg> trade_DB;
    static UN un;
    static Unesco unesco;
    static SC sc;
    static int states_id_count;
    static int res_id_count;
    static int sight_id_count;
};
#endif // DATABASE_H_INCLUDED
