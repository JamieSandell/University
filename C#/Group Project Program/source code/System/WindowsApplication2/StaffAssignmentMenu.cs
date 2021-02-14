using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using SystemManagement;

namespace SystemUserInterface
{
    public partial class StaffAssignmentMenu : Form
    {
        private ITaskAssign taskAssign;

        public StaffAssignmentMenu(ITaskAssign taskAssign)
        {
            InitializeComponent();
            this.taskAssign = taskAssign;
            LoadForm();
        }

        private void LoadForm()
        {
            IEmployee employee = taskAssign.GetEmployee();
            employeeNameLabel.Text = employee.GetName();      // loads employee name and task title
            ITask task = taskAssign.GetTask();
            taskNameLabel.Text = task.GetTitle();           

            dateAssignedBox.Text = taskAssign.GetDateAssigned().ToString();
            dateUnassignedBox.Text = taskAssign.GetDateUnassigned().ToString();
            percentUpDownBox.Value = taskAssign.GetPercentageComplete();
        }

        private string SaveForm()
        {
            string reply = CheckForm();
            if (reply.Length > 0)
            {
                // an error has occured somewhere                
                return reply;
            }
            taskAssign.SetDateAssigned(dateAssignedBox.Value);
            taskAssign.SetDateUnassigned(dateUnassignedBox.Value);
            taskAssign.SetPercentageComplete(percentUpDownBox.Value);
            return "";
        }

        private string CheckForm()
        {
            string reply = "";
            reply += taskAssign.CheckDate(dateAssignedBox.Value, dateUnassignedBox.Value);
            reply += taskAssign.CheckPercentageComplete(percentUpDownBox.Value);
            return reply;
        }

        private void okayButton_Click(object sender, EventArgs e)
        {
            string reply = SaveForm();
            if (reply.Length > 0)
            {
                // we have an error somewhere
                MessageBox.Show("System Management", reply, MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
                return;
            }
            Close();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}