# BroBank Testing

Test 1: Submit Three Transactions
Description: Submit three transactions to the pending queue.
Expected Result: Transactions are processed in FIFO order.
Actual Result: Pass

Test 2: Valid Deposit Then Undo
Description: Process a valid deposit and then undo it.
Expected Result: Original account balance is restored.
Actual Result: Pass

Test 3: Overdraw Withdrawal
Description: Attempt to withdraw more money than the account contains.
Expected Result: Transaction is rejected and no undo record is created.
Actual Result: Pass

Test 4: Queue Full / Empty
Description: Attempt operations when the transaction queue is full or empty.
Expected Result: Safe failure occurs and the bank state remains unchanged.
Actual Result: Pass

Test 5: Duplicate Graph Edge
Description: Process transfers that create an already-existing graph connection.
Expected Result: The account is not visited more than once during traversal.
Actual Result: Pass

Test 6: Invalid Account ID / NULL
Description: Provide an invalid account ID or a NULL BroBank pointer.
Expected Result: Operation fails safely without modifying the bank state.
Actual Result: Pass


## Testing Notes

The tests were designed to verify both successful operations and rejected transactions. Particular attention was given to maintaining consistent account balances when transactions fail and correctly reversing successful transactions through the undo stack.
