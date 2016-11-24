#include "Manage.h"
#include "DataBase.h"
#include "Class.h"
#include "Interface.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
void Manager::createState(State& s)
{
    int id = DataBase::states_id_count;
    DataBase::states_DB[id] = s;
    DataBase::states_DB[id].setID(id);
    DataBase::states_id_count++;
}
void Manager::destroyState(State* s)
{
    int id = s->getID();
    std::vector<Org*> orgs = Manager::idSearch(id);
    for(std::vector<Org*>::iterator it = orgs.begin(); it < orgs.end(); it++)
    {
        (*it)->kickState(id);
    }
    std::map<int,State>::iterator it;
    it = DataBase::states_DB.find(id);
    if (it != DataBase::states_DB.end())
    {
        DataBase::states_DB.erase(it);
    }
}
void Manager::createRes(UN* org,Res& res) throw (bool)
{
    DataBase::res_DB[res.ID] = res;
    if(Manager::statesVote(org->getAllStates()))
    {
        org->addRes(&res);
        res.adoption = true;
    }
    else
    {
        res.adoption = false;
        throw false;
    }
}
void Manager::destroyOrg(Org* org)
{
    std::map<int,State*>::iterator it;
    std::map<int,State*> temp = org->getAllStates();
    for(it = temp.begin(); it != temp.end(); it++)
    {
        org->kickState(it->first);
    }
}
void Manager::createSight(Sight& sight) throw (bool)
{
    DataBase::sight_DB[sight.ID] = sight;
    if(Manager::statesVote(DataBase::unesco.getAllStates()))
    {
        DataBase::unesco.joinSight(&sight);
        sight.unesco_protection = true;
    }
    else
    {
        sight.unesco_protection = false;
        throw false;
    }
}
void Manager::createAlliance(std::string name)
{
    DataBase::alliance_DB.push_back(Alliance(name));
}
void Manager::createTradeOrg(std::string name,double growth)
{
    TradeOrg temp(name,growth);
    DataBase::trade_DB.push_back(temp);
}
void Manager::addState(Org* org, State* s)
{
    org->joinState(s);
}
bool Manager::statesVote(std::map<int,State*> states)
{
    std::map<int,State*>::iterator it;
    unsigned int countAgree = 0;
    for(it = states.begin(); it != states.end(); it++)
    {
        if(it->second->Vote() == 1)
        {
            countAgree++;
        }
    }
    std::cout<<"Voted for:"<<countAgree<<" of "<<states.size()<<"\n";
    return (countAgree > states.size()/2)?true:false;
}
std::vector<Org*> Manager::nameSearch(std::string name) throw (bool)
{
    std::vector<Org*> result;
    std::vector<Org*>::iterator res_it = result.end();
    std::map<int,State>::iterator it;
    for(it = DataBase::states_DB.begin(); it != DataBase::states_DB.end(); it++)
    {
        std::string str = it->second.getName();
        if(str.compare(name) == 0)
        {
            Interface::printState(&it->second);
            std::vector<Org*> result2 = idSearch(it->first);
            if(result2.empty() != true)
            {
                result.insert(res_it,result2.begin(), result2.end());
            }
        }
    }
    if(result.empty() == false)
    {
        return result;
    }
    else
    {
        throw false;
    }
}
std::vector<Org*> Manager::idSearch(int id)
{
    std::vector<Org*> result;
    for(std::vector<Alliance>::iterator it = DataBase::alliance_DB.begin(); it < DataBase::alliance_DB.end(); it++)
    {
        if(it->checkState(id))
        {
            result.push_back(&(*it));
        }
    }
    for(std::vector<TradeOrg>::iterator it = DataBase::trade_DB.begin(); it < DataBase::trade_DB.end(); it++)
    {
        if(it->checkState(id))
        {
            result.push_back(&(*it));
        }
    }
    if(DataBase::un.checkState(id))
    {
        result.push_back(&DataBase::un);
    }
    return result;
}
void Manager::write()
{
    std::ofstream ofst("Curs.txt",std::ios::out|std::ios::trunc);
    ofst<<"States: "<<DataBase::states_DB.size()<<"\n";
    for(std::map<int,State>::iterator it = DataBase::states_DB.begin(); it != DataBase::states_DB.end(); it++)
    {
        ofst<<it->second.getName()<<"# ";
        ofst<<it->second.getPopulation()<<" ";
        ofst<<it->second.getDefence()<<" ";
        ofst<<it->second.getGDP()<<"\n";
    }
    ofst<<"Resolutions: "<<DataBase::res_DB.size()<<"\n";
    for(std::map<int,Res>::iterator it = DataBase::res_DB.begin(); it != DataBase::res_DB.end(); it++)
    {
        ofst<<it->second.name<<"# ";
        ofst<<it->second.adoption<<"\n";
    }
    ofst<<"Sights: "<<DataBase::sight_DB.size()<<"\n";
    for(std::map<int,Sight>::iterator it = DataBase::sight_DB.begin(); it != DataBase::sight_DB.end(); it++)
    {
        ofst<<it->second.name<<"# ";
        ofst<<it->second.state_id<<" ";
        ofst<<it->second.unesco_protection<<"\n";
    }
    ofst<<"Alliances: "<<DataBase::alliance_DB.size()<<"\n";
    for(std::vector<Alliance>::iterator it = DataBase::alliance_DB.begin(); it < DataBase::alliance_DB.end(); it++)
    {
        std::map<int,State*> temp = (*it).getAllStates();
        ofst<<(*it).getName()<<"# "<<temp.size()<<" ";
        for(std::map<int,State*>::iterator it2 = temp.begin(); it2 != temp.end(); it2++)
        {
            ofst<<it2->first<<" ";
        }
        ofst<<"\n";
    }
    ofst<<"Trading organisations: "<<DataBase::trade_DB.size()<<"\n";
    for(std::vector<TradeOrg>::iterator it = DataBase::trade_DB.begin(); it < DataBase::trade_DB.end(); it++)
    {
        std::map<int,State*> temp = (*it).getAllStates();
        ofst<<(*it).getName()<<"# "<<temp.size()<<" ";
        for(std::map<int,State*>::iterator it2 = temp.begin(); it2 != temp.end(); it2++)
        {
            ofst<<it2->first<<" ";
        }
        ofst<<"#\n";
    }
    std::map<int,State*> temp1 = DataBase::un.getAllStates();
    ofst<<"UN: "<<temp1.size()<<" ";
    for(std::map<int,State*>::iterator it = temp1.begin(); it != temp1.end(); it++)
    {
        ofst<<it->first<<" ";
    }
    ofst<<"\n";
    std::map<int,State*> temp2 = DataBase::unesco.getAllStates();
    ofst<<"UNESCO: "<<temp2.size()<<" ";
    for(std::map<int,State*>::iterator it = temp2.begin(); it != temp2.end(); it++)
    {
        ofst<<it->first<<" ";
    }
    ofst<<"\n";
    std::map<int,State*> temp3 = DataBase::sc.getAllStates();
    ofst<<"Security Council: "<<temp3.size()<<" ";
    for(std::map<int,State*>::iterator it = temp3.begin(); it != temp3.end(); it++)
    {
        ofst<<it->first<<" ";
    }
    ofst<<"\n";
    ofst.close();
}
void Manager::read(std::string file) throw (bool)
{
    std::vector<State> state;
    int N;
    int popul;
    int gdp;
    int defence;
    std::string str;
    std::ifstream is(file.c_str(),std::ios::in);
    if(is.fail())
    {
        throw false;
    }
    is>>str;
    if(str.compare("States:") == 0)
    {
        is>>N;
        for(int i = 0; i < N; i++)
        {
            State s;
            state.push_back(s);
            getline(is,str,'#');
            if(str.size() == 0)
            {
                getline(is,str,'#');
            }

            state[i].setName(str.substr(1,str.size()));
            is>>popul>>gdp>>defence;
            state[i].setPopulation(popul);
            state[i].setGDP(gdp);
            state[i].setDefence(defence);
        }
    }
    for(int i = 0; i < N; i++)
    {
        Manager::createState(state[i]);
    }
    is>>str;
    if(str.compare("Resolutions:") == 0)
    {
        is>>N;
        for(int i = 0; i < N; i++)
        {
            Res res;
            getline(is,str,'#');
            if(str.size() == 0)
            {
                getline(is,str,'#');
            }
            res.name = str.substr(1,str.size());
            is>>res.adoption;
            res.ID = Res::res_count;
            DataBase::res_DB[res.ID] = res;
            if(res.adoption == true)
            {
                DataBase::un.addRes(&res);
            }
        }
    }
    is>>str;
    if(str.compare("Sights:") == 0)
    {
        is>>N;
        for(int i = 0; i < N; i++)
        {
            Sight s;
            getline(is,str,'#');
            if(str.size() == 0)
            {
                getline(is,str,'#');
            }
            s.name = str.substr(1,str.size());
            is>>s.state_id;
            is>>s.unesco_protection;
            s.ID = Sight::sight_count;
            Sight::sight_count++;
            DataBase::sight_DB[s.ID] = s;
            if(s.unesco_protection)
            {
                DataBase::unesco.joinSight(&s);
            }
        }
    }
    /*
    is>>str;
    if(str.compare("Alliances:") == 0)
    {
        is>>N;
        for(int i = 0; i < N; i++)
        {
            Alliance a;
            int M;
            getline(is,str,'#');
            if(str.size() == 0)
            {
                getline(is,str,'#');
            }
            a.setName(str.substr(1,str.size()));
            is>>M;
            for(int i = 0; i < M; i++)
            {
                a.joinState(&DataBase::states_DB[i]);
            }
        }
    }
    /*
    is>>str;
    if(str.compare("Trading organisations:") == 0)
    {
        is>>N;
        for(int i = 0; i < N; i++)
        {
            TradeOrg a;
            getline(is,str,'#');
            if(str.size() == 0)
            {
                getline(is,str,'#');
            }
            a.setName(str.substr(1,str.size()));
            std::vector<int> id;
            do
            {
                is>>str;
                int id = stoi(str);
                std::map<int,State>::iterator it;
                it = DataBase::states_DB.find(id);
                if((str.compare("#") != 0)&&(it != DataBase::states_DB.end()))
                {
                    a.joinState(&DataBase::states_DB[id]);
                }
                else
                {
                    break;
                }
            }while(1);
        }
    }
    is>>str;
    if(str.compare("UN:"))
    {
        do
        {
            is>>str;
            int id = stoi(str);
            std::map<int,State>::iterator it;
            it = DataBase::states_DB.find(id);
            if((str.compare("#") != 0)&&(it != DataBase::states_DB.end()))
            {
                DataBase::un.joinState(&DataBase::states_DB[id]);
            }
            else
            {
                break;
            }
        }while(1);
    }
    is>>str;
    if(str.compare("UNESCO:") == 0)
    {
        do
        {
            is>>str;
            int id = stoi(str);
            std::map<int,State>::iterator it;
            it = DataBase::states_DB.find(id);
            if((str.compare("#") != 0)&&(it != DataBase::states_DB.end()))
            {
                DataBase::unesco.joinState(&DataBase::states_DB[id]);
            }
            else
            {
                break;
            }
        }while(1);
    }
    is>>str;
    if(str.compare("Security Council:") == 0)
    {
        do
        {
            is>>str;
            int id = stoi(str);
            std::map<int,State>::iterator it;
            it = DataBase::states_DB.find(id);
            if((str.compare("#") != 0)&&(it != DataBase::states_DB.end()))
            {
                DataBase::sc.joinState(&DataBase::states_DB[id]);
            }
            else
            {
                break;
            }
        }while(1);
    }
    */
}
