using System;
using System.Collections.Generic;
using System.Text;
using Tao.OpenGl;
using Tao.Glut;
using System.Collections;
using System.Windows.Forms;

namespace SpaceInvaders
{
    public interface IPlayer
    {
        /// <summary>
        /// Draw the player on the screen
        /// </summary>
        /// <param name="xPos1">The x postion of the left corner of the triangle</param>
        /// <param name="yPos1">The y postion of the left corner of the triangle</param>
        /// <param name="xPos2">The x position of the top corner of the triangle</param>
        /// <param name="yPos2">The y position of the top corner of the triangle</param>
        /// <param name="xPos3">The x position of the right corner of the triangle</param>
        /// <param name="yPos3">The y position of the right corner of the triangle</param>
        /// <param name="livesRemaining">Used to set the colour of the triangle</param>
        string DrawPlayer(double xPos1, double yPos1, double xPos2, double yPos2,
            double xPos3, double yPos3, int livesRemaining);

        /// <summary>
        /// Move the player on the screen
        /// </summary>
        /// <param name="direction">The direction to move the player (left or right) based on
        /// the input from the keyboard</param>
        /// <param name="xPos1">The x postion of the left corner of the triangle</param>
        /// <param name="yPos1">The y postion of the left corner of the triangle</param>
        /// <param name="xPos2">The x position of the top corner of the triangle</param>
        /// <param name="yPos2">The y position of the top corner of the triangle</param>
        /// <param name="xPos3">The x position of the right corner of the triangle</param>
        /// <param name="yPos3">The y position of the right corner of the triangle</param>
        /// <returns>An empty string if the player was moved OK. An error message if
        /// the player was not moved.</returns>
        string MovePlayer(string direction, ref double xPos1, ref double yPos1, ref double xPos2,
            ref double yPos2, ref double xPos3, ref double yPos3);

        /// <summary>
        /// Player shoots a bullet using the spacebar, player has to wait until the bullet has gone off
        /// the screen or has hit an invader before firing another bullet
        /// </summary>
        /// <param name="playerBulletBottomLeftX">Bottom Left X position</param>
        /// <param name="playerBulletBottomLeftY">Bottom Left Y position</param>
        /// <param name="playerBulletBottomRightX">Bottom Right X position</param>
        /// <param name="playerBulletBottomRightY">Bottom Right Y position</param>
        /// <param name="playerBulletTopLeftX">Top Left X position</param>
        /// <param name="playerBulletTopLeftY">Top Left Y position</param>
        /// <param name="playerBulletTopRightX">Top Right X position</param>
        /// <param name="playerBulletTopRightY">Top Right Y position</param>
        /// <returns>An empty string it the bullet was fired OK. An error message if
        /// the player was not moved.</returns>
        string FirePlayerBullet(ref double playerBulletBottomLeftX, ref double playerBulletBottomLeftY,
            ref double playerBulletBottomRightX, ref double playerBulletBottomRightY,
            ref double playerBulletTopLeftX, ref double playerBulletTopLeftY,
            ref double playerBulletTopRightX, ref double playerBulletTopRightY);

        /// <summary>
        /// Update the position of the bullet
        /// </summary>
        /// <param name="playerBulletBottomLeftX">Bottom Left X position</param>
        /// <param name="playerBulletBottomLeftY">Bottom Left Y position</param>
        /// <param name="playerBulletBottomRightX">Bottom Right X position</param>
        /// <param name="playerBulletBottomRightY">Bottom Right Y position</param>
        /// <param name="playerBulletTopLeftX">Top Left X position</param>
        /// <param name="playerBulletTopLeftY">Top Left Y position</param>
        /// <param name="playerBulletTopRightX">Top Right X position</param>
        /// <param name="playerBulletTopRightY">Top Right Y position</param>
        /// <returns>
        /// Doesn't return anything 
        /// </returns>
        void UpdatePlayerBulletPosition(ref double playerBulletBottomLeftX, ref double playerBulletBottomLeftY,
            ref double playerBulletBottomRightX, ref double playerBulletBottomRightY,
            ref double playerBulletTopLeftX, ref double playerBulletTopLeftY,
            ref double playerBulletTopRightX, ref double playerBulletTopRightY);

