using System;
using System.Drawing;
using System.Windows.Forms;

namespace lab5
{
    public partial class View : Form
    {
        public View()
        {
            InitializeComponent();

            vm = new ViewModel();

            tactsGrid.ColumnCount = 1;
            transitionsGrid.Columns.Add("q0", "q0");
            transitionsGrid.Columns.Add("w0", "w0");
            transitionsGrid.Columns.Add("z0", "z0");
            transitionsGrid.Columns.Add("q1", "q1");
            transitionsGrid.Columns.Add("z1", "z1");
            transitionsGrid.Columns.Add("t", "t");
            transitionsGrid.CellBeginEdit += TransitionsGrid_CellBeginEdit;
            transitionsGrid.EditingControlShowing += TransitionsGrid_EditingControlShowing;

            QInput.KeyPress += KeyPressed;
            V1Input.KeyPress += KeyPressed;
            V2Input.KeyPress += KeyPressed;
            FInput.KeyPress += KeyPressed;
            ZInput.KeyPress += KeyPressed;
            wInput.KeyPress += KeyPressed;

            QInput.TextChanged += InputTextChanged;
            V1Input.TextChanged += InputTextChanged;
            V2Input.TextChanged += InputTextChanged;
            FInput.TextChanged += InputTextChanged;
            ZInput.TextChanged += InputTextChanged;
            wInput.TextChanged += InputTextChanged;

            helpBtn.Click += HelpBtn_Click;
            calcBtn.Click += CalcBtn_Click;
            clearGridBtn.Click += ClearGridBtn_Click;
            defaultBtn.Click += DefaultBtn_Click;
        }

        private const string AVAILABLE_SPEC_SYMS = "*–+-=/\\(){}[]";
        private ViewModel vm;

        private void ValidateCalc()
        {
            calcBtn.Enabled = QInput.Text.Length > 0 && V1Input.Text.Length > 0 && FInput.Text.Length > 0 && ZInput.Text.Length > 0;
        }

        private void KeyPressed(object sender, KeyPressEventArgs e)
        {
            string text = ((TextBox)sender).Text;
            char ch = e.KeyChar;

            if (IsBackspace(ch))
                return;

            if (sender == FInput)
            {
                if (HasSym(QInput.Text, ch) && !HasSym(text, ch))
                    return;
            }
            else if (sender == wInput)
            {
                if (HasSym(V1Input.Text, ch))
                    return;
            }
            else
            {
                if (!HasSym(text, ch) && (IsLetter(ch) || IsDigit(ch) || IsSpecSym(ch)))
                    return;
            }
            e.Handled = true;
        }

        private bool HasSym(string text, char sym)
        {
            return text.IndexOf(sym) != -1;
        }

        private bool IsDigit(char ch)
        {
            return ch >= '0' && ch <= '9';
        }
        private bool IsLetter(char ch)
        {
            return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
        }
        private bool IsBackspace(char ch)
        {
            return ch == (char)Keys.Back;
        }
        private bool IsSpecSym(char ch)
        {
            return AVAILABLE_SPEC_SYMS.IndexOf(ch) >= 0;
        }

        private void InputTextChanged(object sender, EventArgs e)
        {
            ValidateCalc();
        }

        private void HelpBtn_Click(object sender, EventArgs e)
        {
            string description = "Приложение осуществляет перевод входной цепочки w, принадлежащей заданному языку. Для этого необходимо заполнить параметры преобразователя с магазинной памятью и нажать кнопку Выполнить.\n\n";
            description = string.Concat(description, "Для запуска перевода необходимо заполнить все текстовые поля. В качестве начального состояния автомата ");
            description = string.Concat(description, "выбирается первый элемент, указаный во множестве состояний Q, а в качестве начального символа магазина – первый элемент во множестве Z.\n");
            description = string.Concat(description, "Если в таблице переходов не заполнена ячейка q0 или q1, то соот-ая строка будет проигнорирована.");
            DialogResult helpDialog = MessageBox.Show(description, "Помощь", MessageBoxButtons.OK);
        }

