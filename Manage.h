#ifndef MANAGE_H
#define MANAGE_H
#include "Class.h"
class Manager
{
public:
    static void createState(State& s);
    static void createRes(UN* org,Res& res) throw (bool);
    static void createSight(Sight& sight) throw (bool);
    static void createAlliance(std::string name);
    static void createTradeOrg(std::string name,double growth);
    static void destroyState(State* s);
    static void destroyOrg(Org* org);
    static void addState(Org* org, State* s);
    static bool statesVote(std::map<int,State*> states);
    static vector<Org*> nameSearch(std::string name) throw (bool);
    static vector<Org*> idSearch(int id);
    static void write();
    static void read(std::string file) throw (bool);
    static void readOrg(char* str, Org* org);
};
#endif // MANAGE_H
