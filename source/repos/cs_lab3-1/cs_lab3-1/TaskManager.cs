using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cs_lab3_1
{
    class TaskManager
    {
        public void NewTask(List<Task> TaskList, string t, string d, DateTime dl, List<string> tags)
        {
            TaskList.Add(new Task() { Title = t, Description = d, Deadline = dl, Tag = tags });
        }

        public List<Task> Search(List<Task> TaskList, string tag)
        {
            return TaskList.FindAll(t => t.Tag.Contains(tag));
        }

        public List<Task> LastTasks(List<Task> TaskList)
        {
            return TaskList.FindAll(t => t.Deadline >= DateTime.Now);
        }
    }
}