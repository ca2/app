//
// Created by camilo on 2026-07-16 17:15 <3ThomasBorregaardSørensen!! Mummi!! Bilbo
//
#pragma once


class termination_handler
{
public:
   static bool initialize();

   static int notification_fd();

   static bool consume();

private:
   static void signal_handler(int signalNumber);

   inline static int m_pipe[2] = {-1, -1};

};