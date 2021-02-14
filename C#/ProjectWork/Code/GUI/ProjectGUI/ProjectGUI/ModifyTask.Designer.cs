namespace ProjectGUI
{
    partial class ModifyTask
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
            this.buttonModifyTaskForm = new System.Windows.Forms.Button();
            this.dateTimePicker2 = new System.Windows.Forms.DateTimePicker();
            this.labelTaskDeadLine = new System.Windows.Forms.Label();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.labelTaskStartDate = new System.Windows.Forms.Label();
            this.textBoxTaskName = new System.Windows.Forms.TextBox();
            this.labelTaskName = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonModifyTaskForm
            // 
            this.buttonModifyTaskForm.Location = new System.Drawing.Point(109, 107);
            this.buttonModifyTaskForm.Name = "buttonModifyTaskForm";
            this.buttonModifyTaskForm.Size = new System.Drawing.Size(75, 23);
            this.buttonModifyTaskForm.TabIndex = 13;
            this.buttonModifyTaskForm.Text = "Modify Task";
            this.buttonModifyTaskForm.UseVisualStyleBackColor = true;
            this.buttonModifyTaskForm.Click += new System.EventHandler(this.buttonModifyTaskForm_Click);
            // 
            // dateTimePicker2
            // 
            this.dateTimePicker2.Location = new System.Drawing.Point(109, 67);
            this.dateTimePicker2.Name = "dateTimePicker2";
            this.dateTimePicker2.Size = new System.Drawing.Size(200, 20);
            this.dateTimePicker2.TabIndex = 12;
            // 
            // labelTaskDeadLine
            // 
            this.labelTaskDeadLine.AutoSize = true;
            this.labelTaskDeadLine.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelTaskDeadLine.Location = new System.Drawing.Point(2, 71);
            this.labelTaskDeadLine.Name = "labelTaskDeadLine";
            this.labelTaskDeadLine.Size = new System.Drawing.Size(96, 13);
            this.labelTaskDeadLine.TabIndex = 11;
            this.labelTaskDeadLine.Text = "Task End Date:";
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.Location = new System.Drawing.Point(109, 41);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(200, 20);
            this.dateTimePicker1.TabIndex = 10;
            // 
            // labelTaskStartDate
            // 
            this.labelTaskStartDate.AutoSize = true;
            this.labelTaskStartDate.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelTaskStartDate.Location = new System.Drawing.Point(2, 45);
            this.labelTaskStartDate.Name = "labelTaskStartDate";
            this.labelTaskStartDate.Size = new System.Drawing.Size(101, 13);
            this.labelTaskStartDate.TabIndex = 9;
            this.labelTaskStartDate.Text = "Task Start Date:";
            // 
            // textBoxTaskName
            // 
            this.textBoxTaskName.Location = new System.Drawing.Point(109, 12);
            this.textBoxTaskName.Name = "textBoxTaskName";
            this.textBoxTaskName.Size = new System.Drawing.Size(100, 20);
            this.textBoxTaskName.TabIndex = 8;
            // 
            // labelTaskName
            // 
            this.labelTaskName.AutoSize = true;
            this.labelTaskName.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelTaskName.Location = new System.Drawing.Point(2, 15);
            this.labelTaskName.Name = "labelTaskName";
            this.labelTaskName.Size = new System.Drawing.Size(75, 13);
            this.labelTaskName.TabIndex = 7;
            this.labelTaskName.Text = "Task Name:";
            // 
            // ModifyTask
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(313, 154);
            this.Controls.Add(this.buttonModifyTaskForm);
            this.Controls.Add(this.dateTimePicker2);
            this.Controls.Add(this.labelTaskDeadLine);
            this.Controls.Add(this.dateTimePicker1);
            this.Controls.Add(this.labelTaskStartDate);
            this.Controls.Add(this.textBoxTaskName);
            this.Controls.Add(this.labelTaskName);
            this.Name = "ModifyTask";
            this.Text = "ModifyTask";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonModifyTaskForm;
        private System.Windows.Forms.DateTimePicker dateTimePicker2;
        private System.Windows.Forms.Label labelTaskDeadLine;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
        private System.Windows.Forms.Label labelTaskStartDate;
        private System.Windows.Forms.TextBox textBoxTaskName;
        private System.Windows.Forms.Label labelTaskName;
    }
}