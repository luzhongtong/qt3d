/* -*- C++ -*-

   This file contains a testsuite for global queue instantiation in ThreadWeaver.

   $ Author: Mirko Boehm $
   $ Copyright: (C) 2005-2013 Mirko Boehm $
   $ Contact: mirko@kde.org
         http://www.kde.org
         http://creative-destruction.me $

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include <QString>
#include <QtTest>

#include <ThreadWeaver/ThreadWeaver>

// The tests checks if the global ThreadWeaver instance is properly
// destroyed along with QCoreApplication. After that all the puppies
// are sad and the kittens cry, and the test exits.
class ShutdownOnQApplicationQuitTests : public QObject
{
    Q_OBJECT

public:
    ShutdownOnQApplicationQuitTests();

private Q_SLOTS:
    void testShutdownOnQApplicationQuit();
};

ShutdownOnQApplicationQuitTests::ShutdownOnQApplicationQuitTests()
{
}

void ShutdownOnQApplicationQuitTests::testShutdownOnQApplicationQuit()
{
    {
        int argc = 0;
        QCoreApplication app(argc, (char **)0);
        QVERIFY(ThreadWeaver::Queue::instance() != 0);
        ThreadWeaver::Queue::instance()->suspend();
        ThreadWeaver::Queue::instance()->resume();
        QTest::qWait(10);
    }
    QVERIFY(ThreadWeaver::Queue::instance() == 0);
}

QTEST_APPLESS_MAIN(ShutdownOnQApplicationQuitTests)

#include "ShutdownOnQApplicationQuitTests.moc"
