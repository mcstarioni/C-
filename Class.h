#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <map>
#include <stdlib.h>
#include <vector>
using std::vector;
using std::map;
struct Res
{
    std::string name;
    std::map<int,bool> votes;
    bool adoption;
    int ID;
    static int res_count;
};
class State
{
protected:
    std::string name;
    int population;
    int GDP;
    int ID;
    int defence;
public:
    int *common_defence;
    State();
    //~State();
    void setName(std::string name);
    void setPopulation(int pop);
    void setGDP(int gdp);
    void setID(int id);
    void setDefence(int d);
    std::string getName();
    int getPopulation();
    int getGDP();
    int getID();
    int getDefence();
    bool Vote();
    friend class Alliance;
};
struct Sight
{
    std::string name;
    int ID;
    int state_id;
    static int sight_count;
    bool unesco_protection;
};
class Org
{
protected:
    std::string name;
    map<int,State*> state;
public:
    Org();
    Org(std::string name);
    Org(State* s);
    Org(map<int,State*> s);
    void setName(std::string name);
    std::string getName();
    bool checkState(int ID);
    virtual void joinState(State* s);
    virtual void kickState(int N);
    map<int,State*> getAllStates();
};
class UN:public Org
{
private:
    std::vector<Res*> res;
public:
    UN();
    UN(std::string name);
    virtual void addRes(Res* resol);
    std::vector<Res*> getAllRes();
    friend class SC;
};
class Unesco:public UN
{
private:
    std::vector<Sight*> sights;
public:
    Unesco(std::string name);
    void joinSight(Sight* s);
};
class SC:public UN
{
private:
    State* temp;
public:
    void Veto(Res res);
    SC(std::string name);
};
class Alliance:public Org
{
protected:
    int defence;
public:
    int* ptr_def;
    Alliance();
    ~Alliance();
    Alliance(std::string name);
    void joinState(State* s);
    int getDefence();
    void kickState(int id);
};
class TradeOrg:public Org
{
private:
    double growth;
public:
    TradeOrg();
    TradeOrg(std::string name,double growth);
    void joinState(State* s);
    void kickState(int id);
};
#endif
