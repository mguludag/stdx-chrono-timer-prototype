/*****************************************************************************
 * timer.hpp
 *
 * Created: 4/2/2021 2021 by mguludag
 *
 * Copyright 2021 mguludag. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/
#ifndef TIMER_HPP
#define TIMER_HPP
#include <atomic>
#include <chrono>
#include <functional>
#include <thread>

namespace stdx {
    namespace chrono {
        class timer {
        public:
          timer() = default;

          timer(const timer &copy)
              : m_interval(copy.m_interval), m_func(copy.m_func), m_inflight(false) {}

          explicit timer(const std::chrono::milliseconds interval,
                         const std::function<void()> &func)
              : m_interval(interval), m_func(func), m_inflight(true) {
            event_loop();
          }

          explicit timer(const std::chrono::microseconds interval,
                         const std::function<void()> &func)
              : m_interval(
                    std::chrono::duration_cast<std::chrono::milliseconds>(interval)),
                m_func(func), m_inflight(true) {
            event_loop();
          }

          explicit timer(const std::chrono::nanoseconds interval,
                         const std::function<void()> &func)
              : m_interval(
                    std::chrono::duration_cast<std::chrono::milliseconds>(interval)),
                m_func(func), m_inflight(true) {
            event_loop();
          }

          explicit timer(const std::chrono::seconds interval,
                         const std::function<void()> &func)
              : m_interval(
                    std::chrono::duration_cast<std::chrono::milliseconds>(interval)),
                m_func(func), m_inflight(true) {
            event_loop();
          }

          ~timer() { stop_event_loop(); }

          void singleshot(const std::chrono::milliseconds interval,
                         const std::function<void()> &func) {
              m_interval = interval;
              m_func = func;
              m_thread = std::thread([this]{
                  std::this_thread::sleep_for(m_interval);
                  m_func();
              });
          }

          void singleshot(const std::chrono::microseconds interval,
                         const std::function<void()> &func) {
              m_interval = std::chrono::duration_cast<std::chrono::milliseconds>(interval);
              m_func = func;
              m_thread = std::thread([this]{
                  std::this_thread::sleep_for(m_interval);
                  m_func();
              });
          }

          void singleshot(const std::chrono::nanoseconds interval,
                         const std::function<void()> &func) {
              m_interval = std::chrono::duration_cast<std::chrono::milliseconds>(interval);
              m_func = func;
              m_thread = std::thread([this]{
                  std::this_thread::sleep_for(m_interval);
                  m_func();
              });
          }

          void singleshot(const std::chrono::seconds interval,
                         const std::function<void()> &func) {
              m_interval = std::chrono::duration_cast<std::chrono::milliseconds>(interval);
              m_func = func;
              m_thread = std::thread([this]{
                  std::this_thread::sleep_for(m_interval);
                  m_func();
              });
          }

          void set_interval(const std::chrono::milliseconds interval) {
            m_interval = interval;
          }
          void set_interval(const std::chrono::microseconds interval) {
            m_interval =
                std::chrono::duration_cast<std::chrono::milliseconds>(interval);
          }
          void set_interval(const std::chrono::nanoseconds interval) {
            m_interval =
                std::chrono::duration_cast<std::chrono::milliseconds>(interval);
          }
          void set_interval(const std::chrono::seconds interval) {
            m_interval =
                std::chrono::duration_cast<std::chrono::milliseconds>(interval);
          }
          void connect(const std::function<void()> &func) { m_func = func; }
          void start() {
            m_inflight = true;
            event_loop();
          }
          void stop() { stop_event_loop(); }

        private:
          void event_loop() {
            m_thread = std::thread([this] {
              while (m_inflight) {
                std::this_thread::sleep_for(m_interval);
                m_func();
              }
            });
          }

          void stop_event_loop() {
            m_inflight = false;
            if (m_thread.joinable()) {
              m_thread.join();
            }
          }

          std::chrono::milliseconds m_interval{};
          std::function<void()> m_func;
          std::atomic<bool> m_inflight;
          std::thread m_thread;
        };
    } // namespace chrono
} // namespace stdx

#endif // TIMER_HPP