        private int curColumnEditingInd = -1;
        private TextBox curEditingTextBox;
        private void TransitionsGrid_CellBeginEdit(object sender, DataGridViewCellCancelEventArgs e)
        {
            curColumnEditingInd = e.ColumnIndex;
        }
        private void TransitionsGrid_EditingControlShowing(object sender, DataGridViewEditingControlShowingEventArgs e)
        {
            e.Control.KeyPress += CellKeyPressed;
            e.Control.Leave += Control_Leave;
            curEditingTextBox = ((TextBox)e.Control);
            curEditingTextBox.ShortcutsEnabled = false;
        }
        private void Control_Leave(object sender, EventArgs e)
        {
            ((Control)sender).KeyPress -= CellKeyPressed;
        }

        private void CellKeyPressed(object sender, KeyPressEventArgs e)
        {
            char ch = e.KeyChar;
            if (IsBackspace(ch)) return;

            string text = curEditingTextBox.Text;

            switch (curColumnEditingInd)
            {
                //q0
                case (0):
                    if (text.Length > 0 || QInput.Text.IndexOf(ch) == -1)
                        e.Handled = true;
                    break;
                //w0
                case (1):
                    if (text.Length > 0 || V1Input.Text.IndexOf(ch) == -1)
                        e.Handled = true;
                    break;
                //z0
                case (2):
                    if (text.Length > 0 || (V1Input.Text.IndexOf(ch) == -1 && ZInput.Text.IndexOf(text) == -1))
                        e.Handled = true;
                    break;
                //q1
                case (3):
                    if (text.Length > 0 || QInput.Text.IndexOf(ch) == -1)
                        e.Handled = true;
                    break;
                //z1
                case (4):
                    if (V1Input.Text.IndexOf(ch) == -1 && ZInput.Text.IndexOf(ch) == -1)
                        e.Handled = true;
                    break;
                //t
                case (5):
                    if (V2Input.Text.IndexOf(ch) == -1)
                        e.Handled = true;
                    break;
                default:
                    e.Handled = true;
                    break;
            }
        }

        void ClearGridBtn_Click(object sender, EventArgs e)
        {
            transitionsGrid.Rows.Clear();
        }

        void DefaultBtn_Click(object sender, EventArgs e)
        {
            QInput.Text = "prs";
            V1Input.Text = "01";
            V2Input.Text = "ab";
            FInput.Text = "s";
            ZInput.Text = "z0";
            wInput.Text = "0011";
            Oz.Text = "z";

            transitionsGrid.Rows.Clear();
            transitionsGrid.RowCount = 5;

            transitionsGrid.Rows[0].Cells[0].Value = "p";
            transitionsGrid.Rows[0].Cells[1].Value = "0";
            transitionsGrid.Rows[0].Cells[2].Value = "z";
            transitionsGrid.Rows[0].Cells[3].Value = "p";
            transitionsGrid.Rows[0].Cells[4].Value = "0z";
            transitionsGrid.Rows[0].Cells[5].Value = "aa";

            transitionsGrid.Rows[1].Cells[0].Value = "p";
            transitionsGrid.Rows[1].Cells[1].Value = "0";
            transitionsGrid.Rows[1].Cells[2].Value = "0";
            transitionsGrid.Rows[1].Cells[3].Value = "p";
            transitionsGrid.Rows[1].Cells[4].Value = "00";
            transitionsGrid.Rows[1].Cells[5].Value = "aa";

            transitionsGrid.Rows[2].Cells[0].Value = "p";
            transitionsGrid.Rows[2].Cells[1].Value = "1";
            transitionsGrid.Rows[2].Cells[2].Value = "0";
            transitionsGrid.Rows[2].Cells[3].Value = "r";
            transitionsGrid.Rows[2].Cells[4].Value = "";
            transitionsGrid.Rows[2].Cells[5].Value = "bb";

            transitionsGrid.Rows[3].Cells[0].Value = "r";
            transitionsGrid.Rows[3].Cells[1].Value = "1";
            transitionsGrid.Rows[3].Cells[2].Value = "0";
            transitionsGrid.Rows[3].Cells[3].Value = "r";
            transitionsGrid.Rows[3].Cells[4].Value = "";
            transitionsGrid.Rows[3].Cells[5].Value = "bb";

            transitionsGrid.Rows[4].Cells[0].Value = "r";
            transitionsGrid.Rows[4].Cells[1].Value = "";
            transitionsGrid.Rows[4].Cells[2].Value = "z";
            transitionsGrid.Rows[4].Cells[3].Value = "s";
            transitionsGrid.Rows[4].Cells[4].Value = "";
            transitionsGrid.Rows[4].Cells[5].Value = "";
        }

