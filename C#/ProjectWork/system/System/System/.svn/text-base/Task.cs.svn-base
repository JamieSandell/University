using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;


namespace SystemManagement
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
        string CheckEndDate(DateTime DateOne, DateTime DateTwo);

        /// <summary>
        /// Add a staff to a task - use the instances staff arraylist
        /// </summary>
        /// <param name="inStaffName">The name of the staff member</param>
        /// <returns>An empty string if everything went ok</returns>
        string AddStaff(ITaskAssign taskAssign);

        /// <summary>
        /// Remove a staff from a task - use the instances staff arraylist
        /// </summary>
        /// <param name="inStaffName">The name of the staff member</param>
        /// <returns>An empty string if everything went ok</returns>
        string RemoveStaff(ITaskAssign taskAssign);

        /// <summary>
        /// Get all the staff working on a particular task
        /// </summary>
        /// <returns>An arraylist of all the staff working on a particular task</returns>
        ArrayList GetStaff();

        /// <summary>
        /// Get an average of the percentage complete from each employee on the task
        /// </summary>
        /// <param name="taskAssign">The instance of TaskAssign to get the percentage from</param>
        /// <param name="task">The instance of task to get the numberOfPeopleWorkingOnTheTask</param>
        /// <returns>An int of the average percentage complete</returns>
        int GetPercentageComplete(ITaskAssign taskAssign, ITask task);

        /// <summary>
        /// Get the number of people working on the task.
        /// </summary>
        /// <returns>An int of the number of people working on the task.</returns>
        int GetNumberOfPeopleOnTheTask();

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
        //private static int taskID = 0; // Later this should be read in from a file

        public Task(string inTitle)//, string inDescription, DateTime inStartDate,
            //DateTime inEndDate, ArrayList inStaff)
        {
            title = inTitle;
            startDate = DateTime.Now;
            endDate = DateTime.Now;
            //description = inDescription;
            //startDate = inStartDate;
            //endDate = inEndDate;
            //staff = inStaff;
            //taskID++;
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
            string result = CheckEndDate(GetStartDate(), inEndDate);
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

        public string CheckEndDate(DateTime dateOne, DateTime dateTwo)
        {
            //DateTime dateOne = GetStartDate();
            //DateTime dateTwo = GetEndDate();
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

        public string AddStaff(ITaskAssign taskAssign)
        {
            staff.Add(taskAssign);
            return ""; // Everything went ok
        }

        public string RemoveStaff(ITaskAssign taskAssign)
        {
            staff.Remove(taskAssign); // This needs changing to something unique or use hashtable?
            return ""; // Everything went ok
        }

        public ArrayList GetStaff()
        {
            return staff;
        }

        public int GetPercentageComplete(ITaskAssign taskAssign, ITask task)
        {
            int average;
            int totalPercentageComplete = 0;
            int numberOfPeopleOnTheTask;
            totalPercentageComplete += taskAssign.GetPercentageComplete();
            numberOfPeopleOnTheTask = task.GetNumberOfPeopleOnTheTask();
            average = totalPercentageComplete / numberOfPeopleOnTheTask;

            return average;
        }

        public int GetNumberOfPeopleOnTheTask()
        {
            return staff.Count;
        }

    }
}
