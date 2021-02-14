using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Form_GUI
{
    public partial class frontScreen : Form
    {
        public frontScreen()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")
            {
                MessageBox.Show("Please Enter a Valid Name", "Invalid Name",
                   MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }

            else
            {
                CardGame.Program.runGame("plas");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void toolTip1_Popup(object sender, PopupEventArgs e)
        {
            
        }
    }
}