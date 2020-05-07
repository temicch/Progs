using MessageInterface;
using System;
using System.Diagnostics;
using System.Drawing;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;

namespace Client
{
    public partial class MainForm : Form
    {
        public string userName = "";
        public Socket mySocket;
        delegate void SetTextCallback(string text, Color color);
        public void TextWrite(string text, Color color)
        {
            if (this.richTextBox1.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(TextWrite);
                this.Invoke(d, new object[] { text, color });
            }
            else
            {
                richTextBox1.AppendText("[" + DateTime.Now.ToLongTimeString() + "]" + text + "\n", color);
                richTextBox1.SelectionStart = richTextBox1.Text.Length;
                richTextBox1.ScrollToCaret();
            }
        }
        public MainForm()
        {
            InitializeComponent();
            Hide();
            Auth Auth = new Auth();
            Auth.Owner = this;
            Auth.ShowDialog();
            this.ActiveControl = textBox1;
            if (userName.Length == 0)
                Environment.Exit(0);
            listBox1.Items.Add("=> " + userName);
            Control.CheckForIllegalCrossThreadCalls = false;
            comboBox1.Text = "Мир";
        }
        public void ThreadProc()
        {
            byte[] bytesMsg = new byte[322];
            while (true)
            {
                try
                {
                    int bytesRec = mySocket.Receive(bytesMsg);
                    if (bytesRec <= 0)
                        break;
                    if (bytesMsg[0] == (byte)MessageType.MSG_USER_CONNECT)
                    {
                        TextWrite($"Пользователь {Encoding.Unicode.GetString(bytesMsg, 1, bytesRec - 1)} подключился к серверу", Color.Gray);
                        listBox1.Items.Add(Encoding.Unicode.GetString(bytesMsg, 1, bytesRec - 1));
                        comboBox1.Items.Add(Encoding.Unicode.GetString(bytesMsg, 1, bytesRec - 1));
                    }
                    else if (bytesMsg[0] == (byte)MessageType.MSG_AUTH_CONNECT)
                    {
                        //TextWrite("Auth: " + bytesRec.ToString() + " подключился к серверу", Color.Gray);
                    }
                    else if (bytesMsg[0] == (byte)MessageType.MSG_USER_DISCONNECT)
                    {
                        TextWrite($"Пользователь {Encoding.Unicode.GetString(bytesMsg, 1, bytesRec - 1)} отключился от сервера", Color.Gray);
                        listBox1.Items.Remove(Encoding.Unicode.GetString(bytesMsg, 1, bytesRec - 1));
                        comboBox1.Items.Remove(Encoding.Unicode.GetString(bytesMsg, 1, bytesRec - 1));
                    }
                    else if (bytesMsg[0] == (byte)MessageType.MSG_MESSAGE)
                    {
                        byte[] msg = new byte[bytesRec];
                        string decName = Encoding.Unicode.GetString(bytesMsg, 2, bytesMsg[1]),
                                decMsg = Encoding.Unicode.GetString(bytesMsg, 2 + Encoding.Unicode.GetByteCount(decName), bytesRec - 2 - Encoding.Unicode.GetByteCount(decName));
                        TextWrite($"[Мир]{decName}: {decMsg}", Color.FromArgb(222, 225, 146));
                    }
                    else if (bytesMsg[0] == (byte)MessageType.MSG_MESSAGE_WHISPER_IN)
                    {
                        byte[] msg = new byte[bytesRec];
                        string decName = Encoding.Unicode.GetString(bytesMsg, 2, bytesMsg[1]),
                                decMsg = Encoding.Unicode.GetString(bytesMsg, 2 + Encoding.Unicode.GetByteCount(decName), bytesRec - 2 - Encoding.Unicode.GetByteCount(decName));
                        TextWrite($"[{decName}]: {decMsg}", Color.FromArgb(200, 106, 194));
                    }
                    else if (bytesMsg[0] == (byte)MessageType.MSG_MESSAGE_WHISPER_OUT)
                    {
                        byte[] msg = new byte[bytesRec];
                        string decName = Encoding.Unicode.GetString(bytesMsg, 2, bytesMsg[1]),
                                decMsg = Encoding.Unicode.GetString(bytesMsg, 2 + Encoding.Unicode.GetByteCount(decName), bytesRec - 2 - Encoding.Unicode.GetByteCount(decName));
                        TextWrite($"[{userName}][{decName}]: {decMsg}", Color.FromArgb(200, 106, 194));
                    }
                }
                catch (SocketException ex)
                {
                    TextWrite(ex.ToString(), Color.Red);
                    break;
                }
            }
            TextWrite("Соединение с сервером закрыто", Color.Red);
        }
        public void SendSocketMessage(int msgType, String arg1 = null, String arg2 = null)
        {
            if (msgType == (int)MessageType.MSG_AUTH_CONNECT)
            {
                byte[] socketMsg = new byte[666];
                socketMsg[0] = (byte)msgType;
                Buffer.BlockCopy(userName.ToCharArray(), 0, socketMsg, 1, userName.Length * 2);
                mySocket.Send(socketMsg, 1 + (userName.Length * 2), SocketFlags.None);
            }
            else if (msgType == (int)MessageType.MSG_MESSAGE)
            {
                byte[] socketMsg = new byte[1 + (arg1.Length * 2)];
                socketMsg[0] = (byte)msgType;
                Buffer.BlockCopy(arg1.ToCharArray(), 0, socketMsg, 1, arg1.Length * 2);
                mySocket.Send(socketMsg);
            }
            else if (msgType == (int)MessageType.MSG_MESSAGE_WHISPER_OUT)
            {
                byte[] socketMsg = new byte[2 + Encoding.Unicode.GetByteCount(arg1) + Encoding.Unicode.GetByteCount(arg2)];
                socketMsg[0] = (byte)msgType;
                socketMsg[1] = (byte)Encoding.Unicode.GetByteCount(arg1);
                Buffer.BlockCopy(arg1.ToCharArray(), 0, socketMsg, 2, socketMsg[1]);
                Buffer.BlockCopy(arg2.ToCharArray(), 0, socketMsg, 2 + socketMsg[1], Encoding.Unicode.GetByteCount(arg2));
                mySocket.Send(socketMsg);
            }
        }
        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter && textBox1.TextLength != 0)
            {
                try
                {
                    if (comboBox1.SelectedItem.ToString() == "Мир" || comboBox1.SelectedItem.ToString() == "")
                        SendSocketMessage((int)MessageType.MSG_MESSAGE, textBox1.Text);
                    else
                        SendSocketMessage((int)MessageType.MSG_MESSAGE_WHISPER_OUT, comboBox1.SelectedItem.ToString(), textBox1.Text);
                    textBox1.Text = "";
                }
                catch
                {
                    comboBox1.SelectedIndex = 0;
                }
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                if (mySocket.Connected)
                {
                    mySocket.Shutdown(SocketShutdown.Both);
                    mySocket.Close();
                }
            }
            catch { }
            Environment.Exit(1);
        }

        private void listBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (listBox1.SelectedIndex != 0)
                for (int i = 0; i < comboBox1.Items.Count; i++)
                    if (comboBox1.Items[i].ToString() == listBox1.Text)
                    {
                        comboBox1.SelectedIndex = i;
                        this.ActiveControl = textBox1;
                        break;
                    }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
            ActiveControl = textBox1;
        }

        private void создатьКлиентаToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Process process = new Process();
            process.StartInfo.FileName = Process.GetCurrentProcess().MainModule.FileName;
            process.Start();
        }
    }
    public static class RichTextBoxExtensions
    {
        public static void AppendText(this RichTextBox box, string text, Color color)
        {
            box.SelectionStart = box.TextLength;
            box.SelectionLength = text.Length;
            box.SelectionColor = color;
            box.AppendText(text);
            box.SelectionColor = box.ForeColor;
        }
    }
}
