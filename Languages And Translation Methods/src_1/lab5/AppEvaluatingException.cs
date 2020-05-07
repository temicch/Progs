using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace lab5
{
    class AppEvaluatingException:Exception
    {
        public AppEvaluatingException():base() {}
        public AppEvaluatingException(string str) : base(str) { }
    }
}
