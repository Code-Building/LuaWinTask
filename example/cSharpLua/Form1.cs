using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace cSharpLua
{

    public partial class Form1 : Form
    {
        [DllImport("LuaWinTask", CallingConvention = CallingConvention.Cdecl)]
        static extern bool runFile(string filename, bool openconsole);
        [DllImport("LuaWinTask", CallingConvention = CallingConvention.Cdecl)]
        static extern bool runScript(string filename, bool openconsole);

        [DllImport("LuaWinTask", CallingConvention = CallingConvention.Cdecl)]
        static extern int rsti(string filename,string var, bool openconsole);
        public Form1()
        {
            InitializeComponent();
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "dll files (*.dll)|*.dll|All files (*.*)|*.*";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                textBox2.Text = openFileDialog1.FileName;
            }
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            if ((textBox1.Text != "") && (textBox2.Text != ""))
            {
                var path = textBox2.Text.Replace(@"\", @"\\");
                runScript("inject_def(\"" + textBox1.Text + "\", \"" + path + "\")", true);
            }
        }

        private void Button3_Click(object sender, EventArgs e)
        {
            runScript("print(\"hello from csharp\")", true);
        }

        private void Button4_Click(object sender, EventArgs e)
        {
            //if ((textBox1.Text != "")&& (textBox3.Text != ""))
            //{
            //    runScript("print(rpm(\"" + textBox1.Text + "\", " + textBox3.Text + "))", true);
            //}
            if ((textBox1.Text != "") && (textBox3.Text != ""))
            {
                //variaveis a & b, sendo a bool retorno da funcao e b o valor da leitura.
                string myscritp = "a,b =rpm('" + textBox1.Text + "', " + textBox3.Text + ")";
                 int b = rsti(myscritp,"b", false);
                request_label.Text = b.ToString();
            }
        }

        private void Button5_Click(object sender, EventArgs e)
        {
            if ((textBox1.Text != "") && (textBox2.Text != "") && (textBox3.Text != ""))
            {
                runScript("print(wpm(\"" + textBox1.Text + "\", " + textBox3.Text + ","+textBox2.Text+"))", true);
            }
        }

        private void Button6_Click(object sender, EventArgs e)
        {
            runScript("print(rpm(\"dontstarve_steam.exe\",0x00F1D2EC,0x54,0x40,0x50,0x398))", true);
        }

        private void Send_Request_bnt_Click(object sender, EventArgs e)
        {

        }
    }
}
