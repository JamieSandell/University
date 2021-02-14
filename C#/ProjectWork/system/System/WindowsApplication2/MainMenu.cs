using System;
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
                IEmployee employee = new Employee(StaffComboBox.Text);
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
            else
            {
                staffLabelBox.Text = "";
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
            TaskMenu menu = new TaskMenu(task);
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
            else
            {
                TaskLabel.Text = "";
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



        
    }
}