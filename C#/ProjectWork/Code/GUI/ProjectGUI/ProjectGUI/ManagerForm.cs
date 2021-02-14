using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProjectGUI
{
    public partial class ManagerForm : Form
    {
        public ManagerForm()
        {
            InitializeComponent();
        }

        private void buttonTasks_Click(object sender, EventArgs e)
        {
            Tasks taskForm = new Tasks();
            taskForm.Show();
        }

        private void buttonStaff_Click(object sender, EventArgs e)
        {
            Staff staffForm = new Staff();
            staffForm.Show();
        }

        private void buttonReport_Click(object sender, EventArgs e)
        {
            Report reportForm = new Report();
            reportForm.Show();
        }
    }
}