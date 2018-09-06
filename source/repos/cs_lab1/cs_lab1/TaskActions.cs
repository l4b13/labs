using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cs_lab1
{
    class TaskActions
    {
        List<Tasks> TaskList = new System.Collections.Generic.List<Tasks>();

        public void NewTask ()
        {
            string title, description, tag;
            DateTime date;
            List<string> tags = new List<string>();

            Menu.NewTask();

            do
            {
                Menu.ParseTitle();
                title = Console.ReadLine();
                if (title != "")
                {
                    break;
                }
                else
                {
                    Console.WriteLine("\tField is empty, try again.\n");
                }
            } while (true);//parsing title

            do
            {
                Menu.ParseDescription();
                description = Console.ReadLine();
                if (description != "")
                {
                    break;
                }
                else
                {
                    Console.WriteLine("\tField is empty, try again.\n");
                }
            } while (true);//parsing description

            do
            {
                Menu.ParseDeadline();
                if (DateTime.TryParse(Console.ReadLine(), out date))
                {
                    break;
                }
                else
                {
                    Console.WriteLine("\tIncorrect value, type by pattern.\n");
                }
            } while (true);//parsing deadline

            Menu.ParseTags();
            do
            {
                Console.Write("\t");
                tag = Console.ReadLine();
                if (tag != "")
                {
                    tags.Add(tag);
                } else
                {
                    break;
                }
            } while (true);
            TaskList.Add(new Tasks() { Title = title, Description = description, Deadline = date, Tag = tags });
        } 

        public void SearchTasks()
        {
            string filter;
            Boolean status;
            status = false;

            Menu.SearchTasks();

            filter = Console.ReadLine();
            foreach (Tasks tsk in TaskList)
            {
                foreach (string tg in tsk.Tag)
                {
                    if (tg == filter)
                    {
                        status = true;
                        break;
                    }
                }
                if (status)
                {
                    Menu.Output(tsk.Title, tsk.Description, tsk.Deadline, tsk.Tag);
                    status = false;
                }
            }
            Menu.Wait();
        }

        public void LastTasks()
        {
            int taskin, arrayin;
            taskin = 0;
            arrayin = 0;
            int[] valuear = new int[100];
            int[] indexar = new int[100];

            Menu.LastTasks();

            foreach (Tasks tsk in TaskList)
            {
                int currenttime, tasktime;
                currenttime = DateTime.Now.Year * 10000 + DateTime.Now.Month * 100 + DateTime.Now.Day;
                tasktime = tsk.Deadline.Year * 10000 + tsk.Deadline.Month * 100 + tsk.Deadline.Day;
                if (tasktime >= currenttime)
                {
                    valuear[arrayin] = tasktime;
                    indexar[arrayin] = taskin;
                    arrayin++;
                }
                taskin++;
            }
            for (int i = 0; i < arrayin - 1; i++)
            {
                for (int j = i + 1; j < arrayin; j++)
                {
                    if (valuear[i] > valuear[j])
                    {
                        int storage = valuear[i];
                        valuear[i] = valuear[j];
                        valuear[j] = storage;
                        storage = indexar[i];
                        indexar[i] = indexar[j];
                        indexar[j] = storage;
                    }
                }
            }
            for (int i = 0; i < arrayin; i++)
            {
                int j = indexar[i];
                Menu.Output(TaskList[j].Title, TaskList[j].Description, TaskList[j].Deadline, TaskList[j].Tag);
            }
            Menu.Wait();
        }

        public void Exit()
        {
            Environment.Exit(0);
        }
    }
}
