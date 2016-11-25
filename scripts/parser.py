#!/usr/bin/python
#history = BeautifulSoup(open("2022398-history.html"))

import urllib2, os
from bs4 import BeautifulSoup

def getBonus(bonus):
	X = bonus.split(' => ')
	b = 0
	for x in X[1:]:
		b += int(x[0])
	return b	

def getPlayer(NT,cols):
	return {'player' : NT[0] , 'fields' : int(cols[0]) , 'pastures' : int(cols[1]) , 'grain':int(cols[2]) , \
'vegetables' : int(cols[3]) , 'sheep' : int(cols[4]) , 'boar' : int(cols[5]) , 'cattle' : int(cols[6]), \
'unused' : int(cols[7]) , 'fstables' : int(cols[8]) , 'rooms' : int(cols[9]) , 'family':int(cols[10]), \
'cards':int(cols[11]),'bonus':getBonus(cols[12]),'total':int(NT[1])}


r = urllib2.urlopen("file://"+os.path.abspath("2022398-game.html"))
game = r.read()
numPlayers = game.count("</div>&nbsp")
GAME = BeautifulSoup(game,'lxml')
r.close()

scoreTable = GAME.find('table', attrs={'class':'clScore'})
titles = scoreTable.find_all('th')
titles = [ele.text.strip() for ele in titles]
playerTotals = titles[-8:]
players = []

rows = scoreTable.find_all('tr')
i = 0
for row in rows:
	cols = row.find_all('td')
	cols = [ele.text.strip() for ele in cols]
	if cols != []:
		players.append(getPlayer(playerTotals[i:i+2],cols))
		i += 2

# final score table in players
