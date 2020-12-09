#!/usr/bin/env python3
import os

def clear_games():
  for file in os.scandir(r'.'):
    if(file.path.endswith("game.html")):
      switch = file.path.replace("game.html","history.html")
      try:
        with open(switch,'r') as f:
          continue
      except IOError:
        os.remove(file.path)

def clear_history():
  for file in os.scandir(r'.'):
    if(file.path.endswith("history.html")):
      f = open(file,'r')
      text = f.read()
      f.close()
      if (text.count("</div>&nbsp") != 1):
        os.remove(file.path)

clear_games()
# clear_history()
