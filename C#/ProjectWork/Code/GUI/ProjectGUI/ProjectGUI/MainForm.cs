using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProjectGUI
{
    struct StaffStruct
        {
            private string name;
            private decimal salary;
        }

    public partial class MainForm : Form
    {

        ArrayList staffNamesList = new ArrayList();
        ArrayList staffSalary = new ArrayList();
        ArrayList managerNamesList = new ArrayList();

        public MainForm()
        {
            InitializeComponent();

            

            staffNamesList.Add("Staff");
            staffSalary.Add(1000);
            managerNamesList.Add("Manager");

            for (int i = 0; i < staffNamesList.Count; i++)
            {
                listBoxLogon.Items.Add(staffNamesList[i]); // Add staff
            }

            for (int i = 0; i < managerNamesList.Count; i++) // Add managers
            {
                listBoxLogon.Items.Add(managerNamesList[i]);
            }

            listBoxLogon.Sorted = true; // Sort the list
            
        }

        public void MainForm_Load(object sender, EventArgs e)
        {  

        }

        public string Logon(string name, string reply)
        {
            if (name == "")
            {
                reply = "Did not select a name!";
                return reply;
            }
            // Are they a staff member?
            foreach (string s in staffNamesList)
            {
                if (s == name) // Got a staff member
                {
                    reply = "";
                    StaffForm form1 = new StaffForm();
                    form1.Show();
                    return reply;
                }
            }
            foreach (string s in managerNamesList)
            {
                if (s == name) // Got a manager
                {
                    reply = "";
                    ManagerForm managerForm = new ManagerForm();
                    managerForm.Show();
                    return reply;
                }
            }
            reply = "Was not a manager or staff!";
            return reply;
            
        }

        private void buttonLogon_Click(object sender, EventArgs e)
        {
            string reply = "";
            Logon(Convert.ToString(listBoxLogon.SelectedItem), reply);
            // Was there an error?
            if (reply != "")
            {
                MessageBox.Show(reply);
            }
        }

    }
}