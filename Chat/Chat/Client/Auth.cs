using MessageInterface;
using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Windows.Forms;

namespace Client
{
    public partial class Auth : Form
    {
        public Auth()
        {
            InitializeComponent();
            this.ActiveControl = textBox1;
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (textBox1.Text.Length < 3)
                {
                    label2.Visible = true;
                    label2.Text = "Введено неверное количество символов";
                }
                else
                {
                    this.ActiveControl = textBox2;
                    if (label2.Text == "Введено неверное количество символов")
                        label2.Visible = false;
                }
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            IPAddress empty;
            if (textBox1.Text.Length < 3 || !IPAddress.TryParse(textBox2.Text, out empty))
            {
                label2.Visible = true;
                label2.Text = "Введены неверные данные";
            }
            else
            {
                MainForm Main = this.Owner as MainForm;
                IPEndPoint remoteEP = new IPEndPoint(IPAddress.Parse(textBox2.Text), Int32.Parse(textBox3.Text.ToString()));
                try
                {
                    Main.mySocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                    Main.mySocket.Connect(remoteEP);
                    Main.userName = textBox1.Text;
                    Main.SendSocketMessage((int)MessageType.MSG_AUTH_CONNECT, Main.userName);
                    byte[] answer = new byte[1];
                    Main.mySocket.Receive(answer);
                    if (answer[0] == 0)
                    {
                        label2.Text = "Пользователь с таким ником уже находится на сервере";
                        label2.Visible = true;
                        Main.userName = String.Empty;
                        Main.mySocket.Shutdown(SocketShutdown.Both);
                        Main.mySocket.Close();
                        return;
                    }
                    Close();
                    Main.Show();
                    Thread T = new Thread(Main.ThreadProc);
                    T.Start();
                }
                catch (SocketException se)
                {
                    label2.Visible = true;
                    label2.Text = se.Message.ToString();
                }
            }
        }
        private void textBox2_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                IPAddress empty;
                if (!IPAddress.TryParse(textBox2.Text, out empty))
                {
                    label2.Visible = true;
                    label2.Text = "Недопустимый IP адрес";
                }
                else
                {
                    if (label2.Text == "Недопустимый IP адрес")
                        label2.Visible = false;
                    this.ActiveControl = textBox3;
                }
            }
        }

        private void textBox3_KeyDown(object sender, KeyEventArgs e)
        {
            button1_Click(this, e);
        }
    }
}
