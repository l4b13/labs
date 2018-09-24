using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cs_lab3_1
{
    class Program
    {
        static void Main(string[] args)
        {
            Menu MMenu = new MainMenu();
            Menu SMenu = new SideMenu();
            List<Task> TList = new List<Task>();
            TaskManager TAction = new TaskManager();

            string path = ""; //path to *.csv file

            do
            {
                MMenu.Intro();
                MMenu.Choice = MMenu.GetString();
                switch (MMenu.Choice)
                {
                    case "1":
                    case "2":
                        if (MMenu.Choice == "2")
                        {
                            TList.Clear();
                            TList.TrimExcess();
                            MMenu.printpath();
                            path = MMenu.GetString();
                            MMenu.Option1(TList, path);
                        }
                        do
                        {
                            SMenu.Intro();
                            SMenu.Choice = SMenu.GetString();
                            switch (SMenu.Choice)
                            {
                                case "1":
                                    string tag = "";
                                    DateTime date;
                                    SMenu.Option1("title");
                                    string t = SMenu.GetString();
                                    SMenu.Option1("description");
                                    string d = SMenu.GetString();
                                    SMenu.Option1("deadline");
                                    while (!DateTime.TryParse(SMenu.GetString(), out date)) { SMenu.Option1("wrong deadline"); }
                                    SMenu.Option1("tags");
                                    List<string> tags = new List<string>();
                                    do
                                    {
                                        SMenu.consoletab();
                                        tag = SMenu.GetString();
                                        tags.Add(tag);
                                    } while (tag != "");
                                    TAction.NewTask(TList, t, d, date.Date, tags);
                                    break;
                                case "2":
                                    SMenu.Option2();
                                    tag = SMenu.GetString();
                                    foreach (Task task in TAction.Search(TList, tag))
                                    {
                                        SMenu.Output(task);
                                    }
                                    SMenu.pressbutton();
                                    break;
                                case "3":
                                    SMenu.Option3();
                                    foreach (Task task in TAction.LastTasks(TList))
                                    {
                                        SMenu.Output(task);
                                    }
                                    SMenu.pressbutton();
                                    break;
                                case "4":
                                    SMenu.Option4();
                                    break;
                            }
                        } while (SMenu.status);
                        break;
                    case "3":
                        MMenu.Option3(TList, path);
                        break;
                    case "4":
                        MMenu.Option4();
                        break;
                }
            } while (MMenu.status);
        }
    }
}
