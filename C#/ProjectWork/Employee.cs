using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace systemManagement
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
        /// Gets the forename of the Employee
        /// </summary>
        /// <returns>
        /// The employee's forename as currently stored in the Employee class
        /// </returns>
        string GetForename();

        /// <summary>
        /// Gets the surname of the Employee
        /// </summary>
        /// <returns>
        /// The employee's surname as currently stored in the Employee class
        /// </returns>
        string GetSurname();

        /// <summary>
        /// Checks to see if a name is valid
        /// </summary>
        /// <param name="">The name to be checked</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string CheckName(string newName);

        /// <summary>
        /// Sets the forename of the employee, calls CheckName to make sure it's okay
        /// </summary>
        /// <param name="">the new forename to be set</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string SetForename(string newForename);

        /// <summary>
        /// Sets the surname of the employee, calls CheckName to make sure it's okay
        /// </summary>
        /// <param name="">the new surname to be set</param>
        /// <returns>
        /// An empty string if successful, otherwise an error message
        /// </returns>
        string SetSurname(string newSurname);

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
    }

    public class Employee : IEmployee
    {
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


        private string forename;
        private string surname;

        public string GetForename()
        {
            return forename;
        }

        public string GetSurname()
        {
            return surname;
        }

        public string CheckName(string newName)
        {
            if (newName.Length == 0)
            {
                return "Empty name ";
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

        public string SetForename(string newForename)
		{
            string result = CheckName(newForename); //result is set to an empty string if everything okay
            if (result.Length == 0)
            {
                forename = newForename;
                return "";
            }
            return result; //result contains error message
		}

        public string SetSurname(string newSurname)
        {
            string result = CheckName(newSurname); //result is set to an empty string if everything okay
            if (result.Length == 0)
            {
                surname = newSurname;
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
            if (newSalary > 0)
            {
                salary = newSalary;
                return "";
            }
            return "Salary cannot be a negative amount ";
        }

        public string SetWage(decimal newWage)
        {
            if (newWage > 0)
            {
                wage = newWage;
                return "";
            }
            return "Wage cannot be a negative amount ";
        }

        #endregion
    }
}