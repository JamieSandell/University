///////////////////////////////////////////////
//////// Author: Jamie Sandell
//////// Signed On: 10:30am - 1st December 2008
//////// Work Done: Created and worked on the class
//////// Signed Off: 10:43am - 1st December 2008
////
//////// Author: Jamie Sandell
//////// Signed On: 1:24pm - 1st December 2008
//////// Work Done: Added a try/catch to the LoadTexture method
//////// Signed Off: 1:28pm - 1st December 2008
////
//////// Author: Jamie Sandell
//////// Signed On: 1:46pm - 2nd December 2008
//////// Work Done: Changed ref int to ref uint, compiled in Release Mode
//////// Signed Off: 1:46pm - 2nd December 2008
///////////////////////////////////////////////

using System;
using System.Drawing;
using System.Collections.Generic;
using System.Text;
using Tao.OpenGl;

namespace CardGame
{
    public interface ITexture
    {
        /// <summary>
        /// Loads the textures passed in.
        /// </summary>
        /// <param name="inTextureNames">Names of the textures to load</param>
        /// <param name="inTextureStorage">The place the textures are stored</param>
        /// <returns>An empty string if everything went ok, else an error message</returns>
        string LoadTexture(string[] inTextureNames, ref uint[] inTextureStorage);
    }

    public class Texture:ITexture
    {
        public string LoadTexture(string[] inTextureNames, ref uint[] inTextureStorage)
        {
            try
            {
                for (int i = 0; i < inTextureStorage.Length; i++)
                {
                    Bitmap image = new Bitmap(inTextureNames[i]); // TODO: Add error handling code
                    image.RotateFlip(RotateFlipType.RotateNoneFlipY);
                    System.Drawing.Imaging.BitmapData bitmapdata;
                    Rectangle rect = new Rectangle(0, 0, image.Width, image.Height);

                    bitmapdata = image.LockBits(rect, System.Drawing.Imaging.ImageLockMode.ReadOnly,
                        System.Drawing.Imaging.PixelFormat.Format24bppRgb);

                    if (i==0)
                    {
                        Gl.glGenTextures(inTextureStorage.Length, inTextureStorage);
                    }
                    Gl.glBindTexture(Gl.GL_TEXTURE_2D, inTextureStorage[i]);
                    Gl.glTexImage2D(Gl.GL_TEXTURE_2D, 0, (int)Gl.GL_RGB8, image.Width, image.Height,
                        0, Gl.GL_BGR_EXT, Gl.GL_UNSIGNED_BYTE, bitmapdata.Scan0);
                    Gl.glTexParameteri(Gl.GL_TEXTURE_2D, Gl.GL_TEXTURE_MIN_FILTER, Gl.GL_LINEAR);		// Linear Filtering
                    Gl.glTexParameteri(Gl.GL_TEXTURE_2D, Gl.GL_TEXTURE_MAG_FILTER, Gl.GL_LINEAR);		// Linear Filtering

                    image.UnlockBits(bitmapdata);
                    image.Dispose();
                }
            }
            catch (System.Exception e)
            {
                return "Loading Textures problem, exception: " + e.ToString();
            }
            return ""; // If here everything went OK
        }
    }
}
