lines_per_file = 5e6
smallfile = None
with open('./data/enwiki-2013.txt') as bigfile:
    for lineno, line in enumerate(bigfile):
        if lineno % lines_per_file == 0:
            if smallfile:
                smallfile.close()
            small_filename = './data/enwiki-2013-{}.txt'.format(int((lineno + lines_per_file)/lines_per_file))
            smallfile = open(small_filename, "w")
        smallfile.write(line)
    if smallfile:
        smallfile.close()