// Created by camilo helped by Gemini and
// suggested by V0idsEmbrace on 2026-01-07 21:50 <3ThomasBorregaardSørensen!!
#pragma once


#include <chrono>
#include <deque>
#include <iomanip>
#include <iostream>
#include <numeric>

class fps_counter
{
public:
   fps_counter() : m_frameCount(0), m_averageFrameTimeMs(0.0f), m_averageFps(0.0f)
   {
      m_startTime = std::chrono::high_resolution_clock::now();
   }

   void update()
   {
      auto currentTime = std::chrono::high_resolution_clock::now();
      std::chrono::duration<::f64, std::milli> deltaTime = currentTime - m_lastTime;
      m_lastTime = currentTime;

      // Store frame time in ms
      ::f64 frameTimeMs = deltaTime.count();
      m_frameTimes.push_back(frameTimeMs);

      // Update counts
      m_frameCount++;

      // Calculate average over the last second (or some interval)
      std::chrono::duration<::f64, std::milli> elapsedSinceStart = currentTime - m_startTime;
      if (elapsedSinceStart.count() >= 1000.0)
      { // Update every 1 second
         ::f64 totalMs = std::accumulate(m_frameTimes.begin(), m_frameTimes.end(), 0.0);
         m_averageFrameTimeMs = (::f32) (totalMs / m_frameTimes.size());
         m_averageFps = (::f32) ( 1000.0 / m_averageFrameTimeMs);

         // Optional: display results (or use getter functions)
         //display();

         // Reset for the next interval
         m_startTime = currentTime;
         m_frameTimes.clear();
         m_frameCount = 0;
      }
   }

   //void display() const
   //{
   //   // Use std::fixed and std::setprecision for readable output
   //   std::cout << std::fixed << std::setprecision(2);
   //   std::cout << "Avg Frame Time: " << m_averageFrameTimeMs << " ms | ";
   //   std::cout << "Avg FPS: " << m_averageFps << std::endl;
   //}

   // Getter functions
   ::f32 getAverageFrameTime() const { return m_averageFrameTimeMs; }
   ::f32 getAverageFps() const { return m_averageFps; }

private:
   std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
   std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTime;
   ::u32 m_frameCount;
   std::deque<::f64> m_frameTimes; // Store frame times to average over a window
   ::f32 m_averageFrameTimeMs;
   ::f32 m_averageFps;
};
