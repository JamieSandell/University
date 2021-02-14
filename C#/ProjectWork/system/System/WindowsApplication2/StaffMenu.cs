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
            textBoxStaffSalary.Text = Convert.ToString(employee.GetSalary());
            textBoxStaffWage.Text = Convert.ToString(employee.GetWage());

            // Get all instances of tasks the employee is involved with
            ArrayList arrayListTaskInstances = employee.GetTaskInstances();
            ITask task;
            string taskTitle;
            string dateAssigned;
            string hoursWorked;
            string percentCompleted;

            //Populate the listview box
            foreach (TaskAssign taskAssign in arrayListTaskInstances)
            {
                task = taskAssign.GetTask();
                taskTitle = task.GetTitle();
                dateAssigned = Convert.ToString(task.GetStartDate());
                hoursWorked = taskAssign.GetHours();
                percentCompleted = Convert.ToString(task.GetPercentageComplete(taskAssign, task));
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

        private void taskOkayButton_Click(object sender, EventArgs e)
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

        private void buttonStartTimer_Click(object sender, EventArgs e)
        {
            // I think this should be sending a message straight to TaskAssign

            /// TODO: Will since you know how to get information from the selected row this is
            /// what needs doing...
            /// when this button is clicked, get the selected row,
            /// extract the task's name, we will then need to find this instance,
            /// since we know it's a task belonging to a particular employee it should be
            /// a bit easier then expected.
            /// Now use the method
            /// taskAsssign.StartTimer();
            /// Do exactly the same for the StopTimer button.
            /// Thanks!
            /// P.S. Obviously if you show me how to get particular info from a listview box I can do the
            /// above if you want to tackle something else.
        }

        private void buttonEndTimer_Click(object sender, EventArgs e)
        {

        }
    }
}