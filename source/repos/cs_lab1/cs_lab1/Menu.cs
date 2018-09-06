using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cs_lab1
{
    static class Menu
    {
        public static void Hello()
        {
            Console.WriteLine("Enter the number of action and press [Enter]. Then follow instructions\n");
        }

        public static void ChooseTask()
        {
            Console.WriteLine("Menu:");
            Console.WriteLine("\t1.Add task");
            Console.WriteLine("\t2.Search task");
            Console.WriteLine("\t3.Last tasks");
            Console.WriteLine("\t4.Exit");
            Console.WriteLine();
        }

        public static void NewTask()
        {
            Console.WriteLine("New task");
        }

        public static void SearchTasks()
        {
            Console.Write("Search tasks by tag: ");
        }

        public static void LastTasks()
        {
            Console.WriteLine("Actual Tasks:");
        }

        public static void ParseTitle()
        {
            Console.Write("\tTitle: ");
        }

        public static void ParseDescription()
        {
            Console.Write("\tDescription: ");
        }

        public static void ParseDeadline()
        {
            Console.Write("\tDeadline (dd/mm/yyyy): ");
        }

        public static void ParseTags()
        {
            Console.WriteLine("\tTags (finish on empty line):");
        }

        public static void Output(string T, string D, DateTime DT, List<string> TG)
        {
            Console.WriteLine("\tTitle: {0}", T);
            Console.WriteLine("\tDescription: {0}", D);
            Console.WriteLine("\tDeadline: {0}/{1}/{2}", DT.Day, DT.Month, DT.Year);
            Console.Write("\tTags:");
            foreach (string tgs in TG)
            {
                Console.Write(" {0}", tgs);
            }
            Console.WriteLine("\n");
        }

        public static void Wait()
        {
            Console.Write("Press [Enter] to continue...");
            Console.ReadLine();
        }
    }
}
