using System;
using System.Collections.Generic;
using System.Text;


namespace Lab1
{
    class ChainGeneratingException:Exception
    {
        public ChainGeneratingException():base() {}
        public ChainGeneratingException(string str) : base(str) { }
    }
}
