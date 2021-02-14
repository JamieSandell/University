using System;
using System.Collections.Generic;
using System.Text;

namespace systemManagement
{
    public interface ITaskAssign
    {      

        string GetHours();

        string CheckTime(TimeSpan time);

        string AppendHours(TimeSpan time);
    }


    public class TaskAssign : ITaskAssign
    {
        private Employee employee;
        private Task task;
        private TimeSpan timeWorked;

        public TaskAssign(Task task, Employee employee)
        {
            this.employee = employee;
            this.task = task;
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
    }
}
