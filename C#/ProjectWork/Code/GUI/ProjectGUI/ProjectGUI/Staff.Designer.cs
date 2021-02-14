namespace ProjectGUI
{
    partial class Staff
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
            this.buttonAddStaff = new System.Windows.Forms.Button();
            this.labelStaffName = new System.Windows.Forms.Label();
            this.textBoxStaffName = new System.Windows.Forms.TextBox();
            this.labelStaffSalary = new System.Windows.Forms.Label();
            this.textBoxStaffSalary = new System.Windows.Forms.TextBox();
            this.comboBoxstaff = new System.Windows.Forms.ComboBox();
            this.labelStaffFormStaffName = new System.Windows.Forms.Label();
            this.buttonModifyStaff = new System.Windows.Forms.Button();
            this.buttonDeleteStaff = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonAddStaff
            // 
            this.buttonAddStaff.Location = new System.Drawing.Point(30, 72);
            this.buttonAddStaff.Name = "buttonAddStaff";
            this.buttonAddStaff.Size = new System.Drawing.Size(75, 23);
            this.buttonAddStaff.TabIndex = 0;
            this.buttonAddStaff.Text = "Add Staff";
            this.buttonAddStaff.UseVisualStyleBackColor = true;
            // 
            // labelStaffName
            // 
            this.labelStaffName.AutoSize = true;
            this.labelStaffName.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelStaffName.Location = new System.Drawing.Point(24, 13);
            this.labelStaffName.Name = "labelStaffName";
            this.labelStaffName.Size = new System.Drawing.Size(74, 13);
            this.labelStaffName.TabIndex = 1;
            this.labelStaffName.Text = "Staff Name:";
            // 
            // textBoxStaffName
            // 
            this.textBoxStaffName.Location = new System.Drawing.Point(111, 10);
            this.textBoxStaffName.Name = "textBoxStaffName";
            this.textBoxStaffName.Size = new System.Drawing.Size(100, 20);
            this.textBoxStaffName.TabIndex = 2;
            // 
            // labelStaffSalary
            // 
            this.labelStaffSalary.AutoSize = true;
            this.labelStaffSalary.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelStaffSalary.Location = new System.Drawing.Point(24, 39);
            this.labelStaffSalary.Name = "labelStaffSalary";
            this.labelStaffSalary.Size = new System.Drawing.Size(77, 13);
            this.labelStaffSalary.TabIndex = 3;
            this.labelStaffSalary.Text = "Staff Salary:";
            // 
            // textBoxStaffSalary
            // 
            this.textBoxStaffSalary.Location = new System.Drawing.Point(111, 39);
            this.textBoxStaffSalary.Name = "textBoxStaffSalary";
            this.textBoxStaffSalary.Size = new System.Drawing.Size(100, 20);
            this.textBoxStaffSalary.TabIndex = 4;
            // 
            // comboBoxstaff
            // 
            this.comboBoxstaff.FormattingEnabled = true;
            this.comboBoxstaff.Location = new System.Drawing.Point(111, 155);
            this.comboBoxstaff.Name = "comboBoxstaff";
            this.comboBoxstaff.Size = new System.Drawing.Size(121, 21);
            this.comboBoxstaff.TabIndex = 5;
            // 
            // labelStaffFormStaffName
            // 
            this.labelStaffFormStaffName.AutoSize = true;
            this.labelStaffFormStaffName.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelStaffFormStaffName.Location = new System.Drawing.Point(24, 158);
            this.labelStaffFormStaffName.Name = "labelStaffFormStaffName";
            this.labelStaffFormStaffName.Size = new System.Drawing.Size(74, 13);
            this.labelStaffFormStaffName.TabIndex = 6;
            this.labelStaffFormStaffName.Text = "Staff Name:";
            // 
            // buttonModifyStaff
            // 
            this.buttonModifyStaff.Location = new System.Drawing.Point(30, 197);
            this.buttonModifyStaff.Name = "buttonModifyStaff";
            this.buttonModifyStaff.Size = new System.Drawing.Size(75, 23);
            this.buttonModifyStaff.TabIndex = 7;
            this.buttonModifyStaff.Text = "Modify Staff";
            this.buttonModifyStaff.UseVisualStyleBackColor = true;
            this.buttonModifyStaff.Click += new System.EventHandler(this.buttonModifyStaff_Click);
            // 
            // buttonDeleteStaff
            // 
            this.buttonDeleteStaff.Location = new System.Drawing.Point(157, 197);
            this.buttonDeleteStaff.Name = "buttonDeleteStaff";
            this.buttonDeleteStaff.Size = new System.Drawing.Size(75, 23);
            this.buttonDeleteStaff.TabIndex = 8;
            this.buttonDeleteStaff.Text = "Delete Staff";
            this.buttonDeleteStaff.UseVisualStyleBackColor = true;
            // 
            // Staff
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 273);
            this.Controls.Add(this.buttonDeleteStaff);
            this.Controls.Add(this.buttonModifyStaff);
            this.Controls.Add(this.labelStaffFormStaffName);
            this.Controls.Add(this.comboBoxstaff);
            this.Controls.Add(this.textBoxStaffSalary);
            this.Controls.Add(this.labelStaffSalary);
            this.Controls.Add(this.textBoxStaffName);
            this.Controls.Add(this.labelStaffName);
            this.Controls.Add(this.buttonAddStaff);
            this.Name = "Staff";
            this.Text = "Staff";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonAddStaff;
        private System.Windows.Forms.Label labelStaffName;
        private System.Windows.Forms.TextBox textBoxStaffName;
        private System.Windows.Forms.Label labelStaffSalary;
        private System.Windows.Forms.TextBox textBoxStaffSalary;
        private System.Windows.Forms.ComboBox comboBoxstaff;
        private System.Windows.Forms.Label labelStaffFormStaffName;
        private System.Windows.Forms.Button buttonModifyStaff;
        private System.Windows.Forms.Button buttonDeleteStaff;
    }
}