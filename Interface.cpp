#include "Interface.h"
#include "Manage.h"
#include <conio.h>
#include "DataBase.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
const std::string file("Curs.txt");
void Interface::mainMenu()
{
    int Answer;
    do
    {
        system("cls");
        cout<<"Please, choose an option: \n"<<
              "1. Add a new object.\n"<<
              "2. Delete an ob]ect.\n"<<
              "3. Make an inclusion of states.\n"<<
              "4. View data base content.\n"<<
              "5. Search with parameters.\n"<<
              "6. Load the data from file.\n"
              "Press - Enter to save data.\n"<<
              "      - Escape to exit the program.\n";
        Answer = getch();
        switch(Answer)
        {
        case(49):
            {
                Interface::creationMenu();
                break;
            }
        case(50):
            {
                Interface::destructionMenu();
                break;
            }
        case(51):
            {
                Interface::inclusionMenu();
                break;
            }
        case(52):
            {
                Interface::viewDataMenu();
                break;
            }
        case(53):
            {
                Interface::searchMenu();
                break;
            }
        case(54):
            {
                Interface::readMenu();
                break;
            }
        case(13):
            {
                Manager::write();
                break;
            }
        case(27):
            {
                break;
            }
        default:
            {
                break;
            }
        }
    }while(Answer != 27);
}
void Interface::creationMenu()
{
    int Answer;
    do
    {
        system("cls");
        cout<<"What object do you want to create? \n"<<
              "1. State.\n"<<
              "2. Resolution.(Auto vote in UN)\n"<<
              "3. Resolution.(Auto vote in Security Council)\n"<<
              "4. Sight.(Auto vote in UNESCO)\n"<<
              "5. Aliance.\n"<<
              "6. Trade organisation.\n"<<
              "Press Escape to return.\n";
        Answer = getch();
        switch(Answer)
        {
        case(49):
            {
                State s;
                Interface::setState(&s);
                Manager::createState(s);
                break;
            }
        case(50):
            {
                try
                {
                    Res res;
                    Interface::setRes(&res);
                    Manager::createRes(&DataBase::un,res);
                    cout<<"Resolution was accepted! \n";
                }
                catch(bool)
                {
                    cout<<"Resolution was not accepted. \n";
                }
                getch();
                break;
            }
        case(51):
            {
                try
                {
                    Res res;
                    Interface::setRes(&res);
                    Manager::createRes(&DataBase::sc,res);
                    cout<<"Resolution was accepted! \n";
                }
                catch(bool)
                {
                    cout<<"Resolution was not accepted. \n";
                }
                getch();
                break;
            }
        case(52):
            {
                try
                {
                    Sight sight;
                    Interface::setSight(&sight);
                    Manager::createSight(sight);
                    cout<<"Sight was accepted! \n";
                }
                catch(bool)
                {
                    cout<<"Sight was not accepted. \n";
                }
                getch();
                break;
            }
        case(53):
            {
                std::string name;
                cout<<"Enter the name of your Alliance: ";
                cin>>name;
                Manager::createAlliance(name);
                break;
            }
        case(54):
            {
                std::string name;
                cout<<"Enter the name of your trade organisation: ";
                cin>>name;
                double growth;
                cout<<"Enter the annual gdp growth in percents: ";
                cin>>growth;
                Manager::createTradeOrg(name,growth);
                break;
            }
        default:
            {
                break;
            }
        }
    }while(Answer != 27);
}
void Interface::destructionMenu()
{
    int Answer;
    do
    {
        system("cls");
        cout<<"What object do you want to destroy? \n"
            <<"1. State.\n"
            <<"2. Alliance.\n"
            <<"3. Trading organisation.\n";
        Answer = getch();
        switch(Answer)
        {
        case(49):
            {
                Manager::destroyState(Interface::chooseState());
                break;
            }
        case(50):
            {
                Manager::destroyOrg(Interface::chooseAlliance());
                break;
            }
        case(51):
            {
                Manager::destroyOrg(Interface::chooseAlliance());
                break;
            }
        default:
            {
                break;
            }
        }

    }while(Answer != 27);
}
void Interface::inclusionMenu()
{
    int Answer;
    do
    {
        system("cls");
        cout<<"What organisation do you want to add a State? \n"<<
              "1. Aliance.\n"<<
              "2. Trade organisations\n"<<
              "3. UN.\n"<<
              "4. UNESCO.\n"<<
              "5. Security council.\n"<<
              "Press Escape to return.\n";
        Answer = getch();
        switch(Answer)
        {
        case(49):
            {
                try
                {
                    State* state = Interface::chooseState();
                    Org* temp = Interface::chooseAlliance();
                    Manager::addState(temp,state);
                    break;
                }
                catch(bool)
                {
                    cout<<"Any key to continue...\n";
                }
                getch();
                break;
            }
        case(50):
            {
                try
                {
                    State* state = Interface::chooseState();
                    Org* temp = Interface::chooseTradeOrg();
                    Manager::addState(temp,state);
                    break;
                }
                catch(bool)
                {
                    cout<<"Any key to continue...\n";
                }
                getch();
                break;
            }
        case(51):
            {
                try
                {
                    State* state = Interface::chooseState();
                    Manager::addState(&DataBase::un,state);
                }
                catch(bool)
                {
                    cout<<"Any key to continue...\n";
                }
                break;
            }
        case(52):
            {
                try
                {
                    State* state = Interface::chooseState();
                    if(DataBase::un.checkState(state->getID()) == true)
                    {
                        Manager::addState(&DataBase::unesco,state);
                    }
                    else
                    {
                        cout<<"This state is not a member of UN";
                    }
                }
                catch(bool)
                {
                    cout<<"Any key to continue...\n";
                }
                getch();
                break;
            }
        case(53):
            {
                try
                {
                    State* state = Interface::chooseState();
                    if(DataBase::un.checkState(state->getID()) == true)
                    {
                        Manager::addState(&DataBase::sc,state);
                    }
                    else
                    {
                        cout<<"This state is not a member of UN";
                    }
                }
                catch(bool)
                {
                    cout<<"Any key to continue...\n";
                }
                getch();
                break;
            }
        default:
            {
                break;
            }
        }
    }while(Answer != 27);
}
void Interface::viewDataMenu()
{
    int Answer;
    do
    {
        system("cls");
        cout<<"What data do you want to be shown? \n"<<
              "1. All States.\n"<<
              "2. All Resolutions.\n"<<
              "3. All Sights.\n"<<
              "4. Alliances.\n"<<
              "5. Trade Orgs.\n"<<
              "6. UN.\n"<<
              "7. SC.\n"<<
              "8. UNESCO.\n"<<
              "Press Escape to return.\n";
        Answer = getch();
        switch(Answer)
        {
        case(49):
            {
                system("cls");
                std::map<int,State>::iterator it;
                for(it = DataBase::states_DB.begin(); it != DataBase::states_DB.end(); it++)
                {
                    Interface::printState(&it->second);
                }
                getch();
                break;
            }
        case(50):
            {

                system("cls");
                std::map<int,Res>::iterator it;
                for(it = DataBase::res_DB.begin(); it != DataBase::res_DB.end(); it++)
                {
                    Interface::printRes(&it->second);
                }
                getch();

                break;
            }
        case(51):
            {
                system("cls");
                std::map<int,Sight>::iterator it;
                for(it = DataBase::sight_DB.begin(); it != DataBase::sight_DB.end(); it++)
                {
                    Interface::printSight(&it->second);
                }
                getch();
                break;
            }
        case(52):
            {
                system("cls");
                try
                {
                    Alliance* temp = Interface::chooseAlliance();
                    Interface::printOrg(temp);
                    cout<<temp->getDefence()<<"\n";
                }
                catch(bool)
                {
                    cout<<"Any key to continue...\n";
                }
                getch();
                break;
            }
        case(53):
            {
                system("cls");
                try
                {
                    TradeOrg* temp = Interface::chooseTradeOrg();
                    Interface::printOrg(temp);
                }
                catch(bool)
                {
                    cout<<"Any key to continue...\n";
                }
                getch();
                break;
            }
        case(54):
            {
                system("cls");
                Org* temp = &DataBase::un;
                Interface::printOrg(temp);
                getch();
                break;
            }
        case(55):
            {
                system("cls");
                Org* temp = &DataBase::sc;
                Interface::printOrg(temp);
                getch();
                break;
            }
        case(56):
            {
                system("cls");
                Org* temp = &DataBase::unesco;
                Interface::printOrg(temp);
                getch();
                break;
            }
        default:
            {
                break;
            }
        }
    }while(Answer != 27);
}
void Interface::searchMenu()
{
    system("cls");
    int Answer;
    do
    {
        cout<<"What characteristic of the state do you want to search? \n"<<
              "1. Name.\n"<<
              "2. ID.\n";
        Answer = getch();
        switch(Answer)
        {
        case(49):
            {
                cout<<"Enter the name to search: ";
                std::string str;
                std::getline(cin, str);
                if (str.size() == 0)
                {
                    std::getline(cin, str);
                }
                try
                {
                    std::vector<Org*> result = Manager::nameSearch(str);
                    std::vector<Org*>::iterator it;
                    cout<<"Such state exists.\n"<<
                          "Were found following organisations: \n";
                    for(it = result.begin(); it < result.end(); it++)
                    {
                        cout<<(*it)->getName()<<"\n";
                    }
                }
                catch(bool)
                {
                    cout<<"Nothing was found\n";
                }
                break;
            }
        case(50):
            {
                break;
            }
        default:
            {
                break;
            }
        }
    }while(Answer != 27);
}
void Interface::readMenu()
{
    int Answer;
    do
    {
        system("cls");
        cout<<"1. Read from standard Curs.txt file.\n"
            <<"2. Read from custom file.\n";
        Answer = getch();
        switch(Answer)
        {
        case(49):
            {
                try
                {
                    Manager::read(file);
                    cout<<"File was successfully read.\n";
                }
                catch(bool)
                {
                    cout<<"File was not found.";
                }
                getch();
                break;
            }
        case(50):
            {
                cout<<"Enter the name of the file(including .txt): ";
                std::string str;
                getline(cin,str,' ');
                if(str.size() == 0)
                {
                    getline(cin,str,' ');
                }
                try
                {
                    Manager::read(str);
                    cout<<"File was successfully read.\n";
                }
                catch(bool)
                {
                    cout<<"File was not found.";
                }
                getch();
                break;
            }
        default:
            {
                break;
            }
        }
    }while(Answer != 27);
}
void Interface::printState(State* s)
{
    std::cout<<"Name: "<<s->getName()<<"\n";
    std::cout<<"Population: "<<s->getPopulation()<<" million.\n";
    std::cout<<"GDP: "<<s->getGDP()<<" million dollars.\n";
    std::cout<<"Defence personal: "<<s->getDefence()<<"\n";
    std::cout<<"Defence common: "<<*s->common_defence<<"\n";
    std::cout<<"ID: "<<s->getID()<<"\n";
}
void Interface::printRes(Res* res)
{
    cout<<"Name: "<<res->name<<"\n";
    cout<<"ID: "<<res->ID<<"\n";
    if(res->adoption)
    {
        cout<<"Resolution was accepted.\n";
    }
    else
    {
        cout<<"Resolution was not accepted.\n";
    }
}
void Interface::printSight(Sight* s)
{
    cout<<"Name: "<<s->name<<"\n";
    int state_id = s->state_id;
    cout<<"Belongs to "<<DataBase::states_DB[state_id].getName()<<"\n";
    if(s->unesco_protection)
    {
        cout<<"Under UNESCO protection. \n";
    }
}
void Interface::setState(State* s)
{
    cout<<"Enter the name of the state: ";
    std::string str;
    std::getline(cin, str);
    if (str.size() == 0)
    {
        std::getline(cin, str);
    }
    s->setName(str);
    cout<<"Enter the population of "<<str<<" from 0 to 2000 billion: ";
    s->setPopulation(Interface::readNumb(0,2000));
    std::cout<<"Enter the GDP of "<<str<<" from 0 to 20000 in billion dollars per year: ";
    s->setGDP(Interface::readNumb(0,20000));
    std::cout<<"Enter the defence rating of "<<str<<" from 0 to 100: ";
    s->setDefence(Interface::readNumb(0,100));
}
void Interface::setRes(Res* res)
{
    cout<<"Enter the name of your resolution: ";
    std::string str;
    std::getline(cin, str);
    if (str.size() == 0)
    {
        std::getline(cin, str);
    }
    res->name = str;
    res->ID = Res::res_count;
    Res::res_count++;
}
void Interface::setSight(Sight* sight)
{
    cout<<"Enter the name of cultural sight: ";
    std::string str;
    std::getline(cin, str);
    if (str.size() == 0)
    {
        std::getline(cin, str);
    }
    sight->name = str;
    sight->ID = Sight::sight_count;
    Sight::sight_count++;
    sight->state_id = (Interface::chooseState())->getID();
}
void Interface::printOrg(Org* org)
{
    cout<<"Name: "<<org->getName()<<"\n";
    std::cout<<"List of the members: \n";
    std::map<int,State*> members = org->getAllStates();
    std::map<int,State*>::iterator it;
    for(it = members.begin(); it != members.end(); it++)
    {
        std::cout<<"Name: "<<it->second->getName()<<" ID: "<<it->first<<"\n";
    }
}
Alliance* Interface::chooseAlliance() throw (bool)
{
    system("cls");
    std::vector<Alliance>::iterator it;
    unsigned int i = 0;
    unsigned int Answer;
    cout<<"Choose an alliance organisation: \n";
    for(it = DataBase::alliance_DB.begin(); it != DataBase::alliance_DB.end(); it++,i++)
    {
        cout<<i<<". "<<it->getName()<<"\n";
    }
    cout<<"Press Escape to return.\n";
    do
    {
        Answer = getch();
        i = Answer - '0';
        if((Answer != 27)&&(i < DataBase::alliance_DB.size()))
        {
            return &DataBase::alliance_DB[i];
        }
    }while(Answer != 27);
    throw false;
}
TradeOrg* Interface::chooseTradeOrg() throw (bool)
{
    system("cls");
    std::vector<TradeOrg>::iterator it;
    unsigned int i = 0;
    unsigned int Answer;
    cout<<"Choose a trade organisation: \n";
    for(it = DataBase::trade_DB.begin(); it != DataBase::trade_DB.end(); it++,i++)
    {
        cout<<i<<". "<<it->getName()<<"\n";
    }
    cout<<"Press Escape to return.\n";
    do
    {
        Answer = getch();
        i = Answer - '0';
        if((Answer != 27)&&(i < DataBase::trade_DB.size()))
        {
            return &DataBase::trade_DB[i];
        }
    }while(Answer != 27);
    throw false;
}
State* Interface::chooseState() throw (bool)
{
    system("cls");
    std::map<int,State>::iterator it;
    unsigned int i = 0;
    unsigned int Answer;
    cout<<"Choose state number: \n";
    for(it = DataBase::states_DB.begin(); it != DataBase::states_DB.end(); it++,i++)
    {
        cout<<i<<". "<<(it->second.getName())<<" ID: "<<it->first<<"\n";
    }
    cout<<"Press Escape to return.\n";
    it = DataBase::states_DB.begin();
    do
    {
        Answer = getch();
        i = Answer - '0';
        if((Answer != 27)&&(i < DataBase::states_DB.size()))
        {
            for(unsigned int j = 0; j < i; j++,it++){}
            return &it->second;
        }
    }while(Answer != 27);
    throw false;
}
int Interface::readNumb(int min,int max) throw (int)
{
    do
    {
        char c;
        int count = 0;
        int numb = 0;
        int last_numb;
        do
        {
            c = getch();
            if((c > 47)&&(c < 58))
            {
                cout<<c;
                count++;
                last_numb = c - '0';
                numb = numb*10 + (c - '0');
            }else
            {
                if((c == 8)&&(count > 0))
                {
                    count--;
                    cout<<"\b \b";
                    numb = (numb - last_numb)/10;
                }
                else
                {
                    if((c == 13)&&(count > 0))
                    {
                        break;
                    }
                }
            }
        }while(1);
        if(numb > max)
        {
            cout<<"\nThe number is too big.("<<min<<", "<<max<<") Please, try again: ";
            continue;
        }else
        {
            if(numb < min)
            {
                cout<<"\nThe number is too small.("<<min<<", "<<max<<") Please, try again: ";
                continue;
            }else
            {
                cout<<"\n";
                return numb;
            }
        }
    }while(true);
}
