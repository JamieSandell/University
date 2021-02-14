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
    public partial class TaskMenu : Form
    {
        private ITask task;
        private ISystemControl system;

        public TaskMenu(ITask task, ISystemControl system)
        {
            InitializeComponent();
            this.task = task;
            this.system = system;
            LoadForm();
        }

        private void LoadForm()
        {
            taskNameTextBox.Text = task.GetTitle();
            commentsTextBox.Text = task.GetDescription();
            taskSetDateBox.Text = task.GetStartDate().ToString();
            taskDueDateBox.Text = task.GetEndDate().ToString();
            taskCompleteDateBox.Text = task.GetCompleteDate().ToString();
            taskCompleteCheckBox.Checked = task.GetTaskCompleted();

            if (!taskCompleteCheckBox.Checked)
            {
                taskCompleteDateBox.Enabled = false;
            }

            LoadListBox();        
        }

        private string SaveForm()
        {
            string reply = CheckForm();
            if (reply.Length > 0) 
            {
                return reply; // an error has occured somewhere
            }
            task.SetTitle(taskNameTextBox.Text);
            task.SetDescription(commentsTextBox.Text);
            task.SetStartDate(taskSetDateBox.Value);
            task.SetEndDate(taskDueDateBox.Value);
            task.SetTaskCompleted(taskCompleteCheckBox.Checked);
            task.SetCompleteDate(taskCompleteDateBox.Value);
            return ""; //everything is fine
        }

        private string CheckForm()
        {
            string reply = "";
            string oldReply = "";
            reply += task.CheckTitle(taskNameTextBox.Text);
            if (reply.Length > 0)
            {
                reply += "\r\n";
            }
            oldReply = reply;
            reply += task.CheckEndDate(taskSetDateBox.Value, taskDueDateBox.Value);
            if (oldReply != reply) /* if oldReply does not equal reply then a new error message has
                occured and needs a breakline between it and the previous one */
            {
                reply += "\r\n";
            }
            oldReply = reply;
            reply += task.CheckEndDate(taskSetDateBox.Value, taskCompleteDateBox.Value);
            if (oldReply != reply)
            {
                reply += "\r\n";
            }
            reply += task.CheckDescription(commentsTextBox.Text);
            return reply; // if everything is fine reply will still be an empty string, otherwise contains error message
        }        

        private void taskOkayButton_Click(object sender, EventArgs e)
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

        private void doEditTaskAssignment(ITaskAssign taskAssign)
        {
            StaffAssignmentMenu menu = new StaffAssignmentMenu(taskAssign);
            menu.ShowDialog();
        }

        private void taskCancelButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void addStaffButton_Click(object sender, EventArgs e)
        {
            if (assignedEmployeesList.FindItemWithText(EmployeeNameTextBox.Text) != null)
            {
                MessageBox.Show("System Management",
                    "Invalid Employee : That employee is already assigned to this task",
                        MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            if (system.FindEmployeeByName(EmployeeNameTextBox.Text) == null)
            {
                MessageBox.Show("System Management",
                    "Invalid Employee : That employee does not exist on the system",
                        MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            // if here is reached everything okay.
            IEmployee employee = system.FindEmployeeByName(EmployeeNameTextBox.Text);
            ITaskAssign taskAssign = new TaskAssign(task, employee); // creates a new taskAssign instance 
            system.AssignEmployeeToTask(taskAssign, task, employee); // adds the new taskAssign to the relevant Employee and task instances
            doEditTaskAssignment(taskAssign);
            UpdateListBox();            
        }

        private ITaskAssign FindTaskAssign(IEmployee employee)
        {
            ArrayList staff = task.GetStaff();
            for (int i = 0; i < staff.Count; i++)
            {
                ITaskAssign taskAssign = (ITaskAssign)staff[i];
                if (taskAssign.GetEmployee() == employee)   // runs through all the taskAssigns in the task instance
                {                                           // and finds the one for the Employee selected
                    return taskAssign;
                }
            }
            return null;
        }

        private void removeStaffButton_Click(object sender, EventArgs e)
        {
            if (assignedEmployeesList.FindItemWithText(EmployeeNameTextBox.Text) == null)
            {
                return;
            }
            IEmployee employee = system.FindEmployeeByName(EmployeeNameTextBox.Text);
            ITaskAssign taskAssign = FindTaskAssign(employee); 
            system.UnassignEmployeeToTask(taskAssign, task, employee); // removes the taskAssign
            ListViewItem item = assignedEmployeesList.FindItemWithText(EmployeeNameTextBox.Text);
            item.Remove();
            return;            
        }

        private void unassignStaffButton_Click(object sender, EventArgs e)
        {
            if (EmployeeNameTextBox.Text.Length == 0)
            {
                return;
            }
            if (assignedEmployeesList.FindItemWithText(EmployeeNameTextBox.Text) == null)
            {
                MessageBox.Show("System Management",
                    "Invalid Employee : That user is not currently assigned to this task",
                        MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            IEmployee employee = system.FindEmployeeByName(EmployeeNameTextBox.Text);
            ITaskAssign taskAssign = FindTaskAssign(employee);
            doEditTaskAssignment(taskAssign);            
            UpdateListBox();
            return;
        }

        private void LoadListBox()
        {
            ArrayList employee = task.GetStaff();
            foreach (ITaskAssign taskAssign in employee)
            {
                IEmployee employees = taskAssign.GetEmployee();
                string employeeName = employees.GetName();
                string dateAssigned = taskAssign.GetDateAssigned().ToString();
                string hoursWorked = taskAssign.GetHours().ToString();
                string dateUnassigned = taskAssign.GetDateUnassigned().ToString();
                string percentCompleted = taskAssign.GetPercentageComplete().ToString();
                // Add this to the listview box
                assignedEmployeesList.Items.Add(new ListViewItem(new string[] { employeeName, dateAssigned,
                dateUnassigned, hoursWorked, percentCompleted}));                
            }
        }

        private void UpdateListBox()
        {
            assignedEmployeesList.Items.Clear();           
            LoadListBox();
        }

        private void taskCompleteCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (taskCompleteCheckBox.Checked)
            {
                taskCompleteDateBox.Enabled = true;
            }
            else
            {
                taskCompleteDateBox.Enabled = false;
            }

        }
        
    }
}