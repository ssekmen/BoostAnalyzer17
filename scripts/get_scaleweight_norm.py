import ROOT, os, sys, glob

#unskimmed_ntuple = "ntuple/grid18_data_6tb/Nov30_part1/"
#unskimmed_ntuple = "ntuple/grid18_data/Nov30_part1/"
unskimmed_ntuple = "ntuple/grid18_data_6tb/Nov30_part3/"


done = []
for subdir in os.listdir(unskimmed_ntuple):
    if not "Run2016" in subdir and os.path.isdir(unskimmed_ntuple+subdir):
        if subdir.endswith('_recovery'): subdir = subdir[:-9]
        if subdir.endswith('_2'):      subdir = subdir[:-2]
        if subdir.endswith('_ext1'):   subdir = subdir[:-5]
        if subdir.endswith('_ext2'):   subdir = subdir[:-5]
        if subdir.endswith('_ext3'):   subdir = subdir[:-5]
        if subdir.endswith('_ext4'):   subdir = subdir[:-5]
        if subdir.endswith('_backup'): subdir = subdir[:-7]
        if not (subdir in done):
            c = ROOT.TChain("c")
            files = glob.glob(unskimmed_ntuple+subdir+"*/*.root")
            if len(files):
                for f in files: c.Add(f+"/B2GTTreeMaker/B2GTree")
                nom   = ROOT.TH1D(subdir+"_nom",           "",1,0,1)
                f_dn  = ROOT.TH1D(subdir+"_facscale_dn",   "",1,0,1)
                f_up  = ROOT.TH1D(subdir+"_facscale_up",   "",1,0,1)
                r_dn  = ROOT.TH1D(subdir+"_renscale_dn",   "",1,0,1)
                fr_dn = ROOT.TH1D(subdir+"_facrenscale_dn","",1,0,1)
                r_up  = ROOT.TH1D(subdir+"_renscale_up",   "",1,0,1)
                fr_up = ROOT.TH1D(subdir+"_facrenscale_up","",1,0,1)
                c.Draw("0>>"+subdir+"_nom",           "1")
                c.Draw("0>>"+subdir+"_facscale_dn",   "scale_Weights[0]")
                c.Draw("0>>"+subdir+"_facscale_up",   "scale_Weights[1]")
                c.Draw("0>>"+subdir+"_renscale_dn",   "scale_Weights[2]")
                c.Draw("0>>"+subdir+"_facrenscale_dn","scale_Weights[3]")
                c.Draw("0>>"+subdir+"_renscale_up",   "scale_Weights[4]")
                c.Draw("0>>"+subdir+"_facrenscale_up","scale_Weights[5]")
                print ("%4.3f  %4.3f  %4.3f  %4.3f  %4.3f  %4.3f  %s" % (
                    f_dn.Integral()/nom.Integral(),
                    f_up.Integral()/nom.Integral(),
                    r_dn.Integral()/nom.Integral(),
                    fr_dn.Integral()/nom.Integral(),
                    r_up.Integral()/nom.Integral(),
                    fr_up.Integral()/nom.Integral(),
                    subdir))
                sys.stdout.flush()
            done.append(subdir)
