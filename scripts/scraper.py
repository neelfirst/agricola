#!/usr/bin/python

import sys
import urllib.request, urllib.error, urllib.parse
from bs4 import BeautifulSoup

START = 3765004
STOP = 3765006
STEP = 1

def getPage(url):
	user_agent = 'Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_4; en-US) AppleWebKit/534.3 (KHTML, like Gecko) Chrome/6.0.472.63 Safari/534.3'
	headers = { 'User-Agent' : user_agent }
	req = urllib.request.Request(url, None, headers)
	response = urllib.request.urlopen(req)
	page = response.read()
	response.close()
	return page

def checkIfGameIsDone(game,history):
	isGameOver = "- GAME OVER -" in game
	hasGivenUp = "gives up!" in history
	hasLayaboutEffect = "\"Layabout\" effect" in history
	isRound14 = "<td class=\"clHisto\" style=\"text-align:center;vertical-align:middle;font-weight:bold;color:red\">14</td>" in history
	numPlayers = history.count("</div>&nbsp")
	numFeedings = history.count("feeding")
	if (isRound14 and isGameOver and numPlayers*6 == numFeedings+hasLayaboutEffect):
		return True
	else:
		return False

def writePage(url,ext,page):
	f = open(url[-7:]+ext,'w')
	f.write(page)
	f.close()

def main(argv):
	for i in range(START,STOP,STEP):
		try:
			urlPartie = "http://www.boiteajeux.net/jeux/agr/partie.php?id="+str(i)
			urlHistorique = "http://www.boiteajeux.net/jeux/agr/historique.php?id="+str(i)
			pageGame = getPage(urlPartie)
			pageHistory = getPage(urlHistorique)
			if checkIfGameIsDone(pageGame,pageHistory):
				writePage(urlPartie,"-game.html",pageGame)
				writePage(urlHistorique,"-history.html",pageHistory)
				print("valid game i = ",i)
		except Exception as e:
			print(i,e)
			continue
		if (i % 5000 == 0):
			print("checkpoint i = ",i)

if __name__ == "__main__":
	main(sys.argv)
