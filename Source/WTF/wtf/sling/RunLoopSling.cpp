/*
 * Copyright (C) 2013 Naver Corp. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "RunLoop.h"

#include "ThreadLoop.h"

namespace WTF {

RunLoop::RunLoop()
    : m_loop(ThreadLoop::current())
{
}

RunLoop::~RunLoop()
{
}

void RunLoop::run()
{
    RunLoop::current().m_loop.run();
}

void RunLoop::stop()
{
    m_loop.stop();
}

void RunLoop::wakeUp()
{
    // FIXME: No need to wake up the run loop if we've already called dispatch
    // before the run loop has had the time to respond.
    m_loop.dispatch([=] { performWork(); });
}

// RunLoop::Timer

RunLoop::TimerBase::TimerBase(RunLoop& runLoop)
    : m_runLoop(runLoop)
    , m_ID(runLoop.m_loop.registerTimer())
    , m_intervalInMillis(0)
    , m_isRepeating(false)
{
}

RunLoop::TimerBase::~TimerBase()
{
    stop();
}

void RunLoop::TimerBase::timerFired(RunLoop* runLoop, int32_t ID)
{
    TimerMap::iterator it = runLoop->m_activeTimers.find(ID);
    if (it == runLoop->m_activeTimers.end()) {
        // The timer must have been stopped after the timer message was posted to the message queue.
        return;
    }

    TimerBase* timer = it->value;

    if (!timer->m_isRepeating)
        runLoop->m_activeTimers.remove(it);

    timer->fired();

    if (timer->m_isRepeating) {
        runLoop->m_loop.dispatchTimer([=] {
            TimerBase::timerFired(runLoop, timer->m_ID);
        }, timer->m_ID, timer->m_intervalInMillis);
    }
}

void RunLoop::TimerBase::start(double nextFireInterval, bool repeat)
{
    m_intervalInMillis = nextFireInterval * 1000;
    m_isRepeating = repeat;
    RunLoop* runLoop = &m_runLoop;
    int32_t ID = m_ID;
    m_runLoop.m_activeTimers.set(ID, this);
    m_runLoop.m_loop.dispatchTimer([=] {
        TimerBase::timerFired(runLoop, ID);
    }, ID, m_intervalInMillis);
}

void RunLoop::TimerBase::stop()
{
    TimerMap::iterator it = m_runLoop.m_activeTimers.find(m_ID);
    if (it == m_runLoop.m_activeTimers.end())
        return;

    m_runLoop.m_activeTimers.remove(it);
    m_runLoop.m_loop.removeTimer(m_ID);
}

bool RunLoop::TimerBase::isActive() const
{
    return m_runLoop.m_activeTimers.contains(m_ID);
}

} // namespace WebCore
