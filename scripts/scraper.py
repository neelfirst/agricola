#!/usr/bin/env python3

import time
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

def writePage(i,ext,page):
    with open(f'{i:07}'+ext,'w') as file:
        file.write(page)

def main(argv):
    parser = argparse.ArgumentParser(description='scrape boiteajeux.net for agricola games')
    parser.add_argument('start', type=int, help='start game')
    parser.add_argument('stop', type=int, help='stop game')
    parser.add_argument('step', type=int, help='step game')
    args = parser.parse_args()
    for i in range(args.start, args.stop, args.step):
        try:
            historique = "http://www.boiteajeux.net/jeux/agr/historique.php?id="+str(i)
            history = getPage(historique)
            if checkIfGameIsDone(history):
                partie = "http://www.boiteajeux.net/jeux/agr/partie.php?id="+str(i)
                game = getPage(partie)
                writePage(i,"-game.html",game)
                writePage(i,"-history.html",history)
                print("valid game i = ",i)
        except Exception as e:
            print(i,e)
            continue
#        if (i % 5000 == 0):
        print("checkpoint i = ",i)
        time.sleep(1)

if __name__ == "__main__":
    main(sys.argv)
