using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using SystemManagement;
namespace SystemUserInterface
{
    public partial class StaffMenu : Form
    {
        private IEmployee employee;
        

        public StaffMenu(IEmployee employee)
        {
            InitializeComponent();
            this.employee = employee;            
            LoadForm();
        }

        public void LoadForm()
        {
            textBoxStaffID.Text = employee.GetEmployeeID();
            textBoxStaffName.Text = employee.GetName();
            textBoxStaffAddress1.Text = employee.GetAddress1();
            textBoxStaffAddress2.Text = employee.GetAddress2();
            textBoxStaffCounty.Text = employee.GetCounty();
            textBoxStaffPostCode.Text = employee.GetPostcode();
            textBoxStaffTelephone.Text = employee.GetTelephone();
            textBoxStaffMobile.Text = employee.GetMobile();
            textBoxStaffSalary.Text = employee.GetSalary().ToString();
            textBoxStaffWage.Text = employee.GetWage().ToString();

            // Get all instances of tasks the employee is involved with
            ArrayList arrayListTaskInstances = employee.GetTaskInstances();

            //Populate the listview box
            foreach (ITaskAssign taskAssign in arrayListTaskInstances)
            {
                ITask task = taskAssign.GetTask();
                string taskTitle = task.GetTitle();
                string dateAssigned = task.GetStartDate().ToString();
                string hoursWorked = taskAssign.GetHours().ToString();
                string percentCompleted = taskAssign.GetPercentageComplete().ToString();
                // Add this to the listview box
                listViewStaffTasksAssignedTo.Items.Add(new ListViewItem(new string[] { taskTitle, dateAssigned,
                hoursWorked, percentCompleted}));
            }
        }

        private string SaveForm()
        {
            string reply = CheckForm();
            if (reply.Length > 0)
            {
                return reply;
            }
            // Things to save
            employee.SetEmployeeID(textBoxStaffID.Text);
            employee.SetName(textBoxStaffName.Text);
            employee.SetAddress1(textBoxStaffAddress1.Text);
            employee.SetAddress2(textBoxStaffAddress2.Text);
            employee.SetCounty(textBoxStaffCounty.Text);
            employee.SetPostcode(textBoxStaffPostCode.Text);
            employee.SetTelephone(textBoxStaffTelephone.Text);
            employee.SetMobile(textBoxStaffMobile.Text);
            employee.SetSalary(Convert.ToDecimal(textBoxStaffSalary.Text));
            employee.SetWage(Convert.ToDecimal(textBoxStaffWage.Text));
            
            return "";
        }

        private string CheckForm()
        {
            string reply = "";
            string oldReply = "";
            // Some of these need their own methods, or impliment polymorhpism
            reply += employee.CheckName(textBoxStaffName.Text); // puts the text on a new line
            if (reply.Length > 0)
            {
                reply += "\r\n";
            }
            oldReply = reply;
            reply += employee.CheckAddress(textBoxStaffAddress1.Text);
            if (oldReply != reply) /* if oldReply does not equal reply then a new error message has
                occured and needs a breakline between it and the previous one */
            {
                reply += "\r\n";
            }
            oldReply = reply;
            reply += employee.CheckAddress(textBoxStaffAddress2.Text);
            if (oldReply != reply)
            {
                reply += "\r\n";
            }
            oldReply = reply;
            reply += employee.CheckCounty(textBoxStaffCounty.Text);
            if (oldReply != reply)
            {
                reply += "\r\n";
            }
            oldReply = reply;
            reply += employee.CheckPostCode(textBoxStaffPostCode.Text);
            if (oldReply != reply)
            {
                reply += "\r\n";
            }
            oldReply = reply;
            reply += employee.CheckTelephone(textBoxStaffTelephone.Text);
            if (oldReply != reply)
            {
                reply += "\r\n";
            }
            oldReply = reply;
            reply += employee.CheckMobile(textBoxStaffMobile.Text);
            if (oldReply != reply)
            {
                reply += "\r\n";
            }
            oldReply = reply;
            reply += employee.CheckSalary(Convert.ToDecimal(textBoxStaffSalary.Text));
            if (oldReply != reply)
            {
                reply += "\r\n";
            }
            reply += employee.CheckWage(Convert.ToDecimal(textBoxStaffWage.Text));
            oldReply = "";
            return reply;
        }

        private void buttonStaffOk_Click(object sender, EventArgs e)
        {
            string reply = SaveForm();
            if (reply.Length > 0)
            {
                //there is an error somewhere
                MessageBox.Show(reply, "System Management", MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
                return;
            }
            Close();
        }

        private void buttonStaffCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private bool timerStarted = false;
        private DateTime timerStart;
        private DateTime timerStop;
        private ITaskAssign taskAssign;

        private void buttonStartTimer_Click(object sender, EventArgs e)
        {
            if (timerStarted)
            {
                MessageBox.Show("Invalid Timer : You have already started the timer for a task, please stop the timer if you wish to start a timer for another task.",
                    "System Management", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            string taskName = taskNameTextBox.Text;
            taskAssign = FindTaskAssignInstance(taskName);
            if (taskAssign == null)
            {
                MessageBox.Show("Invalid Task : Could not find selected Task",
                    "System Management", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            timerStarted = true;
            timerStart = DateTime.Now;
        }

        private ITaskAssign FindTaskAssignInstance(string name)
        {
            ArrayList tasks = employee.GetTaskInstances();
            foreach (ITaskAssign taskAssign in tasks)
            {
                ITask task = taskAssign.GetTask();
                if (task.GetTitle() == name)
                {
                    return taskAssign;
                }                
            }
            return null;
        }

        private void buttonEndTimer_Click(object sender, EventArgs e)
        {
            if (!timerStarted)
            {
                MessageBox.Show("Invalid Timer : You have not started the timer yet.",
                    "System Management", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            timerStop = DateTime.Now;
            TimeSpan time = timerStop - timerStart;
            taskAssign.AppendHours(time);
            // reset timer
            timerStarted = false;          
            taskAssign = null;
        }

        private void buttonStaffCancel_Click_1(object sender, EventArgs e)
        {
            Close();
        }


    }
}