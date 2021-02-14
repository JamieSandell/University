using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Utilities
{
    public interface IValidation
    {
        /// <summary>
        /// Checks to see if the string is a valid number
        /// </summary>
        /// <param name="inNumber">The number to validate</param>
        /// <param name="outNumber">The number converted from inNumber</param>
        /// <returns>True if it's a valid number, else False</returns>
        bool IsNumber(string inNumber, out double outNumber);

        /// <summary>
        /// Validates the string passed in
        /// </summary>
        /// <param name="inString">The string to be validated</param>
        /// <returns>True if the string is valid, else false</returns>
        bool IsValidString(string inString);
    }

    public class Validation:IValidation
    {
        public bool IsNumber(string inNumber, out double outNumber)
        {
            if (double.TryParse(inNumber, out outNumber))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool IsValidString(string inString)
        {
            if ( (inString.StartsWith(" ")) || (inString.Length==0) )
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}
