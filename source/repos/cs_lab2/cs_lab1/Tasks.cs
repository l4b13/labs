using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cs_lab1
{
    class Tasks
    {
        public string Title;
        public string Description;
        public DateTime Deadline;
        public List<string> Tag;

        public Tasks()
        {
            Tag = new List<string>();
        }
    }
}
