using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

/// TODO:
/// It should not be possible to pay in a negative amount of funds - DONE
/// It should not be possible to withdraw a negative amount of funds - DONE
/// It should not be possible to withdraw more money that is in an account - DONE
/// It should not be possible to create a name which contains numeric digits - DONE
/// Accounts need to hold an overdraft value which gives the amount of overdraft  that that account
/// holder is allowed - DONE
/// An overdraft value of 50 pounds would mean that the account holder could have their balance
/// go as far negative as -50 - DONE
/// An account overdraft value should be held in each account that is created. It can be set in the user
/// interface of an account, must enter negative value - DONE
/// When the balance of an account is displayed the balance should be displayed in red if the account
/// balance is less than 0 pounds - DONE
/// This is not a function of the Account class, it should happen in the user interface - DONE
/// It should not be possible to create two accounts with the same name - DONE
/// The Bank class should prohibit this - DONE
/// Any attempt to add an account with the same name as an existing one should fail - DONE
/// Sort out and complete the test harness - NOT DONE
/// The forms should be a fixed size - NOT DONE
/// Find Account buttons need validation - DONE
/// Bank accounts could have an account number as well as an account holder name. This number should be
/// unique for every account. It should be possible to find an account in the bank based on the account
/// number instead of the name - DONE
/// Fix changing an account name - DONE
/// Add author info etc - NOT DONE
/// Need validation for CheckName/SetName, i.e. Account Edit form - DONE
/// If an account is deleted, the other account numbers should not decrease - NOT DONE
/// The bank account information could be stored in a file when the program exits and loaded again when
/// the program starts - NOT DONE
/// Add a logon screen - NOT DONE

namespace AccountManagement
{

    public interface IAccount
    {
        /// <summary>
        /// Checks to see if a name is valid
        /// </summary>
        /// <param name="inName">The name to be tested.</param>
        /// <returns>An empty string if the name is valid, otherwise an error 
        /// message about why the name is incorrect</returns>
        string CheckName(string inName);

        /// <summary>
        /// Sets the name of the account holder. Calls CheckName to make
        /// sure that it is valid.
        /// </summary>
        /// <param name="inName">The name to be set.</param>
        /// <returns>An empty string if the change has worked, otherwise
        /// an error message</returns>
        string SetName(string inName);

        /// <summary>
        /// Gets the name of the account holder.
        /// </summary>
        /// <returns>The name as presently held in the account.</returns>
        string GetName();

        /// <summary>
        /// Gets the number of the account holder.
        /// </summary>
        /// <returns>The number as presently held in the account.</returns>
        int GetAccountNumber();

        /// <summary>
        /// Checks to see if an addres is valid
        /// </summary>
        /// <param name="inAddress">The address to be checked</param>
        /// <returns>An empty string if the address is valid, otherwise an error
        /// message describing why the address is incorrect</returns>
        string CheckAddress(string inAddress);

        /// <summary>
        /// Sets the address to the given string. Calls CheckAddress to 
        /// make sure the address is valid.
        /// </summary>
        /// <param name="inAddress">The address to be set</param>
        /// <returns>An empty string if the address is valid, otherwise an error
        /// message describing why the address is incorrect.</returns>
        string SetAddress(string inAddress);

        /// <summary>
        /// Gets the address of the account holder.
        /// </summary>
        /// <returns>The address as a string</returns>
        string GetAddress();

        /// <summary>
        /// Pay funds into the account.
        /// </summary>
        /// <param name="amount">The amount to be paid in</param>
        /// <param name="inTheRed">Used to see if the balance is less than 0 and set an appropriate text colour</param>
        /// <returns>An empty string if the funds have been paid in. An error message if the
        /// paying in process fails.</returns>
        string PayInFunds(decimal amount, ref bool inTheRed);

        /// <summary>
        /// Withdraw funds from the account.
        /// </summary>
        /// <param name="amount">The amount to be withdrawn</param>
        /// <param name="inTheRed">Used to see if the balance is less than 0 and set an appropriate text colour</param>
        /// <returns>An empty string if the funds were withdrawn OK. An error message if 
        /// the withdrawal was rejected.</returns>
        string WithdrawFunds(decimal amount, ref bool inTheRed);

