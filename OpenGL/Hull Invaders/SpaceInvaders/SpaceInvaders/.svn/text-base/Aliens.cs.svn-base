using System;
using System.Collections.Generic;
using System.Text;
using Tao.OpenGl;
using Tao.Glut;
using System.Collections;
using System.Windows.Forms;

namespace SpaceInvaders
{
    public interface IAliens
    {
        /// <summary>
        /// Draw the alien on the screen
        /// </summary>
        void DrawAlien();
    }

    public class Aliens : IAliens
    {
        // Have an array of aliens based on the current level
        // and the difficulty setting
        /// TODO:
        /// Add level selection later, for now force the level
        
        // Logistics
        private bool alienBeenHit;
        private static string moveDirection = "right";
        private static double speed = 2;
        private static bool moveDown = false;
        private bool effectFinished;
        private static double degRot = 0;
        private static bool rotateUp = false;

        // Position
        private double colourFadeOut;
        private double alienBottomLeftX;
        private double alienBottomLeftY;
        private double alienBottomRightX;
        private double alienBottomRightY;
        private double alienTopRightX;
        private double alienTopRightY;
        private double alienTopLeftX;
        private double alienTopLeftY;
        private double initialAlienBottomLeftX;
        private double initialAlienBottomLeftY;
        private double initialAlienBottomRightX;
        private double initialAlienBottomRightY;
        private double initialAlienTopRightX;
        private double initialAlienTopRightY;
        private double initialAlienTopLeftX;
        private double initialAlienTopLeftY;
        // Bullet
        private double initialAlienBulletBottomLeftX;
        private double initialAlienBulletBottomLeftY;
        private double initialAlienBulletBottomRightX;
        private double initialAlienBulletBottomRightY;
        private double initialAlienBulletTopRightX;
        private double initialAlienBulletTopRightY;
        private double initialAlienBulletTopLeftX;
        private double initialAlienBulletTopLeftY;

        public Aliens(double bLX, double bLY, double bRX, double bRY, double tRX, double tRY, double tLX,
            double tLY) // Constructor
        {
            alienBottomLeftX = bLX;
            alienBottomLeftY = bLY;
            alienBottomRightX = bRX;
            alienBottomRightY = bRY;
            alienTopRightX = tRX;
            alienTopRightY = tRY;
            alienTopLeftX = tLX;
            alienTopLeftY = tLY;
            initialAlienBottomLeftX = bLX;
            initialAlienBottomLeftY = bLY;
            initialAlienBottomRightX = bRX;
            initialAlienBottomRightY = bRY;
            initialAlienTopRightX = tRX;
            initialAlienTopRightY = tRY;
            initialAlienTopLeftX = tLX;
            initialAlienTopLeftY = tLY;
            alienBeenHit = false;
        }

        public void ResetAlienPosition()
        {
            alienBottomLeftX = initialAlienBottomLeftX;
            alienBottomLeftY = initialAlienBottomLeftY;
            alienBottomRightX = initialAlienBottomRightX;
            alienBottomRightY = initialAlienBottomRightY;
            alienTopRightX = initialAlienTopRightX;
            alienTopRightY = initialAlienTopRightY;
            alienTopLeftX = initialAlienTopLeftX;
            alienTopLeftY = initialAlienTopLeftY;
        }

        public void InitialiseColourFadeOut() // for hit alien effect
        {
            colourFadeOut = 1;
            effectFinished = true;
        }

        public void RotateAndDrawAlien()
        {
            if (!rotateUp)
            {
                degRot -= 0.2;
                if (degRot <= 0)
                {
                    rotateUp = true;
                }
            }
            if (rotateUp)
            {
                degRot += 0.2;
                if (degRot >= 300)
                {
                    rotateUp = false;
                }
            }

            Gl.glPushMatrix();
            Gl.glRotated(degRot, alienBottomLeftX, alienBottomLeftY, 0);
            Gl.glBegin(Gl.GL_POLYGON);
            Gl.glColor3d(colourFadeOut, 0, 0);
            Gl.glVertex2d(alienBottomLeftX, alienBottomLeftY); // BL
            Gl.glColor3d(0, colourFadeOut, colourFadeOut);
            Gl.glVertex2d(alienBottomRightX, alienBottomRightY); // BR
            Gl.glColor3d(0, colourFadeOut, 0);
            Gl.glVertex2d(alienTopRightX, alienTopRightY); // TR
            Gl.glColor3d(0, 0, colourFadeOut);
            Gl.glVertex2d(alienTopLeftX, alienTopLeftY); // TL
            Gl.glEnd();
            Gl.glPopMatrix();

            // set the colour back
            Gl.glColor3d(1, 1, 1);
        }

