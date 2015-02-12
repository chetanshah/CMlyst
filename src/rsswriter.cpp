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

#include "rsswriter.h"

#include <QStringBuilder>
#include <QDebug>

#define NAMESPACE_CONTENT "http://purl.org/rss/1.0/modules/content/"
#define NAMESPACE_WFW     "http://wellformedweb.org/CommentAPI/"
#define NAMESPACE_DC      "http://purl.org/dc/elements/1.1/"
#define NAMESPACE_ATOM    "http://www.w3.org/2005/Atom"
#define NAMESPACE_SY      "http://purl.org/rss/1.0/modules/syndication/"
#define NAMESPACE_SLASH   "http://purl.org/rss/1.0/modules/slash/"
#define NAMESPACE_GEORSS  "http://www.georss.org/georss"
#define NAMESPACE_GEO     "http://www.w3.org/2003/01/geo/wgs84_pos#"
#define NAMESPACE_MEDIA   "http://search.yahoo.com/mrss/"

RSSWriter::RSSWriter(QObject *parent) : QObject(parent)
  , m_stream(&m_output)
{
//    m_stream.setAutoFormatting(true);
    m_stream.writeStartDocument();
    m_stream.writeStartElement(QStringLiteral("rss"));
    m_stream.writeNamespace(NAMESPACE_CONTENT,"content");
    m_stream.writeNamespace(NAMESPACE_WFW,"wfw");
    m_stream.writeNamespace(NAMESPACE_DC,"dc");
    m_stream.writeNamespace(NAMESPACE_ATOM,"atom");
    m_stream.writeNamespace(NAMESPACE_SY,"sy");
    m_stream.writeNamespace(NAMESPACE_SLASH,"slash");
    m_stream.writeNamespace(NAMESPACE_GEORSS,"georss");
    m_stream.writeNamespace(NAMESPACE_GEO,"geo");
    m_stream.writeNamespace(NAMESPACE_MEDIA,"media");
}

RSSWriter::~RSSWriter()
{

}

void RSSWriter::writeStartChannel()
{
    m_stream.writeStartElement(QStringLiteral("channel"));
}

void RSSWriter::writeChannelTitle(const QString &title)
{
    m_stream.writeTextElement(QStringLiteral("title"), title);
}

void RSSWriter::writeChannelLink(const QString &link)
{
    m_stream.writeTextElement(QStringLiteral("link"), link);
}

void RSSWriter::writeChannelFeedLink(const QString &link, const QString &mimeType, const QString &rel)
{
    m_stream.writeStartElement(NAMESPACE_ATOM, QStringLiteral("link"));

    m_stream.writeAttribute(QStringLiteral("href"), link);

    if (rel.isNull()) {
        m_stream.writeAttribute(QStringLiteral("rel"), QStringLiteral("self"));
    } else {
        m_stream.writeAttribute(QStringLiteral("rel"), rel);
    }

    if (mimeType.isNull()) {
        m_stream.writeAttribute(QStringLiteral("type"), QStringLiteral("application/rss+xml"));
    } else {
        m_stream.writeAttribute(QStringLiteral("type"), mimeType);
    }

    m_stream.writeEndElement();
}

void RSSWriter::writeChannelDescription(const QString &description)
{
    m_stream.writeTextElement(QStringLiteral("description"), description);
}

void RSSWriter::writeChannelLastBuildDate(const QDateTime &lastBuildDate)
{
    QLocale locale(QLocale::C);
    const QString &dt = locale.toString(lastBuildDate.toTimeSpec(Qt::UTC),
                                        QLatin1String("ddd, dd MMM yyyy hh:mm:ss")) % QLatin1String(" GMT");
    m_stream.writeTextElement(QStringLiteral("lastBuildDate"), dt);
}

void RSSWriter::writeChannelLanguage(const QString &language)
{
    m_stream.writeTextElement(QStringLiteral("language"), language);
}

void RSSWriter::writeStartImage()
{
    m_stream.writeStartElement(QStringLiteral("image"));
}

void RSSWriter::writeImageUrl(const QString &url)
{
    m_stream.writeTextElement(QStringLiteral("url"), url);
}

void RSSWriter::writeImageTitle(const QString &title)
{
    m_stream.writeTextElement(QStringLiteral("title"), title);
}

void RSSWriter::writeImageLink(const QString &link)
{
    m_stream.writeTextElement(QStringLiteral("link"), link);
}

void RSSWriter::writeEndImage()
{
    m_stream.writeEndElement();
}

void RSSWriter::writeStartItem()
{
    m_stream.writeStartElement(QStringLiteral("item"));
}

void RSSWriter::writeItemTitle(const QString &title)
{
    m_stream.writeTextElement(QStringLiteral("title"), title);
}

void RSSWriter::writeItemLink(const QString &link)
{
    m_stream.writeTextElement(QStringLiteral("link"), link);
}

void RSSWriter::writeItemCommentsLink(const QString &link)
{
    m_stream.writeTextElement(QStringLiteral("comments"), link);
}

void RSSWriter::writeItemNumberOfComments(int number)
{
    m_stream.writeStartElement(NAMESPACE_SLASH, "comments");
    m_stream.writeCDATA(QString::number(number));
    m_stream.writeEndElement();
}

void RSSWriter::writeItemCreator(const QString &creator)
{
    m_stream.writeStartElement(NAMESPACE_DC, "creator");
    m_stream.writeCDATA(creator);
    m_stream.writeEndElement();
}

void RSSWriter::writeItemCategory(const QString &category)
{
    m_stream.writeStartElement("category");
    m_stream.writeCDATA(category);
    m_stream.writeEndElement();
}

void RSSWriter::writeItemPubDate(const QDateTime &pubDate)
{
    QLocale locale(QLocale::C);
    const QString &dt = locale.toString(pubDate.toTimeSpec(Qt::UTC),
                                        QLatin1String("ddd, dd MMM yyyy hh:mm:ss")) % QLatin1String(" GMT");
    m_stream.writeTextElement(QStringLiteral("pubDate"), dt);
}

void RSSWriter::writeItemDescription(const QString &description)
{
    m_stream.writeStartElement("description");
    m_stream.writeCDATA(description);
    m_stream.writeEndElement();
}

void RSSWriter::writeItemContent(const QString &content)
{
    m_stream.writeStartElement(NAMESPACE_CONTENT, QStringLiteral("encoded"));
    m_stream.writeCDATA(content);
    m_stream.writeEndElement();
}

void RSSWriter::writeEndItem()
{
    m_stream.writeEndElement();
}

void RSSWriter::writeEndChannel()
{
    m_stream.writeEndElement();
}

void RSSWriter::endRSS()
{
    m_stream.writeEndElement();
    m_stream.writeEndDocument();
}

QByteArray RSSWriter::result() const
{
    return m_output;
}
