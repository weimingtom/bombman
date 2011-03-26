using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace BombermanMapEditor
{
    public partial class MapEditor : Form
    {
        private GridState itemState = GridState.Empty;
        private Level level;

        public MapEditor()
        {
            InitializeComponent();
            level = new Level("");
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void uwall_Click(object sender, EventArgs e)
        {
            itemState = GridState.Uwall;
        }

        private void dwall_Click(object sender, EventArgs e)
        {
            itemState = GridState.Dwall;
        }

        private void player_Click(object sender, EventArgs e)
        {
            itemState = GridState.Player;
        }

        private void npc_Click(object sender, EventArgs e)
        {
            itemState = GridState.NPC;
        }

        private void addbomb_Click(object sender, EventArgs e)
        {
            itemState = GridState.AddBomb;
        }

        private void addflame_Click(object sender, EventArgs e)
        {
            itemState = GridState.AddFlame;
        }

        private void faster_Click(object sender, EventArgs e)
        {
            itemState = GridState.Faster;
        }

        private void push_Click(object sender, EventArgs e)
        {
            itemState = GridState.Push;
        }

        private void trigger_Click(object sender, EventArgs e)
        {
            itemState = GridState.Trigger;
        }

        private void slower_Click(object sender, EventArgs e)
        {
            itemState = GridState.Slower;
        }

        private void drop_Click(object sender, EventArgs e)
        {
            itemState = GridState.Drop;
        }

        private void paintBoard_OnClickGrid(object sender, PaintBoard.PaintBoard.ClickEventArgs e)
        {
            int x = e.Col;
            int y = e.Row;
            //int index = y * e.Width + x - 1;
            Grid currentGrid = new Grid(y, x);
            currentGrid.ItemType = itemState;
            level.grids.Add(currentGrid);
            Console.WriteLine(currentGrid.ItemType);
        }
    }
}
