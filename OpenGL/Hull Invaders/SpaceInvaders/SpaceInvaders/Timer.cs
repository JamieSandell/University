using System;
using System.Collections.Generic;
using System.Text;
using Tao.OpenGl;
using Tao.Glut;
using System.Collections;
using System.Windows.Forms;

namespace SpaceInvaders
{
    public interface ITimer
    {
        /// <summary>
        /// Returns the amount of time in seconds that has elapsed since the program started
        /// </summary>
        /// <returns>A float</returns>
        float GetRunTime();

        /// <summary>
        /// Returns the amount of time in seconds that has elapsed since the last time that
        /// this function was called
        /// </summary>
        /// <returns>A float</returns>
        float Tick();
    }

    public class Timer : ITimer
    {
        private float ticksSinceStart;
        private float oldTick;

        public Timer()
        {
            ticksSinceStart = oldTick = System.Environment.TickCount;
        }

        public float GetRunTime()
        {
            ticksSinceStart = (float)System.Environment.TickCount;
            return (float)ticksSinceStart;
        }

        public float Tick()
        {
            ticksSinceStart = (float)(System.Environment.TickCount);
            float dt = ((float)(ticksSinceStart-oldTick)/(float)System.Environment.TickCount);
            oldTick = ticksSinceStart;

            return dt;

        }
    }
}
