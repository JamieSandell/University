using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProjectGUI
{
    public partial class ModifyTask : Form
    {
        public ModifyTask()
        {
            InitializeComponent();
        }

        private void buttonModifyTaskForm_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Modified!");
            this.Close();
        }
    }
}