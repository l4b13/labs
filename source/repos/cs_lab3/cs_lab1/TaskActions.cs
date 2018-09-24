using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cs_lab1
{
    class TaskActions
    {
        public string path;

        List<Tasks> TaskList = new List<Tasks>();

        public void NewTask ()
        {
            string title, description, tag;
            DateTime date;
            List<string> tags = new List<string>();

            Menu.NewTask();

            do
            {
                Menu.ParseTitle();
                title = Menu.InputString();
                if (title != "")
                {
                    break;
                }
                else
                {
                    Menu.EmptyField();
                }
            } while (true);//parsing title

            do
            {
                Menu.ParseDescription();
                description = Menu.InputString();
                if (description != "")
                {
                    break;
                }
                else
                {
                    Menu.EmptyField();
                }
            } while (true);//parsing description

            do
            {
                Menu.ParseDeadline();
                if (DateTime.TryParse(Menu.InputString(), out date))
                {
                    break;
                }
                else
                {
                    Menu.IncorrectValue();
                }
            } while (true);//parsing deadline

            Menu.ParseTags();
            do
            {
                Menu.Tab();
                tag = Menu.InputString();
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

        //public IEnumerable<Task> Search(params string[] tags)
        public void SearchTasks()
        {
            string filter;
            Boolean status;
            status = false;

            Menu.SearchTasks();

            filter = Menu.InputString();
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
                    Menu.OutputTask(tsk.Title, tsk.Description, tsk.Deadline, tsk.Tag);
                    status = false;
                }
            }
            Menu.Wait();
        }

        public void LastTasks()
        {
            Menu.LastTasks();

            TaskList.Where(t => t.Deadline >= DateTime.Now).OrderBy(t => t.Deadline);
                Menu.OutputTask(TaskList[j].Title, TaskList[j].Description, TaskList[j].Deadline, TaskList[j].Tag);
            Menu.Wait();
        }

        public void Exit()
        {
            Menu.End();
        }

        public void NewTaskList()
        {
            TaskList.Clear();
            TaskList.TrimExcess();
            path = "";
            Console.WriteLine("new_created");
        }

        public void LoadTaskList()
        {
            TaskList.Clear();
            TaskList.TrimExcess();
            Menu.LoadTaskList();
            path = Menu.InputString();
            try {
                using (StreamReader sr = new StreamReader(path, Encoding.Default))
                    {
                    string line;
                    int i = 0;
                    while ((line = sr.ReadLine()) != null)
                    {
                        if (i > 0)
                        {
                            List<string> lTags = new List<string>();
                            DateTime lDate;

                            int tz = line.IndexOf(";");
                            string lTitle = line.Substring(0, tz);
                            line = line.Remove(0, tz + 1);

                            tz = line.IndexOf(";");
                            string lDesc = line.Substring(0, tz);
                            line = line.Remove(0, tz + 1);

                            tz = line.IndexOf(";");
                            string lDead = line.Substring(0, tz);
                            DateTime.TryParse(lDead, out lDate);
                            line = line.Remove(0, tz + 1);

                            if (line[line.Length - 1] != ';')
                            {
                                line = line + ';';
                            }
                            while (line.Length > 0)
                            {
                                tz = line.IndexOf(";");
                                lTags.Add(line.Substring(0, tz));
                                line = line.Remove(0, tz + 1);
                            }
                            TaskList.Add(new Tasks() { Title = lTitle, Description = lDesc, Deadline = lDate, Tag = lTags });
                        }
                        i++;
                    }
                }
            } catch
            {
                Menu.IncorrectValue();
            }
        }

        public void SaveTaskList()
        {
            if (path == "")
            {
                Menu.SaveTaskList();
                path = Menu.InputString();
            } else
            {
                FileInfo f = new FileInfo(path);
                f.Delete();
                f.Create();
                f = null;
            }
            using (StreamWriter sw = new StreamWriter(path, true, Encoding.Default))
            {
                sw.WriteLine("Title;Description;Deadline;Tags");
            }
            foreach (Tasks tsk in TaskList)
            {
                using (StreamWriter sw = new StreamWriter(path, true, Encoding.Default))
                {
                    sw.Write("{0};{1};{2}/{3}/{4};", tsk.Title, tsk.Description, tsk.Deadline.Day, tsk.Deadline.Month, tsk.Deadline.Year);
                    foreach (string tg in tsk.Tag)
                    {
                        sw.Write("{0};", tg);
                    }
                    sw.WriteLine();
                }
            }
            Console.WriteLine("saved");
        }
    }
}
