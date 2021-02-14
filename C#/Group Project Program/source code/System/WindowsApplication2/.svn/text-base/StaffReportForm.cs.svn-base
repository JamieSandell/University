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
    public partial class StaffReportForm : Form
    {
        private IEmployee employee;

        public StaffReportForm(IEmployee employee)
        {
            InitializeComponent();
            this.employee = employee;
            LoadForm();
        }

        public void LoadForm()
        {
            textBoxStaffName.Text = employee.GetName();
            // Get all instances of tasks the employee is involved with
            ArrayList arrayListTaskInstances = employee.GetTaskInstances();

            //Populate the listview box
            foreach (ITaskAssign taskAssign in arrayListTaskInstances)
            {
                ITask task = taskAssign.GetTask();
                string taskTitle = task.GetTitle();
                string dateAssigned = task.GetStartDate().ToString();
                int hoursWorked = Convert.ToInt32(taskAssign.GetHours());
                decimal salary = employee.GetSalary();
                decimal costPerTask = salary / hoursWorked;
                string costPerTaskString = Convert.ToString(costPerTask);
                string percentCompleted = taskAssign.GetPercentageComplete().ToString();
                // Add this to the listview box
                listViewStaffReport.Items.Add(new ListViewItem(new string[] { taskTitle, percentCompleted,
                costPerTaskString}));
            }
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}