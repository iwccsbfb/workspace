import requests
import json

def getMovieTitles(substr):
    url = 'https://jsonmock.hackerrank.com/api/movies/search/?Title='+substr
    r = requests.get(url)
    data = r.json()
    titles = []
    for i in range(1, data['total_pages']+1):
        url_new = url + '&page=' + str(i)
        r = requests.get(url_new)
        l = [movie['Title'] for movie in r.json()['data']]
        titles.extend(l)
    titles.sort()
    return titles
#   getMovieTitles('spiderman')            


if __name__ == '__main__':
  a = 1