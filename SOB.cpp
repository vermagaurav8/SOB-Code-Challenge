#include <bits/stdc++.h>
using namespace std;

/*
    UNDERSTANDING OF PROBLEM:
        Each transaction has three things:
            - Fee
            - Weight (Size)
            - Parent transaction

        There is an list of transactions with the following conditons:
            1) It should be an ordered list, i.e no transaction should come before Parent transaction
            2) Weight < 4,000,000
            3) A transaction may only appear in a block if all of its parents appear
            _earlier_ in the block.
            4) Maximum fee


    APPROACH(Greedy):
        - Select the transactions with highest value of fee or weight.
        - Check if the selected transaction is valid, i.e. is all its parents are already included in the block.
        - If the transaction is valid include the transaction and update fee and weight and erase it from curr set. 
        - If it is not valid go to next highest transaction.
        - For getting the highest value of fee or weight We are using a set.

    Time Complexity: O(N^2), N = Number of Transaction in CSV file.

    External Source used:
        - https://www.geeksforgeeks.org/csv-file-management-using-c/
        - https://www.youtube.com/watch?v=ZhnJ1bkIWWk&t=664s
*/

string file = "mempool.csv";
int maxBlockWeight = 4000000;

class Transaction
{
public:
    string TxnId;
    int fee;
    int weight;
    vector<string> parents;
};

// Builds all Transactions according given feilds in CSV file.
pair<string, Transaction *> buildTransaction(vector<string> &row)
{
    auto transaction = new Transaction();
    transaction->TxnId = row[0];
    transaction->fee = stoi(row[1]);
    transaction->weight = stoi(row[2]);

    vector<string> parentTransactions;
    for (int i = 3; i < row.size(); i++)
    {
        parentTransactions.push_back(row[i]);
    }
    transaction->parents = parentTransactions;
    return {row[0], transaction};
}

void readCSV(string file, unordered_map<string, Transaction *> &mapPointer)
{
    ifstream fin(file);
    vector<string> row;
    string temp, line, word;
    getline(fin, line);

    while (getline(fin, line))
    {
        row.clear();
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word); // row contains TxnId, fee, weight, parent transactions.
        }
        pair<string, Transaction *> allTransactions = buildTransaction(row);
        mapPointer[allTransactions.first] = allTransactions.second;
    }
    fin.close();
}

// To check the Txn is valid or not
bool validate(Transaction *Txn, set<string> &blockTxnSet)
{
    // Condition: If all parent Txn are in set, then its a valid Txn
    for (auto parent : Txn->parents)
    {
        if (blockTxnSet.find(parent) == blockTxnSet.end())
            return false;
    }
    return true;
}

int main()
{
    // maps transactionId to its pointer
    unordered_map<string, Transaction *> mapPointer;
    readCSV(file, mapPointer);

    // set maintaining highes fee or weight
    set<pair<float, Transaction *>, greater<pair<float, Transaction *>>> TxnSet;
    // set containing Block transactions
    set<string> blockTxnSet;
    // vector for maintaining order in output;
    vector<string> orderTxnVector;

    for (auto Txn : mapPointer)
    {
        TxnSet.insert({(float)Txn.second->fee / (float)Txn.second->weight, Txn.second});
    }

    int blockCurrentWeight = 0, totalFee = 0;

    // loop until we ran out of Txn or we reach maxLimit.
    while (!TxnSet.empty() && blockCurrentWeight < maxBlockWeight)
    {
        bool visited = false;
        for (auto itr = TxnSet.begin(); itr != TxnSet.end(); itr++)
        {
            Transaction *currTxn = (*itr).second;
            int currentFee = currTxn->fee;
            int currentWeight = currTxn->weight;

            // If the Txn is valid:
            // Add weight, fee, save TxnId
            if (validate(currTxn, blockTxnSet) && (blockCurrentWeight + currentWeight <= maxBlockWeight))
            {
                blockCurrentWeight += currentWeight;
                blockTxnSet.insert(currTxn->TxnId);
                orderTxnVector.push_back(currTxn->TxnId);
                totalFee += currentFee;
                TxnSet.erase(itr);
                visited = true;
                break;
            }
        }

        if (!visited) // NO VALID Txn FOUND
            break;
    }

    cout << "Configuration of Final Block: " << endl;
    cout << "1. Fee: " << totalFee << endl;
    cout << "2. Weight: " << blockCurrentWeight << endl;

    // Write in block file
    ofstream myfile("block.txt");
    for (auto TxnId : orderTxnVector)
        myfile << TxnId << endl;
    myfile.close();

    return 0;
}