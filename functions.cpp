#include "functions.h"

//#define DEBUG

/* @brief Universal file openner with built-in prompting
 *
 * @param "file" [in][out] Ifstream object which the function will return
 *
 * @param "typeOfInput" [in] A string that will be used to decide the type of the txt file (stock/consumption/colony)
 *
 * @Precondition: An ifstream object is not bound to a file and the typeOfInput is determined beforehand
 *
 * @Postcondition: The ifstream object is bound to a file, if the file does not exist or fails to open,
 *                 the user is prompted to enter the filename again until a valid file is provided.
 *
 * @note Debug code included
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void fileOpenner(ifstream &file, string typeOfInput){

    cout << "Please enter the " << typeOfInput <<" file name:" << endl;
    string filename;
    cin >> filename;
    file.open(filename.c_str());

    while( file.fail() ){
        cout<< "Unable to open the file " << filename << ". ";
        cout<< "Please enter the correct " << typeOfInput <<" file name:" << endl;
        cin >> filename;
        file.open(filename.c_str());
    }

    #ifdef DEBUG
    cout << "DEBUG: " << typeOfInput << " FILE HAS BEEN SUCCESSFULLY OPENNED !" << endl;
    #endif
}




/* @brief Loads stock data from a text file into a DLL and updates the head and tail pointers.
 *
 * @param "file" [in] Reference to an ifstream object that is already bound to the stock data file.
 *
 * @param "head" [in][out] Reference to the head pointer of the stock DLL. After the function execution, this pointer will point to the first node of the newly created DLL.
 *
 * @param "tail" [in][out] Reference to the tail pointer of the stock DLL. After the function execution, this pointer will point to the last node of the newly created DLL.
 *
 * @pre The head and tail pointers are initialized but not pointing to any valid DLL nodes. The ifstream object (file) is open and ready for reading.
 *
 * @post A new DLL is formed based on the content of the ifstream object.
 *       The head and tail pointers provided by the user are updated to point to the respective nodes of the newly created DLL.
 *       Returns the given now re-pointed pointers in parameters by return-by-reference
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
stockNode* StockLoader(ifstream &file, stockNode*& head,stockNode*& tail) {

    string line;
    while (getline(file, line)) {

        stringstream ss(line);
        string name;
        int quantity;

        ss >> name >> quantity;

        StockAddToEnd(head, tail, name, quantity);
    }

    return head;
}





/* @brief Appends a new node to the end of the stock doubly linked list (DLL).
 *
 * @param "head" [in][out] Pointer to the head of the original stock DLL.
 * @param "tail" [in][out] Pointer to the tail of the original stock DLL.
 * @param "ResType" [in] Type of the resource to be added.
 * @param "quantity" [in] Quantity of the resource to be added.
 *
 * @pre The stock DLL is either empty or already populated.
 *
 * @post A new node with the specified resource type and quantity is appended to the end of the DLL.
 *                The head and tail pointers are updated accordingly.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void StockAddToEnd(stockNode*& head, stockNode*& tail, string ResType, int quantity){

    if (tail == NULL){

        stockNode* ptr = new stockNode(ResType, quantity, NULL, NULL); // Make it standalone if there are no nodes present alreadys
        tail = ptr;
        head = tail;

    } else {
        stockNode* ptr = new stockNode(ResType, quantity, NULL, tail);
        tail->next = ptr;
        tail = ptr;
    }
}




/* @brief Prints the colony DLL with debugging in mind.
 *
 * @param "head" [in] Pointer to the head of the original colony DLL.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void PrintStockDEBUG(stockNode* head) {

    cout << "DEBUG:" << endl;
    stockNode* temp = head; //head preservation

    if (temp == NULL){
        cout << "The list is empty !" << endl;
    } else {

        while (temp != NULL) {

            cout << temp->resourceName << " ";
            cout << temp->resourceQuantity << " ";

            temp = temp->next;
            cout << endl;
        }
        //cout << endl;
    }
}




/* @brief Appends a new node to the end of the consumption DLL.
 *
 * @param "head" [in][out] Reference to the head pointer of the consumption DLL.
 *
 * @param "tail" [in][out] Reference to the tail pointer of the consumption DLL.
 *
 * @param "BuildingType" [in] Type of the building which is a data field of the consumpNode.
 *
 * @param "quantities" [in] Vector containing quantities of resources consumed by the building which is a data field of the consumpNode.
 *
 * @pre The consumption DLL is either empty or already populated, pointers are initialized.
 *
 * @post A new node with the specified building type and quantity vector is appended to the end of the DLL. The head and tail pointers are updated accordingly.
 *
 * @see ConsumptionLoader
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ConsumptionAddToEnd(consumpNode*& head, consumpNode*& tail, char BuildingType, vector<int> quantities){

    if (tail == NULL){

        consumpNode* ptr = new consumpNode(BuildingType, quantities, NULL, NULL);
        tail = ptr;
        head = tail;

    } else {
        consumpNode* ptr = new consumpNode(BuildingType, quantities, NULL, tail);
        tail->next = ptr;
        tail = ptr;
    }
}




/* @brief Loads consumption data from a file into a DLL.
 *
 * @param "file" [in] Reference to an ifstream object containing consumption data.
 *
 * @param "head [in][out] Reference to the head pointer of the consumption DLL.
 *
 * @param "tail" [in][out] Reference to the tail pointer of the consumption DLL.
 *
 * @pre Ifstream object is ready to be used, pointers are present and initalized.
 *
 * @post Creates a consumption DLL based on the contents of the consumption file. Re-directs the head & tail pointers accordingly.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
consumpNode* ConsumptionLoader(ifstream&file, consumpNode*& head, consumpNode*& tail){

    string line;
    while(getline(file,line)){
        // Declare a new int vector for each line in the file
        vector<int> V;

        stringstream ss(line);

        char building;
        int quantity;

        // Dissection happens here
        ss >> building;
        while (ss >> quantity) {
            V.push_back(quantity);
        }

        ConsumptionAddToEnd(head, tail, building, V); // newly formed node gets pushed back into the consumption DLL.
    }
    return head;
}




/* @brief Prints the consumption DLL to console with debugging in mind
 *
 * @param "head" [in] Reference to the head pointer of the consumption DLL.
 *
 * @post Contents of the consumption DLL is printed in the console.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void PrintConsumptionDEBUG(consumpNode* head) {

    cout << "DEBUG:" << endl;

    consumpNode* temp = head;

    if (temp == NULL){
        cout << "The list is empty !" << endl;
    } else {

        while (temp != NULL) {

            cout << temp->buildType << " ";
            for (int i = 0; i < temp->consumpQtys.size(); i++)
                cout << temp->consumpQtys[i] << " ";

            temp = temp->next;

            cout << endl;
        }
        //cout << endl;
    }
}




/* @brief Appends a new node to the end of the colony DLL.
 *
 * @param "head" [in][out] Reference to the head pointer of the colony DLL.
 *
 * @param "tail" [in][out] Reference to the tail pointer of the colony DLL.
 *
 * @param "buildType" [in] Type of the building which is a data field of the colonyNode.
 *
 * @param "emptyBlocks2TheLeft" [in] The encapsulation of amount of dashes on the left of the buildType in the colony DLL. Also a data field of colonyNode.
 *
 * @see ColonyLoader, encodeColony
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ColonyAddToEnd(colonyNode*& head, colonyNode*& tail, char BuildingType, int emptyBlocks){

    if (tail == NULL){

        colonyNode* ptr = new colonyNode(BuildingType, emptyBlocks, NULL, NULL);
        tail = ptr;
        head = tail;

    } else {
        colonyNode* ptr = new colonyNode(BuildingType, emptyBlocks, NULL, tail);
        tail->next = ptr;
        tail = ptr;
    }
}




/* @brief Loads colony data from a file into a DLL, checks for sufficent resources, if sufficent, updates stock quantities based on consumption corresponding consumption data.
 *        else, exits the program while closing the files and deleting the allocated memory.
 *
 * @param "head" [in][out] Reference to the head pointer of the original colony DLL.
 *
 * @param "tail" [in][out] Reference to the tail pointer of the original colony DLL.
 *
 * @param "stockHead" [in][out] Pointer to the head of the original stock DLL.
 *
 * @param "consumpHead" [in] Pointer to the head of the original consumption DLL.
 *
 * @param "fileSTOCK" [in] Reference to an ifstream object containing stock data.
 *
 * @param "fileCONSUMPTION" [in] Reference to an ifstream object containing consumption data.
 *
 * @param "fileCOLONY" [in] Reference to an ifstream object containing colony data.
 *
 * @pre The file objects is successfully opened and ready for reading. The head and tail pointers for the colony, stock, and consumption DLLs should either point to valid nodes or be null.
 *
 * @post Creates a colony DLL based on the contents of the colony file. Updates the stock quantities based on the consumption of resources for each building in the colony.
 *       If there are insufficient resources, the program will terminate after clearing the memory in addition to informing the user about the insufficient resource.
 *       The head & tail pointers of the colony DLL are re-directed accordingly.
 *
 * @note Debug code included
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
colonyNode* ColonyLoader(colonyNode*& head, colonyNode*& tail, stockNode* stockHead, consumpNode* consumpHead, ifstream &fileSTOCK, ifstream &fileCONSUMPTION, ifstream &fileCOLONY){

    char c;

    int emptyBlocks = 0;

    while(fileCOLONY.get(c)){

        if (c == '-') {
            //encountered char is dash, increase counter
            emptyBlocks++;
        } else {

            //
            //Linear searching the consumption DLL to detect the corresponding node
            consumpNode* consumpPtr = consumpHead;
            while (consumpPtr->buildType != c) {    //consumpPtr != NULL && ------------------------------
                consumpPtr = consumpPtr->next;
            }

            //consumption node is found, now checking for the resource sufficency by iterating the elements of the vector
            stockNode* stockPtr = stockHead;
            for (int i = 0; i < consumpPtr->consumpQtys.size(); i++) {

                if (stockPtr->resourceQuantity < consumpPtr->consumpQtys[i]) {          //stockPtr == NULL ||    ------------------------

                    cout << "Insufficient resource " << stockPtr->resourceName << endl;
                    cout << "Failed to load the colony due to insufficient resources." << endl;
                    cout << "Clearing the memory and terminating the program." << endl;

                    fileSTOCK.close();
                    fileCONSUMPTION.close();
                    fileCOLONY.close();

                    DeleteAll(stockHead);
                    DeleteAll(consumpHead);
                    DeleteAll(head);

                    exit(1);
                }
                stockPtr->resourceQuantity = stockPtr->resourceQuantity - consumpPtr->consumpQtys[i]; //deduction
                stockPtr = stockPtr->next; //advance stock pointer to right
            }

            ColonyAddToEnd(head, tail, c, emptyBlocks); //finalization of the current checked element

            #ifdef DEBUG
            cout << "DEBUG: NEW NODE ADDED TO COLONY DLL ! NAME: " << c << " " <<"EMPTYBLOCKS: " << emptyBlocks << endl;
            #endif

            emptyBlocks = 0;  // Resetting the empty blocks variable for the use of other nodes.
        }
    }

    return head; // returns the freshly created DLL's head
}




/* @brief Prints the colony DLL to console with debugging in mind
 *
 * @param "head" [in] Reference to the head pointer of the colony DLL.
 *
 * @post Contents of the colony DLL is printed in the console.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void PrintColonyDEBUG(colonyNode* head) {

    colonyNode* temp = head;

    if (temp == NULL){
        cout << "The list is empty !" << endl;
    } else {

        while (temp != NULL) {

            cout << temp->buildType << " ";
            cout << temp->emptyBlocks2TheLeft << " ";

            temp = temp->next;

            cout << endl;
        }

        cout << endl;
    }
}




/* @brief Deletes all nodes in a given doubly linked list (DLL) and deallocates memory.
 *
 * @tparam Node A template parameter representing the type of node in the DLL. (stock/consumption/colony)
 *
 * @param "head" [in] Reference to the head pointer of the entered DLL.
 *
 * @pre The head pointer points to the first node of the DLL or be null if the list is empty.
 *
 * @post All nodes in the DLL are deleted and their memory is deallocated. The head pointer is set to NULL
 *
 * @note Debug code included
 *
 * @note Dersi 3. alışım, templated kullanmamış olup 3 ayrı fonk yazsaydım sağlam günaha girmiş olurdum
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
template <typename Node>
void DeleteAll(Node*& head) {
    #ifdef DEBUG
    cout << "DEBUG: DELETING THE LINKED LIST" << endl;
    #endif

    while(head != NULL){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}




/* @brief Prints the contents of the stock DLL to the console.
 *
 * @param "head" [in] Pointer to the head node of the stock DLL.
 *
 * @pre The head pointer should either point to the first node of the stock DLL or be nullptr if the list is empty, however null case is an extra guard.
 *
 * @post The contents of the stock DLL are displayed on the console.
 *
 * @note represents button 7 in CLI menu
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void PrintStock(stockNode* head) {

    stockNode* temp = head;

    if (temp == NULL){
        cout << "The list is empty !" << endl;
    } else {

        cout << "Stock DLL:" << endl;

        while (temp != NULL) {

            string tempStr = temp->resourceName;
            int tempInt = temp->resourceQuantity;

            //formatting output
            cout << tempStr << "(" << tempInt << ")" << endl;

            temp = temp->next;
        }
    }
}




/* @brief Prints the colony DLL in the requested format in THE2
 *
 * @param "head" [in] Pointer to the head of the original colony DLL.
 *
 * @note represents button 3 in CLI menu
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void PrintColony(colonyNode* head){

    colonyNode* temp = head;
    colonyNode* temp2 = head;

    cout << "Colony DLL:" << endl;

    if (temp == NULL){
        cout << "The list is empty !" << endl;
    } else {

        string tempStr = "";
        while(temp2 != NULL){
            tempStr = tempStr + temp2->buildType;
            temp2 = temp2->next;
        }

        cout << tempStr << endl;

        while(temp != NULL){

            cout << "(" << temp->emptyBlocks2TheLeft << ")" << temp->buildType;
            temp = temp->next;

        }
        cout << endl;
    }
}




/* @brief Prints the colony DLL in the requested format in THE2 (reverse)
 *
 * @param "head" [in] Pointer to the head of the original colony DLL.
 *
 * @note represents button 4 in CLI menu
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void PrintColonyReverse(colonyNode* node, string& tempStr) {
    if (node == NULL) {
        return;
    }
    PrintColonyReverse(node->next,tempStr);

    tempStr = tempStr + node->buildType;

}




/* @brief Prints the colony DLL in the requested format in THE2 (in decoded string format)
 *
 * @param "head" [in] Pointer to the head of the original colony DLL.
 *
 * @note represents button 5 in CLI menu
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void PrintColonyWithInnerEmptyBlocks(colonyNode* head){

    string tempStr = "";

    colonyNode* ptr = head;

    cout << "Colony DLL:" << endl;

    while (ptr != NULL){

        for (int i = 0; i < ptr->emptyBlocks2TheLeft; i++){
            tempStr += '-';
        }

        tempStr += ptr->buildType;
        ptr = ptr->next;
    }

    cout << tempStr << endl;
}




/* @brief reverses a given string
 *
 * @param "str" [in][out] reference to the given string
 *
 * @note This is a helper function for option 6
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void reverseString(string& str){
    string temp;
    for (int i = str.length() - 1; i >= 0; i--){
        temp += str[i];
    }
    str = temp;
}




/* @brief Prints the colony DLL in the requested format in THE2 (in decoded string format but reverse)
 *
 * @param "head" [in] Pointer to the head of the original colony DLL.
 *
 * @note represents button 6 in CLI menu
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void PrintColonyWithInnerEmptyBlocksREVERSE(colonyNode* head){

    string tempStr = "";

    colonyNode* ptr = head;

    cout << "(Reverse) Colony DLL:" << endl;

    while (ptr != NULL){

        for (int i = 0; i < ptr->emptyBlocks2TheLeft; i++){
            tempStr += '-';
        }

        tempStr += ptr->buildType;
        ptr = ptr->next;
    }

    reverseString(tempStr);

    cout << tempStr << endl;
}




/* @brief Deletes a specified building type from the colony doubly linked list (DLL). If the building type is found,
 *        it's first occurrance is removed from the colony DLL, and the resources associated with it are added back to the stock.
 *        If the building type is not found, the user will be displayed with an appropriate message.
 *
 * @param "colonyHead" [in][out] Reference to the head pointer of the colony DLL. The function may modify the DLL, potentially updating the head pointer if the first node is deleted.
 *
 * @param "buildingType" [in] The type of building to be deleted from the colony.
 *
 * @param "consumpHead" [in] Reference to the head pointer of the consumption DLL. Used to find the resource consumption of the building type to be deleted.
 *
 * @param "stockHead" [in][out] Reference to the head pointer of the stock DLL. The function updates the stock based on the resources associated with the deleted building.
 *
 * @note represents button 2 in CLI menu
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void DeleteBuildingFromColony(colonyNode*& colonyHead, char buildingType, consumpNode* consumpHead, stockNode* stockHead) {

    colonyNode* temp = colonyHead;
    colonyNode* prev = NULL;

    // Search for the first occurrance of user given buildingType in colony DLL by linear searching the colony DLL
    while (temp != NULL && temp->buildType != buildingType) {
        prev = temp;
        temp = temp->next;
    }

    // If the node is not found in the DLL
    if (temp == NULL) {
        cout << "Building of type " << buildingType << " not found in the colony." << endl;

        //Clearing input buffer so that menu inputs wont interfere with last failed menu option case
        cin.clear();
        cin.ignore(9999999, '\n');
        return; // return to asking menu options
    }

    // Find the building type in the consumption DLL
    consumpNode* consumpPtr = consumpHead;
    while (consumpPtr != NULL && consumpPtr->buildType != buildingType) {
        consumpPtr = consumpPtr->next;
    }

    // If the building type is found in the consumption DLL:
    if (consumpPtr != NULL) {
        stockNode* stockPtr = stockHead;
        for (int i = 0; i < consumpPtr->consumpQtys.size(); i++) {

            if (stockPtr != NULL) { // Reclaim the resources

                stockPtr->resourceQuantity += consumpPtr->consumpQtys[i];

                stockPtr = stockPtr->next;
            }
        }
    }

    // If the node to be deleted is the first node
    if (prev == NULL) {
        colonyHead = temp->next;
        if (colonyHead != NULL) { // If the list has more than one node:
            colonyHead->prev = NULL;
            colonyHead->emptyBlocks2TheLeft += (1 + temp->emptyBlocks2TheLeft);
        }
    } else {

        prev->next = temp->next;

        // If the node to be deleted is not the last node
        if (temp->next != NULL) {
            temp->next->prev = prev;
            temp->next->emptyBlocks2TheLeft += (1 + temp->emptyBlocks2TheLeft);
        }
    }
    delete temp;

    cout << "The building of type " << buildingType << " has been deleted from the colony." << endl;
}




/* @brief Constructs a new building in the colony based on the user's input for building type and its position with stock and memory management in mind.
 *
 * @param "colonyHead" [in][out] Reference to the head pointer of the original colony DLL.
 *
 * @param "colonyTail" [in][out] Reference to the tail pointer of the original colony DLL.
 *
 * @param "consumpHead" [in] Reference to the head pointer of the original consumption DLL.
 *
 * @param "stockHead" [in][out] Reference to the head pointer of the original stock DLL.
 *
 * @note Debug code included
 *
 * @note represents button 1 in CLI menu
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ConstructNewBuilding(colonyNode*& colonyHead, colonyNode*& colonyTail, consumpNode* consumpHead, stockNode* stockHead) {

    // First stage, ask for buildingType
    char buildingType;
    cout << "Please enter the building type:" << endl;
    cin >> buildingType;


    // Second stage, Validate the building type
    consumpNode* consumpPtr = consumpHead;
    while (consumpPtr != NULL && consumpPtr->buildType != buildingType) {
        consumpPtr = consumpPtr->next;
    }
    while (consumpPtr == NULL) {

        cout << "Building type " << buildingType << " is not found in the consumption DLL. Please enter a valid building type:" << endl;
        cin >> buildingType;

        consumpPtr = consumpHead;
        while (consumpPtr != NULL && consumpPtr->buildType != buildingType) {
            consumpPtr = consumpPtr->next;
        }
    }


    // Third stage, Check if there are enough resources in the stock
    stockNode* stockPtr = stockHead;
    for (int i = 0; i < consumpPtr->consumpQtys.size(); i++) {
        if (stockPtr->resourceQuantity  <  consumpPtr->consumpQtys[i]) {

            cout << "Insufficient resource " << stockPtr->resourceName << endl;
            cout << "Failed to add the building due to insufficient resources." << endl;
            return;
        } else {

        }
        stockPtr = stockPtr->next;
    }


    // Fourth stage,  If the sequental execution ever comes to this point it means that the buildingType is present and there are enough resources in stocks
    // to build 1 piece of the given buildingType. Therefore, Deduce the resources from stock.

    //Reset pointers
    stockPtr = stockHead;
    consumpPtr = consumpHead;

    //linear search for the corresponding node in consumption DLL
    while (consumpPtr != NULL && consumpPtr->buildType != buildingType) {
        consumpPtr = consumpPtr->next;
    }
    // Deduction happens here
    for (int i = 0; i < consumpPtr->consumpQtys.size(); i++) {
        stockPtr->resourceQuantity = stockPtr->resourceQuantity - consumpPtr->consumpQtys[i];
        stockPtr = stockPtr->next;
    }


    //Fifth stage, prompt the user for the index of the first empty block, apply the modifications on a decoded colony, than encode that colony and than re-arrange the original pointers.
    int index;
    cout << "Please enter the index of the empty block where you want to construct a building of type " << buildingType << endl;
    cin >> index;

    //colony: (2)X(1)Y(3)Z (encoded)
    string COLONYSTRING = decodeColony(colonyHead); // DLL -> character array
    //COLONYSTRING: --X-Y---Z (decoded)

    /*
    CONDITION 1, index mevcuttur hazır stringde. (--X-Y---Z ve index 1 bu olur: A-X-Y---Z) EŞİTSE DE BU CONDITION ÇALIŞIR !
    CONDITION 2, index stringin içinde mevcut degildir, yeni dash eklenip son eklenen dash'ın yerine yerleştirilmesi gerekmektedir yeni Building'in. (--X-Y---Z ve index 8 bu olur: --X-Y---Z-A)
    */

    // Calculate the dashes present in the decoded colony
    int dashamount = 0;
    for (char c : COLONYSTRING){
        if (c == '-'){
            dashamount++;
        }
    }

    //CONDITION1, there is no need to append new dashes, there is room within the array, implement the modifications to colony string
    if (dashamount >= index){

        #ifdef DEBUG
        cout << "DEBUG: CONDITION 1 INVOKED ! (dashamount >= index)" << endl;
        #endif

        int indexavailable = 0;
        for(int i = 0; i < COLONYSTRING.size(); i++){

            if(COLONYSTRING[i] == '-'){
                indexavailable++;
            }
            if(indexavailable == index){

                COLONYSTRING.insert(i, 1, buildingType); // Insert the building at the specified index once
                COLONYSTRING.erase(i+1, 1); // Remove one '-' after inserting the building since we didnt overwrite anything in the previous statement
                break;
            }
        }

        //Now that we have the correct string, encode it to a brand new DLL

        colonyNode* newColHead = encodeColony(COLONYSTRING); //encode the string to a DLL and point local newColHead to that DLL

        DeleteAll(colonyHead); // discard old DLL, original colony head points to garbage.

        colonyHead = newColHead; // Re-point the original pointer to the newly created DLL.

        while (newColHead && newColHead->next) { // Locate new tail
        newColHead = newColHead->next;
        }
        colonyTail = newColHead; // Re-point the orijinal tail ptr to the fresh DLL's tail.

        cout << "Building of type " << buildingType << " has been added at the empty block number: " << index << endl;

    } else {

        //CONDITION2, there is a need to append new dashes, there is no room within the array, implement the modifications to colony string

        #ifdef DEBUG
        cout << "DEBUG: CONDITION 2 INVOKED ! (dashamount < index)" << endl;
        #endif

        // Append the necessary number of dashes to the string
        while (dashamount < index) {
            COLONYSTRING += '-';
            dashamount++;
        }

        // Replace the last dash of the charray with the building type
        COLONYSTRING.back() = buildingType;

        // encode the modified string to a new DLL, do pointer arrangements
        colonyNode* newColHead = encodeColony(COLONYSTRING);
        DeleteAll(colonyHead);
        colonyHead = newColHead;

        while (newColHead && newColHead->next) {
            newColHead = newColHead->next;
        }
        colonyTail = newColHead;  // Update the tail pointer

        cout << "Building of type " << buildingType << " has been added at the empty block number: " << index << endl;
    }
}




