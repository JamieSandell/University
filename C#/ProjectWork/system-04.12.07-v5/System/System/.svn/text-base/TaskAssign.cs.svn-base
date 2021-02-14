using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace SystemManagement
{
    public interface ITaskAssign
    {      

        string GetHours();

        string CheckTime(TimeSpan time);

        string AppendHours(TimeSpan time);

        DateTime GetDateAssigned();

        DateTime GetDateUnassigned();

        string CheckDate(DateTime inDateAssigned, DateTime inDateUnassigned);

        string SetDateAssigned(DateTime inDate);

        string SetDateUnassigned(DateTime inDate);

        ITask GetTask();

        IEmployee GetEmployee();

        string SetPercentageComplete(decimal inPercentageComplete);

        string CheckPercentageComplete(decimal inPercentageComplete);

        decimal GetPercentageComplete();



    }


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
            timeWorked = TimeSpan.MinValue;
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
                return "You must enter an integer between 0 and 100.";
            }
            return ""; // All went well
        }

        public decimal GetPercentageComplete()
        {
            return percentageComplete;
        }
    }    
}
