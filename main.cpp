#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "functions.h"

//#define DEBUG

using namespace std;

int main() {

    //Stock Handling
    ifstream input_stockfile;
    fileOpenner(input_stockfile,"stock"); //stockX.txt is open ! bound to input_stockfile

    stockNode* HEAD_STOCKNODE = NULL;
    stockNode* TAIL_STOCKNODE = NULL;

    HEAD_STOCKNODE = StockLoader(input_stockfile,HEAD_STOCKNODE, TAIL_STOCKNODE);

    #ifdef DEBUG
    PrintStockDEBUG(HEAD_STOCKNODE);
    #endif


    //Consumption Handling
    ifstream input_consumptionfile;
    fileOpenner(input_consumptionfile,"consumption"); //consumptionX.txt is open ! bound to input_consumptionfile

    consumpNode* HEAD_CONSUMPTIONNODE = NULL;
    consumpNode* TAIL_CONSUMPTIONNODE = NULL;

    HEAD_CONSUMPTIONNODE = ConsumptionLoader(input_consumptionfile,HEAD_CONSUMPTIONNODE, TAIL_CONSUMPTIONNODE);

    #ifdef DEBUG
    PrintConsumptionDEBUG(HEAD_CONSUMPTIONNODE);
    #endif


    //Colony Handling
    ifstream input_colonyfile;
    fileOpenner(input_colonyfile,"colony"); //colonyX.txt is open ! bound to input_colonyfile

    colonyNode* HEAD_COLONYNODE = NULL;
    colonyNode* TAIL_COLONYNODE = NULL;

    HEAD_COLONYNODE = ColonyLoader(HEAD_COLONYNODE, TAIL_COLONYNODE, HEAD_STOCKNODE, HEAD_CONSUMPTIONNODE,input_stockfile,input_consumptionfile,input_colonyfile);

    #ifdef DEBUG
    PrintColonyDEBUG(HEAD_COLONYNODE);
    #endif

    #ifdef DEBUG
    PrintStockDEBUG(HEAD_STOCKNODE);
    #endif


    //Releasing the menu
    bool running = true;

    cout << "Please enter your choice:" << endl;
    cout << "1. Construct a new building on the colony" << endl;
    cout << "2. Destruct/Disassemble a building from the colony" << endl;
    cout << "3. Print the colony" << endl;
    cout << "4. Print the colony in reverse" << endl;
    cout << "5. Print the colony while showing inner empty blocks" << endl;
    cout << "6. Print the colony while showing inner empty blocks in reverse" << endl;
    cout << "7. Print the stock" << endl;
    cout << "8. Exit" << endl;

    while (running) {

        int choice;

        cin >> choice;

        switch (choice) {
            case 1:
                // Construct a new building in colony DLL

                #ifdef DEBUG
                cout << "CASE 1 INVOKED !" << endl;
                #endif

                ConstructNewBuilding(HEAD_COLONYNODE, TAIL_COLONYNODE, HEAD_CONSUMPTIONNODE, HEAD_STOCKNODE);

                break;
            case 2:
                // Destruct a first occurrance of a particular building in colony DLL

                #ifdef DEBUG
                cout << "CASE 2 INVOKED !" << endl;
                #endif

                char buildingType;
                cout << "Please enter the building type:" << endl;
                cin >> buildingType;

                DeleteBuildingFromColony(HEAD_COLONYNODE, buildingType, HEAD_CONSUMPTIONNODE, HEAD_STOCKNODE);


                break;
            case 3:
                // Print the colony DLL

                #ifdef DEBUG
                cout << "CASE 3 INVOKED !" << endl;
                #endif

                PrintColony(HEAD_COLONYNODE);

                break;
            case 4:
                {
                // flip it lmao

                #ifdef DEBUG
                cout << "CASE 4 INVOKED !" << endl;
                #endif

                cout << "(Reverse) Colony DLL:" << endl;
                string tempStr;
                PrintColonyReverse(HEAD_COLONYNODE,tempStr);
                cout << tempStr << endl;

                break;
                }
            case 5:
                // print the colony with inner empty blocks shown

                #ifdef DEBUG
                cout << "CASE 5 INVOKED !" << endl;
                #endif

                PrintColonyWithInnerEmptyBlocks(HEAD_COLONYNODE);

                break;
            case 6:
                // https://youtu.be/H3ke3ooK_X4

                #ifdef DEBUG
                cout << "CASE 6 INVOKED !" << endl;
                #endif

                PrintColonyWithInnerEmptyBlocksREVERSE(HEAD_COLONYNODE);

                break;
            case 7:
                // print the stock DLL

                #ifdef DEBUG
                cout << "CASE 7 INVOKED !" << endl;
                #endif

                PrintStock(HEAD_STOCKNODE);

                break;
            case 8:
                // Clear memory and exit.

                #ifdef DEBUG
                cout << "CASE 8 INVOKED !" << endl;
                #endif

                cout << "Clearing the memory and terminating the program." << endl;

                DeleteAll(HEAD_STOCKNODE);
                DeleteAll(HEAD_CONSUMPTIONNODE);
                DeleteAll(HEAD_COLONYNODE);

                input_stockfile.close();
                input_consumptionfile.close();
                input_colonyfile.close();

                // break out of switch
                running = false;
                break;
        }
}

    input_stockfile.close();
    input_consumptionfile.close();
    input_colonyfile.close();

    #ifdef DEBUG
    cout << "WARNING ! IF YOU SEE THIS IT MEANS THAT THE USER INPUTS HAVE BROKEN OUT OF THE MENU" << endl;
    cout << "WARNING ! IF YOU SEE THIS IT MEANS THAT THE USER INPUTS HAVE BROKEN OUT OF THE MENU" << endl;
    cout << "WARNING ! IF YOU SEE THIS IT MEANS THAT THE USER INPUTS HAVE BROKEN OUT OF THE MENU" << endl;
    #endif

    return 0;
}

//***************************************************************************************************************************