/* @brief Decodes a colony DLL into a string
 *
 * @param "head" [in] Reference to the head pointer of the original colony DLL.
 *
 * @pre the data is stored in DLL
 *
 * @post the data is now stored in a string, DLL still exists
 *
 * @note This is a helper function for ConstructNewBuilding
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
string decodeColony(colonyNode* head) {
    string colonyStr = "";
    colonyNode* ptr = head;

    while (ptr != NULL) {
        for (int i = 0; i < ptr->emptyBlocks2TheLeft; i++) {
            colonyStr += '-';
        }
        colonyStr += ptr->buildType;
        ptr = ptr->next;
    }

    return colonyStr;
}




/* @brief Encodes a colony string into a DLL.
 *
 * @param "COLONYSTRING" [in] Reference to the user given string.
 *
 * @pre the data is stored in string
 *
 * @post the data is now stored in a DLL, string still exists
 *
 * @note This is a helper function for ConstructNewBuilding
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
colonyNode* encodeColony(const string& COLONYSTRING) {

    colonyNode* newHead = NULL;
    colonyNode* tail = NULL;
    int emptyBlocks = 0;

    for (char c : COLONYSTRING) {
        if (c == '-') {
            emptyBlocks++;
        } else {
            ColonyAddToEnd(newHead, tail, c, emptyBlocks);
            emptyBlocks = 0;  // Reset the count of empty blocks
        }
    }

    return newHead;
}
