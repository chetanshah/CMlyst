/***************************************************************************
 *   Copyright (C) 2014 Daniel Nicoletti <dantti12@gmail.com>              *
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

#ifndef ADMINPAGES_H
#define ADMINPAGES_H

#include <QObject>
#include <Cutelyst/Controller>

#include "cmengine.h"

using namespace Cutelyst;

class AdminPages : public Controller, public CMEngine
{
    Q_OBJECT
    C_NAMESPACE(".admin/pages")
public:
    AdminPages(Application *app);
    ~AdminPages();

    C_ATTR(index, :Path :AutoArgs)
    virtual void index(Context *c);

    C_ATTR(create, :Path("new") :Local :AutoArgs)
    virtual void create(Context *c);

    C_ATTR(edit, :Local :AutoArgs)
    virtual void edit(Context *c, const QString &id);

    C_ATTR(remove, :Path('delete') :AutoArgs)
    void remove(Context *c, const QString &id);

protected:
    void index(Context *c, const QString &postType, CMS::Engine::Filter filters);
    void create(Context *c, const QString &postType, bool isPage);
    void edit(Context *c, const QString &id, const QString &postType, bool isPage);
};

#endif // ADMINPAGES_H
