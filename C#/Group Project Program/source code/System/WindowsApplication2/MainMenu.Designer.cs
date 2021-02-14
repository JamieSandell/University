namespace SystemUserInterface
{
    partial class MainMenu
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
            this.components = new System.ComponentModel.Container();
            this.AddStaffButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.StaffComboBox = new System.Windows.Forms.ComboBox();
            this.cancelButton = new System.Windows.Forms.Button();
            this.FindStaffButton = new System.Windows.Forms.Button();
            this.RemoveStaffButton = new System.Windows.Forms.Button();
            this.buttonReport = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.staffTab = new System.Windows.Forms.TabPage();
            this.staffLabelBox = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.TaskLabel = new System.Windows.Forms.Label();
            this.AddTaskButton = new System.Windows.Forms.Button();
            this.taskReportButton = new System.Windows.Forms.Button();
            this.TaskComboBox = new System.Windows.Forms.ComboBox();
            this.RemoveTaskButton = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.FindTaskButton = new System.Windows.Forms.Button();
            this.saveButton = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.staffTab.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // AddStaffButton
            // 
            this.AddStaffButton.Location = new System.Drawing.Point(66, 75);
            this.AddStaffButton.Name = "AddStaffButton";
            this.AddStaffButton.Size = new System.Drawing.Size(75, 23);
            this.AddStaffButton.TabIndex = 1;
            this.AddStaffButton.Text = "Add";
            this.AddStaffButton.UseVisualStyleBackColor = true;
            this.AddStaffButton.Click += new System.EventHandler(this.AddStaffButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(93, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(93, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Find Staff Member";
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(61, 4);
            // 
            // StaffComboBox
            // 
            this.StaffComboBox.FormattingEnabled = true;
            this.StaffComboBox.Location = new System.Drawing.Point(68, 48);
            this.StaffComboBox.Name = "StaffComboBox";
            this.StaffComboBox.Size = new System.Drawing.Size(147, 21);
            this.StaffComboBox.TabIndex = 7;
            // 
            // cancelButton
            // 
            this.cancelButton.Location = new System.Drawing.Point(234, 220);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 16;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // FindStaffButton
            // 
            this.FindStaffButton.Location = new System.Drawing.Point(147, 75);
            this.FindStaffButton.Name = "FindStaffButton";
            this.FindStaffButton.Size = new System.Drawing.Size(75, 23);
            this.FindStaffButton.TabIndex = 17;
            this.FindStaffButton.Text = "Find";
            this.FindStaffButton.UseVisualStyleBackColor = true;
            this.FindStaffButton.Click += new System.EventHandler(this.FindStaffButton_Click);
            // 
            // RemoveStaffButton
            // 
            this.RemoveStaffButton.Location = new System.Drawing.Point(66, 104);
            this.RemoveStaffButton.Name = "RemoveStaffButton";
            this.RemoveStaffButton.Size = new System.Drawing.Size(75, 23);
            this.RemoveStaffButton.TabIndex = 18;
            this.RemoveStaffButton.Text = "Remove";
            this.RemoveStaffButton.UseVisualStyleBackColor = true;
            this.RemoveStaffButton.Click += new System.EventHandler(this.RemoveStaffButton_Click);
            // 
            // buttonReport
            // 
            this.buttonReport.Location = new System.Drawing.Point(147, 104);
            this.buttonReport.Name = "buttonReport";
            this.buttonReport.Size = new System.Drawing.Size(75, 23);
            this.buttonReport.TabIndex = 19;
            this.buttonReport.Text = "Report";
            this.buttonReport.UseVisualStyleBackColor = true;
            this.buttonReport.Click += new System.EventHandler(this.buttonReport_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.staffTab);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(12, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(297, 200);
            this.tabControl1.TabIndex = 20;
            // 
            // staffTab
            // 
            this.staffTab.Controls.Add(this.staffLabelBox);
            this.staffTab.Controls.Add(this.AddStaffButton);
            this.staffTab.Controls.Add(this.buttonReport);
            this.staffTab.Controls.Add(this.StaffComboBox);
            this.staffTab.Controls.Add(this.RemoveStaffButton);
            this.staffTab.Controls.Add(this.label1);
            this.staffTab.Controls.Add(this.FindStaffButton);
            this.staffTab.Location = new System.Drawing.Point(4, 22);
            this.staffTab.Name = "staffTab";
            this.staffTab.Padding = new System.Windows.Forms.Padding(3);
            this.staffTab.Size = new System.Drawing.Size(289, 174);
            this.staffTab.TabIndex = 0;
            this.staffTab.Text = "Staff";
            this.staffTab.UseVisualStyleBackColor = true;
            // 
            // staffLabelBox
            // 
            this.staffLabelBox.AutoSize = true;
            this.staffLabelBox.Location = new System.Drawing.Point(65, 158);
            this.staffLabelBox.Name = "staffLabelBox";
            this.staffLabelBox.Size = new System.Drawing.Size(0, 13);
            this.staffLabelBox.TabIndex = 20;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.TaskLabel);
            this.tabPage2.Controls.Add(this.AddTaskButton);
            this.tabPage2.Controls.Add(this.taskReportButton);
            this.tabPage2.Controls.Add(this.TaskComboBox);
            this.tabPage2.Controls.Add(this.RemoveTaskButton);
            this.tabPage2.Controls.Add(this.label2);
            this.tabPage2.Controls.Add(this.FindTaskButton);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(289, 174);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Task";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // TaskLabel
            // 
            this.TaskLabel.AutoSize = true;
            this.TaskLabel.Location = new System.Drawing.Point(68, 155);
            this.TaskLabel.Name = "TaskLabel";
            this.TaskLabel.Size = new System.Drawing.Size(0, 13);
            this.TaskLabel.TabIndex = 26;
            // 
            // AddTaskButton
            // 
            this.AddTaskButton.Location = new System.Drawing.Point(66, 75);
            this.AddTaskButton.Name = "AddTaskButton";
            this.AddTaskButton.Size = new System.Drawing.Size(75, 23);
            this.AddTaskButton.TabIndex = 20;
            this.AddTaskButton.Text = "Add";
            this.AddTaskButton.UseVisualStyleBackColor = true;
            this.AddTaskButton.Click += new System.EventHandler(this.AddTaskButton_Click);
            // 
            // taskReportButton
            // 
            this.taskReportButton.Location = new System.Drawing.Point(147, 104);
            this.taskReportButton.Name = "taskReportButton";
            this.taskReportButton.Size = new System.Drawing.Size(75, 23);
            this.taskReportButton.TabIndex = 25;
            this.taskReportButton.Text = "Report";
            this.taskReportButton.UseVisualStyleBackColor = true;
            this.taskReportButton.Click += new System.EventHandler(this.taskReportButton_Click);
            // 
            // TaskComboBox
            // 
            this.TaskComboBox.FormattingEnabled = true;
            this.TaskComboBox.Location = new System.Drawing.Point(68, 48);
            this.TaskComboBox.Name = "TaskComboBox";
            this.TaskComboBox.Size = new System.Drawing.Size(147, 21);
            this.TaskComboBox.TabIndex = 22;
            // 
            // RemoveTaskButton
            // 
            this.RemoveTaskButton.Location = new System.Drawing.Point(66, 104);
            this.RemoveTaskButton.Name = "RemoveTaskButton";
            this.RemoveTaskButton.Size = new System.Drawing.Size(75, 23);
            this.RemoveTaskButton.TabIndex = 24;
            this.RemoveTaskButton.Text = "Remove";
            this.RemoveTaskButton.UseVisualStyleBackColor = true;
            this.RemoveTaskButton.Click += new System.EventHandler(this.RemoveTaskButton_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(114, 29);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(54, 13);
            this.label2.TabIndex = 21;
            this.label2.Text = "Find Task";
            // 
            // FindTaskButton
            // 
            this.FindTaskButton.Location = new System.Drawing.Point(147, 75);
            this.FindTaskButton.Name = "FindTaskButton";
            this.FindTaskButton.Size = new System.Drawing.Size(75, 23);
            this.FindTaskButton.TabIndex = 23;
            this.FindTaskButton.Text = "Find";
            this.FindTaskButton.UseVisualStyleBackColor = true;
            this.FindTaskButton.Click += new System.EventHandler(this.FindTaskButton_Click);
            // 
            // saveButton
            // 
            this.saveButton.Location = new System.Drawing.Point(112, 220);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(116, 23);
            this.saveButton.TabIndex = 21;
            this.saveButton.Text = "Save and Exit";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
            // 
            // MainMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(326, 255);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.cancelButton);
            this.Name = "MainMenu";
            this.Text = "Staff Menu";
            this.tabControl1.ResumeLayout(false);
            this.staffTab.ResumeLayout(false);
            this.staffTab.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button AddStaffButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ComboBox StaffComboBox;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button FindStaffButton;
        private System.Windows.Forms.Button RemoveStaffButton;
        private System.Windows.Forms.Button buttonReport;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage staffTab;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button AddTaskButton;
        private System.Windows.Forms.Button taskReportButton;
        private System.Windows.Forms.ComboBox TaskComboBox;
        private System.Windows.Forms.Button RemoveTaskButton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button FindTaskButton;
        private System.Windows.Forms.Label staffLabelBox;
        private System.Windows.Forms.Label TaskLabel;
        private System.Windows.Forms.Button saveButton;
    }
}

