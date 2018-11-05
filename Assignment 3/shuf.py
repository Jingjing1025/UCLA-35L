#!/usr/bin/python

"""
Shuffle the lines in a file
Name: Jingjing Nie
UID: 304567417

"""

import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, filename):
        if filename is sys.stdin:
            f = sys.stdin
        else:
            f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()

    def chooseline(self, arg = None, repeat = False):
        totLength=len(self.lines)
        if repeat is True:
            s = []
            for i in range(arg):
                s.append(random.choice(self.lines))
            return "".join(s)
        else:
            if arg is not None and arg <= totLength:
                s = random.sample(self.lines, arg)
            else:
                s = random.sample(self.lines, totLength)
            return "".join(s)

def chooseArgs(inputArg, arg = None, repeat = False):
    totLength=len(inputArg)
    if repeat is True:
        s = []
        for i in range(arg):
            s.append(random.choice(inputArg))
        return "".join(map(lambda a:a[0:] + "\n", s))
    else:
        if arg is not None and arg <= totLength:
            s = random.sample(inputArg, arg)
        else:
            s = random.sample(inputArg, totLength)
        return "".join(map(lambda a:a[0:] + "\n", s))
    
def main():
    version_msg = "%prog 1.0"
    usage_msg = """%prog [OPTION]... FILE

Output shuffles lines from FILE."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--head-count",
                      action="store", dest="count",
                      help="output at most COUNT lines")
    parser.add_option("-e", "--echo", action="store_true", dest="echoName", default=False, help="treat each ARG as an input line")
    parser.add_option("-r", "--repeat", action="store_true", dest="repeat", default=False, help="output lines can be repeated")

    options, args = parser.parse_args(sys.argv[1:])

    if options.count is not None:
        try:
            count = int(options.count)
        except:
            parser.error("invalid line count: {0}".
                         format(options.count))
        if count < 0:
            parser.error("negative count: {0}".
                             format(count))
    else:
        count = None

    if options.echoName is False:
        if len(args) > 1:
            parser.error("extra number of operands")
        if len(args) is 0 or args[0] is "-":
            input_file = sys.stdin
        else:
            input_file = args[0]
        try:
            generator = randline(input_file)
            while True:
                sys.stdout.write(generator.chooseline(count, options.repeat))
                if options.repeat is False or options.count is not None:
                    break
        except OSError as err:
            parser.error("OS error: {0}".
                     format(err))
    elif options.repeat is True and (len(args) is 0 or args[0] is "-"):
        parser.error("segmentation error")
    else:
        while True:
            sys.stdout.write(chooseArgs(args, count, options.repeat))
            if options.repeat is False or options.count is not None:
                break
    

if __name__ == "__main__":
    main()