        /// <summary>
        /// Get the account balance
        /// </summary>
        /// <returns>The value of the balance</returns>
        decimal GetBalance();

        /// <summary>
        /// Get the account overdraft
        /// </summary>
        /// <returns>The value of the overdraft</returns>
        decimal GetOverdraft();

        /// <summary>
        /// Set the overdraft limit of the account
        /// </summary>
        /// <param name="amount">The amount to set the overdraft limit to</param>
        /// <param name="inTheRed">Used to see if the balance is less than 0</param>
        /// <returns>An empty string if the funds were withdrawn OK. An error message if
        /// the withdrawal was rejected.</returns>
        string SetOverdraft(decimal amount, ref bool inTheRed);

        /// <summary>
        /// Get the available funds of the account
        /// </summary>
        /// <returns>The amount of funds available</returns>
        decimal GetAvailableFunds();

    }

    public class Account : IAccount
    {
        #region Name management

        private string name;
        private int accountNumber = 0;

        public string CheckName(string inName) // Validate the name
        {
            bool textIsANumber = false;
            string errorMessageAccountNameContainedNumbers = "Account creation failed because the account name contained a numeric value.";
            string errorMessageFirstCharBlank = "The first character of an account name cannot be an empty space.";
            string errorMessageEmpty = "The name field was empty.";
            string errorMessage = "Account for " + name + " not found.";
            char[] ch = inName.ToCharArray();

            if (inName.Length == 0) // Did they enter anything?
            {
                return errorMessageEmpty;
            }

            for (int i = 0; i < ch.Length; i++) // This validation routine was adapted from a website
            // that gave me the idea - http://www.eggheadcafe.com/community/aspnet/2/84982/using-tochararray.aspx
            {
                if (Char.IsDigit(ch[i]) == true) // Check for any numbers entered
                {
                    textIsANumber = true;
                    break;
                }
            }

            if (textIsANumber)
            {
                // Contained a number
                return errorMessageAccountNameContainedNumbers;
            }

            if (ch[0].Equals(' ')) // First character was a space?
            {
                return errorMessageFirstCharBlank;
            }

            return ""; // If here, everything went well
        }
        public string SetName(string inName)
        {
            name = inName;
            return "";
        }

        public string GetName()
        {
            return name;
        }

        public int GetAccountNumber()
        {
            return accountNumber;
        }

        #endregion 

        #region Address management

        private string address;

        public string CheckAddress(string inAddress)
        {
            string errorMessageEmptyAddress = "The address field was empty.";

            if (inAddress.Length == 0)
            {
                return errorMessageEmptyAddress;
            }
            return "";
        }

        public string SetAddress(string inAddress)
        {
            address = inAddress;
            return "";
        }

        public string GetAddress()
        {
            return address;
        }

        #endregion

        #region Balance management

        private decimal balance = 0;
        private decimal overdraftLimit = -50; // -50 by default
        private decimal availableFunds = 0;

        public string PayInFunds(decimal amount, ref bool inTheRed)
        {

            if (amount < 0)
            {
                return "You cannot pay in a negative amount of funds.";
            }
            if (amount == 0)
            {
                return "You cannot pay in zero funds.";
            }
            else
            {
                balance += amount;
                if (balance > -1)
                {
                    inTheRed = false;
                }
                return "";
            }
        } //  need inTheRed to set black colour back

        public string WithdrawFunds(decimal amount, ref bool inTheRed)
        {

            if (amount < 0)
            {
                return "You cannot withdraw a negative amount of funds.";
            }
            if (amount == 0)
            {
                return "You cannot withdraw zero amount of funds.";
            }
            if (amount > (balance - overdraftLimit))
            {
                return "That amount exceeds your withdrawal limit.";
            }
            else // everything worked and the amount needs deducting from the balance
            {
                balance -= amount;
                if (balance < 0)
                {
                    inTheRed = true; // bool flag for setting the appropriate colour
                }
                return "";
            }
        }

        public decimal GetBalance()
        {
            return balance;
        }

        public decimal GetOverdraft()
        {
            return overdraftLimit;
        }

