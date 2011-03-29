using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
namespace BombermanMapEditor
{
    public class LevelSerializor
    {
        public Stream Serialize(Level level)
        {
            using (FileStream output = new FileStream(level.Get_Level_Name(), FileMode.Create))
            {
                XmlSerializer formatter = new XmlSerializer(typeof(Level));
                formatter.Serialize(output, level);
                return (Stream)output;
            }
        }

        public Level DeSerialize(string level_name)
        {
            Level level;
            using (FileStream input = new FileStream(level_name, FileMode.Open))
            {
                XmlSerializer formatter = new XmlSerializer(typeof(Level));
                level = (Level)formatter.Deserialize(input);
                return level;
            }
        }
    }
}