        void CalcBtn_Click(object sender, EventArgs e)
        {
            try
            {
                vm.Clear();
                vm.Q = QInput.Text;
                vm.V1 = V1Input.Text;
                vm.V2 = V2Input.Text;
                vm.F = FInput.Text;
                vm.Z = ZInput.Text;
                vm.w = wInput.Text;
                vm.oZ = Oz.Text;
                for (int i = 0; i < transitionsGrid.RowCount; i++)
                {
                    vm.AddTransition(
                        GetGrdiVal(i, 0)[0],
                        GetGrdiVal(i, 1)[0],
                        GetGrdiVal(i, 2)[0],
                        GetGrdiVal(i, 3)[0],
                        GetGrdiVal(i, 4),
                        GetGrdiVal(i, 5)
                        );
                }

                vm.Execute();

                status.ForeColor = Color.DarkGreen;
                status.Text = $"Слово w принадлежит заданному КС-языку и успешно переведено: {vm.translation}";
            }
            catch (AppEvaluatingException exc)
            {
                status.ForeColor = Color.DarkRed;
                status.Text = exc.Message;
            }

            tactsGrid.Rows.Clear();
            foreach (string str in vm.tactList)
            {
                DataGridViewRow row = new DataGridViewRow();
                row.CreateCells(tactsGrid, str);
                tactsGrid.Rows.Add(row);
            }
        }

        private string GetGrdiVal(int row, int col)
        {
            object gridVal = transitionsGrid.Rows[row].Cells[col].Value;
            return (gridVal == null || (string)gridVal == "") ? ViewModel.EMPTY_SYM.ToString() : (string)gridVal;
        }


        private void Button1_Click(object sender, EventArgs e)
        {
            QInput.Text = "q";
            V1Input.Text = "a+*";
            V2Input.Text = "a+*";
            FInput.Text = "q";
            ZInput.Text = "+*E";
            wInput.Text = "+aa";
            Oz.Text = "E";

            transitionsGrid.Rows.Clear();
            transitionsGrid.RowCount = 5;

            transitionsGrid.Rows[0].Cells[0].Value = "q";
            transitionsGrid.Rows[0].Cells[1].Value = "*";
            transitionsGrid.Rows[0].Cells[2].Value = "E";
            transitionsGrid.Rows[0].Cells[3].Value = "q";
            transitionsGrid.Rows[0].Cells[4].Value = "EE*";
            transitionsGrid.Rows[0].Cells[5].Value = "";

            transitionsGrid.Rows[1].Cells[0].Value = "q";
            transitionsGrid.Rows[1].Cells[1].Value = "";
            transitionsGrid.Rows[1].Cells[2].Value = "+";
            transitionsGrid.Rows[1].Cells[3].Value = "q";
            transitionsGrid.Rows[1].Cells[4].Value = "";
            transitionsGrid.Rows[1].Cells[5].Value = "+";

            transitionsGrid.Rows[2].Cells[0].Value = "q";
            transitionsGrid.Rows[2].Cells[1].Value = "a";
            transitionsGrid.Rows[2].Cells[2].Value = "E";
            transitionsGrid.Rows[2].Cells[3].Value = "q";
            transitionsGrid.Rows[2].Cells[4].Value = "";
            transitionsGrid.Rows[2].Cells[5].Value = "a";

            transitionsGrid.Rows[3].Cells[0].Value = "q";
            transitionsGrid.Rows[3].Cells[1].Value = "+";
            transitionsGrid.Rows[3].Cells[2].Value = "E";
            transitionsGrid.Rows[3].Cells[3].Value = "q";
            transitionsGrid.Rows[3].Cells[4].Value = "EE+";
            transitionsGrid.Rows[3].Cells[5].Value = "";

            transitionsGrid.Rows[4].Cells[0].Value = "q";
            transitionsGrid.Rows[4].Cells[1].Value = "";
            transitionsGrid.Rows[4].Cells[2].Value = "*";
            transitionsGrid.Rows[4].Cells[3].Value = "q";
            transitionsGrid.Rows[4].Cells[4].Value = "";
            transitionsGrid.Rows[4].Cells[5].Value = "*";

        }
    }
}
