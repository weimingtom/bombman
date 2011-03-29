﻿using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
namespace BombermanMapEditor
{
    public class LevelSerializor
    {
        public void Serialize(Level level, Stream stream)
        {
            XmlSerializer formatter = new XmlSerializer(typeof(Level));
            formatter.Serialize(stream, level);
        }

        public Level DeSerialize(Stream stream)
        {
            XmlSerializer formatter = new XmlSerializer(typeof(Level));
            return (Level)formatter.Deserialize(stream);
        }
    }
}
