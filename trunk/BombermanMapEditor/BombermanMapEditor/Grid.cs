using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BombermanMapEditor
{
    public enum State
    {
        Empty, Uwall, Dwall, Player, NPC
    }
    
    public class Grid
    {
        public Grid()
        {
        }

        public Grid(int row,int col)
        {
            Row = row;
            Col = col;
        }

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

         public State GridState
         {
             get;
             set;
         }
    }
}
