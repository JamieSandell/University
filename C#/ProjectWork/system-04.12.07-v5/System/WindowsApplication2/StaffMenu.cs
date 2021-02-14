using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using SystemManagement;
namespace WindowsApplication1
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
            // Some of these need their own methods, or impliment polymorhpism
            employee.CheckName(textBoxStaffName.Text);
            employee.CheckAddress(textBoxStaffAddress1.Text);
            employee.CheckAddress(textBoxStaffAddress2.Text);
            employee.CheckName(textBoxStaffCounty.Text);
            employee.CheckName(textBoxStaffPostCode.Text);
            employee.CheckTelephone(textBoxStaffTelephone.Text);
            employee.CheckTelephone(textBoxStaffMobile.Text);
            employee.CheckSalary(Convert.ToDecimal(textBoxStaffSalary.Text));
            employee.CheckWage(Convert.ToDecimal(textBoxStaffWage.Text));
            return reply;
        }

        private void buttonStaffOk_Click(object sender, EventArgs e)
        {
            string reply = SaveForm();
            if (reply.Length > 0)
            {
                //there is an error somewhere
                MessageBox.Show(reply);
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
                MessageBox.Show("You have already started the timer for a task, please stop the timer if you wish to start a timer for another task.");
                return;
            }

            string taskName = taskNameTextBox.Text;
            taskAssign = FindTaskAssignInstance(taskName);
            if (taskAssign == null)
            {
                MessageBox.Show("Could not find selected Task");
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
                MessageBox.Show("You have not started the timer yet.");
                return;
            }
            timerStop = DateTime.Now;
            TimeSpan time = timerStop - timerStart;
            taskAssign.AppendHours(time);
            // reset timer
            timerStarted = false;          
            taskAssign = null;
        }


    }
}