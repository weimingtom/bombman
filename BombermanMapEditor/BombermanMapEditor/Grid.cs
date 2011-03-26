using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BombermanMapEditor
{
    class Grid
    {
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

        public string WallType; 

    }
}
