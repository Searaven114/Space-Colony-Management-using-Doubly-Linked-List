// Free Functions to be used in the main

#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

// Struct definitions
//------------------------------------------------------------------------------------------
struct stockNode{

    string resourceName;
    int resourceQuantity;

    stockNode *next;
    stockNode *prev;

    stockNode(string s = "", int i = -1, stockNode* n = NULL, stockNode*p = NULL):
    resourceName(s), resourceQuantity(i), next(n), prev(p) {}

};

struct consumpNode{

    char buildType;
    vector<int> consumpQtys;

    consumpNode *next;
    consumpNode *prev;

    consumpNode(char ch= '\0', vector<int>v = {}, consumpNode* n = NULL, consumpNode*p = NULL) :
    buildType(ch), consumpQtys(v), next(n), prev(p) {};
};

struct colonyNode{

    char buildType;
    int emptyBlocks2TheLeft;

    colonyNode *next;
    colonyNode *prev;

    colonyNode(char c = '\0', int i = -1, colonyNode* n = NULL, colonyNode* p = NULL) :
    buildType(c), emptyBlocks2TheLeft(i), next(n), prev(p) {}
};
//------------------------------------------------------------------------------------------
//
// Function prototypes
//------------------------------------------------------------------------------------------
void fileOpenner(ifstream &file, string typeOfInput);
stockNode* StockLoader(ifstream &file, stockNode*& head,stockNode*& tail);
void StockAddToEnd(stockNode*& head, stockNode*& tail, string ResType, int quantity);
void PrintStockDEBUG(stockNode* head);
void ConsumptionAddToEnd(consumpNode*& head, consumpNode*& tail, char BuildingType, vector<int> quantities);
consumpNode* ConsumptionLoader(ifstream&file, consumpNode*& head, consumpNode*& tail);
void PrintConsumptionDEBUG(consumpNode* head);
void ColonyAddToEnd(colonyNode*& head, colonyNode*& tail, char BuildingType, int emptyBlocks);
colonyNode* ColonyLoader(colonyNode*& head, colonyNode*& tail, stockNode* stockHead, consumpNode* consumpHead,ifstream &fileSTOCK,ifstream &fileCONSUMPTION,ifstream &fileCOLONY);
void PrintColonyDEBUG(colonyNode* head);
template <typename Node> void DeleteAll(Node*& head);
void PrintStock(stockNode* head);
void PrintColony(colonyNode* head);
void PrintColonyReverse(colonyNode* node, string& tempStr);
void PrintColonyWithInnerEmptyBlocks(colonyNode* head);
void reverseString(string& str);
void PrintColonyWithInnerEmptyBlocksREVERSE(colonyNode* head);
void DeleteBuildingFromColony(colonyNode*& colonyHead, char buildingType, consumpNode* consumpHead, stockNode* stockHead);
void ConstructNewBuilding(colonyNode*& colonyHead, colonyNode*& colonyTail, consumpNode* consumpHead, stockNode* stockHead);
string decodeColony(colonyNode* head);
colonyNode* encodeColony(const string& COLONYSTRING);
//------------------------------------------------------------------------------------------
#endif