        public string SetOverdraft(decimal amount, ref bool inTheRed) // Need to fix the red colour issue
        {

            if (amount > -1)
            {
                return "Error: Overdraft value must be 0 or a negative value";
            }

            if((balance < 0) && (amount > overdraftLimit )) // To ensure available funds is never a negative number
            {
                return "Error: The overdraft value cannot be less then the currently available funds.";
            }
            else
            {
                overdraftLimit = amount;
                if (balance < 0)
                {
                    inTheRed = true;
                }
                else
                {
                    inTheRed = false;
                }
                return ""; // Everything went ok
            }
        }

        public decimal GetAvailableFunds()
        {
            availableFunds = balance - overdraftLimit;
            return availableFunds;
        }

        #endregion 

        public Account(string inName, string inAddress, int inAccountNumber)
        {
            name = inName;
            address = inAddress;
            accountNumber = inAccountNumber;
        }
    }

    public interface IBank
    {
        /// <summary>
        /// Add an account to the bank
        /// </summary>
        /// <param name="account">The account to be stored</param>
        /// <returns>An empty string if the account was added correctly, otherwise
        /// an error message.</returns>
        string AddAccount(IAccount account);

        /// <summary>
        /// Delete an account from the bank
        /// </summary>
        /// <param name="account">The account to be deleted</param>
        /// <returns>An empty string if the account was deleted, otherwise 
        /// an error message.</returns>
        string DeleteAccount(IAccount account);

        /// <summary>
        /// Find an account by account holder name
        /// </summary>
        /// <param name="name">The name of the account holder</param>
        /// <returns>The account found, or a null reference if the account
        /// could not be located.</returns>
        IAccount FindAccountByName(string name);

        /// <summary>
        /// Find an account by account holder number
        /// </summary>
        /// <param name="accountNumber">The number of the account holder</param>
        /// <returns>The account found, or a null reference if the account
        /// could not be located.</returns>
        IAccount FindAccountByNumber(int accountNumber);

        /// <summary>
        /// Validate the name of the account to add
        /// </summary>
        /// <param name = "accountName">The name of the account to validate</param>
        /// <returns>An empty string if the if the name is valud. An error message if
        /// the name was invalid</returns>
        string ValidateAccountName(string accountName);
    }

    public class Bank : IBank
    {
        private Hashtable customerAccounts = new Hashtable(); // Setup the hashtables for name and number storage
        private Hashtable customerAccountsNumber = new Hashtable();

        public IAccount FindAccountByName(string name)
        {
            return customerAccounts[name] as IAccount;
        }

        public IAccount FindAccountByNumber(int accountNumber)
        {
            return customerAccountsNumber[accountNumber] as IAccount;
        }

        public string AddAccount(IAccount account)
        {
            customerAccounts.Add(account.GetName(), account);
            customerAccountsNumber.Add(account.GetAccountNumber(), account);
            return "";
        }

        public string DeleteAccount(IAccount account)
        {
            customerAccounts.Remove(account.GetName());
            customerAccountsNumber.Remove(account.GetAccountNumber());
            return "";
        }

        public string ValidateAccountName(string name)
        {
            bool textIsANumber = false;
            string errorMessageAccountNameContainedNumbers = "Account creation failed because the account name contained a numeric value.";
            string errorMessageFirstCharBlank = "The first character of an account name cannot be an empty space.";
            string errorMessageEmpty = "You didn't enter anything.";
            string errorMessage = "Account for " + name + " not found.";
            char[] ch = name.ToCharArray();

            for (int i = 0; i < ch.Length; i++) // This validation routine was adapted from a website
            // that gave me the idea - http://www.eggheadcafe.com/community/aspnet/2/84982/using-tochararray.aspx
            {
                if (Char.IsDigit(ch[i]) == true) // Did they enter a digit?
                {
                    textIsANumber = true;
                    break;
                }
            }

            if (textIsANumber)
            {
                // Contained a number
                return errorMessageAccountNameContainedNumbers;
            }

            if (ch[0].Equals(' ')) // First character was a space?
            {
                return errorMessageFirstCharBlank;
            }

            if (name.Length == 0) // Didn't enter anything
            {
                return errorMessageEmpty;
            }
            else
            {
                return ""; // If here, everything went well
            }


        }
    }
}
