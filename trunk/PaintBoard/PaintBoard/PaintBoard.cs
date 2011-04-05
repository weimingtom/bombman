using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PaintBoard
{
    public partial class PaintBoard : Control
    {
        public int NumberOfRow
        {
            get;
            set;
        }

        public int NumberOfCol
        {
            get;
            set;
        }

        public delegate void ClickEventHandler(object sender, ClickEventArgs e);
        public event ClickEventHandler OnClickGrid;


        public class ClickEventArgs : EventArgs
        {
            public int Row
            {
                get;
                set;
            }

            public int Col
            {
                get;
                set;
            }

            public int Width
            {
                get;
                set;
            }

            public int Height
            {
                get;
                set;
            }
        }

        public PaintBoard()
        {
            InitializeComponent();
            NumberOfRow = 13;
            NumberOfCol = 15;
        }

        public delegate Image ImageSourceDelegate(int row, int col);
        public ImageSourceDelegate source;

        protected override void OnPaint(PaintEventArgs pe)
        {
            base.OnPaint(pe);
            Pen bp = new Pen(Color.Black, 2);
            int sideLength = this.Height / this.NumberOfRow;

            for (int i = 0; i < NumberOfRow+1; ++i)
            {
                Point beginH = new Point(0, sideLength*i);
                Point endH = new Point(this.Width, sideLength*i);
                pe.Graphics.DrawLine(bp, beginH, endH);
            }

            for (int j = 0; j < NumberOfCol+1; ++j)
            {
                Point beginV = new Point(sideLength* j, 0);
                Point endV = new Point(sideLength* j, this.Height);
                pe.Graphics.DrawLine(bp, beginV, endV);
            }

            for (int i = 0; i < NumberOfRow; ++i)
            {
                for (int j = 0; j < NumberOfCol; ++j)
                {
                    if (source != null)
                    {
                        Image image = source(i, j);
                        if (image != null)
                        {
                            pe.Graphics.DrawImage(image, j * sideLength, i * sideLength, sideLength, sideLength);
                        }
                    }
                }
            }
        }

        private void PaintBoard_MouseClick(object sender, MouseEventArgs e)
        {
            int x = e.X;
            int y = e.Y;

            int row = y / 20;
            int col = x / 20;

            ClickEventArgs ea = new ClickEventArgs();
            ea.Row = row;
            ea.Col = col;
            ea.Width = this.Width;
            ea.Height = this.Height;

            if (OnClickGrid != null)
            {
                OnClickGrid(this, ea);
            }
            this.Invalidate();
        }
    }
}
