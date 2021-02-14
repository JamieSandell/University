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
    public partial class MainMenu : Form
    {
        ISystemControl system;
        private static int currentStaffID = 0; /* this should be read in from a file or count the number of
        employees */

        public MainMenu(ISystemControl inSystem)
        {
            system = inSystem;
            InitializeComponent();
        }

        private void doEditEmployee(IEmployee employee)
        {
            StaffMenu menu = new StaffMenu(employee);
            menu.ShowDialog();
        }

        private IEmployee doFindEmployee(string name)
        {
            IEmployee employee = system.FindEmployeeByName(StaffComboBox.Text);
            if (employee == null)
            {
                staffLabelBox.Text = "That Employee does not exist";
                return null;
            }
            return employee;
        }


        private void AddStaffButton_Click(object sender, EventArgs e)
        {
            if (system.FindEmployeeByName(StaffComboBox.Text) == null)
            {
                staffLabelBox.Text = "";
                IEmployee employee = new Employee(StaffComboBox.Text, currentStaffID);
                currentStaffID++;
                doEditEmployee(employee);
                system.AddEmployee(employee);
            }
            else
            {
                staffLabelBox.Text = "That Employee already exists";
            }

        }

        private void RemoveStaffButton_Click(object sender, EventArgs e)
        {            
            IEmployee employee = doFindEmployee(StaffComboBox.Text);
            if (employee == null)
            {
                return;
            }
            DialogResult result = MessageBox.Show("Are you sure you want to delete " + employee.GetName() + "?",
                "System Management", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            
            if (result == DialogResult.Yes)
            {
                staffLabelBox.Text = "";
                ArrayList tasks = employee.GetTaskInstances();
                foreach (ITaskAssign taskAssign in tasks)
                {
                    ITask task = taskAssign.GetTask();
                    task.RemoveStaff(taskAssign);
                }
                system.DeleteEmployee(employee);
            }
        }

        private void FindStaffButton_Click(object sender, EventArgs e)
        {
            IEmployee employee = doFindEmployee(StaffComboBox.Text);
            if (employee == null)
            {
                return;
            }
            else
            {
                doEditEmployee(employee);
            }
        }

        
        private void doEditTask(ITask task)
        {
            TaskMenu menu = new TaskMenu(task, system);
            menu.ShowDialog();
        }

        private ITask doFindTask(string name)
        {
            ITask task = system.FindTaskByName(TaskComboBox.Text);
            if (task == null)
            {
                TaskLabel.Text = "That task does not exist";
                return null;
            }
            return task;
        }

        private void AddTaskButton_Click(object sender, EventArgs e)
        {
            if (system.FindTaskByName(TaskComboBox.Text) == null)
            {
                TaskLabel.Text = "";
                ITask task = new Task(TaskComboBox.Text);
                doEditTask(task);
                system.AddTask(task);
            }
            else
            {
                TaskLabel.Text = "That task already exists";
            }
        }

        private void RemoveTaskButton_Click(object sender, EventArgs e)
        {
            ITask task = doFindTask(TaskComboBox.Text);
            if (task == null)
            {
                return;
            }
            DialogResult result = MessageBox.Show("Are you sure you want to delete " + task.GetTitle() + "?",
                "System Management", MessageBoxButtons.YesNo, MessageBoxIcon.Question);           
            if (result == DialogResult.Yes)
            {
                TaskLabel.Text = "";
                ArrayList staff = task.GetStaff();
                foreach (ITaskAssign taskAssign in staff)
                {
                    IEmployee employee = taskAssign.GetEmployee();
                    employee.RemoveTask(taskAssign);
                }
                system.DeleteTask(task);
            }
        }

        private void FindTaskButton_Click(object sender, EventArgs e)
        {
            ITask task = doFindTask(TaskLabel.Text);
            if (task == null)
            {
                return;
            }
            else
            {
                doEditTask(task);
            }
        }

        private void buttonReport_Click(object sender, EventArgs e)
        {
            IEmployee employee = doFindEmployee(StaffComboBox.Text);
            if (employee == null) // Couldn't be found
            {
                return;
            }
            StaffReportForm form = new StaffReportForm(employee);
            form.ShowDialog();
        }

        private void taskReportButton_Click(object sender, EventArgs e)
        {
            ITask task = doFindTask(TaskLabel.Text);
            if (task == null) // Couldn't be found
            {
                return;
            }
            else
            {
                TaskReportForm form = new TaskReportForm(task);
                form.ShowDialog();
            }
        }
        

        
    }
}