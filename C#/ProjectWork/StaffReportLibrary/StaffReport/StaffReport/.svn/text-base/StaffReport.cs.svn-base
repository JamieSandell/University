using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

/// README - I still think the 'AmIOnThisTask' method is bad design?
/// And should be done outside the StaffReport class?
/// If so the staff report is supposed show all the tasks the staff is working on
/// but I'm not sure how to do this.
/// Unless of course this is the correct way to do things?

namespace systemManagement
{
    public interface IStaffReport
    {
        /// <summary>
        /// Checks whether or not the employee is on task supplied
        /// It will be used like so
        /// for (int i = 0; i < numberofTasks; i++)
        /// {
        ///     StaffReport staffReport[i] = new StaffReport(employee, task[i]);
        ///     bool result = staffReport[i].AmIOnTheTask();
        ///     if (result)
        ///     {
        ///         taskCompletion = staffReport[i].GetTasksCompletions
        ///         taskCompletionArrayList.Add(taskCompletion);
        ///         // etc
        ///     }
        ///     
        /// }
        /// </summary>
        /// <param name="task">the instance of the task</param>
        /// <returns></returns>
        bool AmIOnThisTask(Task task);

        /// <summary>
        /// Find out the tasks completion
        /// </summary>
        /// <returns>Task completion</returns>
        int GetTaskCompletion();

        /// <summary>
        /// Find out the cost of the task
        /// </summary>
        /// <returns>The cost of the task</returns>
        decimal GetTaskCosts();
    }
    public class StaffReport : IStaffReport
    {
        private Task task;
        private Employee employee;
        private TaskAssign taskAssign;

        public StaffReport(Task task, Employee employee)
        {
            this.task = task;
            this.employee = employee;
        }

        public bool AmIOnThisTask(Task task)
        {
            ArrayList staffList = new ArrayList();
            staffList = task.GetStaff();
            if (staffList.Contains(task)) // Staff is on the task
            {
                return true;
            }
            return false; // Not on the task
        }

        public int GetTaskCompletion()
        {
            int taskCompletion = task.GetTaskCompletion();
            return taskCompletion;
        }

        public decimal GetTaskCosts()
        {
            string stringHoursWorked;
            decimal salary;
            decimal hoursWorked;
            decimal taskCosts;
            // Cost per task  based on salary and man hours worked for
            // each task
            salary = employee.GetSalary();
            stringHoursWorked = taskAssign.GetHours();
            hoursWorked = Convert.ToDecimal(stringHoursWorked);
            taskCosts = salary * hoursWorked;
            return taskCosts;
        }
    }
}
