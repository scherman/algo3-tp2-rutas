
import sys
import numpy as np
import time
import subprocess
from subprocess import call

import os
from os import listdir
from os.path import isfile, join



if __name__ == "__main__":

	programa = sys.argv[1]
	carpeta_test = sys.argv[2]
	carpeta_dest = sys.argv[3]
	cantRepes = int(sys.argv[4])
	FNULL = open(os.devnull, 'w')

	print "programa: " + str(programa)
	print "carpeta_test: " + str(carpeta_test)
	print "carpeta_dest: " + str(carpeta_dest)
	print "cantidad repes:" + str(cantRepes)

	tiempos = []

	archivos = sorted([f for f in listdir(carpeta_test) if isfile(join(carpeta_test, f))])
	for f_test in archivos:

		tiempos_parciales = []
		sys.stdout.write("{0}.. ".format("Corriendo input " + f_test + ": "))
		sys.stdout.flush()

		for x in range(0, cantRepes):
			sys.stdout.write("{0}.. ".format(str(x+1)))
			sys.stdout.flush()
			start = time.time()	
			call([programa, (carpeta_test + "/" + f_test)], stdout=FNULL, stderr=subprocess.STDOUT)
			elapsed = (time.time() - start)
			tiempos_parciales.append(elapsed)


		tiempos.append(np.median(tiempos_parciales))
		sys.stdout.write("\n")
		sys.stdout.flush()
