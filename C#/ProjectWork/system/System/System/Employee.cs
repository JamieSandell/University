using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace SystemManagement
{
    public interface IEmployee
    {
        /// <summary>
        /// Gets the employee's ID
        /// </summary>
        /// <returns>
        /// The employee's ID as currently stored in the Employee class
        /// </returns>
        string GetEmployeeID();

        /// <summary>
        /// Sets the ID of the Employee, calls CheckAddress to make sure it is okay
        /// </summary>
        /// <param name="">The new ID to be set</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string SetEmployeeID(string newEmployeeID);

        /// <summary>
        /// Gets the name of the Employee
        /// </summary>
        /// <returns>
        /// The employee's name as currently stored in the Employee class
        /// </returns>
        string GetName();

        /// <summary>
        /// Checks to see if a name is valid
        /// </summary>
        /// <param name="">The name to be checked</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string CheckName(string newName);

        /// <summary>
        /// Sets the name of the employee, calls CheckName to make sure it's okay
        /// </summary>
        /// <param name="">the new name to be set</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string SetName(string newName);

        /// <summary>
        /// Gets the first line of the employee's address
        /// </summary>
        /// <returns>
        /// The first line of the employee's address as currently stored in the Employee class
        /// </returns>
        string GetAddress1();

        /// <summary>
        /// Gets the second line of the employee's address
        /// </summary>
        /// <returns>
        /// The second line of the employee's address as currently stored in the Employee class
        /// </returns>
        string GetAddress2();

        /// <summary>
        /// Gets the county from the employee's address
        /// </summary>
        /// <returns>
        /// The county from the employee's address as currently stored in the Employee class
        /// </returns>
        string GetCounty();

        /// <summary>
        /// Gets the employee's postcode
        /// </summary>
        /// <returns>
        /// The employee's postcode as currently stored in the Employee class
        /// </returns>
        string GetPostcode();

        /// <summary>
        /// Gets the employee's telephone number
        /// </summary>
        /// <returns>
        /// The employee's telephone number as currently stored in the Employee class
        /// </returns>
        string GetTelephone();

        /// <summary>
        /// Gets the employee's mobile telephone number
        /// </summary>
        /// <returns>
        /// The employee's mobile telephone number as currently stored in the Employee class
        /// </returns>
        string GetMobile();

        /// <summary>
        /// Checks to see if an address is valid
        /// </summary>
        /// <param name="">The address line to be checked</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string CheckAddress(string newAddress);

        /// <summary>
        /// Sets the first line of the employee's address, calls CheckAddress to make sure it's okay
        /// </summary>
        /// <param name="">the new address to be set</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string SetAddress1(string newAddress);

        /// <summary>
        /// Sets the second line of the employee's address, calls CheckAddress to make sure it's okay
        /// </summary>
        /// <param name="">the new address to be set</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string SetAddress2(string newAddress);

        /// <summary>
        /// Sets the county for the employee's address, calls CheckName to make sure it's okay
        /// </summary>
        /// <param name="">the new county to be set</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string SetCounty(string newCounty);

        /// <summary>
        /// Sets the employee's postcode, calls CheckAddress to make sure it's okay
        /// </summary>
        /// <param name="">the new postcode to be set</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string SetPostcode(string newPostcode);

        /// <summary>
        /// Checks to see if a telephone number is valid
        /// </summary>
        /// <param name="">The telephone number to be checked</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string CheckTelephone(string telephoneNumber);

        /// <summary>
        /// Sets the employee's telephone number, calls CheckTelephone to make sure it's okay
        /// </summary>
        /// <param name="">the new telephone number to be set</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string SetTelephone(string newTelephone);

        /// <summary>
        /// Sets the employee's mobile telephone number, calls CheckTelephone to make sure it's okay
        /// </summary>
        /// <param name="">the new mobile telephone number to be set</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string SetMobile(string newMobile);

        /// <summary>
        /// Gets the salary of the Employee
        /// </summary>
        /// <returns>
        /// The employee's salary as currently stored in the Employee class
        /// </returns>
        decimal GetSalary();

        /// <summary>
        /// Gets the wage of the Employee
        /// </summary>
        /// <returns>
        /// The employee's wage as currently stored in the Employee class
        /// </returns>
        decimal GetWage();

        /// <summary>
        /// Sets the employee's salary
        /// </summary>
        /// <param name="">the new salary to be set</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string SetSalary(decimal newSalary);

        /// <summary>
        /// Sets the employee's wage
        /// </summary>
        /// <param name="">the new wage to be set</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string SetWage(decimal newWage);

        /// <summary>
        /// Get all instances of the task class
        /// </summary>
        /// <returns>An arraylist containing all instances of the task class</returns>
        ArrayList GetTaskInstances();

        /// <summary>
        /// Validate the employee's salary
        /// </summary>
        /// <param name="newSalary">The employee's salary</param>
        /// <returns>An empty string if everything went OK, else an error message</returns>
        string CheckSalary(decimal newSalary);

        /// <summary>
        /// Validate the employee's wage
        /// </summary>
        /// <param name="newWage">The employee's wage</param>
        /// <returns>An empty string if everything went OK, else an error message</returns>
        string CheckWage(decimal newWage);

        string AddTask(ITaskAssign taskAssign);

        string RemoveTask(ITaskAssign taskAssign);
    }

    public class Employee : IEmployee
    {
        public Employee(string inName)
        {
            name = inName;
        }

        #region EmployeeID

        private string employeeID;

        public string GetEmployeeID()
        {
            return employeeID;
        }

        public string SetEmployeeID(string newEmployeeID)
        {
            string result = CheckAddress(newEmployeeID); //check address returns an empty string if okay.
            if (result.Length == 0) 
            {
                employeeID = newEmployeeID;
                return "";
            }

            return "Invalid EmployeeID ";
        }

        #endregion

        #region Name Management


        private string name;

        public string GetName()
        {
            return name;
        }

        public string CheckName(string newName)
        {
            if (newName.Length == 0)
            {
                return "Empty name ";
            }

            if (newName.StartsWith(" "))
            {
                return "Invalid name: starts with a white space.";
            }

            char[] newNameArray = newName.ToCharArray();
            for (int i = 0; i < newName.Length; i++)
            {
                if (char.IsNumber(newNameArray[i])) //runs through every character in the string and checks for numbers
                {
                    return "Invalid name: contains numbers ";
                }                
            }

            return "";
        }

        public string SetName(string newName)
		{
            string result = CheckName(newName); //result is set to an empty string if everything okay
            if (result.Length == 0)
            {
                name = newName;
                return "";
            }
            return result; //result contains error message
		}

        #endregion 

        #region Address & Telephone Number Management

        private string address1;
        private string address2;
        private string county;
        private string postcode;
        private string telephone;
        private string mobile;

        public string GetAddress1()
        {
            return address1;
        }        

        public string GetAddress2()
        {
            return address2;
        }

        public string GetCounty()
        {
            return county;
        }

        public string GetPostcode()
        {
            return postcode;
        }

        public string GetTelephone()
        {
            return telephone;
        }

        public string GetMobile()
        {
            return mobile;
        }

        public string CheckAddress(string newAddress)
        {
            if (newAddress.Length == 0)
            {
                return "Empty Address ";
            }
            return "";
        }

        public string SetAddress1(string newAddress)
        {
            string result = CheckAddress(newAddress); //result is set to an empty string if everything okay
            if (result.Length == 0)
            {
                address1 = newAddress;
                return "";
            }

            return result; //result contains error message
        }

        public string SetAddress2(string newAddress)
        {
            string result = CheckAddress(newAddress); //result is set to an empty string if everything okay
            if (result.Length == 0)
            {
                address2 = newAddress;
                return "";
            }

            return result; //result contains error message 
        }

        public string SetCounty(string newCounty)
        {
            string result = CheckName(newCounty); //result is set to an empty string if everything okay
            if (result.Length == 0)
            {
                county = newCounty;
                return "";
            }

            return "Invalid County ";
        }

        public string SetPostcode(string newPostcode)
        {
            string result = CheckAddress(newPostcode); //result is set to an empty string if everything okay
            if (result.Length == 0)
            {
                postcode = newPostcode;
                return "";
            }

            return "Invalid Postcode ";
        }

        public string CheckTelephone(string telephoneNumber)
        {
            if (telephoneNumber.Length == 0)
            {
                return "Empty Telephone Number ";
            }
            char[] newNumberArray = telephoneNumber.ToCharArray();
            for (int i = 0; i < telephoneNumber.Length; i++)
            {
                if (!char.IsNumber(newNumberArray[i])) //Checks all characters in the string to see if any are not numbers
                {
                    return "Invalid Number: Not All Characters Are Numbers ";
                }                
            }

            return "";
        }

        public string SetTelephone(string newTelephone)
        {
            string result = CheckTelephone(newTelephone); //result is set to an empty string if everything okay
            if (result.Length == 0)
            {
                telephone = newTelephone;
                return "";
            }

            return result; //result contains error message
        }

        public string SetMobile(string newMobile)
        {
            string result = CheckTelephone(newMobile); //result is set to an empty string if everything okay
            if (result.Length == 0)
            {
                mobile = newMobile;
                return "";
            }

            return result; //result contains error message
        }

        #endregion

        #region Salary & Wage Management

        private decimal salary;
        private decimal wage;

        public decimal GetSalary()
        {
            return salary;
        }

        public decimal GetWage()
        {
            return wage;
        }

        public string SetSalary(decimal newSalary)
        {
            string result = CheckSalary(newSalary);
            if (result.Length == 0)
            {
                salary = newSalary;
                return "";
            }
            return result;
        }

        public string SetWage(decimal newWage)
        {
            string result = CheckWage(newWage);
            if (result.Length == 0)
            {
                wage = newWage;
                return "";
            }
            return result;
        }

        public string CheckSalary(decimal newSalary)
        {
            if (newSalary < 0)
            {
                return "Invalid Salary: Salary cannot be a negative amount.";
            }
            return "";
        }

        public string CheckWage(decimal newWage)
        {
            if (newWage < 0)
            {
                return "Invalid Wage: Wage cannot be a negative amount.";
            }
            return "";
        }

        #endregion

        private ArrayList tasks = new ArrayList();

        public string AddTask(ITaskAssign taskAssign)
        {
            tasks.Add(taskAssign);
            return "";
        }

        public string RemoveTask(ITaskAssign taskAssign)
        {
            tasks.Remove(taskAssign);
            return "";
        }

        public ArrayList GetTaskInstances()
        {
            return tasks;
        }
    }
}