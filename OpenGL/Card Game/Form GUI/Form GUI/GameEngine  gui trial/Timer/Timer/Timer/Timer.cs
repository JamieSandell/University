//////////////////////////////////////////////////
///////////Author: Jamie Sandell
///////////Signed On: 10:32am - Tuesday 2nd December 2008
///////////Work Done: Created and worked on the class
///////////Signed Off: 10:49am - Tuesday 2nd December 2008
////
//////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace CardGame
{
    public interface ITimer
    {
        /// <summary>
        /// Start the timer
        /// </summary>
        void StartTimer();

        /// <summary>
        /// Stop the timer
        /// </summary>
        void StopTimer();

        /// <summary>
        /// Reset the timer
        /// </summary>
        void ResetTimer();

        /// <summary>
        /// Get the time elapsed (in milliseconds) that has elapsed since the timer started
        /// </summary>
        /// <returns></returns>
        int GetTimeElapsed();
    }

    public class Timer:ITimer
    {
        Stopwatch _MTimer = new Stopwatch();

        public void StartTimer()
        {
            _MTimer.Start();
        }

        public void StopTimer()
        {
            _MTimer.Stop();
        }

        public void ResetTimer()
        {
            _MTimer.Reset();
        }

        public int GetTimeElapsed()
        {
            return (int)_MTimer.ElapsedMilliseconds;
        }
    }
}
