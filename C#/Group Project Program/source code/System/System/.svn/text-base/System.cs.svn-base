using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace SystemManagement
{
    public interface ISystemControl
    {
        /// <summary>
        /// Finds the employee instance in the hash table
        /// </summary>
        /// <param name="name">the name of the employee to be found</param>
        /// <returns>
        /// an employee instance
        /// </returns>
        IEmployee FindEmployeeByName(string name);

        /// <summary>
        /// Adds an employee to the hash table
        /// </summary>
        /// <param name="employee">the employee class instance to be added</param>
        /// <returns>
        /// an empty string if everything went well, an error message if not
        /// </returns>
        string AddEmployee(IEmployee employee);

        /// <summary>
        /// Deletes an employee from the hash table
        /// </summary>
        /// <param name="employee">the name of the employee to be deleted</param>
        /// <returns>
        /// an empty string if everything went well, an error message if not
        /// </returns>
        string DeleteEmployee(IEmployee employee);

        /// <summary>
        /// Finds the task instance in the hash table
        /// </summary>
        /// <param name="name">the name of the task to be found</param>
        /// <returns>
        /// a task instance
        /// </returns>
        ITask FindTaskByName(string name);

        /// <summary>
        /// adds a task instance to the hash table
        /// </summary>
        /// <param name="task">the task to be added</param>
        /// <returns>
        /// an empty string if everything went well, an error message if not
        /// </returns>
        string AddTask(ITask task);

        /// <summary>
        /// deletes a task instance from the hash table
        /// </summary>
        /// <param name="task">the task to be deleted</param>
        /// <returns>
        /// an empty string if everything went well, an error message if not
        /// </returns>
        string DeleteTask(ITask task);

        /// <summary>
        /// links an employee to a task with a taskAssign
        /// </summary>
        /// <param name="taskAssign">the new taskAssign to be linked to the employee</param>
        /// <param name="task">the task to be linked to the employee</param>
        /// <param name="employee">the employee to be linked</param>
        /// <returns>
        /// an empty string if everything went well, an error message if not
        /// </returns>
        string AssignEmployeeToTask(ITaskAssign taskAssign, ITask task, IEmployee employee);

        /// <summary>
        /// Unlinks an employee to a task with a taskAssign
        /// </summary>
        /// <param name="taskAssign">the taskAssign to be unlinked to the employee</param>
        /// <param name="task">the task to be unlinked to the employee</param>
        /// <param name="employee">the employee to be unlinked</param>
        /// <returns>
        /// an empty string if everything went well, an error message if not
        /// </returns>
        string UnassignEmployeeToTask(ITaskAssign taskAssign, ITask task, IEmployee employee);
    }

    [Serializable()]
    public class SystemControl : ISystemControl
    {
        private Hashtable employeeName = new Hashtable();

        public IEmployee FindEmployeeByName(string name)
        {
            return employeeName[name] as IEmployee;
        }

        public string AddEmployee(IEmployee employee)
        {            
            employeeName.Add(employee.GetName(), employee);
            return "";
        }

        public string DeleteEmployee(IEmployee employee)
        {            
            employeeName.Remove(employee.GetName());
            return "";
        }

        private Hashtable taskName = new Hashtable();

        public ITask FindTaskByName(string name)
        {
            return taskName[name] as ITask;
        }

        public string AddTask(ITask task)
        {
            taskName.Add(task.GetTitle(), task);
            return "";
        }

        public string DeleteTask(ITask task)
        {
            taskName.Remove(task.GetTitle());
            return "";
        }

        public string AssignEmployeeToTask(ITaskAssign taskAssign, ITask task, IEmployee employee)
        {
            task.AddStaff(taskAssign);
            employee.AddTask(taskAssign);
            return "";
        }

        public string UnassignEmployeeToTask(ITaskAssign taskAssign, ITask task, IEmployee employee)
        {
            task.RemoveStaff(taskAssign);
            employee.RemoveTask(taskAssign);
            return "";
        }


    }
}
