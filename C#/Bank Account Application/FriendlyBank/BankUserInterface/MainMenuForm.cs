using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using AccountManagement;

namespace BankUserInterface
{
    public partial class MainMenuForm : Form
    {
        private int accountNumber = 0;

        IBank bank; 

        public MainMenuForm( IBank inBank)
        {
            bank = inBank;
            InitializeComponent();

        }

        private void doEditAccount(IAccount account)
        {
            AccountManageForm form = new AccountManageForm(account);

            form.ShowDialog();
        }

        private void doRemoveAccount(IAccount account)
        {
            bank.DeleteAccount(account);
        }

        private IAccount doFindAccount(string name)
        {
            
            IAccount account = bank.FindAccountByName(name);

            if (account == null)
            {
                return null;
            }

            return account;
        }

        private IAccount doFindAccountByNumber(int accountNumber)
        {
            try
            {
                IAccount account = bank.FindAccountByNumber(accountNumber);
                if (account == null)
                {
                    MessageBox.Show("Account for " + nameTextBox.Text + " not found");
                    return null;
                }

                return account;
            }
            catch
            {
                MessageBox.Show("Please enter a numeric value");
                return null;
            }
        }

        private void findButton_Click(object sender, EventArgs e)
        {
            string errorCaption = "Find Account Error:";
            string errorMessageFirstCharBlank = "The first character of an account name cannot be an empty space.";
            string errorMessage = "Account for " + nameTextBox.Text + " not found.";
            char[] ch = nameTextBox.Text.ToCharArray();
            int blankSpaceCounter = 0;

            IAccount account = doFindAccount(nameTextBox.Text);
            for (int i = 0; i < nameTextBox.Text.Length; i++)
            {
                if (ch[i].Equals(' '))
                {
                    blankSpaceCounter++;
                    if (ch[i].Equals(' ') && (blankSpaceCounter == 1)) // First character was a space?
                        {
                            MessageBox.Show(errorMessageFirstCharBlank, errorCaption,
                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                            return;
                        }
                }
            }
            if (account == null)
            {
                MessageBox.Show(errorMessage, errorCaption,
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }
            doEditAccount(account);
        }

        private void newAccountButton_Click(object sender, EventArgs e)
        {
            string validateText = nameTextBox.Text;
            string errorCaption = "Creating Account";
            string errorMessageAccountNameDuplicate = "The account name '" + nameTextBox.Text + "' already exists.";
            string reply = "";
            char[] ch = nameTextBox.Text.ToCharArray();


            reply = reply + bank.ValidateAccountName(validateText);
            if (reply == "")
            {
                IAccount account2 = bank.FindAccountByName(nameTextBox.Text); // Easy to check for duplicates
                if (account2 != null) // Use account2 because account is already defined
                {
                    MessageBox.Show(errorMessageAccountNameDuplicate, errorCaption,
                        MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
                else
                {
                    accountNumber++; // Unique account number for each account created
                    IAccount account = new Account(nameTextBox.Text, "", accountNumber);
                    doEditAccount(account); // Load edit account form
                    bank.AddAccount(account); // Add the account
                }
            }
            else
            {
                MessageBox.Show(reply, errorCaption,
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void findAccountByNumberButton_Click(object sender, EventArgs e) // Need to add validation, try/catch
        {

            try
            {   // Find the account, if found edit it
                IAccount account = doFindAccountByNumber(Int32.Parse(nameTextBox.Text));
                if (account == null)
                {
                    return;
                }
                doEditAccount(account);
            }
            catch
            {
                MessageBox.Show("Please enter an account number to search for.");
            }
        }

        private void removeAccountByNumberButton_Click(object sender, EventArgs e)
        {
            try
            {   // Find the account, if found remove it
                IAccount account = doFindAccountByNumber(Int32.Parse(nameTextBox.Text));
                if (account == null)
                {
                    return;
                }
                doRemoveAccount(account);
            }
            catch
            {
                MessageBox.Show("Please enter an account number to remove.");
            }
        }
    }
}