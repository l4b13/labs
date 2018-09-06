using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cs_lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            Menu.Hello();
            TaskActions list1 = new TaskActions();
            do
            {
                Menu.ChooseOption();
                Menu.Status = true;
                string choice = Menu.InputString();
                if (choice == "1" || choice == "2")
                {
                    if (choice == "2")
                    {
                        list1.LoadTaskList();
                    } else
                    {
                        list1.NewTaskList();
                    }
                    do
                    {
                        Menu.ChooseTask();
                        switch (Menu.InputString())
                        {
                            case "1":
                                list1.NewTask();
                                break;
                            case "2":
                                list1.SearchTasks();
                                break;
                            case "3":
                                list1.LastTasks();
                                break;
                            case "4":
                                list1.SaveTaskList();
                                break;
                            case "5":
                                Menu.Status = false;
                                break;
                            case "6":
                                list1.Exit();
                                break;
                            default:
                                Menu.IncorrectValue();
                                break;
                        }
                    } while (Menu.Status);
                } else
                {
                    if (choice == "3")
                    {
                        list1.Exit();
                    } else
                    {
                        Menu.IncorrectValue();
                    }
                }
            } while (true);

        }
    }
}
