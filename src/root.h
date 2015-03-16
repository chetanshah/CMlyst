/***************************************************************************
 *   Copyright (C) 2014-2015 Daniel Nicoletti <dantti12@gmail.com>         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; see the file COPYING. If not, write to       *
 *   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,  *
 *   Boston, MA 02110-1301, USA.                                           *
 ***************************************************************************/

#ifndef ROOT_H
#define ROOT_H

#include <Cutelyst/Controller>
#include <QDir>

#include "cmengine.h"

using namespace Cutelyst;

namespace CMS {
class Engine;
}

class Root : public Controller, public CMEngine
{
    Q_OBJECT
    C_NAMESPACE("")
public:
    Root();
    ~Root();

public:
    C_ATTR(notFound, :Path)
    void notFound(Context *ctx);

    C_ATTR(page, :Page)
    void page(Cutelyst::Context *ctx);

    C_ATTR(post, :Post)
    void post(Cutelyst::Context *ctx);

    C_ATTR(lastPosts, :LatestPosts)
    void lastPosts(Cutelyst::Context *ctx);

    C_ATTR(feed, :Path(.feed))
    void feed(Cutelyst::Context *ctx);

protected:
    virtual bool postFork(Application *app);

private:
    C_ATTR(End, :ActionClass(RenderView))
    void End(Context *ctx);

    QDir m_rootDir;
    QString m_theme;
};

#endif // ROOT_H
