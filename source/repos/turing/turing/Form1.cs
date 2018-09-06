using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace turing
{

    public partial class Form1 : Form
    {
        private string lenta0 = "";
        private string[] tBox = new string [12];
        private bool status = false;

        public bool CheckTable()
        {
            int count = 0;
            for (int i=0; i<12; i++)
            {
                string s = tBox[i];
                if (s[0] == 'q' && s.Length == 4)
                {
                    if (s[1] == '0' || s[1] == '1' || s[1] == '2' || s[1] == '3')
                    {
                        if (s[2] == '0' || s[2] == '1' || s[2] == '2')
                        {
                            if (s[3] == 'L' || s[3] == 'C' || s[3] == 'R')
                            {
                                count++;
                            }
                        }
                    }
                }
            }
            if (count != 12)
            {
                MessageBox.Show("Error: wrong input! Please, try again.");
                return false;
            } else
            {
                return true;
            }
        } //

        public Form1()
        {
            InitializeComponent();
        } //

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            tBox[0] = textBox1.Text;
        } //tb1

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            tBox[1] = textBox2.Text;
        } //tb2

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            tBox[2] = textBox3.Text;
        } //tb3

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            tBox[3] = textBox4.Text;
        } //tb4

        private void textBox5_TextChanged(object sender, EventArgs e)
        {
            tBox[4] = textBox5.Text;
        } //tb5

        private void textBox6_TextChanged(object sender, EventArgs e)
        {
            tBox[5] = textBox6.Text;
        } //tb6

        private void textBox7_TextChanged(object sender, EventArgs e)
        {
            tBox[6] = textBox7.Text;
        } //tb7

        private void textBox8_TextChanged(object sender, EventArgs e)
        {
            tBox[7] = textBox8.Text;
        } //tb8

        private void textBox9_TextChanged(object sender, EventArgs e)
        {
            tBox[8] = textBox9.Text;
        } //tb9

        private void textBox10_TextChanged(object sender, EventArgs e)
        {
            tBox[9] = textBox10.Text;
        } //tb10

        private void textBox11_TextChanged(object sender, EventArgs e)
        {
            tBox[10] = textBox11.Text;
        } //tb11

        private void textBox12_TextChanged(object sender, EventArgs e)
        {
            tBox[11] = textBox12.Text;
        } //tb12

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show(tBox[0]);
            if (CheckTable())
            {

            }
        } //step-by-step

        private void button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("2");
            if (CheckTable())
            {

            }
        } //full

        private void button3_Click(object sender, EventArgs e)
        {
            textBox1.Text = "q01L";
            textBox2.Text = "q31R";
            textBox3.Text = "q12R";
            textBox4.Text = "q30R";
            textBox5.Text = "q02C";
            textBox6.Text = "q22R";
            textBox7.Text = "q10R";
            textBox8.Text = "q21R";
            textBox9.Text = "q00R";
            textBox10.Text = "q22L";
            textBox11.Text = "q32C";
            textBox12.Text = "q12L";
        } //test1

        private void button4_Click(object sender, EventArgs e)
        {
            textBox1.Text = "q01L";
            textBox2.Text = "q31R";
            textBox3.Text = "q12R";
            textBox4.Text = "q30R";
            textBox5.Text = "q02C";
            textBox6.Text = "q22R";
            textBox7.Text = "q10R";
            textBox8.Text = "q21R";
            textBox9.Text = "q00R";
            textBox10.Text = "q22L";
            textBox11.Text = "q32C";
            textBox12.Text = "q12L";
        } //test2

        private void button5_Click(object sender, EventArgs e)
        {
            textBox1.Text = "q01L";
            textBox2.Text = "q31R";
            textBox3.Text = "q12R";
            textBox4.Text = "q30R";
            textBox5.Text = "q22C";
            textBox6.Text = "q22R";
            textBox7.Text = "q10R";
            textBox8.Text = "q21R";
            textBox9.Text = "q00R";
            textBox10.Text = "q22L";
            textBox11.Text = "q32C";
            textBox12.Text = "q12L";
        } //test3

        private void button6_Click(object sender, EventArgs e)
        {
            textBox1.Text = "q01L";
            textBox2.Text = "q31R";
            textBox3.Text = "q12R";
            textBox4.Text = "q30R";
            textBox5.Text = "q20L";
            textBox6.Text = "q22R";
            textBox7.Text = "q10R";
            textBox8.Text = "q21R";
            textBox9.Text = "q00R";
            textBox10.Text = "q22L";
            textBox11.Text = "q32C";
            textBox12.Text = "q12L";
        } //test4

        private void button7_Click(object sender, EventArgs e)
        {
            Stream myStream = null;
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            openFileDialog1.InitialDirectory = "C:\\Users\\l4b13\\Desktop\\turing";
            openFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    if ((myStream = openFileDialog1.OpenFile()) != null)
                    {
                        using (myStream)
                        {
                            // Insert code to read the stream here.
                            TextReader TextReader1 = new StreamReader(myStream);
                            string text = TextReader1.ReadToEnd();
                            MessageBox.Show(text);
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }
        } //load

        private void textBox13_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox14_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox15_TextChanged(object sender, EventArgs e)
        {
            
        }
    }
}
