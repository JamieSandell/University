namespace ProjectGUI
{
    partial class Report
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
            this.labelStaffReport = new System.Windows.Forms.Label();
            this.labelStaffMember = new System.Windows.Forms.Label();
            this.comboBoxStaffMember = new System.Windows.Forms.ComboBox();
            this.labelCompletionOfTasks = new System.Windows.Forms.Label();
            this.listBoxCompletionOfTasks = new System.Windows.Forms.ListBox();
            this.labelTaskReport = new System.Windows.Forms.Label();
            this.labelTask = new System.Windows.Forms.Label();
            this.comboBoxTask = new System.Windows.Forms.ComboBox();
            this.listBoxStaffWorkingOnTask = new System.Windows.Forms.ListBox();
            this.labelStaffWorkingOnTask = new System.Windows.Forms.Label();
            this.listBoxOverallTaskCompletion = new System.Windows.Forms.ListBox();
            this.labelOverallTaskCompletion = new System.Windows.Forms.Label();
            this.listBoxCostPerTask = new System.Windows.Forms.ListBox();
            this.labelCostPerTask = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // labelStaffReport
            // 
            this.labelStaffReport.AutoSize = true;
            this.labelStaffReport.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelStaffReport.Location = new System.Drawing.Point(8, 15);
            this.labelStaffReport.Name = "labelStaffReport";
            this.labelStaffReport.Size = new System.Drawing.Size(114, 20);
            this.labelStaffReport.TabIndex = 0;
            this.labelStaffReport.Text = "Staff Report:";
            this.labelStaffReport.Click += new System.EventHandler(this.labelStaffReport_Click);
            // 
            // labelStaffMember
            // 
            this.labelStaffMember.AutoSize = true;
            this.labelStaffMember.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelStaffMember.Location = new System.Drawing.Point(30, 49);
            this.labelStaffMember.Name = "labelStaffMember";
            this.labelStaffMember.Size = new System.Drawing.Size(86, 13);
            this.labelStaffMember.TabIndex = 1;
            this.labelStaffMember.Text = "Staff Member:";
            this.labelStaffMember.Click += new System.EventHandler(this.labelStaffMember_Click);
            // 
            // comboBoxStaffMember
            // 
            this.comboBoxStaffMember.FormattingEnabled = true;
            this.comboBoxStaffMember.Location = new System.Drawing.Point(124, 49);
            this.comboBoxStaffMember.Name = "comboBoxStaffMember";
            this.comboBoxStaffMember.Size = new System.Drawing.Size(121, 21);
            this.comboBoxStaffMember.TabIndex = 2;
            this.comboBoxStaffMember.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // labelCompletionOfTasks
            // 
            this.labelCompletionOfTasks.AutoSize = true;
            this.labelCompletionOfTasks.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelCompletionOfTasks.Location = new System.Drawing.Point(30, 103);
            this.labelCompletionOfTasks.Name = "labelCompletionOfTasks";
            this.labelCompletionOfTasks.Size = new System.Drawing.Size(126, 13);
            this.labelCompletionOfTasks.TabIndex = 3;
            this.labelCompletionOfTasks.Text = "Completion of Tasks:";
            this.labelCompletionOfTasks.Click += new System.EventHandler(this.labelCompletionOfTasks_Click);
            // 
            // listBoxCompletionOfTasks
            // 
            this.listBoxCompletionOfTasks.FormattingEnabled = true;
            this.listBoxCompletionOfTasks.Location = new System.Drawing.Point(33, 131);
            this.listBoxCompletionOfTasks.Name = "listBoxCompletionOfTasks";
            this.listBoxCompletionOfTasks.Size = new System.Drawing.Size(120, 95);
            this.listBoxCompletionOfTasks.TabIndex = 4;
            this.listBoxCompletionOfTasks.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // labelTaskReport
            // 
            this.labelTaskReport.AutoSize = true;
            this.labelTaskReport.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelTaskReport.Location = new System.Drawing.Point(11, 320);
            this.labelTaskReport.Name = "labelTaskReport";
            this.labelTaskReport.Size = new System.Drawing.Size(112, 20);
            this.labelTaskReport.TabIndex = 5;
            this.labelTaskReport.Text = "Task Report:";
            // 
            // labelTask
            // 
            this.labelTask.AutoSize = true;
            this.labelTask.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelTask.Location = new System.Drawing.Point(34, 354);
            this.labelTask.Name = "labelTask";
            this.labelTask.Size = new System.Drawing.Size(39, 13);
            this.labelTask.TabIndex = 6;
            this.labelTask.Text = "Task:";
            // 
            // comboBoxTask
            // 
            this.comboBoxTask.FormattingEnabled = true;
            this.comboBoxTask.Location = new System.Drawing.Point(124, 351);
            this.comboBoxTask.Name = "comboBoxTask";
            this.comboBoxTask.Size = new System.Drawing.Size(121, 21);
            this.comboBoxTask.TabIndex = 7;
            // 
            // listBoxStaffWorkingOnTask
            // 
            this.listBoxStaffWorkingOnTask.FormattingEnabled = true;
            this.listBoxStaffWorkingOnTask.Location = new System.Drawing.Point(37, 421);
            this.listBoxStaffWorkingOnTask.Name = "listBoxStaffWorkingOnTask";
            this.listBoxStaffWorkingOnTask.Size = new System.Drawing.Size(120, 95);
            this.listBoxStaffWorkingOnTask.TabIndex = 9;
            // 
            // labelStaffWorkingOnTask
            // 
            this.labelStaffWorkingOnTask.AutoSize = true;
            this.labelStaffWorkingOnTask.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelStaffWorkingOnTask.Location = new System.Drawing.Point(34, 393);
            this.labelStaffWorkingOnTask.Name = "labelStaffWorkingOnTask";
            this.labelStaffWorkingOnTask.Size = new System.Drawing.Size(141, 13);
            this.labelStaffWorkingOnTask.TabIndex = 8;
            this.labelStaffWorkingOnTask.Text = "Staff Working On Task:";
            // 
            // listBoxOverallTaskCompletion
            // 
            this.listBoxOverallTaskCompletion.FormattingEnabled = true;
            this.listBoxOverallTaskCompletion.Location = new System.Drawing.Point(228, 421);
            this.listBoxOverallTaskCompletion.Name = "listBoxOverallTaskCompletion";
            this.listBoxOverallTaskCompletion.Size = new System.Drawing.Size(120, 95);
            this.listBoxOverallTaskCompletion.TabIndex = 11;
            // 
            // labelOverallTaskCompletion
            // 
            this.labelOverallTaskCompletion.AutoSize = true;
            this.labelOverallTaskCompletion.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelOverallTaskCompletion.Location = new System.Drawing.Point(225, 393);
            this.labelOverallTaskCompletion.Name = "labelOverallTaskCompletion";
            this.labelOverallTaskCompletion.Size = new System.Drawing.Size(145, 13);
            this.labelOverallTaskCompletion.TabIndex = 10;
            this.labelOverallTaskCompletion.Text = "Overall Task Completion";
            // 
            // listBoxCostPerTask
            // 
            this.listBoxCostPerTask.FormattingEnabled = true;
            this.listBoxCostPerTask.Location = new System.Drawing.Point(228, 131);
            this.listBoxCostPerTask.Name = "listBoxCostPerTask";
            this.listBoxCostPerTask.Size = new System.Drawing.Size(120, 95);
            this.listBoxCostPerTask.TabIndex = 13;
            // 
            // labelCostPerTask
            // 
            this.labelCostPerTask.AutoSize = true;
            this.labelCostPerTask.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelCostPerTask.Location = new System.Drawing.Point(225, 103);
            this.labelCostPerTask.Name = "labelCostPerTask";
            this.labelCostPerTask.Size = new System.Drawing.Size(91, 13);
            this.labelCostPerTask.TabIndex = 12;
            this.labelCostPerTask.Text = "Cost Per Task:";
            // 
            // Report
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(412, 570);
            this.Controls.Add(this.listBoxCostPerTask);
            this.Controls.Add(this.labelCostPerTask);
            this.Controls.Add(this.listBoxOverallTaskCompletion);
            this.Controls.Add(this.labelOverallTaskCompletion);
            this.Controls.Add(this.listBoxStaffWorkingOnTask);
            this.Controls.Add(this.labelStaffWorkingOnTask);
            this.Controls.Add(this.comboBoxTask);
            this.Controls.Add(this.labelTask);
            this.Controls.Add(this.labelTaskReport);
            this.Controls.Add(this.listBoxCompletionOfTasks);
            this.Controls.Add(this.labelCompletionOfTasks);
            this.Controls.Add(this.comboBoxStaffMember);
            this.Controls.Add(this.labelStaffMember);
            this.Controls.Add(this.labelStaffReport);
            this.Name = "Report";
            this.Text = "Report";
            this.Load += new System.EventHandler(this.Report_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelStaffReport;
        private System.Windows.Forms.Label labelStaffMember;
        private System.Windows.Forms.ComboBox comboBoxStaffMember;
        private System.Windows.Forms.Label labelCompletionOfTasks;
        private System.Windows.Forms.ListBox listBoxCompletionOfTasks;
        private System.Windows.Forms.Label labelTaskReport;
        private System.Windows.Forms.Label labelTask;
        private System.Windows.Forms.ComboBox comboBoxTask;
        private System.Windows.Forms.ListBox listBoxStaffWorkingOnTask;
        private System.Windows.Forms.Label labelStaffWorkingOnTask;
        private System.Windows.Forms.ListBox listBoxOverallTaskCompletion;
        private System.Windows.Forms.Label labelOverallTaskCompletion;
        private System.Windows.Forms.ListBox listBoxCostPerTask;
        private System.Windows.Forms.Label labelCostPerTask;
    }
}