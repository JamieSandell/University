namespace SystemUserInterface
{
    partial class TaskReportForm
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.okayButton = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.taskTitleLabel = new System.Windows.Forms.Label();
            this.taskStartDateLabel = new System.Windows.Forms.Label();
            this.taskDueDateLabel = new System.Windows.Forms.Label();
            this.taskCompletionDateLabel = new System.Windows.Forms.Label();
            this.taskCompletionPercentageLabel = new System.Windows.Forms.Label();
            this.assignedEmployeesList = new System.Windows.Forms.ListView();
            this.employeeNameColumn = new System.Windows.Forms.ColumnHeader();
            this.percentCompleteColumn = new System.Windows.Forms.ColumnHeader();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(30, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Title:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 30);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(85, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Task Start Date:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(10, 52);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(83, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Task Due Date:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 75);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(115, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Task Completion Date:";
            // 
            // okayButton
            // 
            this.okayButton.Location = new System.Drawing.Point(197, 259);
            this.okayButton.Name = "okayButton";
            this.okayButton.Size = new System.Drawing.Size(75, 23);
            this.okayButton.TabIndex = 5;
            this.okayButton.Text = "OK";
            this.okayButton.UseVisualStyleBackColor = true;
            this.okayButton.Click += new System.EventHandler(this.okayButton_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 232);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(147, 13);
            this.label5.TabIndex = 6;
            this.label5.Text = "Task Completion Percentage:";
            // 
            // taskTitleLabel
            // 
            this.taskTitleLabel.AutoSize = true;
            this.taskTitleLabel.Location = new System.Drawing.Point(186, 9);
            this.taskTitleLabel.Name = "taskTitleLabel";
            this.taskTitleLabel.Size = new System.Drawing.Size(35, 13);
            this.taskTitleLabel.TabIndex = 7;
            this.taskTitleLabel.Text = "label6";
            // 
            // taskStartDateLabel
            // 
            this.taskStartDateLabel.AutoSize = true;
            this.taskStartDateLabel.Location = new System.Drawing.Point(186, 30);
            this.taskStartDateLabel.Name = "taskStartDateLabel";
            this.taskStartDateLabel.Size = new System.Drawing.Size(35, 13);
            this.taskStartDateLabel.TabIndex = 8;
            this.taskStartDateLabel.Text = "label6";
            // 
            // taskDueDateLabel
            // 
            this.taskDueDateLabel.AutoSize = true;
            this.taskDueDateLabel.Location = new System.Drawing.Point(186, 52);
            this.taskDueDateLabel.Name = "taskDueDateLabel";
            this.taskDueDateLabel.Size = new System.Drawing.Size(35, 13);
            this.taskDueDateLabel.TabIndex = 9;
            this.taskDueDateLabel.Text = "label6";
            // 
            // taskCompletionDateLabel
            // 
            this.taskCompletionDateLabel.AutoSize = true;
            this.taskCompletionDateLabel.Location = new System.Drawing.Point(186, 75);
            this.taskCompletionDateLabel.Name = "taskCompletionDateLabel";
            this.taskCompletionDateLabel.Size = new System.Drawing.Size(0, 13);
            this.taskCompletionDateLabel.TabIndex = 10;
            // 
            // taskCompletionPercentageLabel
            // 
            this.taskCompletionPercentageLabel.AutoSize = true;
            this.taskCompletionPercentageLabel.Location = new System.Drawing.Point(186, 232);
            this.taskCompletionPercentageLabel.Name = "taskCompletionPercentageLabel";
            this.taskCompletionPercentageLabel.Size = new System.Drawing.Size(35, 13);
            this.taskCompletionPercentageLabel.TabIndex = 11;
            this.taskCompletionPercentageLabel.Text = "label6";
            // 
            // assignedEmployeesList
            // 
            this.assignedEmployeesList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.employeeNameColumn,
            this.percentCompleteColumn});
            this.assignedEmployeesList.Location = new System.Drawing.Point(13, 101);
            this.assignedEmployeesList.Name = "assignedEmployeesList";
            this.assignedEmployeesList.Size = new System.Drawing.Size(259, 119);
            this.assignedEmployeesList.TabIndex = 12;
            this.assignedEmployeesList.UseCompatibleStateImageBehavior = false;
            this.assignedEmployeesList.View = System.Windows.Forms.View.Details;
            // 
            // employeeNameColumn
            // 
            this.employeeNameColumn.Text = "Name";
            this.employeeNameColumn.Width = 159;
            // 
            // percentCompleteColumn
            // 
            this.percentCompleteColumn.Text = "% Complete";
            this.percentCompleteColumn.Width = 96;
            // 
            // TaskReportForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(283, 294);
            this.Controls.Add(this.assignedEmployeesList);
            this.Controls.Add(this.taskCompletionPercentageLabel);
            this.Controls.Add(this.taskCompletionDateLabel);
            this.Controls.Add(this.taskDueDateLabel);
            this.Controls.Add(this.taskStartDateLabel);
            this.Controls.Add(this.taskTitleLabel);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.okayButton);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "TaskReportForm";
            this.Text = "TaskReportForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button okayButton;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label taskTitleLabel;
        private System.Windows.Forms.Label taskStartDateLabel;
        private System.Windows.Forms.Label taskDueDateLabel;
        private System.Windows.Forms.Label taskCompletionDateLabel;
        private System.Windows.Forms.Label taskCompletionPercentageLabel;
        private System.Windows.Forms.ListView assignedEmployeesList;
        private System.Windows.Forms.ColumnHeader employeeNameColumn;
        private System.Windows.Forms.ColumnHeader percentCompleteColumn;
    }
}