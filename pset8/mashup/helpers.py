import feedparser
import urllib.parse
from random import shuffle, seed

UKR_NEWS = ["https://news.yandex.ua/index.rss", "http://www.ukr-portal.com/php/rss_1.xml",
"http://www.ua.rian.ru/export/rss2/index.xml", "http://feeds.feedburner.com/zaxid/rss_ua", "http://www.dt.ua/export.rss"]

def lookup(geo, lang="us"):
    """Looks up articles for geo."""
    
    # check cache for geo
    if geo in lookup.cache:
        if lookup.query_counter[geo] < 10:
            return lookup.cache[geo]
        else:
            del lookup.cache[geo]
            del lookup.query_counter[geo]
            
    url = "http://news.google.com/news?ned=" + lang+ "&geo={}&output=rss"
    
    # get feed from Google
    feed = feedparser.parse(url.format(urllib.parse.quote(geo, safe="")))

    # if no items in feed, get feed from other
    if not feed["items"]:
        if lang == "ru_ua":
            
            # get random UKR_NEWS
            seed()
            shuffle(UKR_NEWS)
            feed = feedparser.parse(UKR_NEWS[0])
            if not feed["items"]:
                
                # there is always news
                feed = feedparser.parse("http://news.yandex.ru/index.rss")
        else:
            
            # get from Onion
            feed = feedparser.parse("http://www.theonion.com/feeds/rss")
            
    # cache results
    lookup.cache[geo] = [{"link": item["link"], "title": item["title"]} for item in feed["items"]]
    
    # add counter
    lookup.query_counter[geo] = 1

    # return results
    return lookup.cache[geo]

# initialize cache
lookup.cache = {}

# initialize query counter
lookup.query_counter = {}

