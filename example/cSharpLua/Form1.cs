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
    }
}
