using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace systemManagement
{
    /// README : NOTES
    /// If you look at the addstaff method you can see we will definitely
    /// need to have a taskID and taskName in a hashtable.
    /// Obviously this will be in the control class but just something to keep in mind,
    /// when looking at the below code.


    public interface ITask
    {
        /// <summary>
        /// Set the title of the task
        /// </summary>
        /// <param name="inTitle">The name of the new task</param>
        /// <returns>An empty string if everything went well</returns>
        string SetTitle(string inTitle);

        /// <summary>
        /// Get the title of the task
        /// </summary>
        /// <returns>The task's title</returns>
        string GetTitle();

        /// <summary>
        /// Check the title of the task is valid
        /// </summary>
        /// <param name="inTitle">The title of the task to validae</param>
        /// <returns>An empty string if everything went well</returns>
        string CheckTitle(string inTitle);

        /// <summary>
        /// Set the task's description
        /// </summary>
        /// <param name="inDescription">The description of the task</param>
        /// <returns>An empty string if everything goes well</returns>
        string SetDescription(string inDescription);

        /// <summary>
        /// Get the description of the task
        /// </summary>
        /// <returns>The description of the task</returns>
        string GetDescription();

        /// <summary>
        /// Validate the description of the task
        /// </summary>
        /// <param name="inDescription">The task's description</param>
        /// <returns>An empty string if it was successful</returns>
        string CheckDescription(string inDescription);

        /// <summary>
        /// Set the start date of the task
        /// </summary>
        /// <param name="inStartDate">The start date of the task</param>
        /// <returns>An empty string if everything went ok</returns>
        string SetStartDate(DateTime inStartDate);

        /// <summary>
        /// Get the start date of the task
        /// </summary>
        /// <returns>The start date of the task</returns>
        DateTime GetStartDate();

        /// <summary>
        /// Set the end date of the task
        /// </summary>
        /// <param name="inEndDate">The end date of the task</param>
        /// <returns>Returns an empty string if everything went ok</returns>
        string SetEndDate(DateTime inEndDate);

        /// <summary>
        /// Get the end date of the task
        /// </summary>
        /// <returns>The end date of the task</returns>
        DateTime GetEndDate();

        /// <summary>
        /// Make sure the end date is not before the start date
        /// </summary>
        /// <returns>An empty string if everything went ok</returns>
        string CheckEndDate();

        /// <summary>
        /// Add a staff to a task - use the instances staff arraylist
        /// </summary>
        /// <param name="inStaffName">The name of the staff member</param>
        /// <returns>An empty string if everything went ok</returns>
        string AddStaff(string inStaffName);

        /// <summary>
        /// Remove a staff from a task - use the instances staff arraylist
        /// </summary>
        /// <param name="inStaffName">The name of the staff member</param>
        /// <returns>An empty string if everything went ok</returns>
        string RemoveStaff(string staffName);

        /// <summary>
        /// Get all the staff working on a particular task
        /// </summary>
        /// <returns>An arraylist of all the staff working on a particular task</returns>
        ArrayList GetStaff();

        /// <summary>
        /// Get the tasks completion value (in percentage)
        /// </summary>
        /// <returns>The task completion value (in percentage)</returns>
        int GetTaskCompletion();

        /// <summary>
        /// Set the tasks completion value (in percentage)
        /// </summary>
        /// <param name="inTaskCompletion">The task completion's value</param>
        /// <returns>The task's completion value (in percentage)</returns>
        string SetTaskCompletion(int inTaskCompletion);

    }

    public class Task : ITask
    {
        //private Hashtable staffNames = new Hashtable();
        //private Hashtable staffIDs = new Hashtable();
        //private Hashtable taskNames = new Hashtable();
        //private Hashtable taskIDs = new Hashtable();

        private string title;
        private string description;
        private DateTime startDate;
        private DateTime endDate;
        private ArrayList staff = new ArrayList();
        private static int taskID = 0; // Later this should be read in from a file
        private int taskCompletion = 0;

        public Task(string inTitle, string inDescription, DateTime inStartDate,
            DateTime inEndDate, ArrayList inStaff) /* Had to add ArrayList back in,
             even if the arraylist is set to empty (meaning to staff assigned to task yet),
             this is so each instance of the task has its own set of staff members assigned
             to it */
        {
            taskCompletion = 0;
            title = inTitle;
            description = inDescription;
            startDate = inStartDate;
            endDate = inEndDate;
            staff = inStaff; // Initially in the instance no staff are added to the task
            taskID++;
        }

        public string SetTitle(string inTitle)
        {
            string result = CheckTitle(inTitle);
            if (result.Length == 0)
            {
                title = inTitle;
                return ""; // Everything went ok
            }
            return result;
        }

        public string GetTitle()
        {
            return title;
        }

        public string CheckTitle(string inTitle)
        {
            if (inTitle == "") // Empty string
            {
                return "The title of the task cannot be blank.";
            }
            if (inTitle.StartsWith(" "))// Cannot start with a space
            {
                return "The title of the task cannot begin with an empty space.";
            }
            return ""; // Everything went ok
        }

        public string SetDescription(string inDescription)
        {
            string result = CheckDescription(inDescription);
            if (result.Length == 0)
            {
                description = inDescription;
                return ""; // Everything went ok
            }
            return result;
        }

        public string GetDescription()
        {
            return description;
        }

        public string CheckDescription(string inDescription)
        {
            if (inDescription == "") // Empty string
            {
                return "The description of the task cannot be blank.";
            }
            if(inDescription.StartsWith(" ")) // Cannot start with a space
            {
                return "The description of the task cannot begin with an empty space.";
            }
            return ""; // Everything went ok
        }

        public string SetStartDate(DateTime inStartDate)
        {
            startDate = inStartDate;
            return ""; // Everything went ok
        }

        public DateTime GetStartDate()
        {
            return startDate;
        }

        public string SetEndDate(DateTime inEndDate)
        {
            string result = CheckEndDate();
            if (result.Length == 0)
            {
                endDate = inEndDate;
                return ""; // Everything went ok
            }
            return result;
        }

        public DateTime GetEndDate()
        {
            return endDate;
        }

        public string CheckEndDate()
        {
            DateTime dateOne = GetStartDate();
            DateTime dateTwo = GetEndDate();
            TimeSpan span = dateTwo.Subtract(dateOne); // Get the difference between them

            if (span.TotalMinutes == 0) // The same
            {
                return "The end date cannot be set to the same as the start date.";
            }
            if (span.TotalMinutes < 0) // endDate is before the startDate
            {
                return "The end date cannot be set to before the start date.";
            }
            return ""; // Everything went ok
        }

        public string AddStaff(string inStaffName)
        {
            staff.Add(inStaffName);
            return ""; // Everything went ok
        }

        public string RemoveStaff(string inStaffName)
        {
            staff.Remove(inStaffName); // This needs changing to something unique or use hashtable?
            return ""; // Everything went ok
        }

        public ArrayList GetStaff()
        {
            return staff;
        }

        public string SetTaskCompletion(int inTaskCompletion)
        {
            if ((inTaskCompletion < 0) || (inTaskCompletion > 100))
            {
                return "The task's completion value is in percentage and must be between 0 and a 100.";
            }
            taskCompletion = inTaskCompletion;
            return ""; // Everything went well
        }

        public int GetTaskCompletion()
        {
            return taskCompletion;         
        }

    }
}
