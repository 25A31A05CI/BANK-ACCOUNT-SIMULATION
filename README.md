# Bank Account Simulation

C project that simulates basic bank operations (create account, deposit, withdraw, show balance) using loops, switch-case, and file I/O with persistent storage.

## Features
- Create account with auto-incremented ID
- Deposit and withdraw with basic validation
- Show account balance and list all accounts
- Data persists in a simple text file: `accounts.txt`
- Clear, menu-driven interface

## How to Run on GDB Online (OnlineGDB)
OnlineGDB lets you run C programs in your browser perfect for beginners.

1) Open: [OnlineGDB C Compiler](https://www.onlinegdb.com/online_c_compiler)
2) Set Language: C
3) Replace the default code with your `bank.c` program (paste your code into the editor).
   - Optional: rename the file tab to `bank.c` for clarity.
4) Click the green “Run” button.
5) Use the right-side console to interact with the program (type choices and press Enter).

Notes about saved data:
- The program saves data to `accounts.txt` in the session’s working folder.
- In OnlineGDB, open the left “Files” panel to see `accounts.txt` after running.
- Data usually persists for your current OnlineGDB session/project. Starting a fresh session may not carry the file over.

Resetting data:
- In the left “Files” panel, right-click `accounts.txt` and delete it (or start a new OnlineGDB project).

## Menu Options (What to Type)
- 1 Create Account
  - Prompts for name (you can use spaces) and initial deposit (>= 0).
- 2 Deposit
  - Enter account ID (shown when you created the account) and an amount (> 0).
- 3 Withdraw
  - Enter account ID and an amount (> 0 and not more than balance).
- 4 Show Account Balance
  - Enter account ID to view details.
- 5 List All Accounts
  - Prints all stored accounts.
- 0 Exit
  - Saves data and quits.

### Example Session
```
==== Simple Bank Menu ====
1. Create Account
2. Deposit
3. Withdraw
4. Show Account Balance
5. List All Accounts
0. Exit
Enter your choice: 1
Enter account holder name: Alice
Enter initial deposit amount: 500
Account created successfully! Account ID: 1

Enter your choice: 2
Enter account ID: 1
Enter amount to deposit: 200
Deposit successful. New balance: 700.00

Enter your choice: 4
Enter account ID: 1

Account ID: 1
Name      : Alice
Balance   : 700.00

Enter your choice: 0
Saving data and exiting...
```

## File Format
`accounts.txt` stores one account per line:
```
<id>|<name>|<balance>
```
Example:
```
1|Alice|500.00
2|Bob|1200.50
```

## Project Structure
- `bank.c` - main program (menu, operations, file I/O)
- `accounts.txt` - data file (auto-created/updated when you save or exit)

## Troubleshooting (OnlineGDB)
- If a prompt looks “skipped,” press Enter once and continue.
- If you type letters where a number is expected, the program will show “Invalid input.” Try again with a number.
- Use a dot for decimals: `150.75` (not a comma).
- If the console freezes, click Stop, then Run again.

## Learning Highlights
- Structs to represent an `Account`
- Arrays to store accounts in memory
- Loops + switch-case for a menu-based UI
- File I/O to persist data across runs

## PPT (Presentation)
link it:
  - [Project Presentation](https://drive.google.com/file/d/1_x-C7lSgAFiiLzl1jxBTb1Taywu9XM0V/view?usp=sharing)
## License
MIT (or choose your preferred license)
