#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "Class.h"
class Interface
{
public:
    static void printState(State* s);
    static void printRes(Res* res);
    static void printSight(Sight* sight);
    static void setState(State* s);
    static void setRes(Res* res);
    static void setSight(Sight* sight);
    static void printOrg(Org* org);
    static void mainMenu();
    static void creationMenu();
    static void destructionMenu();
    static void inclusionMenu();
    static void viewDataMenu();
    static void searchMenu();
    static void readMenu();
    static Alliance* chooseAlliance() throw (bool);
    static TradeOrg* chooseTradeOrg() throw (bool);
    static State* chooseState() throw (bool);
    static int readNumb(int max,int min) throw (int);
    //static void chooseMenu();
};
#endif // INTERFACE_H_INCLUDED
