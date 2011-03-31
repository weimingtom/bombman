using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BombermanMapEditor
{
    public class Level
    {
        public Grid GetGrid(int row, int col)
        {
            foreach (Grid current in grids)
            {
                if (current.Col == col && current.Row == row)
                    return current;
            }
            return null;
        }

        public void SetGrid(int row, int col, ref Grid grid, State gridState)
        {
            if (grid == null)
            {
                grid = new Grid(row, col);
                this.grids.Add(grid);
            }
            grid.GridState = gridState;
        }
        
        public List<Grid> grids;

        public Level()
        {
            grids = new List<Grid>();
        }

        public int AddBombP
        {
            get;
            set;
        }

        public int AddFlameP
        {
            get;
            set;
        }

        public int FasterP
        {
            get;
            set;
        }

        public int PushP
        {
            get;
            set;
        }

        public int TriggerP
        {
            get;
            set;
        }

        public int SlowerP
        {
            get;
            set;
        }

        public int DropP
        {
            get;
            set;
        }
    }
}
