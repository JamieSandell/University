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
    public partial class TaskReportForm : Form
    {
        private ITask task;

        public TaskReportForm(ITask task)
        {
            InitializeComponent();
            this.task = task;
            LoadForm();
        }

        private void LoadForm()
        {
            taskTitleLabel.Text = task.GetTitle();
            taskStartDateLabel.Text = task.GetStartDate().Date.ToString();
            taskDueDateLabel.Text = task.GetEndDate().Date.ToString();
            if (task.GetTaskCompleted())
            {
                taskCompletionDateLabel.Text = task.GetCompleteDate().Date.ToString();
            }
            taskCompletionPercentageLabel.Text = CalculateAverageCompletion().ToString();
            LoadListBox();
        }

        private void LoadListBox()
        {            
            ArrayList staff = task.GetStaff();            
            foreach (ITaskAssign taskAssign in staff)
            {
                IEmployee employee = taskAssign.GetEmployee();
                string employeeName = employee.GetName();
                string percentCompleted = taskAssign.GetPercentageComplete().ToString();                
                // Add this to the listview box
                assignedEmployeesList.Items.Add(new ListViewItem(new string[] {employeeName, percentCompleted}));
            }
        }

        private decimal CalculateAverageCompletion()
        {
            decimal totalPercentage = 0;
            int counter = 0;
            ArrayList staff = task.GetStaff();
            foreach (ITaskAssign taskAssign in staff)
            {
                totalPercentage += taskAssign.GetPercentageComplete();
                counter++;
            }
            return (totalPercentage / counter); 
        }

        private void okayButton_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}