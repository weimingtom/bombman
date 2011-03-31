﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace BombermanMapEditor
{
    public partial class MapEditor : Form
    {
        private State type = State.Empty;
        private Level level;
        private PaintBoard.PaintBoard paintBoard;

        private void initPaintBoard()
        {
            if (paintBoard != null)
                paintBoard.Dispose();
            paintBoard = new PaintBoard.PaintBoard();
            this.Controls.Add(this.paintBoard);
            this.paintBoard.Location = new System.Drawing.Point(297, 116);
            this.paintBoard.Name = "paintBoard";
            this.paintBoard.NumberOfCol = 15;
            this.paintBoard.NumberOfRow = 13;
            this.paintBoard.Size = new System.Drawing.Size(300, 260);
            this.paintBoard.TabIndex = 25;
            this.paintBoard.Text = "paintBoard1";
            this.paintBoard.OnClickGrid += new PaintBoard.PaintBoard.ClickEventHandler(this.paintBoard_OnClickGrid);
        }

        public MapEditor()
        {
            InitializeComponent();
            //level = new Level("");
            level = new Level();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void uwall_Click(object sender, EventArgs e)
        {
            type = State.Uwall;
        }

        private void dwall_Click(object sender, EventArgs e)
        {
            type = State.Dwall;
        }

        private void paintBoard_OnClickGrid(object sender, PaintBoard.PaintBoard.ClickEventArgs e)
        {
            int x = e.Col;
            int y = e.Row;
            Grid currentGrid = level.GetGrid(y, x);
            level.SetGrid(y, x, ref currentGrid, type);
            //Console.WriteLine(currentGrid.GridState);
        }

        //Save as
        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                LevelSerializor serializor = new LevelSerializor();
                serializor.Serialize(this.level, sfd.OpenFile());
            }
        }

        // New
        private void kjkkToolStripMenuItem_Click(object sender, EventArgs e)
        {
            initPaintBoard();
            if (level != null)
            {
                level = null;
                level = new Level();
            }
            type = State.Empty;
        }

        //Exit
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void addbombp_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)(sender);
            int value = int.Parse(tb.Text);
            if (value >= 0 && value <= 100)
                level.AddBombP = value;
        }

        private void addflamep_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)(sender);
            int value = int.Parse(tb.Text);
            if (value >= 0 && value <= 100)
                level.AddFlameP = value;
        }

        private void fasterp_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)(sender);
            int value = int.Parse(tb.Text);
            if (value >= 0 && value <= 100)
                level.FasterP = value;
        }

        private void pushp_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)(sender);
            int value = int.Parse(tb.Text);
            if (value >= 0 && value <= 100)
                level.PushP = value;
        }

        private void triggerp_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)(sender);
            int value = int.Parse(tb.Text);
            if (value >= 0 && value <= 100)
                level.TriggerP = value;
        }

        private void slowerp_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)(sender);
            int value = int.Parse(tb.Text);
            if (value >= 0 && value <= 100)
                level.SlowerP = value;
        }

        private void dropp_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)(sender);
            int value = int.Parse(tb.Text);
            if (value >= 0 && value <= 100)
                level.DropP = value;
        }

        private void player_Click(object sender, EventArgs e)
        {
            type = State.Player;
        }

        private void npc_Click(object sender, EventArgs e)
        {
            type = State.NPC;
        }

        //open
        private void kkkToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                LevelSerializor serializor = new LevelSerializor();
                this.level = serializor.DeSerialize(ofd.OpenFile());
            }
        }
    }
}