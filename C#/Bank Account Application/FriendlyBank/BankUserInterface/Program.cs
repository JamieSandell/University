using System;
using System.Collections.Generic;
using System.Windows.Forms;
using AccountManagement;

namespace BankUserInterface
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            IBank bank = new Bank();

            Application.Run(new MainMenuForm(bank));
        }
    }
}