# Summer Of Bitcoin Code Challenge

## What is a BitCoin?
BitCoin can be considered as a type of cryptocurrency. It was invented in 2009.. There are no physical bitcoins, only balances kept on a public ledger that everyone has transparent access to. All bitcoin transactions are verified by a massive amount of computing power. Bitcoin is very popular and has triggered the launch of hundreds of other cryptocurrencies, collectively referred to as altcoins.  Bitcoin is commonly abbreviated as "BTC." BitCoin can be considered as a leisure, for eg : you pay money to fruit seller that is considered as a trade.


## UNDERSTANDING OF PROBLEM:
   Each transaction has three things:
   - Fee
   - Weight (Size)
   - Parent transaction
   <br>

<b>Constraint :</b>
   - It should be an ordered list, i.e no transaction should come before Parent transaction.
   - Weight < 4,000,000.
   - A transaction may only appear in a block if all of its parents appear earlier in the block.
   - Maximum fee

<br>

<b> Task: </b>
   - We would be importing csv file with certain constraints and would be reading the data in the file in the given format. 
   - Concept of blocks will be also used to get the maximum profit/fee. 
   - After that, we would be mining the data using bitcoin mining to get the desired output. 
<br>

## Tools and Technologies used for the task
   - C++ Language
   - Ubuntu Operating System 
   - Blockchain 
   - Data Mining
<br>

## APPROACH(Greedy):
   - Select the transactions with highest value of fee or weight.
   - Check if the selected transaction is valid, i.e. is all its parents are already included in the block.
   - If the transaction is valid include the transaction and update fee and weight and erase it from curr set. 
   - If it is not valid go to next highest transaction.
   - For getting the highest value of fee or weight We are using a set.

### Time Complexity: O(N^2), N = Number of transactions in CSV file.
