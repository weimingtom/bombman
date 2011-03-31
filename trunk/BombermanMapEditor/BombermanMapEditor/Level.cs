using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BombermanMapEditor
{
    public class Level
    {
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

        public int Trigger
        {
            get;
            set;
        }

        public int Slower
        {
            get;
            set;
        }

        public int Drop
        {
            get;
            set;
        }
    }
}
