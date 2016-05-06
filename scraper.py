#!/usr/bin/python

import sys
import urllib2
from bs4 import BeautifulSoup
import numpy as np

def getPage(URL):
	user_agent = 'Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_4; en-US) AppleWebKit/534.3 (KHTML, like Gecko) Chrome/6.0.472.63 Safari/534.3'
	headers = { 'User-Agent' : user_agent }
	req = urllib2.Request(URL, None, headers)
	response = urllib2.urlopen(req)
	page = response.read()
	response.close()
	return page

def checkIfGameIsDone(GAME,HISTORY):
#	print HISTORY
	isGameOver = "- GAME OVER -" in GAME
	hasGivenUp = "gives up!" in HISTORY
	hasLayaboutEffect = "\"Layabout\" effect" in HISTORY
	isRound14 = "<td class=\"clHisto\" style=\"text-align:center;vertical-align:middle;font-weight:bold;color:red\">14</td>" in HISTORY
	numPlayers = HISTORY.count("</div>&nbsp")
	numFeedings = HISTORY.count("feeding")
	print "isGameOver = ",isGameOver
	print "hasGivenUp = ",hasGivenUp
	print "isRound14 = ",isRound14
	print "numPlayers*6 = ",numPlayers*6
	print "numFeedings+hasLayaboutEffect = ",numFeedings+hasLayaboutEffect
	print "hasLayaboutEffect = ",hasLayaboutEffect
	if (isRound14 and isGameOver and numPlayers*6 == numFeedings+hasLayaboutEffect):
		return True
	else:
		return False
	

def writePage(URL,EXT,PAGE):
	f = open(URL[-7:]+EXT,'w')
	f.write(PAGE)
	f.close()

def checkAllPages():
	for i in np.arange (1,2500000,1):
		try:
			urlHistorique = "http://www.boiteajeux.net/jeux/agr/historique.php?id="+str(i)
			request = urllib2.Request(urlHistorique)
			response = urllib2.urlopen(request)
			page = response.read()
			soup = BeautifulSoup(page,"lxml")
			if (len(str(soup.body)) >= 2000):
				print i
#			else:
#				print urlHistorique
#				print len(str(soup.body))
#				break
		except Exception as e:
			print e
	return 0

def main(argv):
	i = argv[1]
	try:
		urlPartie = "http://www.boiteajeux.net/jeux/agr/partie.php?id="+str(i)
		urlHistorique = "http://www.boiteajeux.net/jeux/agr/historique.php?id="+str(i)
		pageGame = getPage(urlPartie)
		pageHistory = getPage(urlHistorique)
		if checkIfGameIsDone(pageGame,pageHistory):
			writePage(urlPartie,"-game.html",pageGame)
			writePage(urlHistorique,"-history.html",pageHistory)
	except Exception as e:
		print i,e

if __name__ == "__main__":
	main(sys.argv)
