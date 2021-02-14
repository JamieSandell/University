using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace SystemManagement
{
    public interface ISystemControl
    {
        IEmployee FindEmployeeByName(string name);

        string AddEmployee(IEmployee employee);

        string DeleteEmployee(IEmployee employee);

        ITask FindTaskByName(string name);

        string AddTask(ITask task);

        string DeleteTask(ITask task);

        string AssignEmployeeToTask(ITaskAssign taskAssign, ITask task, IEmployee employee);
    }

    public class SystemControl : ISystemControl
    {
        private Hashtable employeeName = new Hashtable();

        public IEmployee FindEmployeeByName(string name)
        {
            return employeeName[name] as IEmployee;
        }

        public string AddEmployee(IEmployee employee)
        {
            string name = employee.GetName();
            employeeName.Add(name, employee);
            return "";
        }

        public string DeleteEmployee(IEmployee employee)
        {
            string name = employee.GetName();
            employeeName.Remove(name);
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
