///////////////////////////////////////
///////// Author: Jason Carby
///////// Created: 12:30pm 1st December 2008
///////// Work: Created Interface and RenderString Method
////////////////Changed reference to Tao.OpenGL.dll
///////// Signed Off: 12:35pm 1st December 2008
//////////////////////////////////////

using Tao.OpenGl;
using Tao.Glut;

namespace CardGame
{
    public interface IText
    {
        ///<summary>
        ///Renders text on the screen
        ///</summary>
        ///<returns>Nothing</returns>
        void RenderString(float x, float y, string str);
    }

    public class Text:IText
    {
        // Note x and y are in world co-ordinates, not screen.
        public void RenderString(float x, float y, string str)
        {
            Gl.glRasterPos2f(x, y);
            int len = str.Length;
            for (int i = 0; i < len; i++)
            {
                Glut.glutBitmapCharacter(Glut.GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
            }
        }
    }
}