        /// <summary>
        /// Check to see if the player's bullet has hit anything or gone off the screen
        /// </summary>
        /// <returns>A bool, if true the player can fire another bullet, else cannot</returns>
        bool GetPlayerBulletStatus();

        /// <summary>
        /// Update the player's score
        /// </summary>
        /// <param name="playerScore">The player's current score</param>
        /// <returns>The player's updated score</returns>
        int UpdatePlayerScore(int playerScore);

        /// <summary>
        /// Draw the bullet
        /// </summary>
        /// <param name="playerBulletBottomLeftX">Bottom Left X position</param>
        /// <param name="playerBulletBottomLeftY">Bottom Left Y position</param>
        /// <param name="playerBulletBottomRightX">Bottom Right X position</param>
        /// <param name="playerBulletBottomRightY">Bottom Right Y position</param>
        /// <param name="playerBulletTopLeftX">Top Left X position</param>
        /// <param name="playerBulletTopLeftY">Top Left Y position</param>
        /// <param name="playerBulletTopRightX">Top Right X position</param>
        /// <param name="playerBulletTopRightY">Top Right Y position</param>
        /// <returns>An empty string it the bullet was drawn OK. An error message if
        /// the bullet was not moved.</returns>
        string DrawPlayerBullet(ref double playerBulletBottomLeftX, ref double playerBulletBottomLeftY,
            ref double playerBulletBottomRightX, ref double playerBulletBottomRightY,
            ref double playerBulletTopLeftX, ref double playerBulletTopLeftY,
            ref double playerBulletTopRightX, ref double playerBulletTopRightY);

        /// <summary>
        /// The player has been hit, calls UpdateLives
        /// </summary>
        /// <returns>An empty string if successfull, else an error message.</returns>
        string PlayerHasBeenHit();

        /// <summary>
        /// Updates the lives of the player, sets the GameOver bool value accordingly.
        /// </summary>
        /// <param name="livesModifier">The value of which to modify the player's lives</param>
        /// <returns></returns>
        string UpdateLives(int livesModifier);

        /// <summary>
        /// Returns the status of the gameOver bool value
        /// </summary>
        /// <returns>Returns the status of the gameOver bool value</returns>
        bool GetGameOverStatus();

        /// <summary>
        /// Get the player's lives
        /// </summary>
        /// <returns>The player's lives</returns>
        int GetPlayerLives();

        /// <summary>
        /// Checks to see whether the player has been hit, calls Aliens.GetBulletPosition
        /// </summary>
        /// <param name="alien"></param>
        /// <param name="playerBottomLeftX">Player position</param>
        /// <param name="playerBottomLeftY">Player position</param>
        /// <param name="playerBottomRightX">Player position</param>
        /// <param name="playerBottomRightY">Player position</param>
        /// <param name="playerTopRightX">Player position</param>
        /// <param name="playerTopRightY">Player position</param>
        /// <param name="playerTopLeftX">Player position</param>
        /// <param name="playerTopLeftY">Player position</param>
        /// <returns></returns>
        bool HaveIBeenHit(Aliens alien, double playerBottomLeftX, double playerBottomLeftY,
            double playerBottomRightX, double playerBottomRightY, double playerTopX,
                double playerTopY);

        /// <summary>
        /// Get the player's current position
        /// </summary>
        /// <param name="playerBottomLeftX">Player's position</param>
        /// <param name="playerBottomLeftY">Player's position</param>
        /// <param name="playerBottomRightX">Player's position</param>
        /// <param name="playerBottomRightY">Player's position</param>
        /// <param name="playerTopRightX">Player's position</param>
        /// <param name="playerTopRightY">Player's position</param>
        /// <param name="playerTopLeftX">Player's position</param>
        /// <param name="playerTopLeftY">Player's position</param>
        void GetPlayerPosition(out double playerBottomLeftX, out double playerBottomLeftY,
            out double playerBottomRightX, out double playerBottomRightY, out double playerTopX,
                out double playerTopY);

    }

