#!/usr/bin/python

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

#def checkPage(PAGE):
#	page = PAGE
#	if page is blank:
#		return "b-"
#	if page is abandoned:
#		return "a-"
#	if page is incomplete:
#		return "i-"
#	else:
#		return ""

def writePage(URL,CHECK,PAGE):
	f = open(CHECK+URL,'w')
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

#def main():
#	for i in range (0,3000000):
#		try:
#			urlPartie = "http://www.boiteajeux.net/jeux/agr/partie.php?id="+str(i)
#			urlHistorique = "http://www.boiteajeux.net/jeux/agr/historique.php?id="+str(i)
#			for url in [urlPartie, urlHistorique]:
#				page = getPage(url)
#				check = checkPage(page)
#				writePage(url,check,page)
#		except (Exception e):
#			print i,e

#if __name__ == "__main__":
checkAllPages()
