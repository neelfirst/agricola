#!/bin/bash -e

for i in {1..2400000}; do python scraper.py $i; done