    public class Player : IPlayer
    {
        private static int modifier = 2;
        private static int playerLives = 3;
        private bool gameOver = false;
        private static double initialPlayerBottomLeftX;
        private static double initialPlayerBottomLeftY;
        private static double initialPlayerTopX;
        private static double initialPlayerTopY;
        private static double initialPlayerBottomRightX;
        private static double initialPlayerBottomRightY;

        public Player(int inLives)
        {
            playerLives = inLives;
        }

        public string DrawPlayer(double xPos1, double yPos1, double xPos2, double yPos2,
            double xPos3, double yPos3, int gameStatus)
        {
            switch (gameStatus)
            {
                case 1: Gl.glColor3d(1, 0, 0); // 1 life remaining
                    break;
                case 2: Gl.glColor3d(1, 0.5, 0); // 2 lives remaining
                    break;
                case 3: Gl.glColor3d(0, 1, 0); // 3 lives remaining
                    break;
                default: Gl.glColor3d(1, 0, 0); // If here must be 3 lives remaining
                    break;
            }

            Gl.glBegin(Gl.GL_TRIANGLES);
            Gl.glVertex2d(xPos1, yPos1);
            Gl.glVertex2d(xPos2, yPos2);
            Gl.glVertex2d(xPos3, yPos3);
            Gl.glEnd();
            // Set the colour back
            Gl.glColor3d(1, 1, 1);

            // for collision code
            initialPlayerBottomLeftX = xPos1;
            initialPlayerBottomLeftY = yPos1;
            initialPlayerBottomRightX = xPos2;
            initialPlayerBottomRightY = yPos2;
            initialPlayerTopX = xPos3;
            initialPlayerTopY = yPos3;

            return "";
        }

        public string MovePlayer(string direction, ref double xPos1, ref double yPos1, ref double xPos2,
            ref double yPos2, ref double xPos3, ref double yPos3)
        {

            if (direction == "left") // Move player left
            {
                xPos1 = xPos1 - 5;
                xPos2 = xPos2 - 5;
                xPos3 = xPos3 - 5;
                return "";

            }

            if (direction == "right") // Move player right
            {
                xPos1 = xPos1 + 5;
                xPos2 = xPos2 + 5;
                xPos3 = xPos3 + 5;
                return "";

            }
            return "";
        }

        public string FirePlayerBullet(ref double playerBulletBottomLeftX,
            ref double playerBulletBottomLeftY, ref double playerBulletBottomRightX,
            ref double playerBulletBottomRightY, ref double playerBulletTopLeftX,
            ref double playerBulletTopLeftY, ref double playerBulletTopRightX,
            ref double playerBulletTopRightY)
        {
            double playerTopYPos = playerBulletBottomLeftY; // Now got the Y centre pos of player
            double playerTopXPos = playerBulletBottomLeftX; // Now got the X centre pos of player
            // TODO:
            // Assign numbers to all the variables in the method header.
            playerBulletBottomLeftX = playerTopXPos - 5;
            playerBulletBottomLeftY = playerTopYPos + 1;
            playerBulletBottomRightX = playerTopXPos - 5;
            playerBulletBottomRightY = playerTopYPos + 1;
            playerBulletTopRightX = playerBulletBottomRightX;
            playerBulletTopRightY = playerTopYPos + 10;
            playerBulletTopLeftX = playerBulletBottomLeftX;
            playerBulletTopLeftY = playerBulletTopRightY;

            Gl.glRectd(playerBulletBottomLeftX, playerBulletBottomLeftY,
                playerBulletTopRightX, playerBulletTopRightY);
            return "";
        }

        public void UpdatePlayerBulletPosition(ref double playerBulletBottomLeftX,
            ref double playerBulletBottomLeftY, ref double playerBulletBottomRightX,
            ref double playerBulletBottomRightY, ref double playerBulletTopLeftX,
            ref double playerBulletTopLeftY, ref double playerBulletTopRightX,
            ref double playerBulletTopRightY)
        {
            playerBulletBottomLeftY = playerBulletBottomLeftY + 5;
            playerBulletBottomRightY = playerBulletBottomRightY + 5;
            playerBulletTopLeftY = playerBulletTopLeftY + 5;
            playerBulletTopRightY = playerBulletTopRightY + 5;
        }

