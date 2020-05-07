using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Timers;

namespace Lab1
{
    class ViewModel
    {
        public void init()
        {
            rulesHash = new Dictionary<string, string[]>();
            chainsHash = new Dictionary<string, string>();
        }

        private const int MAX_CHAIN_NUM = 1000000;
        private const int MAX_RECURSION_DEPTH = 100000;
        public const string EMPTY_STR = "λ";

        public string VT = "";//множество терминальных символов
        public string VN = "";//множество нетерминальных символов
        public string startKey = "";//начальный нетерминальный символ
        public uint maxChainLen = 10;//максимальная длина результата выводимой цепочки
        public uint minChainLen = 1;//минимальная длина результата выводимой цепочки
        public bool isLeftSideGenerating = true;//направление построения

        private bool fl_out = false;

        public Dictionary<string, string> chainsHash;
        private Dictionary<string, string[]> rulesHash;
        private int recursionDepth = 0;
        public int nTime = 15;

        public void addRuleDescription(string key, string description)
        {
            rulesHash[key] = description.Split('|');
        }

        public void removeAllRules()
        {
            rulesHash.Clear();
            chainsHash.Clear();
        }

        public void calc()
        {
            recursionDepth = 0;
            generateChains(startKey);
        }

        private void HandleTimer(object source, ElapsedEventArgs e)
        {
            fl_out = true;
        }

        private void generateChains(string key)
        {
            string[] rules = rulesHash[key];
            List<Chain> nonterminalChains = new List<Chain>();
            char ch;
            uint validateStatus;

            foreach (string ruleRightPart in rules)
            {
                //определяем есть ли в правилах нетерминальные символы, если нет, 
                //то сразу добавляем в таблицу результатов это значение, оставляя
                //на обработку только те цепочки, которые содердат не терминальные
                //символы и подлежат обработке; такие цепочки добавляем в список
                //цепочек unterminalChains.

                Chain startChain = new Chain();
                startChain.history = key + "->" + ruleRightPart;
                startChain.line = ruleRightPart;

                validateStatus = validateChain(ruleRightPart);
                if (validateStatus == ChainValidateStatus.PASSED) saveChain(startChain);
                else if (validateStatus == ChainValidateStatus.HAS_NONTERMINAL) nonterminalChains.Add(startChain);
            }
            Timer timer = new Timer(nTime);
            timer.Elapsed += HandleTimer;
            timer.Start();
            while (nonterminalChains.Capacity != 0 && recursionDepth <= MAX_RECURSION_DEPTH)
            {
                recursionDepth++;
                List<Chain> updatedNonterminalChains = new List<Chain>();
                foreach (Chain chain in nonterminalChains)
                {
                    string chainResultPrefix = "";
                    for (int i = 0; i < chain.line.Length; i++)
                    {
                        ch = chain.line[isLeftSideGenerating ? i : chain.line.Length - i - 1];

                        if (isTerminal(ch))
                        {
                            chainResultPrefix = isLeftSideGenerating ? chainResultPrefix + ch : ch + chainResultPrefix;
                        }
                        else
                        {
                            foreach (string ruleRightPart in rulesHash[ch.ToString()])
                            {
                                string res = isLeftSideGenerating ? chainResultPrefix + ruleRightPart + chain.line.Substring(i + 1) : chain.line.Substring(0, chain.line.Length - i - 1) + ruleRightPart + chainResultPrefix;
                                validateStatus = validateChain(res);
                               
                                Chain updatedChain = new Chain();
                                updatedChain.history = chain.history + "->" + res;
                                updatedChain.line = res;


                                if (validateStatus == ChainValidateStatus.PASSED) saveChain(updatedChain);
                                else if (validateStatus == ChainValidateStatus.HAS_NONTERMINAL) updatedNonterminalChains.Add(updatedChain);

                            }
                            break;
                        }
                    }
                }
                nonterminalChains.Clear();
                nonterminalChains = updatedNonterminalChains;
                if (nonterminalChains.Capacity > MAX_CHAIN_NUM) break;// throw new ChainGeneratingException("Слишком большое количество цепочек: будут показаны не все результаты.");
                if (fl_out)
                {
                    fl_out = false;
                    timer.Stop();
                    throw new ChainGeneratingException("Время ожидания истекло\nГенерация цепочка закончена");
                }
            }
            timer.Stop();
            fl_out = false;
        }

        private bool isTerminal(char sym)
        {
            return !rulesHash.ContainsKey(sym.ToString());
        }



        private uint validateChain(string line)
        {
            bool hasNonterminalSym = false;
            int terminalSymNum = 0;
            foreach (char ch in line)
            {
                if (isTerminal(ch)) terminalSymNum++;
                else hasNonterminalSym = true;
            }

            //if (terminalSymNum > maxChainLen) return ChainValidateStatus.INCORRECT_SIZE;
            //if (terminalSymNum < minChainLen) return ChainValidateStatus.INCORRECT_SIZE;
            return hasNonterminalSym ? ChainValidateStatus.HAS_NONTERMINAL : ChainValidateStatus.PASSED;
        }

        private void saveChain(Chain c)
        {
            chainsHash[c.line == "" ? EMPTY_STR : c.line] = c.history;
        }

    }

    class Chain
    {
        public string history = "";//история, сценарий построения цепочки
        public string line = "";//правая часть правила, использующая при построении
    }
    class ChainValidateStatus
    {
        public const uint INCORRECT_SIZE = 0;
        public const uint HAS_NONTERMINAL = 1;
        public const uint PASSED = 2;
    }
}
