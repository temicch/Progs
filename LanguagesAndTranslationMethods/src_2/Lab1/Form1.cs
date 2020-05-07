using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Lab1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            gridRowHash = new Dictionary<string, DataGridViewRow>();
            vm = new ViewModel();

            vtInput.KeyPress += VtInputKeyPressed;
            vtInput.TextChanged += VtInputTextChanged;
            vnInput.KeyPress += VnInputKeyPressed;
            vnInput.TextChanged += VnInputTextChanged;

            startSymbol.KeyPress += StartSymbolInputKeyPressed;
            startSymbol.TextChanged += StartSymbolInputTextChanged;

            rulesDataGrid.Columns.Add("name", "Имя");
            rulesDataGrid.Columns.Add("content", "Значение");
            rulesDataGrid.Columns[0].ReadOnly = true;
            rulesDataGrid.Columns[0].Width = 50;
            rulesDataGrid.EditingControlShowing += RulesDataGrid_EditingControlShowing;

            dataGridViewOne.Columns.Add("name", "Имя");
            dataGridViewOne.Columns.Add("content", "Значение");
            dataGridViewOne.Columns[0].ReadOnly = true;
            dataGridViewOne.Columns[0].Width = 50;
            //dataGridViewOne.EditingControlShowing += rulesDataGrid_EditingControlShowing;

            dataGridViewTwo.Columns.Add("name", "Имя");
            dataGridViewTwo.Columns.Add("content", "Значение");
            dataGridViewTwo.Columns[0].ReadOnly = true;
            dataGridViewTwo.Columns[0].Width = 50;
            //dataGridViewTwo.EditingControlShowing += rulesDataGrid_EditingControlShowing;

            dataGridViewThree.Columns.Add("name", "Имя");
            dataGridViewThree.Columns.Add("content", "Значение");
            dataGridViewThree.Columns[0].ReadOnly = true;
            dataGridViewThree.Columns[0].Width = 50;
            //dataGridViewThree.EditingControlShowing += rulesDataGrid_EditingControlShowing;

            dataGridViewFour.Columns.Add("name", "Имя");
            dataGridViewFour.Columns.Add("content", "Значение");
            dataGridViewFour.Columns[0].ReadOnly = true;
            dataGridViewFour.Columns[0].Width = 50;
            //dataGridViewFour.EditingControlShowing += rulesDataGrid_EditingControlShowing;

            resultsDataGrid.Columns.Add("result", "Результат");
            resultsDataGrid.Columns.Add("history", "Цепочка");
            resultsDataGrid.Columns[0].MinimumWidth = 120;
            resultsDataGrid.Columns[1].MinimumWidth = resultsDataGrid.Width - 120 - 1;

            resultsDataGrid2.Columns.Add("result", "Результат");
            resultsDataGrid2.Columns.Add("history", "Цепочка");
            resultsDataGrid2.Columns[0].MinimumWidth = 120;
            resultsDataGrid2.Columns[1].MinimumWidth = resultsDataGrid.Width - 120 - 1;

            vm.init();
            setDefaults();

            calcBtn.Click += CalcBtn_Click;
        }
        
        private ViewModel vm;
        private Dictionary<string, DataGridViewRow> gridRowHash, gridRowHashOne, gridRowHashTwo, gridRowHashThree, gridRowHashFour;


        /*********************************************************
         *  METHODS
         * *******************************************************/

        private void setDefaults()
        {
            vtInput.Text = "bc01";
            vnInput.Text = "SAB";
            startSymbol.Text = "S";
            updateRulesDataGrid();

            gridRowHash["S"].Cells[1].Value = "AbcB";
            gridRowHash["A"].Cells[1].Value = "cc||bb";
            gridRowHash["B"].Cells[1].Value = "0|1";

            grammarLbl.Text = "Данные по грамматике заданы по умолчанию.";
        }


        private void updateRulesDataGrid()
        {
            String vn = vnInput.Text;
            DataGridViewRow row;
            int i;
            string key;
            //remove deleted rules
            for (i = 0; i < gridRowHash.Keys.Count; i++)
            {
                key = gridRowHash.Keys.ElementAt(i);
                if (vn.IndexOf(key) == -1)
                {
                    rulesDataGrid.Rows.Remove(gridRowHash[key]);
                    gridRowHash.Remove(key);
                }
            }
            //add new rules
            for (i = 0; i < vn.Length; i++)
            {
                key = (vn[i]).ToString();
                if (!gridRowHash.ContainsKey(key))
                {
                    row = new DataGridViewRow();
                    row.CreateCells(rulesDataGrid, key, "");
                    rulesDataGrid.Rows.Add(row);
                    gridRowHash[key] = row;
                }
            }

        }

        private void updateGrammar()
        {
            String vn = vnInput.Text;
            int i;
            string key;
            string val;
            string rules = "";
            for (i = 0; i < vn.Length; i++)
            {
                key = (vn[i]).ToString();
                val = (string)gridRowHash[key].Cells[1].Value;
                rules = String.Concat(rules, key, "->", (val == "" ? ViewModel.EMPTY_STR : val), i == vn.Length - 1 ? "" : ", ");
                if (rules.Length > 150)
                {
                    rules = String.Concat(rules, "...");
                    break;
                }
            }
            grammarLbl.Text = $"Результаты показаны для грамматики G(VT, VN, P, S) = G({vtInput.Text}, {vnInput.Text}, {rules}, {(vn.Length > 0 ? vn[0].ToString() : "")})";
        }

        private void ValidateCalc()
        {
            calcBtn.Enabled = vtInput.Text.Length != 0 && vnInput.Text.Length != 0 && startSymbol.Text.Length != 0;
        }

        private void ShowChains(DataGridView results)
        {
            results.Rows.Clear();
            var list = vm.chainsHash.Keys.ToList();
            list.Sort(delegate(string x, string y) 
            {
                if (x.Length < y.Length)
                    return -1;
                else if (x.Length > y.Length)
                    return 1;
                else 
                    return x.CompareTo(y);
             });
            foreach (string key in list)
            {
                if (key.Length < minChainResultLenSpinner.Value || key.Length > maxChainResultLenSpinner.Value)
                    continue;
                DataGridViewRow row = new DataGridViewRow();
                row.CreateCells(rulesDataGrid, key, vm.chainsHash[key]);
                results.Rows.Add(row);
            }
        }

        private void Build(TextBox _VT, TextBox _VN, TextBox _start, Dictionary <string, DataGridViewRow> _hash, DataGridView P, DataGridView results)
        {
            if (_start.Text.Length == 0)
                return;
            vm.removeAllRules();
            vm.VT = _VT.Text;
            vm.VN = _VN.Text;
            vm.startKey = _start.Text[0].ToString();
            vm.isLeftSideGenerating = true;
            vm.maxChainLen = (uint)maxChainResultLenSpinner.Value;
            vm.minChainLen = (uint)minChainResultLenSpinner.Value;
            vm.nTime = decimal.ToInt16(nTimer.Value) * 1000;

            string key;

            for (int i = 0; i < _hash.Keys.Count; i++)
            {
                key = _hash.Keys.ElementAt(i);
                vm.addRuleDescription(key, _hash[key].Cells[1].Value != null ? _hash[key].Cells[1].Value.ToString() : "");
            }
            try
            {
                calcBtn.Text = "Идет вычисление...";
                calcBtn.Enabled = false;
                calcBtn.Refresh();
                Cursor.Current = Cursors.WaitCursor;
                vm.calc();
                Cursor.Current = Cursors.Default;
            }
            catch (ChainGeneratingException exc)
            {
                DialogResult errorDialog = MessageBox.Show(exc.Message, "Уведомление", MessageBoxButtons.OK);
            }
            calcBtn.Text = "Выполнить";
            calcBtn.Enabled = true;
            ShowChains(results);
            updateGrammar();
        }

        private void CalcBtn_Click(object sender, EventArgs e)
        {
            Build(vtInput, vnInput, startSymbol, gridRowHash, rulesDataGrid, resultsDataGrid);
            Build(VT4, VN4, start4, gridRowHashFour, dataGridViewFour, resultsDataGrid2);
            if (start4.Text.Length == 0)
                MessageBox.Show("Цепочки были сгенерированы для основной грамматики");
            else
                MessageBox.Show("Цепочки были сгенерированы для основной и канонической грамматики");
        }
        
        private void RulesDataGrid_EditingControlShowing(object sender, DataGridViewEditingControlShowingEventArgs e)
        {
            e.Control.KeyPress += CellKeyPressed;
            e.Control.Leave += Control_Leave;
            ((TextBox)e.Control).ShortcutsEnabled = false;
        }

        private void Control_Leave(object sender, EventArgs e)
        {
            ((Control)sender).KeyPress -= CellKeyPressed;
        }


        private void VnInputTextChanged(object sender, EventArgs e)
        {
            updateRulesDataGrid();
            ValidateCalc();
            if (!vnInput.Text.Contains(startSymbol.Text))
                startSymbol.Text = "";
        }

        private void VtInputTextChanged(object sender, EventArgs e)
        {
            DataGridViewRow row;

            for (int i = 0; i < gridRowHash.Values.Count; i++)
            {
                row = gridRowHash.Values.ElementAt(i);
                row.Cells[1].Value = "";
            }
            ValidateCalc();
        }

        private void StartSymbolInputTextChanged(object sender, EventArgs e)
        {
            ValidateCalc();
        }

        private void VnInputKeyPressed(object sender, KeyPressEventArgs e)
        {
            if ((vnInput.Text.IndexOf(e.KeyChar) != -1 || e.KeyChar < 'A' || e.KeyChar > 'X') && e.KeyChar != (char)Keys.Back)
                e.Handled = true;
        }

        private void VtInputKeyPressed(object sender, KeyPressEventArgs e)
        {
            if (vtInput.Text.IndexOf(e.KeyChar) != -1 || (e.KeyChar >= 'A' && e.KeyChar <= 'Z') || e.KeyChar == '|')
                e.Handled = true;
        }

        private void CellKeyPressed(object sender, KeyPressEventArgs e)
        {
            if (vnInput.Text.IndexOf(e.KeyChar) == -1 && vtInput.Text.IndexOf(e.KeyChar) == -1 && e.KeyChar != '|' && e.KeyChar != (char)Keys.Back) e.Handled = true;
        }

        private void StartSymbolInputKeyPressed(object sender, KeyPressEventArgs e)
        {
            if ((startSymbol.Text.Length == 1 || vnInput.Text.IndexOf(e.KeyChar) == -1 || e.KeyChar < 'A' || e.KeyChar > 'Z') && e.KeyChar != (char)Keys.Back )
                e.Handled = true;
            ValidateCalc();
        }

        private void MaxChainResultLenSpinner_ValueChanged(object sender, EventArgs e)
        {
            minChainResultLenSpinner.Maximum = maxChainResultLenSpinner.Value;
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            vtInput.Text = "bc01";
            vnInput.Text = "SAB";
            startSymbol.Text = "S";

            updateRulesDataGrid();

            gridRowHash["S"].Cells[1].Value = "AbcB";
            gridRowHash["A"].Cells[1].Value = "cc||bb";
            gridRowHash["B"].Cells[1].Value = "0|1";
            updateRulesDataGrid();
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            vtInput.Text = "abc";
            vnInput.Text = "SABCDEFG";
            startSymbol.Text = "S";

            updateRulesDataGrid();

            gridRowHash["S"].Cells[1].Value = "aAB|E";
            gridRowHash["A"].Cells[1].Value = "aA|bB";
            gridRowHash["B"].Cells[1].Value = "ACb|b";
            gridRowHash["C"].Cells[1].Value = "A|bA|cC|aE";
            gridRowHash["D"].Cells[1].Value = "a|c|Fb";
            gridRowHash["E"].Cells[1].Value = "cE|aE|Eb|ED|FG";
            gridRowHash["F"].Cells[1].Value = "BC|EC|AC";
            gridRowHash["G"].Cells[1].Value = "Ga|Gb";

            updateRulesDataGrid();
        }

        private void Button3_Click(object sender, EventArgs e)
        {
            vtInput.Text = "abc";
            vnInput.Text = "SABC";
            startSymbol.Text = "S";

            updateRulesDataGrid();

            gridRowHash["S"].Cells[1].Value = "AaB|aB|cC";
            gridRowHash["A"].Cells[1].Value = "AB|a|b|B";
            gridRowHash["B"].Cells[1].Value = "Ba|";
            gridRowHash["C"].Cells[1].Value = "AB|c";

            updateRulesDataGrid();
        }

        private void Button4_Click(object sender, EventArgs e)
        {
            vtInput.Text = "ac";
            vnInput.Text = "SAD";
            startSymbol.Text = "S";

            updateRulesDataGrid();

            gridRowHash["S"].Cells[1].Value = "Ac";
            gridRowHash["A"].Cells[1].Value = "SD|a";
            gridRowHash["D"].Cells[1].Value = "aD";

            updateRulesDataGrid();
        }

        private bool HasVN(string str)
        {
            foreach (char chr in str)
                if (vnInput.Text.Contains(chr))
                    return true;
            return false;
        }

        private void Button5_Click(object sender, EventArgs e)
        {
            vtInput.Text = "afs";
            vnInput.Text = "SABEF";
            startSymbol.Text = "S";

            updateRulesDataGrid();

            gridRowHash["S"].Cells[1].Value = "AS|BS|s";
            gridRowHash["A"].Cells[1].Value = "a";
            gridRowHash["B"].Cells[1].Value = "B";
            gridRowHash["E"].Cells[1].Value = "EF|FF";
            gridRowHash["F"].Cells[1].Value = "f";

            updateRulesDataGrid();
        }

        private bool IsTerm(char chr, TextBox vt)
        {
            if (vt.Text.Contains(chr) || chr == 0)
                return true;
            return false;
        }

        public static IEnumerable<int[]> Combinations(int m, int n)
        {
            int[] result = new int[m];
            Stack<int> stack = new Stack<int>();
            stack.Push(0);

            while (stack.Count > 0)
            {
                int index = stack.Count - 1;
                int value = stack.Pop();

                while (value < n)
                {
                    result[index++] = ++value;
                    stack.Push(value);
                    if (index == m)
                    {
                        yield return result;
                        break;
                    }
                }
            }
        }

        private bool IsSame(string str, char chr)
        {
            foreach (char _chr in str)
            {
                if (_chr != chr)
                    return false;
            }
            return true;
        }

        private void GetTerminals(Dictionary<string, DataGridViewRow> hash, TextBox VT, TextBox VN, TextBox start, RichTextBox rb, string startSym)
        {
            HashSet<char> _VN = new HashSet<char>();
            HashSet<char> _VT = new HashSet<char>();
            foreach (KeyValuePair<string, DataGridViewRow> h in hash)
            {
                _VN.Add(h.Key[0]);
                foreach (string str in h.Value.Cells[1].Value.ToString().Split('|'))
                    foreach (char chr in str)
                        _VT.Add(chr);
            }
            VN.Text = string.Join("", _VN);
            _VT.ExceptWith(_VN);
            VT.Text = string.Join("", _VT);
            start.Text = startSym;
            rb.Text += $"\nG(VT, VN, P, S) = G({string.Join(", ", _VT)}, {string.Join(", ", _VN)}, P, {startSym})";
            _VN = null;
            _VT = null;
        }

        private void StepOne()
        {
            gridRowHashOne = null;
            gridRowHashOne = new Dictionary<string, DataGridViewRow>();

            rbStepOne.Text = "Y0 = Ø, i = 1\n";
            HashSet<string> Y = new HashSet<string>();

            for (int i = 0; i < vnInput.Text.Length; i++)
            {
                HashSet<string> Yt = new HashSet<string>();
                foreach (KeyValuePair<string, DataGridViewRow> lSide in gridRowHash)
                {
                    try
                    {
                        foreach (string rSide in lSide.Value.Cells[1].Value.ToString().Split('|'))
                        {
                            bool flag = true;
                            if (!HasVN(rSide))
                                Yt.Add(lSide.Value.Cells[0].Value.ToString());
                            else
                            {
                                foreach (char chr in rSide)
                                    if (!IsTerm(chr, vtInput) && !Y.Contains(chr.ToString()))
                                    {
                                        flag = false;
                                        break;
                                    }
                                if (flag)
                                    Yt.Add(lSide.Value.Cells[0].Value.ToString());
                            }
                        }
                    }
                    catch (Exception){ }
                }
                HashSet<string> Yprev = new HashSet<string>(Y);
                Y.UnionWith(Yt);
                rbStepOne.Text += "Y" + (i + 1).ToString() + " = { " + string.Join(",", Y.ToArray()) + " }, i = " + (i + 2).ToString() + "\n";
                if (Yprev.Count == Y.Count)
                {
                    Yt = null;
                    Yprev = null;
                    rbStepOne.Text += "Y" + (i).ToString() + " == Y" + (i + 1).ToString() + "\n";
                    break;
                }
                Yt = null;
                Yprev = null;
            }
            rbStepOne.Text += "Построение окончено";

            dataGridViewOne.Rows.Clear();
            foreach (KeyValuePair<string, DataGridViewRow> lSide in gridRowHash)
            {
                if(Y.Contains(lSide.Value.Cells[0].Value.ToString()))
                {
                    List<string> items = new List<string>();
                    foreach (string rSide in lSide.Value.Cells[1].Value.ToString().Split('|'))
                    {
                        bool fl = true;
                        foreach (char chr in rSide)
                        {
                            if (!IsTerm(chr, vtInput) && !Y.Contains(chr.ToString()))
                                fl = false;
                        }
                        if (fl)
                        {
                            items.Add(rSide);
                        }
                    }
                    DataGridViewRow row = new DataGridViewRow();
                    row.CreateCells(dataGridViewOne, lSide.Value.Cells[0].Value.ToString(), string.Join("|", items.ToArray()));
                    gridRowHashOne[lSide.Value.Cells[0].Value.ToString()] = row;
                    dataGridViewOne.Rows.Add(row);
                    row = null;
                    items = null;
                }
            }
            GetTerminals(gridRowHashOne, VT1, VN1, start1, rbStepOne, startSymbol.Text);
        }

        private void B1_Click(object sender, EventArgs e)
        {
            if (start1.Text.Length == 0)
            {
                MessageBox.Show("Отсутствует целевой символ в грамматике\nВозможно, не были построены правила");
                return;
            }
            Build(VT1, VN1, start1, gridRowHashOne, dataGridViewOne, resultsDataGrid2);
        }

        private void B2_Click(object sender, EventArgs e)
        {
            if (start2.Text.Length == 0)
            {
                MessageBox.Show("Отсутствует целевой символ в грамматике\nВозможно, не были построены правила");
                return;
            }
            Build(VT2, VN2, start2, gridRowHashTwo, dataGridViewTwo, resultsDataGrid2);
        }

        private void B3_Click(object sender, EventArgs e)
        {
            if (start3.Text.Length == 0)
            {
                MessageBox.Show("Отсутствует целевой символ в грамматике\nВозможно, не были построены правила");
                return;
            }
            Build(VT3, VN3, start3, gridRowHashThree, dataGridViewThree, resultsDataGrid2);
        }

        private void B4_Click(object sender, EventArgs e)
        {
            if (start4.Text.Length == 0)
            {
                MessageBox.Show("Отсутствует целевой символ в грамматике\nВозможно, не были построены правила");
                return;
            }
            Build(VT4, VN4, start4, gridRowHashFour, dataGridViewFour, resultsDataGrid2);
        }

        private void ПомощьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Help form = new Help();
            form.Show();
        }

        private void ТемаЗаданияToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Вариант 17\n\nЗадана произвольная контекстно - свободная грамматика. Выполнить преобразование ее к каноническому виду. Преобразование осуществлять поэтапно, отображая результат на каждом из этапов. Проверить построенную грамматику на эквивалентность исходной: по обеим грамматикам сгенерировать множества всех цепочек в заданном пользователем диапазоне длин и проверить их на идентичность. Для подтверждения корректности выполняемых действий предусмотреть возможность корректировки любого из построенных множеств пользователем (изменение цепочки, добавление, удаление). При обнаружении несовпадения должна выдаваться диагностика различий – где именно несовпадения и в чем они состоят.", "Тема задания");
        }

        private void ЗагрузитьДанныеСФайлаToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                Multiselect = false,
                FileName = "Правила",
                DefaultExt = "txt",
                Filter =
                "Text files (*.txt)|*.txt|All files (*.*)|*.*"
            };

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string FilePath = openFileDialog.FileName;
                using (var FileStream = File.OpenText(FilePath))
                {
                    vnInput.Text = FileStream.ReadLine();
                    vtInput.Text = FileStream.ReadLine();
                    startSymbol.Text = FileStream.ReadLine();
                    updateRulesDataGrid();
                    try
                    {
                        while (true)
                        {
                            gridRowHash[FileStream.ReadLine()].Cells[1].Value = FileStream.ReadLine();
                        }
                    }
                    catch (Exception) { }
                    updateRulesDataGrid();
                }
            }

        }

        private void СохранитьПравилаВФайлToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog
            {
                FileName = "Правила",
                DefaultExt = "txt",
                Filter =
                "Text files (*.txt)|*.txt|All files (*.*)|*.*"
            };
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                string FilePath = saveFileDialog.FileName;
                using (var FileStream = File.AppendText(FilePath))
                {
                    FileStream.WriteLine(vnInput.Text);
                    FileStream.WriteLine(vtInput.Text);
                    FileStream.WriteLine(startSymbol.Text);
                    foreach(DataGridViewRow row in rulesDataGrid.Rows)
                    {
                        FileStream.WriteLine(row.Cells[0].Value.ToString());
                        FileStream.WriteLine(row.Cells[1].Value.ToString());
                    }
                }
            }
        }

        private void СохранитьРезультатВФайлToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog
            {
                FileName = "Результаты",
                DefaultExt = "txt",
                Filter =
                "Text files (*.txt)|*.txt|All files (*.*)|*.*",
                CreatePrompt = true
            };

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                string FilePath = saveFileDialog.FileName;
                using (var FileStream = File.AppendText(FilePath))
                {
                    FileStream.WriteLine("VT:");
                    FileStream.WriteLine("\t"+vtInput.Text);
                    FileStream.WriteLine("\nVN:");
                    FileStream.WriteLine("\t"+vnInput.Text);
                    FileStream.WriteLine("\nЦелевой символ");
                    FileStream.WriteLine("\t"+startSymbol.Text);
                    FileStream.WriteLine("\nПравила");
                    foreach (DataGridViewRow row in rulesDataGrid.Rows)
                    {
                        FileStream.WriteLine("\t"+row.Cells[0].Value.ToString() + " - > " + row.Cells[1].Value.ToString());
                    }
                    FileStream.WriteLine("\nЦепочки в диапазоне " + minChainResultLenSpinner.Value + " - " + maxChainResultLenSpinner.Value);
                    foreach (DataGridViewRow row in resultsDataGrid.Rows)
                    {
                        FileStream.WriteLine("\t" + row.Cells[0].Value.ToString());
                    }
                    FileStream.WriteLine("\nЦепочки в диапазоне (Канонический вид) " + minChainResultLenSpinner.Value + " - " + maxChainResultLenSpinner.Value);
                    foreach (DataGridViewRow row in resultsDataGrid2.Rows)
                    {
                        FileStream.WriteLine("\t" + row.Cells[0].Value.ToString());
                    }
                }
            }
        }

        private void Button6_Click_1(object sender, EventArgs e)
        {
            HashSet<string> rules1 = new HashSet<string>();
            HashSet<string> rules2 = new HashSet<string>();
            foreach (DataGridViewRow row in resultsDataGrid.Rows)
            {
                rules1.Add(row.Cells[0].Value.ToString());
            }
            foreach (DataGridViewRow row in resultsDataGrid2.Rows)
            {
                rules2.Add(row.Cells[0].Value.ToString());
            }
            rules1.ExceptWith(rules2);
            string Text = $"Сравнение закончено\n\n{(rules1.Count == 0 ? "Полное совпадение" : "Найдены лишние цепочки:\n")}{string.Join("\n", rules1)}";
            MessageBox.Show(Text, "Сравнение");
        }

        private void StepTwo()
        {
            gridRowHashTwo = null;
            gridRowHashTwo = new Dictionary<string, DataGridViewRow>();

            rbStepTwo.Text = "V0 = { S }, i = 1\n";
            HashSet<string> V = new HashSet<string>();
            HashSet<string> Vt = new HashSet<string>
            {
                startSymbol.Text[0].ToString()
            };

            int i = 0;
            while (true)
            {
                HashSet<string> Vnew = new HashSet<string>();
                foreach (string lSide in Vt.Except(V))
                {
                    if (IsTerm(lSide[0], vtInput)) continue;
                    try
                    {
                        foreach (string rSide in gridRowHashOne[lSide].Cells[1].Value.ToString().Split('|'))
                        {
                            foreach (char chr in rSide)
                            {
                                Vnew.Add(chr.ToString());
                            }
                        }
                    }
                    catch (System.Exception) { }
                }
                V = new HashSet<string>(Vt);
                Vt.UnionWith(Vnew);

                rbStepTwo.Text += "V" + (i + 1).ToString() + " = { " + string.Join(",", Vt.ToArray()) + " }, i = " + (i + 2).ToString() + "\n";

                if (V.Count == Vt.Count)
                {
                    rbStepTwo.Text += "V" + (i).ToString() + " == V" + (i + 1).ToString() + "\nПостроение окончено";
                    break;
                }
                i++;
            }
            dataGridViewTwo.Rows.Clear();
            foreach (KeyValuePair<string, DataGridViewRow> lSide in gridRowHashOne)
            {
                if (Vt.Contains(lSide.Value.Cells[0].Value.ToString()))
                {
                    DataGridViewRow row = new DataGridViewRow();
                    row.CreateCells(dataGridViewTwo, lSide.Value.Cells[0].Value.ToString(), lSide.Value.Cells[1].Value.ToString());
                    gridRowHashTwo[lSide.Value.Cells[0].Value.ToString()] = row;
                    dataGridViewTwo.Rows.Add(row);
                    row = null;
                }
            }
            V = null;
            Vt = null;
            GetTerminals(gridRowHashTwo, VT2, VN2, start2, rbStepTwo, startSymbol.Text);
        }

        private void StepThree()
        {
            gridRowHashThree = null;
            gridRowHashThree = new Dictionary<string, DataGridViewRow>();

            dataGridViewThree.Rows.Clear();

            HashSet<string> W = new HashSet<string>();
            HashSet<string> Wt = new HashSet<string>();
            Dictionary<string, HashSet<string>> Ps = new Dictionary<string, HashSet<string>>();
            foreach (KeyValuePair<string, DataGridViewRow> lSide in gridRowHashTwo)
            {
                Ps[lSide.Value.Cells[0].Value.ToString()] = new HashSet<string>();
                foreach (string rSide in lSide.Value.Cells[1].Value.ToString().Split('|'))
                {
                    if (rSide.Length == 0)
                    {
                        Wt.Add(lSide.Value.Cells[0].Value.ToString());
                    }
                    else
                        Ps[lSide.Value.Cells[0].Value.ToString()].Add(rSide);
                }
            }
            rbStepThree.Text = "W0 = { " + (Wt.Count == 0 ? "Ø" : string.Join(",", Wt.ToArray())) + " }, i = 1\n";
            if (Wt.Count == 0)
            {
                rbStepThree.Text += "\nНе найдено ε - правил";
                gridRowHashThree = null;
                gridRowHashThree = new Dictionary<string, DataGridViewRow>(gridRowHashTwo);
                foreach (KeyValuePair<string, DataGridViewRow> lSide in gridRowHashThree)
                {
                    DataGridViewRow row = new DataGridViewRow();
                    row.CreateCells(dataGridViewThree, lSide.Value.Cells[0].Value.ToString(), lSide.Value.Cells[1].Value.ToString());
                    dataGridViewThree.Rows.Add(row);
                    row = null;
                }
                GetTerminals(gridRowHashThree, VT3, VN3, start3, rbStepThree, startSymbol.Text);
                return;
            }
            int i = 1;
            while (true)
            {
                foreach (KeyValuePair<string, DataGridViewRow> lSide in gridRowHashTwo)
                {
                    foreach (string rSide in lSide.Value.Cells[1].Value.ToString().Split('|'))
                    {
                        bool fl = true;
                        foreach (char chr in rSide)
                        {
                            if (IsTerm(chr, vtInput) || !Wt.Contains(chr.ToString()))
                            {
                                fl = false;
                                break;
                            }
                        }
                        if (fl)
                        {
                            W.Add(lSide.Value.Cells[0].Value.ToString());
                        }
                    }
                }
                HashSet<string> Wprev = new HashSet<string>(Wt);
                Wt.UnionWith(W);
                rbStepThree.Text += "W" + i + " = { " + string.Join(",", Wt.ToArray()) + " }, i = " + (i + 1).ToString() + "\n";
                if (Wprev.Count == Wt.Count)
                {
                    rbStepThree.Text += "W" + (i - 1).ToString() + " == W" + (i).ToString() + "\n";
                    break;
                }
                i++;
            }

            string nonW = "";
            foreach (char chr in vtInput.Text)
            {
                if (!W.Contains(chr.ToString()))
                {
                    nonW += chr;
                }
            }
            foreach (char chr in vnInput.Text)
            {
                if (!W.Contains(chr.ToString()))
                {
                    nonW += chr;
                }
            }
            rbStepThree.Text += "\nДобавим (без повторений) цепочки '{a}' путем исключения из 'a' всех возможных комбинаций из символов Wi:\n";
            // Формируем все возможные цепочки
            foreach (KeyValuePair<string, HashSet<string>> P in Ps)
            {
                HashSet<string> addList = new HashSet<string>();
                foreach (string str in P.Value)
                {
                    int Winn = str.Intersect(string.Join("", W)).Count();
                    if (Winn != 0)
                    {
                        int nonWCount = str.Intersect(nonW).Count();
                        for (i = 1; i <= str.Length; i++)
                        {
                            foreach (int[] c in Combinations(i, str.Length))
                            {
                                string temp = "";
                                foreach (int j in c)
                                    temp += str[j - 1];
                                if (IsSame(temp, P.Key[0]))
                                    continue;
                                if (nonWCount == temp.Intersect(nonW).Count())
                                {
                                    addList.Add(temp);
                                }
                            }
                        }
                    }
                }
                rbStepThree.Text += P.Key.ToString() + " -> " + string.Join("|", addList.ToArray()) + "\n";
                P.Value.UnionWith(addList);
            }
            bool fl2 = false;
            if(W.Contains(startSymbol.Text))
            {
                fl2 = true;
                rbStepThree.Text += "Целевой символ " + startSymbol.Text + " содержится в множестве W\nДобавим новый символ Z в качестве целевого символа:\nZ->" + startSymbol.Text + "|\n";
                start3.Text = "Z";

                Ps["Z"] = new HashSet<string>();
                Ps["Z"].Add(startSymbol.Text);
                Ps["Z"].Add("");
            }
            foreach (KeyValuePair<string, HashSet<string>> P in Ps)
            {
                DataGridViewRow row = new DataGridViewRow();
                row.CreateCells(dataGridViewThree, P.Key, string.Join("|", P.Value));
                dataGridViewThree.Rows.Add(row);
                gridRowHashThree[P.Key] = row;
                row = null;
            }
            if (fl2)
                start3.Text = "Z";
            else
                start3.Text = startSymbol.Text;
            GetTerminals(gridRowHashThree, VT3, VN3, start3, rbStepThree, start3.Text);
        }

        private void StepFour()
        {
            gridRowHashFour = null;
            gridRowHashFour = new Dictionary<string, DataGridViewRow>();

            dataGridViewFour.Rows.Clear();

            rbStepFour.Text = "";

            Dictionary<string, HashSet<string>> Ps = new Dictionary<string, HashSet<string>>();
            foreach (KeyValuePair<string, DataGridViewRow> lSide in gridRowHashThree)
            {
                Ps[lSide.Value.Cells[0].Value.ToString()] = new HashSet<string>();
                foreach (string rSide in lSide.Value.Cells[1].Value.ToString().Split('|'))
                {
                    Ps[lSide.Value.Cells[0].Value.ToString()].Add(rSide);
                }
            }

            Dictionary<string, HashSet<string>> N = new Dictionary<string, HashSet<string>>();
            Dictionary<string, HashSet<string>> Nt = new Dictionary<string, HashSet<string>>();
            foreach (KeyValuePair<string, DataGridViewRow> lSide in gridRowHashThree)
            {
                N[lSide.Value.Cells[0].Value.ToString()] = new HashSet<string>();
                Nt[lSide.Value.Cells[0].Value.ToString()] = new HashSet<string>();
                N[lSide.Value.Cells[0].Value.ToString()].Add(lSide.Value.Cells[0].Value.ToString());

                rbStepFour.Text += "\nN(" + lSide.Value.Cells[0].Value.ToString() + "0) = { " + string.Join(",", N[lSide.Value.Cells[0].Value.ToString()]) + " }, i = 1";

                for(int i = 1; i > 0; i++)
                {
                    foreach (string P in N[lSide.Value.Cells[0].Value.ToString()])
                    {
                        foreach (string str in Ps[P])
                        {
                            if (str.Length == 1)
                            {
                                if (!IsTerm(str[0], VT3))
                                {
                                    Nt[lSide.Value.Cells[0].Value.ToString()].Add(str);
                                }
                            }
                        }
                    }
                    Dictionary<string, HashSet<string>> Nprev = new Dictionary<string, HashSet<string>>(N);
                    N[lSide.Value.Cells[0].Value.ToString()].UnionWith(Nt[lSide.Value.Cells[0].Value.ToString()]);
                    rbStepFour.Text += "\nN(" + lSide.Value.Cells[0].Value.ToString() + i.ToString() + ") = { " + string.Join(",", N[lSide.Value.Cells[0].Value.ToString()]) + " }, i = " + (i+1).ToString();
                    if (N[lSide.Value.Cells[0].Value.ToString()].Except(Nprev[lSide.Value.Cells[0].Value.ToString()]).Count() == 0)
                    {
                        rbStepFour.Text += ", N(" + lSide.Value.Cells[0].Value.ToString() + (i-1).ToString() + ") == N(" + lSide.Value.Cells[0].Value.ToString() + (i).ToString() + ")\n";
                        N[lSide.Value.Cells[0].Value.ToString()].Remove(lSide.Value.Cells[0].Value.ToString());
                        rbStepFour.Text += "N(" + lSide.Value.Cells[0].Value.ToString() + ") = N(" + lSide.Value.Cells[0].Value.ToString() + i.ToString() + ") \\ {" + lSide.Value.Cells[0].Value.ToString() + "} = " + (N[lSide.Value.Cells[0].Value.ToString()].Count == 0 ? "Ø" : "{" + string.Join(", ", N[lSide.Value.Cells[0].Value.ToString()]) + "}") + "\n";
                        break;
                    }
                }
            }
            HashSet<string> vns = new HashSet<string>();
            foreach(char chr in VN3.Text)
            {
                vns.Add(chr.ToString());
            }
            foreach (KeyValuePair<string, HashSet<string>> P in Ps)
                P.Value.ExceptWith(vns);
            foreach (KeyValuePair<string, HashSet<string>> _N in N)
            {
                foreach(string hs in _N.Value)
                {
                    Ps[_N.Key].UnionWith(Ps[hs]);
                }
            }
            foreach (KeyValuePair<string, HashSet<string>> P in Ps)
            {
                DataGridViewRow row = new DataGridViewRow();
                row.CreateCells(dataGridViewFour, P.Key, string.Join("|", P.Value));
                dataGridViewFour.Rows.Add(row);
                gridRowHashFour[P.Key] = row;
                row = null;
            }
            GetTerminals(gridRowHashFour, VT4, VN4, start4, rbStepFour, start3.Text);
            return;
        }

        private void Button6_Click(object sender, EventArgs e)
        {
            StepOne();
            StepTwo();
            StepThree();
            StepFour();
        }
    }
}