        public string DrawPlayerBullet(ref double playerBulletBottomLeftX, ref double playerBulletBottomLeftY,
            ref double playerBulletBottomRightX, ref double playerBulletBottomRightY,
            ref double playerBulletTopLeftX, ref double playerBulletTopLeftY,
            ref double playerBulletTopRightX, ref double playerBulletTopRightY)
        {
            Gl.glColor3d(1, 1, 0);
            Gl.glBegin(Gl.GL_LINE_LOOP);
            Gl.glVertex2d(playerBulletBottomLeftX, playerBulletBottomLeftY); // BL
            Gl.glVertex2d(playerBulletBottomRightX, playerBulletBottomRightY); // BR
            Gl.glVertex2d(playerBulletTopRightX, playerBulletTopRightY); // TR
            Gl.glVertex2d(playerBulletTopLeftX, playerBulletTopLeftY); // TL
            Gl.glEnd();

            return "";
        }

        public bool GetPlayerBulletStatus()
        {
            return true;
        }

        public bool HaveIBeenHit(Aliens alien, double playerTopX, double playerTopY,
            double playerBottomLeftX, double playerBottomLeftY, double playerBottomRightX,
                double playerBottomRightY)
        {
            double alienBulletBottomLeftX;
            double alienBulletBottomLeftY;
            double alienBulletBottomRightX;
            double alienBulletBottomRightY;
            double alienBulletTopRightX;
            double alienBulletTopRightY;
            double alienBulletTopLeftX;
            double alienBulletTopLeftY;

            double playerBottomMiddle = (playerBottomLeftX + playerBottomRightX) / 2;

            alien.GetBulletPosition(out alienBulletTopLeftX, out alienBulletTopLeftY,
                out alienBulletTopRightX, out alienBulletTopRightY, out alienBulletBottomLeftX,
                    out alienBulletBottomLeftY, out alienBulletBottomRightX, out alienBulletBottomRightY);

            // Hit the top right of the player
            if ((alienBulletBottomLeftY <= playerTopY) && (alienBulletBottomLeftY < playerBottomLeftY))
            {
                if (alienBulletBottomRightX == playerTopX)
                {
                    return true; // Been hit
                }
            }

            // Hit the top left of the player
            if ((alienBulletBottomLeftY <= playerTopY) && (alienBulletBottomLeftY < playerBottomLeftY))
            {
                if (alienBulletBottomLeftX == playerTopX)
                {
                    return true;
                }
            }

            // Hit somewhere within the middle of the player
            if ((alienBulletBottomLeftY <= playerTopY) && (alienBulletBottomLeftY < playerBottomLeftY))
            {
                if ((alienBulletBottomLeftX >= playerBottomLeftX) && (alienBulletBottomLeftX <= playerBottomRightX))
                {
                    return true;
                }
            }

            return false; // Not been hit
        }

        public int UpdatePlayerScore(int playerScore)
        {
            playerScore = playerScore + modifier;
            return playerScore;
        }

        public string PlayerHasBeenHit()
        {
            //UpdateLives(-1);
            return ""; // Everything went OK.
        }

        public string UpdateLives(int livesModifier)
        {
            playerLives += livesModifier;
            if (playerLives <= 0)
            {
                gameOver = true;
            }
            return ""; // Everything went OK.
        }

        public bool GetGameOverStatus()
        {
            return gameOver;
        }

        public int GetPlayerLives()
        {
            return playerLives;
        }

        public void GetPlayerPosition(out double playerBottomLeftX, out double playerBottomLeftY,
            out double playerBottomRightX, out double playerBottomRightY, out double playerTopX,
                out double playerTopY)
        {
            playerBottomLeftX = initialPlayerBottomLeftX;
            playerBottomLeftY = initialPlayerBottomLeftY;
            playerBottomRightX = initialPlayerBottomRightX;
            playerBottomRightY = initialPlayerBottomRightY;
            playerTopX = initialPlayerTopX;
            playerTopY = initialPlayerTopY;
        }
    }
}
