using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace lab5
{
    class ViewModel
    {
        public const char EMPTY_SYM = 'λ';
        // Список тактов 
        public List<string> tactList;
        // Функция переходов
        public Dictionary<string, Transition> transitionHash;
        // Перевод входной цепочки
        public string translation = "";
        public string Q;
        public string V1;
        public string V2;
        public string F;
        public string Z;
        public string w;
        public string oZ;

        public ViewModel()
        {
            tactList = new List<string>();
            transitionHash = new Dictionary<string, Transition>();
        }

        public void Clear()
        {
            tactList.Clear();
            transitionHash.Clear();
        }

        public void AddTransition(char q0, char w0, char z0, char q1, string z1, string t)
        {
            if (q0 != EMPTY_SYM && q1 != EMPTY_SYM)
            {
                Transition trans = new Transition
                {
                    q0 = q0,
                    w0 = w0,
                    z0 = z0,
                    q1 = q1,
                    z1 = z1,
                    t = t
                };
                transitionHash[GetTransHashKey(q0, w0, z0)] = trans;
            }
        }

        private string GetTransHashKey(char q0, char w0, char z0)
        {
            return string.Concat(q0, w0, z0);
        }

        public void Execute()
        {
            Validate();
            Evaluate();
        }

        private void Validate()
        {
            int errorRowInd = 0;
            char unknownSym = '\0';
            // Поиск неизвестных символов во множестве конечных состояний
            foreach (char ch in F) if (Q.IndexOf(ch) == -1) 
                    throw new AppEvaluatingException($"Во множестве конечных состояний F обнаружен неизвестный символ: '{ch}' !");
            // Поиск неизвестных символов в проверяемой цепочке
            foreach (char ch in w) if (V1.IndexOf(ch) == -1) 
                    throw new AppEvaluatingException($"В проверяемой цепочке w обнаружен неизвестный символ: '{ch}' !");
            // Поиск неизвестных символов в таблице переходов
            foreach (Transition trans in transitionHash.Values)
            {
                errorRowInd++;
                if (Q.IndexOf(trans.q0) == -1 && trans.q0 != EMPTY_SYM) 
                { 
                    unknownSym = trans.q0; 
                }
                else if (Q.IndexOf(trans.q1) == -1 && trans.q1 != EMPTY_SYM) 
                { 
                    unknownSym = trans.q1; 
                }
                else if (V1.IndexOf(trans.w0) == -1 && trans.w0 != EMPTY_SYM) 
                { 
                    unknownSym = trans.w0; 
                }
                else if (V1.IndexOf(trans.z0) == -1 && Z.IndexOf(trans.z0) == -1 && trans.z0 != EMPTY_SYM) 
                { 
                    unknownSym = trans.z0; 
                }
                else
                {
                    foreach (char ch in trans.z1) 
                        if (V1.IndexOf(ch) == -1 && Z.IndexOf(ch) == -1 && ch != EMPTY_SYM) 
                        { 
                            unknownSym = ch; 
                            break; 
                        }
                    foreach (char ch in trans.t) 
                        if (V2.IndexOf(ch) == -1 && ch != EMPTY_SYM) 
                        { 
                            unknownSym = ch; 
                            break; 
                        }
                }
                if (unknownSym != '\0')
                {
                    throw new AppEvaluatingException($"В таблице переходов на строчке {errorRowInd} обнаружен неизвестный символ: '{unknownSym}' !");
                }
            }
        }

        private void Evaluate()
        {
            Stack<char> magazine = new Stack<char>();

            for (int i = oZ.Length - 1; i >= 0; i--)
                magazine.Push(oZ[i]);

            char q0 = Q[0];
            char w0 = w.Length > 0 ? w[0] : EMPTY_SYM;
            char z0 = Z[0];

            string t = "";

            Transition curTrans;
            int curSymInd = 0;
            do
            {
                tactList.Add("[" + q0 + ", " + WordToString(w, curSymInd) + ", " + MagazineToString(magazine) + ", " + (t == "" ? EMPTY_SYM.ToString() : t) + "]");
                z0 = magazine.Count > 0 ? magazine.Pop() : EMPTY_SYM;

                if (transitionHash.ContainsKey(GetTransHashKey(q0, w0, z0)))
                {
                    curTrans = transitionHash[GetTransHashKey(q0, w0, z0)];
                    w0 = ++curSymInd >= w.Length ? EMPTY_SYM : w[curSymInd];
                    q0 = curTrans.q1;
                    t += (curTrans.t == EMPTY_SYM.ToString() ? "" : curTrans.t);
                    PushToStack(magazine, curTrans.z1);
                }
                else if (transitionHash.ContainsKey(GetTransHashKey(q0, EMPTY_SYM, z0)))
                {
                    curTrans = transitionHash[GetTransHashKey(q0, EMPTY_SYM, z0)];
                    q0 = curTrans.q1;
                    t += (curTrans.t == EMPTY_SYM.ToString() ? "" : curTrans.t);
                    PushToStack(magazine, curTrans.z1);
                }
                else
                {
                    if (IsFinal(q0, w0, z0, magazine))
                        break;
                    throw new AppEvaluatingException($"Слово w НЕ принадлежит заданному КС-языку! Отсутствует переход для q0 = '{q0}', w0 = '{w0}', z0 = '{z0}'.");
                }
            }
            while (!IsFinal(q0, w0, z0, magazine));

            tactList.Add($"[{q0}, {WordToString(w, curSymInd)}, {MagazineToString(magazine)}, {(t == "" ? EMPTY_SYM.ToString() : t)}]");
            if (curSymInd < w.Length) 
                throw new AppEvaluatingException("Слово w НЕ принадлежит заданному КС-языку!\nЦепочка не прочитана до конца!");
            if (F.IndexOf(q0) == -1) 
                throw new AppEvaluatingException($"Слово w НЕ принадлежит заданному КС-языку!\nАвтомат перешел в состояние '{q0}', не являющееся конечным!");
            translation = t;
        }

        private string MagazineToString(Stack<char> stack)
        {
            string res = "";
            foreach (char sym in stack)
            {
                res += sym;
            }
            return res == "" ? EMPTY_SYM.ToString() : res;
        }

        private string WordToString(string word, int startInd)
        {
            if (startInd >= word.Length) 
                return EMPTY_SYM.ToString();
            return word.Substring(startInd);
        }

        private void PushToStack(Stack<char> stack, string str)
        {
            foreach (char ch in str.Reverse())
            {
                if (ch != EMPTY_SYM) stack.Push(ch);
            }
        }

        private bool IsFinal(char q0, char w0, char z0, Stack<char> stack)
        {
            if (stack.Count > 0)
                return false;
            return stack.Count == 0 || (F.IndexOf(q0) != -1 && w0 == EMPTY_SYM && Z.IndexOf(z0) != -1);
        }
    }

    class Transition
    {
        public char q0 = ViewModel.EMPTY_SYM;
        public char w0 = ViewModel.EMPTY_SYM;
        public char z0 = ViewModel.EMPTY_SYM;
        public char q1 = ViewModel.EMPTY_SYM;
        public string z1 = ViewModel.EMPTY_SYM.ToString();
        public string t = ViewModel.EMPTY_SYM.ToString();
    }

}
