using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using PalindromeEngine;

namespace PalindromeUserInterface
{
    public partial class MainMenuForm : Form
    {
        IPalindrome palindrome;

        public MainMenuForm( IPalindrome inPalindrome)
        {
            palindrome = inPalindrome;
            InitializeComponent();
        }

        private void MainMenuForm_Load(object sender, EventArgs e)
        {

        }

        private void buttonVerify_Click(object sender, EventArgs e)
        {
            string textToVerify = textBoxVerify.Text; // Get the entered text to verify
            bool isPalindrome = false; // Status of the verification

            palindrome.VerifyText(textToVerify, out isPalindrome);
            if (isPalindrome == false)
            {
                textBoxResult.Text = "Not a palindrome!";
            }
            else
            {
                textBoxResult.Text = "Palindrome!";
            }
        }



    }
}