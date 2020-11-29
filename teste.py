import re, sys

with open(sys.argv[1], "r") as f:
  s = " ".join([l.rstrip() for l in f])
  regex = re.findall(r'(\w+)', s)
  print("{0} palavras no arquivo".format(len(regex)))