namespace ManagementInformationSystem
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPageLastTen = new System.Windows.Forms.TabPage();
            this.buttonGenerateLastTen = new System.Windows.Forms.Button();
            this.richTextBoxLastTen = new System.Windows.Forms.RichTextBox();
            this.tabPageUnderweight = new System.Windows.Forms.TabPage();
            this.buttonGenerateUnderweight = new System.Windows.Forms.Button();
            this.richTextBoxUnderweight = new System.Windows.Forms.RichTextBox();
            this.tabControl1.SuspendLayout();
            this.tabPageLastTen.SuspendLayout();
            this.tabPageUnderweight.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPageLastTen);
            this.tabControl1.Controls.Add(this.tabPageUnderweight);
            this.tabControl1.Location = new System.Drawing.Point(12, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(268, 235);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPageLastTen
            // 
            this.tabPageLastTen.Controls.Add(this.buttonGenerateLastTen);
            this.tabPageLastTen.Controls.Add(this.richTextBoxLastTen);
            this.tabPageLastTen.Location = new System.Drawing.Point(4, 22);
            this.tabPageLastTen.Name = "tabPageLastTen";
            this.tabPageLastTen.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageLastTen.Size = new System.Drawing.Size(260, 209);
            this.tabPageLastTen.TabIndex = 0;
            this.tabPageLastTen.Text = "Last Ten";
            this.tabPageLastTen.UseVisualStyleBackColor = true;
            // 
            // buttonGenerateLastTen
            // 
            this.buttonGenerateLastTen.Location = new System.Drawing.Point(96, 173);
            this.buttonGenerateLastTen.Name = "buttonGenerateLastTen";
            this.buttonGenerateLastTen.Size = new System.Drawing.Size(75, 23);
            this.buttonGenerateLastTen.TabIndex = 1;
            this.buttonGenerateLastTen.Text = "Generate";
            this.buttonGenerateLastTen.UseVisualStyleBackColor = true;
            this.buttonGenerateLastTen.Click += new System.EventHandler(this.buttonGenerateLastTen_Click);
            // 
            // richTextBoxLastTen
            // 
            this.richTextBoxLastTen.Location = new System.Drawing.Point(26, 6);
            this.richTextBoxLastTen.Name = "richTextBoxLastTen";
            this.richTextBoxLastTen.Size = new System.Drawing.Size(208, 161);
            this.richTextBoxLastTen.TabIndex = 0;
            this.richTextBoxLastTen.Text = "";
            // 
            // tabPageUnderweight
            // 
            this.tabPageUnderweight.Controls.Add(this.buttonGenerateUnderweight);
            this.tabPageUnderweight.Controls.Add(this.richTextBoxUnderweight);
            this.tabPageUnderweight.Location = new System.Drawing.Point(4, 22);
            this.tabPageUnderweight.Name = "tabPageUnderweight";
            this.tabPageUnderweight.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageUnderweight.Size = new System.Drawing.Size(260, 209);
            this.tabPageUnderweight.TabIndex = 1;
            this.tabPageUnderweight.Text = "Underweight";
            this.tabPageUnderweight.UseVisualStyleBackColor = true;
            // 
            // buttonGenerateUnderweight
            // 
            this.buttonGenerateUnderweight.Location = new System.Drawing.Point(96, 176);
            this.buttonGenerateUnderweight.Name = "buttonGenerateUnderweight";
            this.buttonGenerateUnderweight.Size = new System.Drawing.Size(75, 23);
            this.buttonGenerateUnderweight.TabIndex = 3;
            this.buttonGenerateUnderweight.Text = "Generate";
            this.buttonGenerateUnderweight.UseVisualStyleBackColor = true;
            this.buttonGenerateUnderweight.Click += new System.EventHandler(this.buttonGenerateUnderweight_Click);
            // 
            // richTextBoxUnderweight
            // 
            this.richTextBoxUnderweight.Location = new System.Drawing.Point(26, 9);
            this.richTextBoxUnderweight.Name = "richTextBoxUnderweight";
            this.richTextBoxUnderweight.Size = new System.Drawing.Size(208, 161);
            this.richTextBoxUnderweight.TabIndex = 2;
            this.richTextBoxUnderweight.Text = "";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 273);
            this.Controls.Add(this.tabControl1);
            this.Name = "Form1";
            this.Text = "MIS Terminal";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPageLastTen.ResumeLayout(false);
            this.tabPageUnderweight.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPageLastTen;
        private System.Windows.Forms.Button buttonGenerateLastTen;
        private System.Windows.Forms.RichTextBox richTextBoxLastTen;
        private System.Windows.Forms.TabPage tabPageUnderweight;
        private System.Windows.Forms.Button buttonGenerateUnderweight;
        private System.Windows.Forms.RichTextBox richTextBoxUnderweight;
    }
}

