using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Resources;

namespace BombermanMapEditor
{
    public partial class MapEditor : Form
    {
        private State type;
        private Level level;
        private string fileName;
        private bool deleteClick;
        private ResourceManager resMan;

        private void init()
        {
            paintBoard.source = new PaintBoard.PaintBoard.ImageSourceDelegate(this.SourceImageCallback);
            //level = new Level();
            type = State.Empty;
            //fileName = null;
            deleteClick = false;
            resMan = new ResourceManager(typeof(MapEditor));
        }


        public MapEditor()
        {
            InitializeComponent();
        }

        //set image for different types of grids
        private Image SourceImageCallback(int row, int col)
        {
            Grid currentGrid = level.GetGrid(row, col);
            if (currentGrid == null) return null;
            Image sourceImage = null;
            Image icon = null;
            switch (currentGrid.GridState)
            {
                case State.Uwall:
                    sourceImage = (Image)resMan.GetObject("uwall");
                    break;
                case State.Dwall:
                    sourceImage = (Image)resMan.GetObject("wall");
                    break;
                case State.Player:
                    sourceImage = (Image)resMan.GetObject("bombman");
                    break;
                case State.NPC:
                    sourceImage = (Image)resMan.GetObject("npc");
                    break;
            }
            if(sourceImage != null)
                icon = new Bitmap(sourceImage, paintBoard.Width/paintBoard.NumberOfCol, paintBoard.Height/paintBoard.NumberOfRow);
            return icon;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        //click button
        private void uwall_Click(object sender, EventArgs e)
        {
            type = State.Uwall;
            deleteClick = false;
        }

        private void dwall_Click(object sender, EventArgs e)
        {
            type = State.Dwall;
            deleteClick = false;
        } 
        
        private void player_Click(object sender, EventArgs e)
        {
            type = State.Player;
            deleteClick = false;
        }


        private void npc_Click(object sender, EventArgs e)
        {
            type = State.NPC;
            deleteClick = false;
        }

        //click paintBoard
        private void paintBoard_OnClickGrid(object sender, PaintBoard.PaintBoard.ClickEventArgs e)
        {
            int x = e.Col;
            int y = e.Row;
            Grid currentGrid = level.GetGrid(y, x);
            if (currentGrid == null)
            {
                currentGrid = new Grid(y, x);
                level.grids.Add(currentGrid);
            }

            if (deleteClick)
            {
                level.DeleteGrid(y, x);
            }
            else
            {
                currentGrid.GridState = type;
                level.SetGrid(y, x, currentGrid);
            }
            
            //Console.WriteLine(currentGrid.GridState);
        }

        // New
        private void kjkkToolStripMenuItem_Click(object sender, EventArgs e)
        {
            init();
            level = new Level();
            fileName = null;
            paintBoard.Visible = true;
            paintBoard.Invalidate();
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
            init();
            fileName = ofd.FileName;
            paintBoard.Visible = true;
            paintBoard.Invalidate();
        }

        //Save as
        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                LevelSerializor serializor = new LevelSerializor();
                serializor.Serialize(this.level, sfd.OpenFile());
                fileName = sfd.FileName;
            }
        }
        
        //save
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (fileName == null)
            {
                saveAsToolStripMenuItem_Click(sender, e);
            }
            else
            {
                FileStream currentStream = File.Open(fileName, FileMode.Open);
                LevelSerializor serializor = new LevelSerializor();
                serializor.Serialize(this.level, currentStream);
            }
        }
        
        //Exit
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        //set bonus/malus percentage
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

        //delete tool
        private void delete_Click(object sender, EventArgs e)
        {
            deleteClick = true;
        }
    }
}
