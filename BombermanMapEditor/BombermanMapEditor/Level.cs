using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BombermanMapEditor
{
    class Level
    {
        public List<Grid> grids;
        private string levelName;
        
        public Level(string _name)
        {
            levelName = _name;
            grids = new List<Grid>();
        }
    }
}
