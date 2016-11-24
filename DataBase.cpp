#include "DataBase.h"
#include <fstream>
std::map<int,State> DataBase::states_DB;
std::map<int,Res> DataBase::res_DB;
std::map<int,Sight> DataBase::sight_DB;
std::vector<Alliance> DataBase::alliance_DB;
std::vector<TradeOrg> DataBase::trade_DB;
const std::string un_str = "United Nations";
const std::string cs_str = "Security Council";
const std::string us_str = "UNESCO";
UN DataBase::un(un_str);
Unesco DataBase::unesco(us_str);
SC DataBase::sc(cs_str);
int DataBase::states_id_count = 1;
int DataBase::res_id_count = 1;
int DataBase::sight_id_count = 1;
