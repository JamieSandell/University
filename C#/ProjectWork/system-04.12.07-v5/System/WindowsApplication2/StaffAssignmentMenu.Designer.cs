namespace WindowsApplication1
{
    partial class StaffAssignmentMenu
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
            this.nameLabel = new System.Windows.Forms.Label();
            this.taskLabel = new System.Windows.Forms.Label();
            this.dateAssignedLabel = new System.Windows.Forms.Label();
            this.dateUnassignedLabel = new System.Windows.Forms.Label();
            this.employeeNameLabel = new System.Windows.Forms.Label();
            this.taskNameLabel = new System.Windows.Forms.Label();
            this.dateAssignedBox = new System.Windows.Forms.DateTimePicker();
            this.dateUnassignedBox = new System.Windows.Forms.DateTimePicker();
            this.percentLabel = new System.Windows.Forms.Label();
            this.percentUpDownBox = new System.Windows.Forms.NumericUpDown();
            this.okayButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.percentUpDownBox)).BeginInit();
            this.SuspendLayout();
            // 
            // nameLabel
            // 
            this.nameLabel.AutoSize = true;
            this.nameLabel.Location = new System.Drawing.Point(13, 9);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(38, 13);
            this.nameLabel.TabIndex = 0;
            this.nameLabel.Text = "Name:";
            // 
            // taskLabel
            // 
            this.taskLabel.AutoSize = true;
            this.taskLabel.Location = new System.Drawing.Point(13, 35);
            this.taskLabel.Name = "taskLabel";
            this.taskLabel.Size = new System.Drawing.Size(34, 13);
            this.taskLabel.TabIndex = 2;
            this.taskLabel.Text = "Task:";
            // 
            // dateAssignedLabel
            // 
            this.dateAssignedLabel.AutoSize = true;
            this.dateAssignedLabel.Location = new System.Drawing.Point(15, 60);
            this.dateAssignedLabel.Name = "dateAssignedLabel";
            this.dateAssignedLabel.Size = new System.Drawing.Size(79, 13);
            this.dateAssignedLabel.TabIndex = 3;
            this.dateAssignedLabel.Text = "Date Assigned:";
            // 
            // dateUnassignedLabel
            // 
            this.dateUnassignedLabel.AutoSize = true;
            this.dateUnassignedLabel.Location = new System.Drawing.Point(15, 108);
            this.dateUnassignedLabel.Name = "dateUnassignedLabel";
            this.dateUnassignedLabel.Size = new System.Drawing.Size(89, 13);
            this.dateUnassignedLabel.TabIndex = 4;
            this.dateUnassignedLabel.Text = "Date Unassigned";
            // 
            // employeeNameLabel
            // 
            this.employeeNameLabel.AutoSize = true;
            this.employeeNameLabel.Location = new System.Drawing.Point(58, 9);
            this.employeeNameLabel.Name = "employeeNameLabel";
            this.employeeNameLabel.Size = new System.Drawing.Size(35, 13);
            this.employeeNameLabel.TabIndex = 5;
            this.employeeNameLabel.Text = "label1";
            // 
            // taskNameLabel
            // 
            this.taskNameLabel.AutoSize = true;
            this.taskNameLabel.Location = new System.Drawing.Point(58, 35);
            this.taskNameLabel.Name = "taskNameLabel";
            this.taskNameLabel.Size = new System.Drawing.Size(35, 13);
            this.taskNameLabel.TabIndex = 6;
            this.taskNameLabel.Text = "label1";
            // 
            // dateAssignedBox
            // 
            this.dateAssignedBox.Location = new System.Drawing.Point(13, 76);
            this.dateAssignedBox.Name = "dateAssignedBox";
            this.dateAssignedBox.Size = new System.Drawing.Size(200, 20);
            this.dateAssignedBox.TabIndex = 7;
            // 
            // dateUnassignedBox
            // 
            this.dateUnassignedBox.Location = new System.Drawing.Point(13, 124);
            this.dateUnassignedBox.Name = "dateUnassignedBox";
            this.dateUnassignedBox.Size = new System.Drawing.Size(200, 20);
            this.dateUnassignedBox.TabIndex = 8;
            // 
            // percentLabel
            // 
            this.percentLabel.AutoSize = true;
            this.percentLabel.Location = new System.Drawing.Point(13, 161);
            this.percentLabel.Name = "percentLabel";
            this.percentLabel.Size = new System.Drawing.Size(94, 13);
            this.percentLabel.TabIndex = 9;
            this.percentLabel.Text = "Percent Complete:";
            // 
            // percentUpDownBox
            // 
            this.percentUpDownBox.Location = new System.Drawing.Point(113, 159);
            this.percentUpDownBox.Name = "percentUpDownBox";
            this.percentUpDownBox.Size = new System.Drawing.Size(120, 20);
            this.percentUpDownBox.TabIndex = 10;
            // 
            // okayButton
            // 
            this.okayButton.Location = new System.Drawing.Point(197, 197);
            this.okayButton.Name = "okayButton";
            this.okayButton.Size = new System.Drawing.Size(75, 23);
            this.okayButton.TabIndex = 11;
            this.okayButton.Text = "OK";
            this.okayButton.UseVisualStyleBackColor = true;
            this.okayButton.Click += new System.EventHandler(this.okayButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.Location = new System.Drawing.Point(116, 197);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 12;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // StaffAssignmentMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 232);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.okayButton);
            this.Controls.Add(this.percentUpDownBox);
            this.Controls.Add(this.percentLabel);
            this.Controls.Add(this.dateUnassignedBox);
            this.Controls.Add(this.dateAssignedBox);
            this.Controls.Add(this.taskNameLabel);
            this.Controls.Add(this.employeeNameLabel);
            this.Controls.Add(this.dateUnassignedLabel);
            this.Controls.Add(this.dateAssignedLabel);
            this.Controls.Add(this.taskLabel);
            this.Controls.Add(this.nameLabel);
            this.Name = "StaffAssignmentMenu";
            this.Text = "Edit Staff Assignment";
            ((System.ComponentModel.ISupportInitialize)(this.percentUpDownBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label nameLabel;
        private System.Windows.Forms.Label taskLabel;
        private System.Windows.Forms.Label dateAssignedLabel;
        private System.Windows.Forms.Label dateUnassignedLabel;
        private System.Windows.Forms.Label employeeNameLabel;
        private System.Windows.Forms.Label taskNameLabel;
        private System.Windows.Forms.DateTimePicker dateAssignedBox;
        private System.Windows.Forms.DateTimePicker dateUnassignedBox;
        private System.Windows.Forms.Label percentLabel;
        private System.Windows.Forms.NumericUpDown percentUpDownBox;
        private System.Windows.Forms.Button okayButton;
        private System.Windows.Forms.Button cancelButton;
    }
}