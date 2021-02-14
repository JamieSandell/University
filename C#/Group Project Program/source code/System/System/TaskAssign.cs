using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace SystemManagement
{
    public interface ITaskAssign
    {
        /// <summary>
        /// returns the number of hours worked as a string
        /// </summary>        
        /// <returns>
        /// the number of hours worked
        /// </returns>
        string GetHours();

        /// <summary>
        /// Checks a timespan to make sure it's valid
        /// </summary>
        /// <param name="time">the time to be checked</param>
        /// <returns>
        /// an empty string if everything went well, an error message if not
        /// </returns>
        string CheckTime(TimeSpan time);

        /// <summary>
        /// increments the hours worked by the input value
        /// </summary>
        /// <param name="name">the time to be added to the number of hours worked</param>
        /// <returns>
        /// an empty string if everything went well, an error message if not
        /// </returns>
        string AppendHours(TimeSpan time);

        /// <summary>
        /// gets the date employee was assigned to a task
        /// </summary>        
        /// <returns>
        /// a DateTime containing the date an employee was assigned to a task
        /// </returns>
        DateTime GetDateAssigned();

        /// <summary>
        /// gets the date an employee was unassigned to a task
        /// </summary>        
        /// <returns>
        /// the date the employee was unassigned
        /// </returns>
        DateTime GetDateUnassigned();

        /// <summary>
        /// Checks two dates to make sure they are valid
        /// </summary>
        /// <param name="inDateAssigned">the first date to be checked</param>
        /// <param name="inDateUnassigned">the second date to be checked</param>
        /// <returns>
        /// an empty string if everything went well, an error message if not
        /// </returns>
        string CheckDate(DateTime inDateAssigned, DateTime inDateUnassigned);

        /// <summary>
        /// Sets the date assigned
        /// </summary>
        /// <param name="inDate">the new date</param>
        /// <returns>
        /// an empty string if everything went well, an error message if not
        /// </returns>
        string SetDateAssigned(DateTime inDate);

        /// <summary>
        /// sets the date unassigned
        /// </summary>
        /// <param name="inDate">the new date</param>
        /// <returns>
        /// an empty string if everything went well, an error message if not
        /// </returns>
        string SetDateUnassigned(DateTime inDate);

        /// <summary>
        /// gets the instance of a task the task assign is linking to
        /// </summary>        
        /// <returns>
        /// the relevant Task instance
        /// </returns>
        ITask GetTask();

        /// <summary>
        /// gets the instance of employee the task assing is linking to
        /// </summary>        
        /// <returns>
        /// an employee instance
        /// </returns>
        IEmployee GetEmployee();

        /// <summary>
        /// Sets the percentage complete of the task
        /// </summary>
        /// <param name="inPercentageComplete">the new percetage</param>
        /// <returns>
        /// an empty string if everything went well, an error message if not
        /// </returns>
        string SetPercentageComplete(decimal inPercentageComplete);

        /// <summary>
        /// Checls the percentage complete
        /// </summary>
        /// <param name="inPercentageComplete">the percentage to be checked</param>
        /// <returns>
        /// aan empty string if everything went well, an error message if not
        /// </returns>
        string CheckPercentageComplete(decimal inPercentageComplete);

        /// <summary>
        /// Gets the percentage complete of the task
        /// </summary>        
        /// <returns>
        /// a decimal containing the percentage complete
        /// </returns>
        decimal GetPercentageComplete();



    }

    [Serializable()]
    public class TaskAssign : ITaskAssign
    {
        private IEmployee employee;
        private ITask task;
        private TimeSpan timeWorked;
        private DateTime dateAssigned;
        private DateTime dateUnassigned;
        private decimal percentageComplete;


        public TaskAssign(ITask task, IEmployee employee)
        {
            this.employee = employee;
            this.task = task;
            dateAssigned = task.GetStartDate();
            dateUnassigned = task.GetEndDate();
            percentageComplete = 0;
            // timeWorked = TimeSpan.MinValue; // This should be 0?
            timeWorked = TimeSpan.Zero;
        }

        public string GetHours()
        {
            return timeWorked.Hours.ToString();
        }

        public string CheckTime(TimeSpan time)
        {
            if (time.Seconds < 0)
            {
                return "cannot enter a negative time";
            }
            return "";
        }

        public string AppendHours(TimeSpan time)
        {
            string result = CheckTime(time);
            if (result.Length == 0)
            {
                timeWorked += time;
            }
            return result;
        }

        public DateTime GetDateAssigned()
        {
            return dateAssigned;
        }

        public DateTime GetDateUnassigned()
        {
            return dateUnassigned;
        }

        public string CheckDate(DateTime inDateAssigned, DateTime inDateUnassigned)
        {
            TimeSpan reply = inDateAssigned - task.GetStartDate();
            TimeSpan time = inDateUnassigned - inDateAssigned;
            if (time.Minutes < 0)
            {
                return "The date unassigned cannot be before the date assigned";
            }
            if (reply.Minutes < 0)
            {
                return "The date assigned cannot be before the start date of the task";
            }
            return "";
        }

        public string SetDateAssigned(DateTime inDate)
        {
            string reply = CheckDate(inDate, dateUnassigned);
            if (reply.Length > 0)
            {
                return reply;
            }
            dateAssigned = inDate;
            return "";
        }

        public string SetDateUnassigned(DateTime inDate)
        {
            string reply = CheckDate(dateAssigned, inDate);
            if (reply.Length > 0)
            {
                return reply;
            }
            dateUnassigned = inDate;
            return "";
        }

        public ITask GetTask()
        {
            return task;
        }

        public IEmployee GetEmployee()
        {
            return employee;
        }

        public string SetPercentageComplete(decimal inPercentageCompletion)
        {
            string reply = CheckPercentageComplete(inPercentageCompletion);
            if (reply.Length > 0)
            {
                return reply;
            }
            percentageComplete = inPercentageCompletion;
            return "";
        }

        public string CheckPercentageComplete(decimal inPercentageCompletion)
        {
            if ((inPercentageCompletion < 0) || (inPercentageCompletion > 100))
            {
                return "Invalid Percentage : You must enter an integer between 0 and 100.";
            }
            return ""; // All went well
        }

        public decimal GetPercentageComplete()
        {
            return percentageComplete;
        }
    }    
}