        public void DrawAlien()
        {
            if (!alienBeenHit) // If alien hasn't been hit
            {
                Gl.glBegin(Gl.GL_POLYGON);
                Gl.glColor3d(colourFadeOut, 0, 0);
                Gl.glVertex2d(alienBottomLeftX, alienBottomLeftY); // BL
                Gl.glColor3d(0, colourFadeOut, colourFadeOut);
                Gl.glVertex2d(alienBottomRightX, alienBottomRightY); // BR
                Gl.glColor3d(0, colourFadeOut, 0);
                Gl.glVertex2d(alienTopRightX, alienTopRightY); // TR
                Gl.glColor3d(0, 0, colourFadeOut);
                Gl.glVertex2d(alienTopLeftX, alienTopLeftY); // TL
                Gl.glEnd();

                // set the colour back
                Gl.glColor3d(1, 1, 1);
            }
            if (alienBeenHit)
            {
                if (colourFadeOut > 0.0)
                {
                    colourFadeOut -= 0.05;
                    Gl.glBegin(Gl.GL_POLYGON);
                    Gl.glColor3d(colourFadeOut, 0, 0);
                    Gl.glVertex2d(alienBottomLeftX, alienBottomLeftY); // BL
                    Gl.glColor3d(0, colourFadeOut, colourFadeOut);
                    Gl.glVertex2d(alienBottomRightX, alienBottomRightY); // BR
                    Gl.glColor3d(0, colourFadeOut, 0);
                    Gl.glVertex2d(alienTopRightX, alienTopRightY); // TR
                    Gl.glColor3d(0, 0, colourFadeOut);
                    Gl.glVertex2d(alienTopLeftX, alienTopLeftY); // TL
                    Gl.glEnd();

                    // set the colour back
                    Gl.glColor3d(1, 1, 1);
                }
                else
                {
                    effectFinished = true; // No need for the hit effect now
                }
            }
        }

        public bool GetEffectFinishedStatus()
        {
            return effectFinished;
        }

        public void SetEffectFinishedStatus(bool status) // So the aliens can be redrawn for a new level
        {
            effectFinished = status;
        }

        public void GetBulletPosition(out double bulletTopLeftX, out double bulletTopLeftY,
            out double bulletTopRightX, out double bulletTopRightY, out double bulletBottomLeftX,
            out double bulletBottomLeftY, out double bulletBottomRightX, out double bulletBottomRightY)
        {
            bulletTopLeftX = initialAlienBulletTopLeftX;
            bulletTopLeftY = initialAlienBulletTopLeftY;
            bulletTopRightX = initialAlienBulletTopRightX;
            bulletTopRightY = initialAlienBulletTopRightY;
            bulletBottomLeftX = initialAlienBulletBottomLeftX;
            bulletBottomLeftY = initialAlienBulletBottomLeftY;
            bulletBottomRightX = initialAlienBulletBottomRightX;
            bulletBottomRightY = initialAlienBulletBottomRightY;
        }

        public bool HaveIBeenHit(double bulletTopLeftX, double bulletTopLeftY, double bulletTopRightX,
            double bulletTopRightY, double bulletBottomLeftX, double bulletBottomLeftY,
            double bulletBottomRightX, double bulletBottomRightY)
        {
            if (alienBeenHit)
            {
                return false; // It's already been hit so avoid the collision
            }
            if ((bulletTopLeftY >= alienBottomLeftY) && (bulletTopLeftY <= alienTopLeftY))
            {
                if (bulletBottomLeftX == alienBottomLeftX) // direct hit
                {
                    // Hit the alien
                    alienBeenHit = true;
                    return true;
                }
            }
            if ((bulletTopLeftY >= alienBottomLeftY) && (bulletTopLeftY <= alienTopLeftY))
            {
                if ((bulletBottomLeftX > alienBottomLeftX) &&
                    (bulletBottomRightX < alienBottomRightX)) // hit somewhere in the middle
                {
                alienBeenHit = true;
                return true;
                }
            }
            return false; // Not been hit
        }

        public void HasAlienHitWall()
        {
            // Find out where they are
            if (alienBottomLeftX <= 0) // Hit the left hand side
            {
                moveDirection = "right";
                moveDown = true; // So all the aliens move down
            }
            if (alienBottomRightX >= 500) // Hit the right hand side
            {
                moveDirection = "left";
                moveDown = true; // So all the aliens move down
            }
        }

