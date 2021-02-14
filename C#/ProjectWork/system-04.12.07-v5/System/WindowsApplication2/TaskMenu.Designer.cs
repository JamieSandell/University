namespace WindowsApplication1
{
    partial class TaskMenu
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
            this.taskNameTextBox = new System.Windows.Forms.TextBox();
            this.taskOkayButton = new System.Windows.Forms.Button();
            this.taskCancelButton = new System.Windows.Forms.Button();
            this.taskSetDateBox = new System.Windows.Forms.DateTimePicker();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.taskDueDateBox = new System.Windows.Forms.DateTimePicker();
            this.assignedEmployeesList = new System.Windows.Forms.ListView();
            this.employeeNameColumn = new System.Windows.Forms.ColumnHeader();
            this.dateAssignedColumn = new System.Windows.Forms.ColumnHeader();
            this.dateUnassignedColumn = new System.Windows.Forms.ColumnHeader();
            this.hoursWorkedColumn = new System.Windows.Forms.ColumnHeader();
            this.percentCompleteColumn = new System.Windows.Forms.ColumnHeader();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.taskCompleteDateBox = new System.Windows.Forms.DateTimePicker();
            this.taskCompleteCheckBox = new System.Windows.Forms.CheckBox();
            this.commentsTextBox = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.addStaffButton = new System.Windows.Forms.Button();
            this.removeStaffButton = new System.Windows.Forms.Button();
            this.EmployeeNameTextBox = new System.Windows.Forms.TextBox();
            this.editStaffButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Task Name";
            // 
            // taskNameTextBox
            // 
            this.taskNameTextBox.Location = new System.Drawing.Point(13, 30);
            this.taskNameTextBox.Name = "taskNameTextBox";
            this.taskNameTextBox.Size = new System.Drawing.Size(100, 20);
            this.taskNameTextBox.TabIndex = 1;
            // 
            // taskOkayButton
            // 
            this.taskOkayButton.Location = new System.Drawing.Point(451, 426);
            this.taskOkayButton.Name = "taskOkayButton";
            this.taskOkayButton.Size = new System.Drawing.Size(75, 23);
            this.taskOkayButton.TabIndex = 2;
            this.taskOkayButton.Text = "OK";
            this.taskOkayButton.UseVisualStyleBackColor = true;
            this.taskOkayButton.Click += new System.EventHandler(this.taskOkayButton_Click);
            // 
            // taskCancelButton
            // 
            this.taskCancelButton.Location = new System.Drawing.Point(370, 426);
            this.taskCancelButton.Name = "taskCancelButton";
            this.taskCancelButton.Size = new System.Drawing.Size(75, 23);
            this.taskCancelButton.TabIndex = 3;
            this.taskCancelButton.Text = "Cancel";
            this.taskCancelButton.UseVisualStyleBackColor = true;
            this.taskCancelButton.Click += new System.EventHandler(this.taskCancelButton_Click);
            // 
            // taskSetDateBox
            // 
            this.taskSetDateBox.Location = new System.Drawing.Point(12, 85);
            this.taskSetDateBox.Name = "taskSetDateBox";
            this.taskSetDateBox.Size = new System.Drawing.Size(200, 20);
            this.taskSetDateBox.TabIndex = 4;
            this.taskSetDateBox.Value = new System.DateTime(2007, 12, 2, 0, 0, 0, 0);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 69);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(76, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Task Set Date";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 112);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(80, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Task Due Date";
            // 
            // taskDueDateBox
            // 
            this.taskDueDateBox.Location = new System.Drawing.Point(13, 128);
            this.taskDueDateBox.Name = "taskDueDateBox";
            this.taskDueDateBox.Size = new System.Drawing.Size(200, 20);
            this.taskDueDateBox.TabIndex = 7;
            this.taskDueDateBox.Value = new System.DateTime(2007, 12, 2, 0, 0, 0, 0);
            // 
            // assignedEmployeesList
            // 
            this.assignedEmployeesList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.employeeNameColumn,
            this.dateAssignedColumn,
            this.dateUnassignedColumn,
            this.hoursWorkedColumn,
            this.percentCompleteColumn});
            this.assignedEmployeesList.Location = new System.Drawing.Point(12, 183);
            this.assignedEmployeesList.Name = "assignedEmployeesList";
            this.assignedEmployeesList.Size = new System.Drawing.Size(514, 147);
            this.assignedEmployeesList.TabIndex = 8;
            this.assignedEmployeesList.UseCompatibleStateImageBehavior = false;
            this.assignedEmployeesList.View = System.Windows.Forms.View.Details;
            // 
            // employeeNameColumn
            // 
            this.employeeNameColumn.Text = "Name";
            this.employeeNameColumn.Width = 145;
            // 
            // dateAssignedColumn
            // 
            this.dateAssignedColumn.Text = "Date Assigned";
            this.dateAssignedColumn.Width = 94;
            // 
            // dateUnassignedColumn
            // 
            this.dateUnassignedColumn.Text = "Date Unassigned";
            this.dateUnassignedColumn.Width = 104;
            // 
            // hoursWorkedColumn
            // 
            this.hoursWorkedColumn.Text = "Hours Work";
            this.hoursWorkedColumn.Width = 74;
            // 
            // percentCompleteColumn
            // 
            this.percentCompleteColumn.Text = "% Complete";
            this.percentCompleteColumn.Width = 77;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(197, 167);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(160, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "Staff Members Assigned to Task";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(16, 374);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(112, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "Task Completion Date";
            // 
            // taskCompleteDateBox
            // 
            this.taskCompleteDateBox.Checked = false;
            this.taskCompleteDateBox.Location = new System.Drawing.Point(14, 390);
            this.taskCompleteDateBox.Name = "taskCompleteDateBox";
            this.taskCompleteDateBox.Size = new System.Drawing.Size(200, 20);
            this.taskCompleteDateBox.TabIndex = 13;
            // 
            // taskCompleteCheckBox
            // 
            this.taskCompleteCheckBox.AutoSize = true;
            this.taskCompleteCheckBox.Location = new System.Drawing.Point(14, 345);
            this.taskCompleteCheckBox.Name = "taskCompleteCheckBox";
            this.taskCompleteCheckBox.Size = new System.Drawing.Size(109, 17);
            this.taskCompleteCheckBox.TabIndex = 14;
            this.taskCompleteCheckBox.Text = "Task Completed?";
            this.taskCompleteCheckBox.UseVisualStyleBackColor = true;
            this.taskCompleteCheckBox.CheckedChanged += new System.EventHandler(this.taskCompleteCheckBox_CheckedChanged);
            // 
            // commentsTextBox
            // 
            this.commentsTextBox.Location = new System.Drawing.Point(238, 30);
            this.commentsTextBox.Multiline = true;
            this.commentsTextBox.Name = "commentsTextBox";
            this.commentsTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.commentsTextBox.Size = new System.Drawing.Size(288, 118);
            this.commentsTextBox.TabIndex = 15;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(235, 13);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(63, 13);
            this.label6.TabIndex = 16;
            this.label6.Text = "Description:";
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(96, 426);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 23);
            this.button4.TabIndex = 18;
            this.button4.Text = "End Timer";
            this.button4.UseVisualStyleBackColor = true;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(14, 426);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 17;
            this.button3.Text = "Start Timer";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // addStaffButton
            // 
            this.addStaffButton.Location = new System.Drawing.Point(436, 362);
            this.addStaffButton.Name = "addStaffButton";
            this.addStaffButton.Size = new System.Drawing.Size(90, 23);
            this.addStaffButton.TabIndex = 19;
            this.addStaffButton.Text = "Add Staff";
            this.addStaffButton.UseVisualStyleBackColor = true;
            this.addStaffButton.Click += new System.EventHandler(this.addStaffButton_Click);
            // 
            // removeStaffButton
            // 
            this.removeStaffButton.Location = new System.Drawing.Point(436, 390);
            this.removeStaffButton.Name = "removeStaffButton";
            this.removeStaffButton.Size = new System.Drawing.Size(90, 23);
            this.removeStaffButton.TabIndex = 20;
            this.removeStaffButton.Text = "Remove Staff";
            this.removeStaffButton.UseVisualStyleBackColor = true;
            this.removeStaffButton.Click += new System.EventHandler(this.removeStaffButton_Click);
            // 
            // EmployeeNameTextBox
            // 
            this.EmployeeNameTextBox.Location = new System.Drawing.Point(340, 336);
            this.EmployeeNameTextBox.Name = "EmployeeNameTextBox";
            this.EmployeeNameTextBox.Size = new System.Drawing.Size(186, 20);
            this.EmployeeNameTextBox.TabIndex = 21;
            // 
            // editStaffButton
            // 
            this.editStaffButton.Location = new System.Drawing.Point(340, 363);
            this.editStaffButton.Name = "editStaffButton";
            this.editStaffButton.Size = new System.Drawing.Size(90, 23);
            this.editStaffButton.TabIndex = 22;
            this.editStaffButton.Text = "Edit Staff Assignment";
            this.editStaffButton.UseVisualStyleBackColor = true;
            this.editStaffButton.Click += new System.EventHandler(this.unassignStaffButton_Click);
            // 
            // TaskMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(542, 461);
            this.Controls.Add(this.editStaffButton);
            this.Controls.Add(this.EmployeeNameTextBox);
            this.Controls.Add(this.removeStaffButton);
            this.Controls.Add(this.addStaffButton);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.commentsTextBox);
            this.Controls.Add(this.taskCompleteCheckBox);
            this.Controls.Add(this.taskCompleteDateBox);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.assignedEmployeesList);
            this.Controls.Add(this.taskDueDateBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.taskSetDateBox);
            this.Controls.Add(this.taskCancelButton);
            this.Controls.Add(this.taskOkayButton);
            this.Controls.Add(this.taskNameTextBox);
            this.Controls.Add(this.label1);
            this.Name = "TaskMenu";
            this.Text = "Task";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox taskNameTextBox;
        private System.Windows.Forms.Button taskOkayButton;
        private System.Windows.Forms.Button taskCancelButton;
        private System.Windows.Forms.DateTimePicker taskSetDateBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DateTimePicker taskDueDateBox;
        private System.Windows.Forms.ListView assignedEmployeesList;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.DateTimePicker taskCompleteDateBox;
        private System.Windows.Forms.ColumnHeader employeeNameColumn;
        private System.Windows.Forms.ColumnHeader dateAssignedColumn;
        private System.Windows.Forms.CheckBox taskCompleteCheckBox;
        private System.Windows.Forms.ColumnHeader dateUnassignedColumn;
        private System.Windows.Forms.ColumnHeader hoursWorkedColumn;
        private System.Windows.Forms.TextBox commentsTextBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ColumnHeader percentCompleteColumn;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button addStaffButton;
        private System.Windows.Forms.Button removeStaffButton;
        private System.Windows.Forms.TextBox EmployeeNameTextBox;
        private System.Windows.Forms.Button editStaffButton;
    }
}