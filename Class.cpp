#include "Class.h"
#include "Manage.h"
#include <iostream>
#include <vector>
#include <iostream>
int Res::res_count = 0;
int Sight::sight_count = 0;
State::State()
{
    this->defence = 0;
    this->common_defence = &(this->defence);
}
void State::setName(std::string name)
{
    this->name = name;
}
void State::setPopulation(int pop)
{
    this->population = pop;
}
void State::setGDP(int gdp)
{
    this->GDP = gdp;
}
void State::setID(int id)
{
    this->ID = id;
}
void State::setDefence(int d)
{
    this->defence = d;
    //this->common_defence = &this->defence;
}
std::string State::getName()
{
    return this->name;
}
int State::getPopulation()
{
    return this->population;
}
int State::getGDP()
{
    return this->GDP;
}
int State::getID()
{
    return this->ID;
}
int State::getDefence()
{
    return this->defence;
}
bool State::Vote()
{
    return rand()%2;
}
Org::Org(){}
Org::Org(std::string name)
{
    this->name = name;
}
void Org::setName(std::string name)
{
    this->name = name;
}
std::string Org::getName()
{
    return this->name;
}
Org::Org(State* s)
{
    this->state[s->getID()] = s;
}
void Org::joinState(State* s)
{
    std::map<int,State*>::iterator it;
    it = this->state.find(s->getID());
    if (it == this->state.end())
    {
        this->state[s->getID()] = s;
    }
}
void Org::kickState(int i)
{
    std::map<int,State*>::iterator it;
    it = this->state.find(i);
    if (it != this->state.end())
    {
        this->state.erase(it);
    }
}
bool Org::checkState(int id)
{
    std::map<int,State*>::iterator it;
    it = this->state.find(id);
    if (it != this->state.end())
    {
        return true;
    }
    return false;
}
std::map<int,State*> Org::getAllStates()
{
    return this->state;
}
UN::UN():Org::Org(){}
UN::UN(std::string name):Org::Org(name) {}
void UN::addRes(Res* resol)
{
    this->res.push_back(resol);
}
std::vector<Res*> UN::getAllRes()
{
    return this->res;
}
Unesco::Unesco(std::string name):UN::UN(name){}
void Unesco::joinSight(Sight* s)
{
    this->sights.push_back(s);
}
Alliance::Alliance():Org::Org(){this->defence = 0;}
Alliance::Alliance(std::string name):Org(name)
{
    this->defence = 0;
}
void Alliance::joinState(State* s)
{
    std::map<int,State*>::iterator it;
    it = this->state.find(s->getID());
    if (it == this->state.end())
    {
        this->state[s->getID()] = s;
        this->defence += *(s->common_defence);
        s->common_defence = &this->defence;
    }
}
int Alliance::getDefence()
{
    return this->defence;
}
void Alliance::kickState(int id)
{
    std::map<int,State*>::iterator it;
    it = this->state.find(id);
    if (it != this->state.end())
    {
        this->defence = this->defence - (this->state[id])->defence;
        (this->state[id])->common_defence = &(this->state[id]->defence);
        this->state.erase(it);
    }
}
Alliance::~Alliance()
{
    std::map<int,State*>::iterator it;
    for(it = this->state.begin(); it != this->state.end(); it++)
    {
        int id = it->second->getID();
        this->kickState(id);
    }
}
TradeOrg::TradeOrg():Org::Org(){}
TradeOrg::TradeOrg(std::string name,double growth):Org::Org(name){this->growth = growth;}
void TradeOrg::joinState(State* s)
{
    std::map<int,State*>::iterator it;
    it = this->state.find(s->getID());
    if (it == this->state.end())
    {
        this->state[s->getID()] = s;
        double gdp = s->getGDP() * this->growth;
        s->setGDP((int)gdp);
    }
}
void TradeOrg::kickState(int id)
{
    std::map<int,State*>::iterator it;
    it = this->state.find(id);
    if (it != this->state.end())
    {
        int gdp = it->second->getGDP();
        it->second->setGDP((int)(gdp/this->growth));
        this->state.erase(it);
    }
}
SC::SC(std::string name):UN::UN(name){}

