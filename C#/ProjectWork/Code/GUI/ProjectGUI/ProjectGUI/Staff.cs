using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProjectGUI
{
    public partial class Staff : Form
    {
        public Staff()
        {
            InitializeComponent();
        }

        private void buttonModifyStaff_Click(object sender, EventArgs e)
        {
            ModifyStaff form1 = new ModifyStaff();
            form1.Show();
        }
    }
}