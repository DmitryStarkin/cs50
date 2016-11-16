import feedparser
import urllib.parse
from random import shuffle, seed

UKR_NEWS = ["http://news.yandex.ru/index.rss", "http://feeds.feedburner.com/korrespondent/gLtc", "http://www.ukr-portal.com/php/rss_1.xml",
"http://www.ua.rian.ru/export/rss2/index.xml", "http://feeds.feedburner.com/zaxid/rss_ua", "http://www.dt.ua/export.rss"]

def lookup(geo, lang="us"):
    """Looks up articles for geo."""
    
    url = "http://news.google.com/news?ned=" + lang+ "&geo={}&output=rss"
    
    # check cache for geo
    if geo in lookup.cache:
        return lookup.cache[geo]

    # get feed from Google
    feed = feedparser.parse(url.format(urllib.parse.quote(geo, safe="")))

    # if no items in feed, get feed from Onion
    if not feed["items"]:
        if lang == "ru_ua":
            seed()
            shuffle(UKR_NEWS)
            feed = feedparser.parse(UKR_NEWS[0])
        else:
            feed = feedparser.parse("http://www.theonion.com/feeds/rss")
            
    # cache results
    lookup.cache[geo] = [{"link": item["link"], "title": item["title"]} for item in feed["items"]]

    # return results
    return lookup.cache[geo]

# initialize cache
lookup.cache = {}