        public void MoveAliens()
        {
            if (moveDirection == "left")
            {
                alienBottomLeftX -= speed;
                alienBottomRightX -= speed;
                alienTopLeftX -= speed;
                alienTopRightX -= speed;
            }
            if (moveDirection == "right")
            {
                alienBottomLeftX += speed;
                alienBottomRightX += speed;
                alienTopLeftX += speed;
                alienTopRightX += speed;
            }
            if (moveDown)
            {
                // drop down effect
                alienTopLeftY -= 10;
                alienTopRightY -= 10;
                alienBottomLeftY -= 10;
                alienBottomRightY -= 10;
            }
        }

        public void UpdateSpeed(double newSpeed)
        {
            speed += newSpeed;
        }

        public void ResetAlienBeenHit()
        {
            alienBeenHit = false;
        }

        public string DrawAlienBullet()
        {
            Gl.glColor3d(1, 1, 0);
            Gl.glRectd(initialAlienBulletBottomLeftX, initialAlienBulletBottomLeftY,
                initialAlienBulletTopRightX, initialAlienBulletTopRightY);
            return "";
        }

        public void UpdateAlienBulletPosition()
        {

            initialAlienBulletBottomLeftY = initialAlienBulletBottomLeftY - 5;
            initialAlienBulletBottomRightY = initialAlienBulletBottomRightY - 5;
            initialAlienBulletTopLeftY = initialAlienBulletTopLeftY - 5;
            initialAlienBulletTopRightY = initialAlienBulletTopRightY - 5;
        }

        public void SetUpInitialBulletPosition()
        {
            initialAlienBulletBottomLeftX = (alienBottomLeftX + alienBottomRightX) / 2;
            initialAlienBulletBottomLeftY = alienBottomLeftY;
            initialAlienBulletBottomRightX = initialAlienBulletBottomLeftX + 5; // 5 is the width
            initialAlienBulletBottomRightY = alienBottomRightY;
            initialAlienBulletTopRightX = initialAlienBulletBottomRightX; // width
            initialAlienBulletTopRightY = initialAlienBulletBottomRightY + 5; // Height
            initialAlienBulletTopLeftX = initialAlienBulletBottomLeftX;
            initialAlienBulletTopLeftY = initialAlienBulletTopRightY; // Height

        }

        public double GetAlienBulletTopLeftY()
        {
            return initialAlienBulletTopLeftY;
        }

        public void SetMoveDown(bool status)
        {
            if (status)
            {
                moveDown = true;
            }
            else
            {
                moveDown = false;
            }
        }

        public bool GetAlienHitStatus()
        {
            if (colourFadeOut > 0.0) // effect hasn't finished
            {
                return false;
            }
            return alienBeenHit;
        }

        public bool HaveICollidedWithThePlayer(double playerBottomLeftX, double playerBottomLeftY,
            double playerBottomRightX, double playerBottomRightY, double playerTopX, double playerTopY)
        {
            // Skip this if the alien isn't drawn on the screen
            if (alienBeenHit)
            {
                return false;
            }

            // Hit the top right of the player
            if ((alienBottomLeftY <= playerTopY) && (alienTopLeftY > playerBottomLeftY))
            {
                if (alienBottomRightX == playerTopX)
                {
                    return true; // Been hit
                }
            }

            // Hit the top left of the player
            if ((alienBottomLeftY <= playerTopY) && (alienTopLeftY > playerBottomLeftY))
            {
                if (alienBottomLeftX == playerTopX)
                {
                    return true;
                }
            }

            // Hit somewhere within the middle of the player
            if ((alienBottomLeftY <= playerTopY) && (alienTopLeftY > playerBottomLeftY))
            {
                // Alien bottom left hit somewhere in the middle of the player
                if ((alienBottomLeftX >= playerBottomLeftX) && (alienBottomLeftX <= playerBottomRightX))
                {
                    return true;
                }
                // Alien bottom left hit the top of the player or alien bottom right hit the left of the
                // player
                if ((alienBottomLeftX == playerTopX) || (alienBottomRightX == playerBottomLeftX))
                {
                    return true;
                }
                // Alien top left hit the player at the top or alien top left hit the player at the
                // at the bottom right
                if ((alienTopLeftX == playerTopX) || (alienTopLeftX == playerBottomRightX))
                {
                    return true;
                }
            }
            return false; // Not collided with the player

        }

        public bool HaveIGoneOffTheScreen(double playerBottomY) // Since the player can't go up this must
            // be the bottom
        {
            if (alienBottomRightY < playerBottomY)
            {
                return true;
            }
            return false; // Haven't gone off the screen
        }
    }
}
