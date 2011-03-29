using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BombermanMapEditor
{
    public enum GridState
    {
        Empty,Uwall,Dwall,Player,NPC,AddBomb,AddFlame,Faster,Push,Trigger,Slower,Drop
    }

    public class Grid
    {
        public Grid()
        {
        }

        public Grid(int _row,int _col)
        {
            PosX = _row;
            PosY = _col;
        }

        public int PosX
        {
            get;
            set;
        }

         public int PosY
        {
             get;
             set;
        }

         public GridState ItemType
         {
             get;
             set;
         }

    }
}
