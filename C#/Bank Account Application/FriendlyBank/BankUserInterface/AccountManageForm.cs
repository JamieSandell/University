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
    public partial class AccountManageForm : Form
    {
        IAccount account;

        /// <summary>
        /// Constructor for the form
        /// </summary>
        /// <param name="inAccount">The account being managed</param>
        public AccountManageForm(IAccount inAccount)
        {
            InitializeComponent();
            account = inAccount;
            loadForm();
        }

        /// <summary>
        /// Loads the account into the form. 
        /// </summary>
        private void loadForm()
        {
            nameTextBox.Text = account.GetName();
            addressTextBox.Text = account.GetAddress();
            balanceValueLabel.Text = account.GetBalance().ToString();
            availableFundsValueLabel.Text = account.GetAvailableFunds().ToString();
            overdraftLimitValueLabel.Text = account.GetOverdraft().ToString();
            accountNumberValueLabel.Text = account.GetAccountNumber().ToString();
        }

        /// <summary>
        /// Saves the form back into the account
        /// </summary>
        /// <returns>an empty string if it worked. An error message if 
        /// the save could not be performed</returns>
        private string saveForm()
        {
            string reply = checkForm();
            if (reply.Length > 0)
            {
                return reply;
            }

            account.SetName(nameTextBox.Text);

            account.SetAddress(addressTextBox.Text);

            return "";
        }

        /// <summary>
        /// Checks that the form contains valid data. 
        /// </summary>
        /// <returns>An error message describing what is wrong with the form
        /// </returns>
        private string checkForm () 
        {

            string reply = "";

            reply = reply + account.CheckName(nameTextBox.Text);

            reply = reply + account.CheckAddress(addressTextBox.Text);

            return reply;
        }

        private void doneButton_Click(object sender, EventArgs e)
        {
            string errorCaption = "Account Edit Error";

            string reply = saveForm();
            if (reply.Length > 0)
            {
                // we have an error somewhere in our data
                MessageBox.Show(reply, errorCaption,
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }
            Close();
        }

        private void withdrawButton_Click(object sender, EventArgs e)
        {
            string reply = "";
            string errorCaption = "Withdraw Funds Error";
            string errorMessageInvalidAmount = "Invalid amount : ";
            decimal amount = 0;
            bool inTheRed = false;

            try
            {
                amount = decimal.Parse(amountTextBox.Text);
            }
            catch
            {
                MessageBox.Show(errorMessageInvalidAmount + amountTextBox.Text, errorCaption,
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }
            reply = reply + account.WithdrawFunds(amount, ref inTheRed);
            if (reply != "") // Something went wrong
            {
                MessageBox.Show(reply, errorCaption,
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            else
            {
                balanceValueLabel.Text = account.GetBalance().ToString(); // Update the balance label
                if (inTheRed)
                {
                    balanceValueLabel.ForeColor = Color.Red;
                }
                else
                {
                    balanceValueLabel.ForeColor = Color.Black;
                }
                availableFundsValueLabel.Text = account.GetAvailableFunds().ToString(); // Update the funds available
            }
        }

        private void payInButton_Click(object sender, EventArgs e)
        {
            string errorCaption = "Pay In Funds Error";
            string errorMessageInvalidAmount = "Invalid amount : ";
            string reply = "";
            decimal amount = 0;
            bool inTheRed = false;

            try // leave this in but add valiation that checks for letters etc
            {
                amount = decimal.Parse(amountTextBox.Text);
            }
            catch
            {
                MessageBox.Show(errorMessageInvalidAmount + amountTextBox.Text, errorCaption,
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }
            reply = reply + account.PayInFunds(amount, ref inTheRed);
            if (reply != "") // Something went wrong
            {
                MessageBox.Show(reply, errorCaption,
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            else
            {
                if (inTheRed)
                {
                    balanceValueLabel.ForeColor = Color.Red;
                }
                else
                {
                    balanceValueLabel.ForeColor = Color.Black;
                }
            }
            balanceValueLabel.Text = account.GetBalance().ToString();
            availableFundsValueLabel.Text = account.GetAvailableFunds().ToString(); // Update the funds available

        }

        private void setOverdraftButton_Click(object sender, EventArgs e)
        {
            string errorCaption = "Set Overdraft Error";
            string errorMessageInvalidAmount = "Invalid amount : ";
            string reply = "";
            decimal amount = 0;
            bool inTheRed = false;

            try // leave this in but add validation that checks for letters etc
            {
                amount = decimal.Parse(amountTextBox.Text);
            }
            catch
            {
                MessageBox.Show(errorMessageInvalidAmount + amountTextBox.Text, errorCaption,
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }
            // If all went well try and set the overdraft
            reply = reply + account.SetOverdraft(amount, ref inTheRed);
            if (reply != "") // If something went wrong
            {
                MessageBox.Show(reply, errorCaption, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            else // Everything worked
            {
                overdraftLimitValueLabel.Text = account.GetOverdraft().ToString(); // Set the appropriate label colour
                if (inTheRed)
                {
                    balanceValueLabel.ForeColor = Color.Red;
                }
                else
                {
                    balanceValueLabel.ForeColor = Color.Black;
                }
                availableFundsValueLabel.Text = account.GetAvailableFunds().ToString(); // Update the funds available
            }
        }

        private void overdraftLabel_Click(object sender, EventArgs e)
        {

        }

    }
}