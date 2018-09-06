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
                Menu.ChooseTask();
                switch (Console.ReadLine())
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
                        list1.Exit();
                        break;
                    default:
                        break;
                }
            } while (true);
        }
    }
}
