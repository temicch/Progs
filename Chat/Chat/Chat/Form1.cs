using MessageInterface;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Chat
{
    public partial class Form1 : Form
    {
        Thread auth;
        Socket authSocket;
        class UserInfo
        {
            public string name;
            public Thread thread;
            public UserInfo(Thread th)
            {
                thread = th;
                name = null;
            }
            public void SetName(string n)
            {
                name = n;
            }
        };

        Dictionary<Socket, UserInfo> userList = new Dictionary<Socket, UserInfo>();

        public Form1()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
        }

        Action<string> SetTextCallback;

        public void TextWrite(string text)
        {
            if (richTextBox1.InvokeRequired)
            {
                SetTextCallback = TextWrite;
                Invoke(SetTextCallback, new object[] { text });
            }
            else
            {
                richTextBox1.Text += $"[{DateTime.Now.ToLongTimeString()}]{text}\n";
                richTextBox1.SelectionStart = richTextBox1.Text.Length;
                richTextBox1.ScrollToCaret();
            }
        }

        private void ThreadReceive(Socket handler)
        {
            byte[] bytesMsg = new byte[322];
            string userName = null;
            while (true)
            {
                try
                {
                    int bytesRec1 = handler.Receive(bytesMsg);
                    if (bytesRec1 <= 0)
                        break;
                    if (bytesMsg[0] == (byte)MessageType.MSG_AUTH_CONNECT)
                    {
                        userName = Encoding.Unicode.GetString(bytesMsg, 1, bytesRec1 - 1);
                        byte[] answer = new byte[1];
                        foreach (Socket j in userList.Keys)
                        {
                            if (userList[j].name == userName)
                            {
                                answer[0] = 0;
                                TextWrite($"Неудачная попытка авторизации: {userName}");
                                userList.Remove(handler);
                                handler.Send(answer);
                                handler.Shutdown(SocketShutdown.Both);
                                handler.Close();
                                return;
                            }
                        }
                        answer[0] = 1;
                        handler.Send(answer);
                        TextWrite($"Подключился: {userName}");
                        userList[handler].SetName(userName);
                        bytesMsg[0] = (byte)MessageType.MSG_USER_CONNECT;
                        for (int i = 0; i < listBox1.Items.Count; i++)
                        {
                            byte[] everyMsg = new byte[1 + Encoding.Unicode.GetByteCount(listBox1.Items[i].ToString())];
                            everyMsg[0] = (int)MessageType.MSG_USER_CONNECT;
                            Buffer.BlockCopy(listBox1.Items[i].ToString().ToCharArray(), 0, everyMsg, 1, Encoding.Unicode.GetByteCount(listBox1.Items[i].ToString()));
                            handler.Send(everyMsg);
                            Thread.Sleep(20);
                        }
                        foreach (Socket j in userList.Keys)
                        {
                            if (j != handler)
                                j.Send(bytesMsg, 1 + Encoding.Unicode.GetByteCount(userName), SocketFlags.None);
                        }
                        listBox1.Items.Add(userName);
                    }
                    else if (bytesMsg[0] == (byte)MessageType.MSG_MESSAGE)
                    {
                        byte[] everyMsg = new byte[Encoding.Unicode.GetByteCount(userName) + bytesRec1 + 1];
                        everyMsg[0] = (byte)MessageType.MSG_MESSAGE;
                        everyMsg[1] = (byte)Encoding.Unicode.GetByteCount(userName);
                        string msg = Encoding.Unicode.GetString(bytesMsg, 1, bytesRec1 - 1);
                        Buffer.BlockCopy(userName.ToCharArray(), 0, everyMsg, 2, Encoding.Unicode.GetByteCount(userName));
                        Buffer.BlockCopy(msg.ToCharArray(), 0, everyMsg, 1 + Encoding.Unicode.GetByteCount(userName) + 1, Encoding.Unicode.GetByteCount(msg));
                        foreach (Socket j in userList.Keys)
                        {
                            j.Send(everyMsg);
                        }
                        TextWrite($"{userName}: {Encoding.Unicode.GetString(bytesMsg, 1, bytesRec1 - 1)}");
                    }
                    else if (bytesMsg[0] == (byte)MessageType.MSG_MESSAGE_WHISPER_OUT)
                    {
                        string decName = Encoding.Unicode.GetString(bytesMsg, 2, bytesMsg[1]);
                        string decMsg = Encoding.Unicode.GetString(bytesMsg, 2 + bytesMsg[1], bytesRec1 - 2 - Encoding.Unicode.GetByteCount(decName));
                        bool isFound = false;
                        foreach (Socket j in userList.Keys)
                        {
                            if (userList[j].name == decName)
                            {
                                byte[] oneMsg = new byte[2 + Encoding.Unicode.GetByteCount(userName) + Encoding.Unicode.GetByteCount(decMsg)];
                                oneMsg[0] = (byte)MessageType.MSG_MESSAGE_WHISPER_IN;
                                oneMsg[1] = (byte)Encoding.Unicode.GetByteCount(userName);
                                Buffer.BlockCopy(userName.ToCharArray(), 0, oneMsg, 2, oneMsg[1]);
                                Buffer.BlockCopy(decMsg.ToCharArray(), 0, oneMsg, 2 + oneMsg[1], Encoding.Unicode.GetByteCount(decMsg));
                                isFound = true;
                                j.Send(oneMsg);
                                TextWrite($"[{userName}][{decName}]: {decMsg}");
                                break;
                            }
                        }
                        if (isFound)
                        {
                            bytesMsg[0] = (byte)MessageType.MSG_MESSAGE_WHISPER_OUT;
                            handler.Send(bytesMsg, bytesRec1, SocketFlags.None);
                        }
                    }
                }
                catch (SocketException ex)
                {
                    TextWrite(ex.ToString());
                    break;
                }
            }
            Kick(handler, userName);
        }
        public void Kick(Socket handler, string userName)
        {
            byte[] bytesMsg = new byte[322];
            handler.Shutdown(SocketShutdown.Both);
            handler.Close();
            Thread t = userList[handler].thread;
            userList.Remove(handler);
            TextWrite($"Покинул сервер: {userName}");
            listBox1.Items.Remove(userName);
            bytesMsg[0] = (byte)MessageType.MSG_USER_DISCONNECT;
            Buffer.BlockCopy(userName.ToCharArray(), 0, bytesMsg, 1, Encoding.Unicode.GetByteCount(userName));
            foreach (Socket i in userList.Keys)
            {
                i.Send(bytesMsg, 1 + Encoding.Unicode.GetByteCount(userName), SocketFlags.None);
            }
            t.Abort();
        }
        public void ThreadForAuth(IPEndPoint localEndPoint)
        {
            try
            {
                authSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                authSocket.Bind(localEndPoint);
                TextWrite("Ожидание подключений");
                button1.Enabled = false;
                richTextBox2.Enabled = false;
                authSocket.Listen(10);
                while (true)
                {
                    Socket handler = authSocket.Accept();
                    Thread t = new Thread(() => ThreadReceive(handler));
                    userList.Add(handler, new UserInfo(t));
                    t.IsBackground = true;
                    t.Start();
                }
            }
            catch (Exception ex)
            {
                TextWrite(ex.ToString());
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Any, int.Parse(richTextBox2.Text.ToString()));
            auth = new Thread(() => ThreadForAuth(localEndPoint));
            auth.Start();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            foreach (Socket j in userList.Keys)
            {
                j.Shutdown(SocketShutdown.Both);
                j.Close();
            }
            Environment.Exit(1);
        }

        private void listBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            string uName = listBox1.Text;
            foreach (Socket j in userList.Keys)
            {
                if (userList[j].name == uName)
                {
                    Kick(j, userList[j].name);
                    break;
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Process process = new Process();
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.RedirectStandardOutput = true;
            process.StartInfo.FileName = "Client.exe";
            process.Start();
        }
    }
}
