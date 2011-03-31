using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BombermanMapEditor
{
    public enum Wall
    {
        Empty, Uwall, Dwall
    }

    public enum Character
    {
        Player,NPC
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

         public Wall WallType
         {
             get;
             set;
         }

         public Character CharacterType
         {
             get;
             set;
         }
    }
}
