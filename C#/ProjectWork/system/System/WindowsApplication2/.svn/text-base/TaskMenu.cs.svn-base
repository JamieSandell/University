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
    public partial class TaskMenu : Form
    {
        private ITask task;

        public TaskMenu(ITask task)
        {
            InitializeComponent();
            this.task = task;
            LoadForm();
        }

        private void LoadForm()
        {
            taskNameTextBox.Text = task.GetTitle();
            commentsTextBox.Text = task.GetDescription();
            taskSetDateBox.Text = task.GetStartDate().ToString();
            taskDueDateBox.Text = task.GetEndDate().ToString();
        }

        private string SaveForm()
        {
            string reply = CheckForm();
            if (reply.Length > 0)
            {
                return reply;
            }
            task.SetTitle(taskNameTextBox.Text);
            task.SetDescription(commentsTextBox.Text);
            task.SetStartDate(taskSetDateBox.Value);
            task.SetEndDate(taskDueDateBox.Value);
            return "";
        }

        private string CheckForm()
        {
            string reply = "";
            reply += task.CheckTitle(taskNameTextBox.Text);
            reply += task.CheckEndDate(taskSetDateBox.Value, taskDueDateBox.Value);
            reply += task.CheckDescription(commentsTextBox.Text);
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

        private void taskCancelButton_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}