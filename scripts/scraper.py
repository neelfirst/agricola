#!/usr/bin/env python3

import sys
import requests
import argparse
from bs4 import BeautifulSoup

def getPage(url):
    r = requests.get(url)
    return r.text

def checkIfGameIsDone(history):
    hasLayaboutEffect = "\"Layabout\" effect" in history
    numPlayers = history.count("</div>&nbsp")
    numFeedings = history.count("feeding")
    if (numPlayers*6 == numFeedings + hasLayaboutEffect):
        return True
    else:
        return False

def writePage(url,ext,page):
    f = open(url[-7:]+ext,'w')
    f.write(page)
    f.close()

def main(argv):
    parser = argparse.ArgumentParser(description='scrape boiteajeux.net for agricola games')
    parser.add_argument('start', type=int, help='start game')
    parser.add_argument('stop', type=int, help='stop game')
    parser.add_argument('step', type=int, help='step game')
    args = parser.parse_args()
    for i in range(args.start, args.stop, args.step):
        try:
  #          partie = "http://www.boiteajeux.net/jeux/agr/partie.php?id="+str(i)
            historique = "http://www.boiteajeux.net/jeux/agr/historique.php?id="+str(i)
  #          game = getPage(partie)
            history = getPage(historique)
            if checkIfGameIsDone(history):
  #              writePage(partie,"-game.html",game)
                writePage(historique,"-history.html",history)
                print("valid game i = ",i)
        except Exception as e:
            print(i,e)
            continue
        if (i % 5000 == 0):
            print("checkpoint i = ",i)

if __name__ == "__main__":
    main(sys.argv)
