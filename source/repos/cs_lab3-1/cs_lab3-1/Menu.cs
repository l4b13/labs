using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cs_lab3_1
{
    abstract class Menu
    {
        public string Choice;
        public bool status = true;
        public virtual void Intro() { }
        public string GetString() { return Console.ReadLine(); }
        public virtual void Output(Task t) { }
        public virtual void Option1(string str) { }
        public virtual void Option1() { }
        public virtual void Option2() { }
        public virtual void Option2(List<Task> t, string path) { }
        public virtual void Option3() { }
        public virtual void Option3(List<Task> t, string path) { }
        public void Option4() { status = false; }
        public void consoletab() { Console.Write("\t"); }
        public void pressbutton() { Console.Write("Press [Enter] to continue..."); GetString(); }
        public void printpath() { Console.WriteLine("Print name (*.csv):"); }
    }

    class MainMenu : Menu
    {
        public override void Intro()
        {
            status = true;
            Console.WriteLine("Choose option:");
            Console.WriteLine("\t1.New to-do-list");
            Console.WriteLine("\t2.Load to-do-list");
            Console.WriteLine("\t3.Save to-do-list");
            Console.WriteLine("\t4.Exit");
            Console.WriteLine();
        }

        public override void Option1()
        {
            Console.WriteLine("New to-do-list created.");
        }

        public override void Option2(List<Task> t, string path)
        {
            try
            {
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
                            t.Add(new Task() { Title = lTitle, Description = lDesc, Deadline = lDate, Tag = lTags });
                        }
                        i++;
                    }
                }
            }
            catch
            {
                Console.WriteLine("file not found");
            }
        }

        public override void Option3(List<Task> t, string path)
        {
            printpath();
            path = GetString();
            FileStream f = new FileStream(path, FileMode.Create);
            try
            {
                using (StreamWriter sw = new StreamWriter(f))
                {
                    sw.WriteLine("Title;Description;Deadline;Tags");
                    sw.Close();
                    f.Close();
                    f = null;
                }
                FileStream f1 = new FileStream(path, FileMode.Append);
                foreach (Task tsk in t)
                {                    
                    using (StreamWriter sw = new StreamWriter(f1))
                    {
                        sw.Write("{0};{1};{2}/{3}/{4};", tsk.Title, tsk.Description, tsk.Deadline.Day, tsk.Deadline.Month, tsk.Deadline.Year);
                        foreach (string tg in tsk.Tag)
                        {
                            sw.Write("{0};", tg);
                        }
                        sw.WriteLine();
                        sw.Close();
                    }                    
                }
                f1.Close();
                Console.WriteLine("saved");
            } catch (Exception ex)
            {
                Console.WriteLine("not saved\n{0}", ex);
            }
        }
    }

    class SideMenu : Menu
    {
        public override void Output(Task t)
        {
            Console.WriteLine("\tTitle: {0}", t.Title);
            Console.WriteLine("\tDescription: {0}", t.Description);
            Console.WriteLine("\tDeadline: {0}", t.Deadline.Date);
            Console.Write("\tTags:");
            foreach (string tgs in t.Tag)
            {
                Console.Write(" {0}", tgs);
            }
            Console.WriteLine("\n");
        }

        public override void Intro()
        {
            status = true;
            Console.WriteLine("Menu:");
            Console.WriteLine("\t1.Add task");
            Console.WriteLine("\t2.Search task");
            Console.WriteLine("\t3.Last tasks");
            Console.WriteLine("\t4.Back to options");
            Console.WriteLine();
        }

        public override void Option1(string str)
        {
            switch(str)
            {
                case "title":
                    Console.WriteLine("New task");
                    Console.Write("\tTitle: ");
                    break;
                case "description":
                    Console.Write("\tDescription: ");
                    break;
                case "deadline":
                    Console.Write("\tDeadline (dd/mm/yyyy): ");
                    break;
                case "tags":
                    Console.WriteLine("\tTags (finish on empty line):");
                    break;
                case "wrong deadline":
                    Console.Write("\tWrong input, try again (dd/mm/yyyy): ");
                    break;
            }
        }

        public override void Option2()
        {
            Console.Write("Search tasks by tag: ");
        }

        public override void Option3()
        {
            Console.WriteLine("Actual Tasks:");
        }
    }
}