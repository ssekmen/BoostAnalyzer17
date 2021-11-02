import random as rd
import sys
import datetime

random     = False # True: vary sigma randomly, False: generate a line both for up and down for each systematic
#nsyst      = 11+69 # Number of gaussians to generate (11 sigma for syst, 69 sigma for SF)
nsyst      = 11+0  # Number of gaussians to generate (11 sigma for syst, 69 sigma for SF)
nline      = 500 if random else nsyst*2
scale_vars = [3]   # 1: factorization, 2: renormalization, 3: both simultaneously
nmax_pdf   = 0     # Number of pdfs to consider (0 currently)

def generate_line(iline, random):
    sysline = ""
    if random:
        # Here we generate one line in the systematics file
        # it consists of n gaussians, and then a uniform number for the pdfs
        for i in range(nsyst):
            number = rd.gauss(0,1)
            sysline = sysline + ("%+.3f" % number).replace("+"," ") + " "
        
        # randrange returns integers
        scalenumber = scale_vars[rd.randrange(0,len(scale_vars))]
        sysline = sysline + str(scalenumber)
        if nmax_pdf>0:
            pdfnumber   = rd.randrange(1,nmax_pdf+1)
            sysline = sysline + " " + str(pdfnumber)        
    else:
        # Generate a single systematic up/down line
        for i in range(nsyst):
            if iline/2 == i:
                number = 1 if iline%2==0 else -1
            else:
                number = 0
            sysline = sysline + ("%+.1f" % number).replace("+"," ") + " "
        
        # last-1 number is the scale variation that is considered (specify only one if not using random)
        scalenumber = scale_vars[0]
        sysline = sysline + str(scalenumber)
        
        # last number is the pdf variation (not supported currently)
        pdfnumber = 0
        sysline = sysline + " " + str(pdfnumber)
    
    return sysline

if __name__ == "__main__":
    
    #if len(sys.argv) < 2:
    #    print "Usage: python %s nsyst" % (sys.argv[0])
    #    exit()
    #nsyst = int(sys.argv[1])
    today = datetime.date.today()
    fname = "systematics/%s.txt" % (str(today).replace("-","_"))
    
    systfile = open(fname,'w')
    
    for i in range(nline):
        l = generate_line(i, random)
        systfile.write(l+"\n")
    
    systfile.close()
